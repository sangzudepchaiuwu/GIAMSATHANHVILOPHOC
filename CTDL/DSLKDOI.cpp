#include<iostream>
using namespace std;

//================ NODE =================
struct Node{
    int data;
    Node *prev;
    Node *next;
};

//================ LIST =================
struct doublyList{
    Node *head;
    Node *tail;
};

//================ BASIC =================
void KhoiTao(doublyList &L){
    L.head = NULL;
    L.tail = NULL;
}

Node* createNode(int d){
    Node *p = new Node;
    p->data = d;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

//================ INSERT =================
void insertFirst(doublyList &L, int d){
    Node *p = createNode(d);
    if(L.head == NULL){
        L.head = L.tail = p;
    }else{
        p->next = L.head;
        L.head->prev = p;
        L.head = p;
    }
}

void insertLast(doublyList &L, int d){
    Node *p = createNode(d);
    if(L.head == NULL){
        L.head = L.tail = p;
    }else{
        p->prev = L.tail;
        L.tail->next = p;
        L.tail = p;
    }
}

void insertMid(doublyList &L, int pos, int d){
    if(pos < 0){
        cout<<"Vi tri khong hop le\n";
        return;
    }

    if(pos == 0){
        insertFirst(L,d);
        return;
    }

    Node *cur = L.head;
    for(int i = 0; i < pos - 1 && cur != NULL; i++){
        cur = cur->next;
    }

    if(cur == NULL){
        cout<<"Vi tri khong hop le\n";
        return;
    }

    if(cur == L.tail){
        insertLast(L,d);
        return;
    }

    Node *p = createNode(d);
    p->next = cur->next;
    p->prev = cur;

    cur->next->prev = p;
    cur->next = p;
}

//================ SIZE =================
int sizeOfList(doublyList L){
    int count = 0;
    Node *p = L.head;
    while(p != NULL){
        count++;
        p = p->next;
    }
    return count;
}

//================ PRINT =================
void printList(doublyList &L){
    Node *p = L.head;
    if(p == NULL){
        cout<<"Danh sach rong\n";
        return;
    }
    cout<<"Danh sach: ";
    while(p != NULL){
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}

// In nguoc (di?m m?nh c?a DLL)
void printReverse(doublyList &L){
    Node *p = L.tail;
    cout<<"Dao nguoc: ";
    while(p != NULL){
        cout<<p->data<<" ";
        p = p->prev;
    }
    cout<<endl;
}

//================ DELETE =================
void deleteNode(doublyList &L, int x){
    if(L.head == NULL){
        cout<<"Danh sach rong\n";
        return;
    }

    Node *p = L.head;

    while(p != NULL && p->data != x){
        p = p->next;
    }

    if(p == NULL){
        cout<<"Khong tim thay!\n";
        return;
    }

    // xoa dau
    if(p == L.head){
        L.head = p->next;
        if(L.head != NULL) L.head->prev = NULL;
        else L.tail = NULL;
    }
    // xoa cuoi
    else if(p == L.tail){
        L.tail = p->prev;
        L.tail->next = NULL;
    }
    // xoa giua
    else{
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    delete p;
    cout<<"Da xoa!\n";
}

//================ UPDATE =================
void updateNode(doublyList &L, int oldVal, int newVal){
    Node *p = L.head;
    while(p != NULL){
        if(p->data == oldVal){
            p->data = newVal;
            cout<<"Da sua!\n";
            return;
        }
        p = p->next;
    }
    cout<<"Khong tim thay!\n";
}

//================ MAX MIN =================
int findMax(doublyList L){
    if(L.head == NULL) return -1;
    int max = L.head->data;
    Node *p = L.head;
    while(p != NULL){
        if(p->data > max) max = p->data;
        p = p->next;
    }
    return max;
}

int findMin(doublyList L){
    if(L.head == NULL) return -1;
    int min = L.head->data;
    Node *p = L.head;
    while(p != NULL){
        if(p->data < min) min = p->data;
        p = p->next;
    }
    return min;
}

//================ SORT =================
void sortDesc(doublyList &L){
    for(Node *i = L.head; i != NULL; i = i->next){
        for(Node *j = i->next; j != NULL; j = j->next){
            if(i->data < j->data){
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    cout<<"Da sap xep!\n";
}

//================ MENU =================
void menu(){
    cout<<"\n========== MENU ==========\n";
    cout<<"1. Them phan tu\n";
    cout<<"2. Sua phan tu\n";
    cout<<"3. Xoa phan tu\n";
    cout<<"4. Tim MAX\n";
    cout<<"5. Tim MIN\n";
    cout<<"6. Sap xep giam dan\n";
    cout<<"7. In danh sach\n";
    cout<<"8. In nguoc\n";
    cout<<"0. Thoat\n";
    cout<<"==========================\n";
    cout<<"Nhap lua chon: ";
}

//================ MAIN =================
int main(){
    doublyList L;
    KhoiTao(L);

    insertFirst(L,2);
    insertFirst(L,5);
    insertFirst(L,4);
    insertFirst(L,8);
    insertFirst(L,9);
    insertLast(L,12);
    insertMid(L,3,15);

    printList(L);

    int choice;

    do{
        menu();
        cin>>choice;

        switch(choice){
            case 1:{
                int x;
                cout<<"Nhap gia tri: ";
                cin>>x;
                insertLast(L,x);
                printList(L);
                break;
            }

            case 2:{
                int oldVal, newVal;
                cin>>oldVal>>newVal;
                updateNode(L,oldVal,newVal);
                break;
            }

            case 3:{
                int x;
                cin>>x;
                deleteNode(L,x);
                break;
            }

            case 4:
                cout<<"Max = "<<findMax(L)<<endl;
                break;

            case 5:
                cout<<"Min = "<<findMin(L)<<endl;
                break;

            case 6:
                sortDesc(L);
                break;

            case 7:
                printList(L);
                break;

            case 8:
                printReverse(L);
                break;

        }

    }while(choice != 0);

    return 0;
}
