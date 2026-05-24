<h1 align="center">CLASSROOM BEHAVIOR MONITORING SYSTEM
HỆ THỐNG GIÁM SÁT HÀNH VI LỚP HỌC</h1>


<div align="center">
<p align="center">
  <img src="static/logoDaiNam.png" alt="DaiNam University Logo" width="200"/>
  <img src="static/LogoAIoTLab.png" alt="AIoTLab Logo" width="170"/>
</p>

[![Made by AIoTLab](https://img.shields.io/badge/Made%20by%20AIoTLab-blue?style=for-the-badge)](https://www.facebook.com/DNUAIoTLab)
[![Fit DNU](https://img.shields.io/badge/Fit%20DNU-green?style=for-the-badge)](https://fitdnu.net/)
[![DaiNam University](https://img.shields.io/badge/DaiNam%20University-red?style=for-the-badge)](https://dainam.edu.vn)

[![Made with Flask](https://img.shields.io/badge/Made%20with-Flask-blue?style=for-the-badge)](https://flask.palletsprojects.com/)
[![YOLOv8](https://img.shields.io/badge/YOLOv8-Computer%20Vision-green?style=for-the-badge)](https://github.com/ultralytics/ultralytics)
[![Python](https://img.shields.io/badge/Python-3.8+-yellow?style=for-the-badge)](https://www.python.org/)
[![Telegram Bot](https://img.shields.io/badge/Telegram-Bot%20API-0088cc?style=for-the-badge)](https://telegram.org/blog/bot-revolution)

</div>

---

## 🌟 Giới thiệu

**Classroom Behavior Monitoring System** là một hệ thống thông minh sử dụng **Thị giác Máy tính (Computer Vision)** và **AI (YOLOv8)** để giám sát và phân tích hành vi học sinh trong lớp học theo thời gian thực.

Hệ thống tự động phát hiện các hành vi bất thường (ngủ gật, sử dụng điện thoại, v.v.) và gửi cảnh báo tức thì tới **Telegram Bot** để giáo viên hoặc quản lý lớp có thể xử lý kịp thời.

<img src="https://via.placeholder.com/800x400?text=Classroom+Monitoring+Dashboard" alt="Dashboard" width="100%"/>

---

## 🚀 Tính Năng Chính

### 📊 **Giám sát Hành vi Thực tế**
- **Phát hiện 9 hành vi học sinh:**
  - 👋 Giơ tay
  - 😴 Ngủ gật
  - ⬅️ Quay trái
  - ➡️ Quay phải
  - 💻 Sử dụng máy tính
  - 📱 Sử dụng điện thoại
  - ✍️ Đang viết
  - 🖥️ Máy tính
  - 📞 Điện thoại

### ⚠️ **Hệ Thống Cảnh báo Thông Minh**
- **Tự động gửi Telegram Alert** khi:
  - Phát hiện ≥ 3 học sinh ngủ gật
  - Phát hiện ≥ 3 học sinh sử dụng điện thoại
- **Cooldown cảnh báo** (60 giây) để tránh spam
- **Thông báo chi tiết** với số lượng học sinh bất thường

### 📹 **Phân Tích Video**
- Upload video lớp học để phân tích
- Tự động nhận diện hành vi trên từng frame
- Xuất video đã phân tích với annotation
- Thống kê tổng hợp hành vi cho toàn video

### 🎥 **Hỗ Trợ Nhiều Nguồn Camera**
- **Webcam máy tính** (mặc định)
- **IP Camera** (camera an ninh, điện thoại qua ứng dụng)
- **Live stream** với feed thực tế

### 📈 **Dashboard Thống Kê**
- Hiển thị số lượng hành vi theo thời gian thực
- Cập nhật stats mỗi 500ms
- Giao diện thân thiện người dùng

---

## 📁 Cấu Trúc Dự Án

```
CLASSROOM-BEHAVIOR-MONITORING/
│
├── app.py                      # 🔧 File chính (Flask server + YOLO inference)
├── requirements.txt            # 📦 Thư viện cần thiết
├── README.md                   # 📖 Tài liệu này
│
├── templates/
│   └── index.html             # 🌐 Frontend HTML
│
├── static/
│   └── uploads/               # 📹 Thư mục lưu trữ video phân tích
│       ├── analyzed_*.mp4     # Video đã phân tích
│       ├── res_*.jpg          # Ảnh đã phân tích
│       └── ...
│
├── classroom_behavior_finetune-20260523T202145Z-3-001/
│   └── classroom_behavior_finetune/
│       ├── args.yaml          # 🎯 Cấu hình training YOLO
│       ├── results.csv        # 📊 Kết quả training
│       └── weights/
│           ├── best.pt        # ⭐ Model YOLO tốt nhất (đang dùng)
│           └── last.pt        # Model checkpoint cuối cùng
│
├── Test/                      # 🧪 Thư mục test dataset
│   ├── T-Student_FIT-DNU.v1i.yolov8/
│   └── T-Student_FIT-DNU.v2i.yolov11/
│
└── venv/                      # 🐍 Python Virtual Environment
```

---

## ⚙️ Công Nghệ Sử Dụng

| Công nghệ | Mục đích |
|-----------|---------|
| **Python 3.8+** | Ngôn ngữ lập trình chính |
| **Flask** | Web framework cho API & dashboard |
| **YOLOv8** | Mô hình AI phát hiện hành vi học sinh |
| **OpenCV** | Xử lý video & camera |
| **Telegram Bot API** | Gửi cảnh báo tức thì |
| **imageio-ffmpeg** | Encoding video MP4 |
| **NumPy** | Xử lý dữ liệu toán học |

---

## 🖥️ Cài Đặt & Chạy Chương Trình

### 1️⃣ **Clone Repository**
```bash
git clone <repo-url>
cd classroom-behavior-monitoring
```

### 2️⃣ **Tạo Virtual Environment**
```bash
# Windows
python -m venv venv
venv\Scripts\activate

# Linux / MacOS
python3 -m venv venv
source venv/bin/activate
```

### 3️⃣ **Cài Thư Viện**
```bash
pip install -r requirements.txt
```

### 4️⃣ **Cấu Hình Telegram Bot (Tùy chọn)**
Mở `app.py` và thay đổi:
```python
TELEGRAM_BOT_TOKEN = 'YOUR_BOT_TOKEN'
TELEGRAM_CHAT_ID = 'YOUR_CHAT_ID'
```

**Cách lấy Telegram credentials:**
- Tạo bot với [@BotFather](https://t.me/botfather)
- Lấy Chat ID từ [@userinfobot](https://t.me/userinfobot)

### 5️⃣ **Chạy Ứng Dụng**
```bash
python app.py
```

**Truy cập:** `http://localhost:5000`

---

## 📖 Hướng Dẫn Sử Dụng

### 🎥 **Sử dụng Camera Trực Tiếp**
1. Nhấn nút **"Sử dụng Camera"**
2. Chọn loại camera:
   - ✅ Webcam máy tính (mặc định)
   - 🔗 IP Camera (nhập URL)
3. Nhấn **"Bắt đầu xem Camera"**
4. Xem feed thực tế + thống kê hành vi

### 📹 **Phân Tích Video**
1. Nhấn nút **"Phân Tích Video"**
2. Chọn file video (.mp4, .avi, v.v.)
3. Nhấn **"Phân Tích Video"**
4. Chờ xử lý (thời gian tùy độ dài video)
5. Xem video đã phân tích + thống kê chi tiết

### 📷 **Phân Tích Ảnh**
1. Nhấn nút **"Tải Ảnh Lên"**
2. Chọn file ảnh (.jpg, .png)
3. Xem kết quả nhận diện hành vi

---

## 🔧 Cấu Hình Model YOLO

Model hiện tại sử dụng: **YOLOv8** fine-tuned trên dataset lớp học.

Để sử dụng model khác:
```python
# app.py - dòng 14
model = YOLO(r'đường_dẫn_tới_model.pt')
```

### Fine-tune Model của Riêng Bạn
```bash
from ultralytics import YOLO

model = YOLO('yolov8n.pt')
results = model.train(
    data='data.yaml',
    epochs=100,
    imgsz=640,
    device=0  # GPU ID
)
```

---

## 📊 API Endpoints

| Endpoint | Phương thức | Mục đích |
|----------|-----------|---------|
| `/` | GET | Trang chính (Dashboard) |
| `/video_feed` | GET | Truyền luồng camera live |
| `/stats` | GET | Lấy thống kê hành vi hiện tại |
| `/analyze_video` | POST | Phân tích video upload |
| `/upload` | POST | Phân tích ảnh upload |
| `/get_video/<filename>` | GET | Serve video đã phân tích |

### Ví dụ Request

**Phân tích video:**
```bash
curl -X POST -F "video=@video.mp4" http://localhost:5000/analyze_video
```

**Response:**
```json
{
  "success": true,
  "output_video": "analyzed_1234567890_video.mp4",
  "stats": {
    "Giơ tay": 5,
    "Ngủ gật": 2,
    "Sử dụng điện thoại": 3
  },
  "frame_count": 1500
}
```

---

## ⚡ Tối Ưu Hiệu Năng

### 🖥️ Sử dụng GPU
```bash
# Cài CUDA (nếu có NVIDIA GPU)
pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118

# Model sẽ tự dùng GPU nếu available
```

### 🎯 Điều chỉnh Confidence Score
```python
# app.py - dòng 62, 72
results = model.track(frame, conf=0.75, ...)  # Tăng conf = ít phát hiện sai
```

### 📹 Giảm Kích Thước Video
```python
# Resize frame trước inference
frame = cv2.resize(frame, (640, 480))
```

---


<div align="center">

**⭐ Nếu dự án hữu ích, hãy cho một ⭐ star!**

</div>
