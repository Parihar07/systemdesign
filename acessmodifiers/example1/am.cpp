#include<iostream>
#include"box.h". // here we are exposing means visibile to compiler
using namespace std;

int main(){
    cout << "hello access modifier..\n";
    Box box;
    box.getlength(); // this is accessible
    //box.len = 6; //not access and error

    return 0;
}