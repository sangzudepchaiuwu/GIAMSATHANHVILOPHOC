#include<iostream>
using namespace std;

struct TNode
{
    int value;
    TNode *pLeft;
    TNode *pRight;
};

typedef TNode* BTree;

TNode *createNode(int v)
{
    TNode *node = new TNode;
    node->value = v;
    node->pLeft = node->pRight = NULL;
    return node;
}

void InsertNode(BTree &root, int v)
{
    TNode *node = createNode(v);
    if(root == NULL)
    {
        root = node;
    }
    else
    {
        BTree tmp = root;
        BTree parent = NULL;
        while(tmp != NULL)
        {
            parent = tmp;
            if(tmp->value > node->value)
                tmp = tmp->pLeft;
            else
                tmp = tmp->pRight;
        }
        if(parent->value > node->value)
            parent->pLeft = node;
        else
            parent->pRight = node;
    }
}


void PreOrder_NLR(BTree root){
    if(root != NULL){
        cout << root->value << "\t";
        PreOrder_NLR(root->pLeft);
        PreOrder_NLR(root->pRight);
    }
}


void InOrder_LNR(BTree root){
    if(root != NULL){
        InOrder_LNR(root->pLeft);
        cout << root->value << "\t";
        InOrder_LNR(root->pRight);
    }
}


void PostOrder_LRN(BTree root){
    if(root != NULL){
        PostOrder_LRN(root->pLeft);
        PostOrder_LRN(root->pRight);
        cout << root->value << "\t";
    }
}

int main()
{
    BTree root = NULL;

    InsertNode(root,17);
    InsertNode(root,6);
    InsertNode(root,8);
    InsertNode(root,20);
    InsertNode(root,7);
    InsertNode(root,19);
    InsertNode(root,21);
    InsertNode(root,9);

    cout<<"Duyet truoc: ";
    PreOrder_NLR(root);

    cout<<"\nDuyet sau: ";
    PostOrder_LRN(root);

    cout<<"\nDuyet giua: ";
    InOrder_LNR(root);

    return 0;
}
