#include<iostream>
using namespace std;

class Base
{
    protected:
        int x = 42;
        void protectedMethod() {};
};

class Derived : public Base{
    public:
    void test1(){
        x = 40;
        this->x = 30;
    }
};
class Base
{
protected:
    int x = 10;
};

class Derived : public Base
{
public:
    void test1()
    {
        x = 20;       // ✅ OK: accessing own inherited x
        this->x = 30; // ✅ OK: accessing through 'this'
    }

    void test2(Derived &d)
    {
        d.x = 40; // ✅ OK: d is a Derived object
    }

    void test3(Base &b)
    {
        b.x = 50; // ❌ ERROR: b is a Base reference!
                  // Even though Derived inherits from Base,
                  // you can't access protected through Base&
    }

    void test4(Derived *d)
    {
        d->x = 60; // ✅ OK: d is Derived*
    }

    void test5(Base *b)
    {
        b->x = 70; // ❌ ERROR: b is Base*
    }
};