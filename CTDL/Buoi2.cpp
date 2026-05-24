#include<iostream>
using namespace std;

//================ NODE =================
struct Node{
    int data;
    Node *pNext;
};

//================ LIST =================
struct singleList{
    Node *pHead;
};

//================ BASIC =================
void KhoiTao(singleList &L){
    L.pHead = NULL;
}

Node* createNode(int d){
    Node *p = new Node;
    p->data = d;
    p->pNext = NULL;
    return p;
}

//================ INSERT =================
void insertFirst(singleList &L, int d){
    Node *p = createNode(d);
    p->pNext = L.pHead;
    L.pHead = p;
}

void insertLast(singleList &L, int d){
    Node *p = createNode(d);
    if(L.pHead == NULL){
        L.pHead = p;
    }else{
        Node *cur = L.pHead;
        while(cur->pNext != NULL){
            cur = cur->pNext;
        }
        cur->pNext = p;
    }
}

void insertMid(singleList &L, int pos, int d){
    if(pos < 0){
        cout<<"Vi tri khong hop le\n";
        return;
    }

    if(pos == 0){
        insertFirst(L,d);
        return;
    }

    Node *cur = L.pHead;
    for(int i = 0; i < pos - 1 && cur != NULL; i++){
        cur = cur->pNext;
    }

    if(cur == NULL){
        cout<<"Vi tri khong hop le\n";
        return;
    }

    Node *p = createNode(d);
    p->pNext = cur->pNext;
    cur->pNext = p;
}

//================ SIZE =================
int sizeOfList(singleList L){
    int count = 0;
    Node *p = L.pHead;
    while(p != NULL){
        count++;
        p = p->pNext;
    }
    return count;
}

//================ PRINT =================
void printList(singleList &L){
    Node *p = L.pHead;
    if(p == NULL){
        cout<<"Danh sach rong\n";
        return;
    }
    cout<<"Danh sach: ";
    while(p != NULL){
        cout<<p->data<<" ";
        p = p->pNext;
    }
    cout<<endl;
}

void printAll(singleList &L){
    Node *p = L.pHead;
    if(p == NULL){
        cout<<"Danh sach rong\n";
        return;
    }
    cout<<"Danh sach: ";
    while(p != NULL){
        cout<<p->data<<" ";
        p = p->pNext;
    }
    cout<<endl;
}

//================ DELETE =================
void deleteNode(singleList &L, int x){
    if(L.pHead == NULL){
        cout<<"Danh sach rong\n";
        return;
    }

    Node *p = L.pHead;

    if(p->data == x){
        L.pHead = p->pNext;
        delete p;
        cout<<"Da xoa!\n";
        return;
    }

    Node *prev = NULL;
    while(p != NULL && p->data != x){
        prev = p;
        p = p->pNext;
    }

    if(p == NULL){
        cout<<"Khong tim thay!\n";
        return;
    }

    prev->pNext = p->pNext;
    delete p;
    cout<<"Da xoa!\n";
}

//================ UPDATE =================
void updateNode(singleList &L, int oldVal, int newVal){
    Node *p = L.pHead;
    while(p != NULL){
        if(p->data == oldVal){
            p->data = newVal;
            cout<<"Da sua!\n";
            return;
        }
        p = p->pNext;
    }
    cout<<"Khong tim thay!\n";
}

//================ MAX MIN =================
int findMax(singleList L){
    if(L.pHead == NULL) return -1;
    int max = L.pHead->data;
    Node *p = L.pHead;
    while(p != NULL){
        if(p->data > max) max = p->data;
        p = p->pNext;
    }
    return max;
}

int findMin(singleList L){
    if(L.pHead == NULL) return -1;
    int min = L.pHead->data;
    Node *p = L.pHead;
    while(p != NULL){
        if(p->data < min) min = p->data;
        p = p->pNext;
    }
    return min;
}

//================ SORT =================
void sortDesc(singleList &L){
    for(Node *i = L.pHead; i != NULL; i = i->pNext){
        for(Node *j = i->pNext; j != NULL; j = j->pNext){
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
    cout<<"0. Thoat\n";
    cout<<"==========================\n";
    cout<<"Nhap lua chon: ";
}

//================ MAIN =================
int main(){
    singleList L;
    KhoiTao(L);

    insertFirst(L,2);
    insertFirst(L,5);
    insertFirst(L,4);
    insertFirst(L,8);
    insertFirst(L,9);
    insertLast(L,12);
    insertMid(L,3,15);

    printAll(L);
    cout<<"So phan tu: "<<sizeOfList(L)<<endl;

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
                printAll(L);
                break;
            }

            case 2:{
                int oldVal, newVal;
                cout<<"Nhap gia tri can sua: ";
                cin>>oldVal;
                cout<<"Nhap gia tri moi: ";
                cin>>newVal;
                updateNode(L,oldVal,newVal);
                printAll(L);
                break;
            }

            case 3:{
                int x;
                cout<<"Nhap gia tri can xoa: ";
                cin>>x;
                deleteNode(L,x);
                printAll(L);
                break;
            }

            case 4:{
                int m = findMax(L);
                if(m != -1) cout<<"Max = "<<m<<endl;
                break;
            }

            case 5:{
                int m = findMin(L);
                if(m != -1) cout<<"Min = "<<m<<endl;
                break;
            }

            case 6:{
                sortDesc(L);
                printAll(L);
                break;
            }

            case 7:{
                printAll(L);
                break;
            }

            case 0:
                cout<<"Thoat!\n";
                break;

            default:
cout<<"Lua chon sai!\n";
        }

    }while(choice != 0);

    return 0;
}

