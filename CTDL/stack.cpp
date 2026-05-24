#include<iostream>
using namespace std;

int s[100];
int top = -1;

void Push(int s[100], int x){
    if(top >= 99){
        cout << "Ngan xep day";
    }
    else{
        top++;
        s[top] = x;
    }
}

int Pop(int s[100]){
    if(top == -1){
        cout << "Ngan xep rong";
        return -1;
    }
    else{
        int x = s[top];
        top--;
        return x;
    }
}

int main(){
    int n;

    cout << "n = ";
    cin >> n;
    int temp = n;

    while(temp != 0){
        Push(s, temp % 2);
        temp = temp / 2;
    }
    cout << "Co so 2: ";
    while(top >= 0){
        cout << Pop(s);
    }
    top = -1; 
    temp = n;
    while(temp != 0){
        Push(s, temp % 8);
        temp = temp / 8;
    }

    cout << "\nCo so 8: ";
    while(top >= 0){
        cout << Pop(s);
    }
    top = -1; 
    temp = n;
    while(temp != 0){
        Push(s, temp % 16);
        temp = temp / 16;
    }

    cout << "\nCo so 16: ";
    while(top >= 0){
        int x = Pop(s);
        if(x >= 10){
            cout << char(x - 10 + 'A'); // A-F
        } else {
            cout << x;
        }
    }

    return 0;
}
