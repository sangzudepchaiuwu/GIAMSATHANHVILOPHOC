import os
import cv2
import time
import requests
import mimetypes
import imageio
from flask import Flask, render_template, request, Response, url_for, jsonify, send_file
from ultralytics import YOLO
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'static/uploads/'
os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)

# Đường dẫn mô hình của bạn
model = YOLO(r'D:\THIGIACMAYTINH\classroom_behavior_finetune-20260523T202145Z-3-001\classroom_behavior_finetune\weights\best.pt')

# --- CẤU HÌNH TELEGRAM BOT ---
TELEGRAM_BOT_TOKEN = '8672687128:AAGl3zkIdkR2eXeojH7ESAS1cU1PaNl5LNI'
TELEGRAM_CHAT_ID = '7492055263'

# Hàm gửi tin nhắn Telegram
def send_telegram_alert(message):
    url = f"https://api.telegram.org/bot{TELEGRAM_BOT_TOKEN}/sendMessage"
    payload = {
        'chat_id': TELEGRAM_CHAT_ID,
        'text': message,
        'parse_mode': 'HTML'
    }
    try:
        requests.post(url, json=payload, timeout=5)
    except Exception as e:
        print(f"Lỗi khi gửi Telegram: {e}")

# --- CẤU HÌNH NHÃN VÀ CẢNH BÁO ---
CLASS_MAPPING = {
    0: 'Máy tính', 1: 'Điện thoại', 2: 'Giơ tay', 3: 'Ngủ gật',
    4: 'Quay trái', 5: 'Quay phải', 6: 'Sử dụng máy tính', 
    7: 'Sử dụng điện thoại', 8: 'Đang viết'
}

BEHAVIOR_IDS = [2, 3, 4, 5, 6, 7, 8]

# Các hành vi cần cảnh báo và ngưỡng số lượng
ALERT_CONDITIONS = {
    'Ngủ gật': 3,
    'Sử dụng điện thoại': 3
}

# Thời gian chờ giữa 2 lần cảnh báo (tính bằng giây) để tránh spam
COOLDOWN_TIME = 60 
last_alert_time = {behavior: 0 for behavior in ALERT_CONDITIONS.keys()}

current_stats = {CLASS_MAPPING[i]: 0 for i in BEHAVIOR_IDS}

