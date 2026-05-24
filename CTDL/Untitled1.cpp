#include<iostream>
using namespace std;

//1. xau dung cau truc mot node

struct Node{
	int data;
	Node *pNext;
};

//2. xay dung cau truc cua 1 danh sach lien ket don
struct singleList{
	Node *pHead;
};
//3. Ham khoi tao
void initialize(singleList &L){
	L.pHead = NULL;
};
//4. Ham tao node
Node *createNode(int d){
	Node *p = new Node;
	p->data = d;
	p->pNext = NULL;
	return p;
}

//5. chen dau danh sach
void insertFirst(singleList &L, int d){
	Node *p = createNode(d);
	if(L.pHead==NULL){
		L.pHead = p;
	}
	else{
		p->pNext =L.pHead;
		L.pHead =p;
	}
};

//6. in danh sach
void printList(singleList L){
	Node *p=L.pHead;
	if(L.pHead==NULL){
		cout<<"DS rong";
	}
	else{
		while(p!=NULL){
			cout<<p->data<<"\t";
			p = p->pNext;
		}
	}
};

//7. Them vao cuoi
void insertLast(singleList &L, int d){
	Node *p = createNode(d);
	if(L.pHead==NULL){
		L.pHead = p;
	}
	else{
		Node *p1 = L.pHead;
		while(p1->pNext !=NULL){
			p1=p1->pNext;
		}
		p1->pNext =p;
	}
}

//8. Dem so phan tu cua danh sach
int sizeOfList(singleList L){
	int d = 0;
	Node *p =L.pHead;
	while(p!=NULL){
		d++;
		p = p->pNext;
	}
	return d;
}

//9. chen vao giua
void insertMid(singleList &L, int pos, int d){
	if(pos<0||pos>=sizeOfList(L)){
		cout<<"Vi tri chen khong hop le";
	}
	else if(pos ==0){
		insertFirst(L,d);
	}
	else if(pos ==sizeOfList(L)-1){
		insertLast(L,d);
	}
	else{
		Node *p = createNode(d);
		Node *pIns = L.pHead;
		Node *pPre = NULL;
		int i =0;
		while(pIns !=NULL){
			if(i==pos)
			break;
			pPre = pIns;
			pIns = pIns->pNext;
			i++;
		}
		pPre->pNext = p;
		p->pNext =pIns;
	}
}

int main(){
	singleList L;
	initialize(L);
	insertFirst(L,2);
	insertFirst(L,5);
	insertFirst(L,8);
	insertFirst(L,9);
	insertFirst(L,4);
	insertLast(L,22);
	insertMid(L,3,7);
	printList(L);
	cout<<"\n so pt cua ds la:"<<sizeOfList(L);
}
