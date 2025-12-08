#include<iostream>
using namespace std; 
class Stack{
    private:
    int *data;
    int capacity;
    int top;
    public:
Stack(int size){           //1
    capacity = size;
 data = new int [capacity];
  top = 0 ;


}
~Stack(){                    //2
    delete[] data;
}

void push (int value ){           //3 
    if(top==capacity){
        cout<<"cant enter more data into stack due to space";
        return;
    }
    data[top]=value;
    top++;

}
void display(){          // 4
    for(int i = 0;i < top;i++){
        cout<<data[i];
        cout<<endl;
    }
}

Stack( const Stack&other){       // 5
    top = other.top;
    capacity = other.capacity;
    data = new int [capacity];
    for(int i = 0 ; i<top;i++){
        data[i]= other.data[i];
    }
}
int pop(){                  //6
    if(top==0){
        cout<<"this is empty already";
        return  -1;
    }
    top--;
    return data[top];
    
}
  void topValue(){
  cout<<  data[top-1]; //displays the value at the top of stack
  }
void display_top(){
    cout<<top-1; // displays the amount of stack indices 

}
Stack& operator=(const Stack & other){
    if(this==&other){
        return*this;

    }
top = other.top;
    capacity = other.capacity;
    delete[] data;
        data = new int [capacity];
    for(int i = 0 ; i<top;i++){
        data[i]= other.data[i];
    }
    string reverseWords(const string &str){


    }
    return *this;
}

};
int main(){
    
Stack s1(10);
s1.push(2);
s1.push(3);
s1.push(2);
s1.push(3);
Stack s2(s1);
s1.display();
s2.display();
cout<<s1.pop();


    return 0 ;
}
