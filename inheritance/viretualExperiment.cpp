#include<iostream>
#include<string>
using namespace std;

class Shape_NoVirtual
{
public:
    Shape_NoVirtual()
    {
        cout << "Shape Constructor" << endl;
    }

    ~Shape_NoVirtual()
    { // ❌ NOT virtual!
        cout << "Shape Destructor" << endl;
    }
};

class Circle_NoVirtual : public Shape_NoVirtual
{
private:
    int *data; // Dynamically allocated memory

public:
    Circle_NoVirtual()
    {
        data = new int[100];
        cout << "Circle Constructor (allocated memory)" << endl;
    }

    ~Circle_NoVirtual()
    {
        delete[] data;
        cout << "Circle Destructor (freed memory)" << endl;
    }
};

class Shape_WithVirtual
{
public:
    Shape_WithVirtual()
    {
        cout << "Shape Constructor" << endl;
    }

    virtual ~Shape_WithVirtual()
    { // ✅ Virtual destructor!
        cout << "Shape Destructor" << endl;
    }
};

class Circle_WithVirtual : public Shape_WithVirtual
{
private:
    int *data;

public:
    Circle_WithVirtual()
    {
        data = new int[100];
        cout << "Circle Constructor (allocated memory)" << endl;
    }

    ~Circle_WithVirtual()
    {
        delete[] data;
        cout << "Circle Destructor (freed memory)" << endl;
    }
};

void testVirtualDestructor()
{
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║  VIRTUAL DESTRUCTOR (CRITICAL!)                        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;

    cout << "\n❌ WITHOUT Virtual Destructor:" << endl;
    {
        Shape_NoVirtual *shape = new Circle_NoVirtual();
        delete shape; // ⚠️ Only Shape destructor called! MEMORY LEAK!
    }

    cout << "\n✅ WITH Virtual Destructor:" << endl;
    {
        Shape_WithVirtual *shape = new Circle_WithVirtual();
        delete shape; // ✅ Both destructors called! No leak!
    }

    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║  🔥 GOLDEN RULE:                                       ║" << endl;
    cout << "║  If a class is meant to be inherited,                 ║" << endl;
    cout << "║  ALWAYS make destructor virtual!                      ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
}


int main(){

    testVirtualDestructor();

    Shape_NoVirtual nvShape;
    cout << "---=--=-=------\n";
    Circle_NoVirtual nvCiricle;
    cout << "---=--=-=------\n";
    return 0;
}
