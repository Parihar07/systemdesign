#include<iostream>
#include<string>
using namespace std;

class Base{
    private:
        int val;
    public:
        Base() : val(0) {
            cout << "Defulat Base constructor\n";
        }
        Base(int b): val(b) {
            cout << "Base pararmeterised Constructor\n";
        }
        void show(){
            cout << "Base : " << val << endl;
        }
};

class Derived1 : virtual public Base{
    private:

    public:
    Derived1(int d) : Base(d){
        cout << "Derived1 constructor\n";
    }   
};

class Derived2 : virtual public Base{
    private:
    public:
    Derived2(int d) : Base(d){
        cout << "Dervied2 constructor\n";
    }
};

class FinalDerived : public Derived1, Derived2 {
    private:
    public:
        // With virtual inheritance, FinalDerived MUST initialize Base directly!
        FinalDerived(int f) : Base(f), Derived1(f+100), Derived2(f+200){
            cout << "Final Derived Cnsturctor\n";
        }
};

int main()
{
    cout << "Diaamond problem illustration\n";

    FinalDerived fd(20);
    fd.show();
    return 0;
}