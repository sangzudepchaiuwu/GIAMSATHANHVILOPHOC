#include <iostream>
#include <string>
using namespace std;

// ================== STRUCT ==================
struct Hotel {
    int id;             // Mã khách s?n
    string name;        // Tên
    int stars;          // S? sao
    string address;     // Ð?a ch?
    double revenue;     // Doanh thu
};

struct Node {
    Hotel data;
    Node* left;
    Node* right;
};

typedef Node* Tree;

// ================== T?O NODE ==================
Node* createNode(Hotel h) {
    Node* p = new Node;
    p->data = h;
    p->left = p->right = NULL;
    return p;
}

// ================== INSERT ==================
void insertNode(Tree &root, Hotel h) {
    if (root == NULL) {
        root = createNode(h);
        return;
    }

    if (h.id < root->data.id)
        insertNode(root->left, h);
    else if (h.id > root->data.id)
        insertNode(root->right, h);
    else
        cout << "Ma khach san da ton tai!\n";
}

// ================== HI?N TH? 1 KHÁCH S?N ==================
void showHotel(Hotel h) {
    cout << "ID: " << h.id << endl;
    cout << "Ten: " << h.name << endl;
    cout << "So sao: " << h.stars << endl;
    cout << "Dia chi: " << h.address << endl;
    cout << "Doanh thu: " << h.revenue << endl;
    cout << "----------------------\n";
}

// ================== DUY?T CÂY (LNR) ==================
void inOrder(Tree root) {
    if (root == NULL) return;

    inOrder(root->left);
    showHotel(root->data);
    inOrder(root->right);
}

// ================== TÌM KI?M ==================
Node* search(Tree root, int id) {
    if (root == NULL || root->data.id == id)
        return root;

    if (id < root->data.id)
        return search(root->left, id);
    else
        return search(root->right, id);
}

// ================== NH?P ==================
Hotel inputHotel() {
    Hotel h;
    cout << "Nhap ma: ";
    cin >> h.id;
    cin.ignore(1000, '\n');

    cout << "Nhap ten: ";
    getline(cin, h.name);

    cout << "Nhap so sao: ";
    cin >> h.stars;
    cin.ignore(1000, '\n');

    cout << "Nhap dia chi: ";
    getline(cin, h.address);

    cout << "Nhap doanh thu: ";
    cin >> h.revenue;

    return h;
}

// ================== MAIN ==================
int main() {
    Tree root = NULL;
    int choice;

    do {
        cout << "\n===== MENU =====";
        cout << "\n1. Them khach san";
        cout << "\n2. Hien thi danh sach";
        cout << "\n3. Tim theo ma";
        cout << "\n0. Thoat";
        cout << "\nChon: ";
        cin >> choice;

        if (choice == 1) {
            Hotel h = inputHotel();
            insertNode(root, h);
        }
        else if (choice == 2) {
            if (root == NULL)
                cout << "Danh sach rong!\n";
            else
                inOrder(root);
        }
        else if (choice == 3) {
            int id;
            cout << "Nhap ma can tim: ";
            cin >> id;

            Node* result = search(root, id);
            if (result != NULL)
                showHotel(result->data);
            else
                cout << "Khong tim thay!\n";
        }

    } while (choice != 0);

    return 0;
}
