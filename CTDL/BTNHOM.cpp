#include <iostream>
#include <string>
#include <iomanip> 

using namespace std;


struct SinhVien {
    int maSV;
    string hoTen;
    float diem;
};


struct Node {
    SinhVien data; 
    Node* next;    
};


Node* createNode(int maSV, string hoTen, float diem) {
    Node* newNode = new Node(); 
    newNode->data.maSV = maSV;
    newNode->data.hoTen = hoTen;
    newNode->data.diem = diem;
    newNode->next = NULL;       
    return newNode;
}


void addStudent(Node*& head, int maSV, string hoTen, float diem) {
    Node* newNode = createNode(maSV, hoTen, diem);
    

    if (head == NULL) {
        head = newNode;
        return;
    }
    

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    

    temp->next = newNode;
}



void printList(Node* head) {
    if (head == NULL) {
        cout << "-> Danh sach sinh vien dang trong!" << endl;
        return;
    }

    // V? vi?n trên cùng c?a b?ng
    cout << "+" << string(12, '-') << "+" << string(32, '-') << "+" << string(12, '-') << "+" << endl;
    
    // In dòng Tiêu d?
    cout << "|" << left << setw(12) << " Ma SV" 
         << "|" << setw(32) << " Ho va Ten" 
         << "|" << setw(12) << " Diem" << "|" << endl;
         
    // V? vi?n ngan cách gi?a Tiêu d? và D? li?u
    cout << "+" << string(12, '-') << "+" << string(32, '-') << "+" << string(12, '-') << "+" << endl;

    // Duy?t qua t?ng node d? in thông tin sinh viên
    Node* temp = head;
    while (temp != NULL) {
        // Luu ý: Thêm 1 kho?ng tr?ng " " ? d?u m?i c?t d? ch? không b? dính sát vào du?ng k? vi?n
        cout << "|" << " " << left << setw(11) << temp->data.maSV
             << "|" << " " << setw(31) << temp->data.hoTen
             << "|" << " " << setw(11) << fixed << setprecision(2) << temp->data.diem << "|" << endl;
        temp = temp->next; // Chuy?n sang node ti?p theo
    }
    
    // V? vi?n du?i cùng ch?t l?i b?ng
    cout << "+" << string(12, '-') << "+" << string(32, '-') << "+" << string(12, '-') << "+" << endl;
}
int main() {
    
    Node* head = NULL; 

    // --- THÊM S?N CÁC SINH VIÊN M?U ---
    addStudent(head, 101, "Nguyen Van A", 8.5);
    addStudent(head, 102, "Tran Thi B", 9.0);
    addStudent(head, 103, "Le Van C", 7.25);

    int choice;
    do {
        cout << "\n=== CHUONG TRINH QUAN LY SINH VIEN ===" << endl;
        cout << "1. Them sinh vien moi" << endl;
        cout << "2. In danh sach sinh vien" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int maSV;
                string hoTen;
                float diem;

                cout << "\n--- THEM SINH VIEN ---" << endl;
                cout << "Nhap Ma SV (So nguyen): ";
                cin >> maSV;
                
                // L?nh cin.ignore() c?c k? quan tr?ng d? xóa ký t? '\n' 
                // còn sót l?i trong b? nh? d?m tru?c khi nh?p chu?i b?ng getline
                cin.ignore(); 
                
                cout << "Nhap Ho va Ten: ";
                getline(cin, hoTen);
                
                cout << "Nhap Diem (So thuc): ";
                cin >> diem;

                addStudent(head, maSV, hoTen, diem);
                cout << "-> Da them sinh vien vao danh sach thanh cong!" << endl;
                break;
            }
            case 2: {
                cout << "\n--- DANH SACH SINH VIEN HIEN TAI ---" << endl;
                printList(head);
                break;
            }
            case 0:
                cout << "Dang thoat chuong trinh. Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
        }
    } while (choice != 0);

    // Gi?i phóng b? nh? tru?c khi k?t thúc chuong trình d? tránh rò r? b? nh? (Memory Leak)
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