# Hàm xử lý Camera (Hỗ trợ cả Webcam mặc định và IP Camera)
def gen_frames(camera_source='0'):
    global current_stats, last_alert_time
    
    # Kiểm tra xem người dùng chọn Webcam máy tính (số) hay IP Camera (chuỗi URL)
    if camera_source.isdigit():
        cap = cv2.VideoCapture(int(camera_source))
    else:
        cap = cv2.VideoCapture(camera_source)
        
    while True:
        success, frame = cap.read()
        if not success:
            break
        
        results = model.track(
            frame, conf=0.75, verbose=False, tracker='bytetrack.yaml', persist=True
        )
    
        temp_stats = {CLASS_MAPPING[i]: 0 for i in BEHAVIOR_IDS}
        
        # Đếm số lượng hành vi
        boxes = results[0].boxes
        for box in boxes:
            cls_id = int(box.cls[0]) 
            if cls_id in BEHAVIOR_IDS:
                vn_name = CLASS_MAPPING[cls_id]
                temp_stats[vn_name] += 1
                
        current_stats = temp_stats.copy()
        
        # --- LOGIC KIỂM TRA NGƯỠNG VÀ GỬI TELEGRAM ---
        current_time = time.time()
        for behavior, threshold in ALERT_CONDITIONS.items():
            if current_stats.get(behavior, 0) >= threshold:
                # Kiểm tra xem đã qua thời gian Cooldown chưa
                if current_time - last_alert_time[behavior] > COOLDOWN_TIME:
                    msg = f"⚠️ <b>CẢNH BÁO LỚP HỌC</b> ⚠️\nPhát hiện có <b>{current_stats[behavior]}</b> học sinh đang <b>{behavior.lower()}</b>!"
                    
                    # Gọi hàm gửi tin nhắn
                    send_telegram_alert(msg)
                    
                    # Cập nhật lại thời gian gửi cảnh báo gần nhất
                    last_alert_time[behavior] = current_time
        # ---------------------------------------------
        
        annotated_frame = results[0].plot()
        ret, buffer = cv2.imencode('.jpg', annotated_frame)
        frame = buffer.tobytes()
        
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    camera_source = request.args.get('src', '0')
    return Response(gen_frames(camera_source), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/stats')
def get_stats():
    return jsonify(current_stats)

@app.route('/analyze_video', methods=['POST'])
def analyze_video():
    if 'video' not in request.files:
        return jsonify({'success': False, 'error': 'No video file provided'}), 400
    
    file = request.files['video']
    if file.filename == '':
        return jsonify({'success': False, 'error': 'No file selected'}), 400
    
    if file:
        try:
            filename = secure_filename(file.filename)
            temp_filepath = os.path.join(app.config['UPLOAD_FOLDER'], f'temp_{filename}')
            file.save(temp_filepath)
            
            # Process video
            cap = cv2.VideoCapture(temp_filepath)
            
            if not cap.isOpened():
                os.remove(temp_filepath)
                return jsonify({'success': False, 'error': 'Could not open video file'}), 400
            
            # Get video properties
            fps = int(cap.get(cv2.CAP_PROP_FPS))
            width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
            height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
            
            # Define output video with .mp4 extension
            output_filename = f'analyzed_{int(time.time())}_{filename}'.rsplit('.', 1)[0] + '.mp4'
            output_filepath = os.path.join(app.config['UPLOAD_FOLDER'], output_filename)
            
            # Use imageio for MP4 encoding instead of OpenCV
            video_writer = imageio.get_writer(output_filepath, fps=fps, codec='libx264')
            
            # Statistics for the entire video
            video_stats = {CLASS_MAPPING[i]: 0 for i in BEHAVIOR_IDS}
            
            frame_count = 0
            while True:
                success, frame = cap.read()
                if not success:
                    break
                
                frame_count += 1
                
                # Run inference
                results = model.predict(frame, conf=0.6, verbose=False)
                
                # Count behaviors in this frame
                boxes = results[0].boxes
                for box in boxes:
                    cls_id = int(box.cls[0])
                    if cls_id in BEHAVIOR_IDS:
                        vn_name = CLASS_MAPPING[cls_id]
                        video_stats[vn_name] += 1
                
                # Write annotated frame to output video using imageio
                annotated_frame = results[0].plot()
                # Convert BGR to RGB for imageio
                annotated_frame_rgb = cv2.cvtColor(annotated_frame, cv2.COLOR_BGR2RGB)
                video_writer.append_data(annotated_frame_rgb)
            
            cap.release()
            video_writer.close()
            
            # Clean up temp file
            os.remove(temp_filepath)
            
            return jsonify({
                'success': True,
                'output_video': output_filename,
                'stats': video_stats,
                'frame_count': frame_count
            })
        
        except Exception as e:
            return jsonify({'success': False, 'error': str(e)}), 500

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file:
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        img = cv2.imread(filepath)
        results = model.predict(img, conf=0.5)
        
        annotated_img = results[0].plot()
        result_filename = 'res_' + filename
        result_filepath = os.path.join(app.config['UPLOAD_FOLDER'], result_filename)
        cv2.imwrite(result_filepath, annotated_img)
        
        return render_template('index.html', result_image=result_filename)

@app.route('/get_video/<filename>')
def get_video(filename):
    """Serve video files with correct MIME type"""
    filepath = os.path.join(app.config['UPLOAD_FOLDER'], secure_filename(filename))
    if os.path.exists(filepath):
        return send_file(filepath, mimetype='video/mp4', as_attachment=False)
    else:
        return jsonify({'error': 'File not found'}), 404

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)