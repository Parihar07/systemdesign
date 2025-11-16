#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * PART 6: VIRTUAL FUNCTIONS & POLYMORPHISM
 * =========================================
 * Deep dive into virtual functions and runtime polmorphism:
 * - What is polymorphism?
 * - How virtual functions work (vtable/vptr)
 * - Pure virtual functions
 * - Abstract classes
 * - Runtime vs Compile-time polymorphism
 */

// ============================================================================
// EXAMPLE 1: What is Polymorphism?
// ============================================================================

class Shape {
public:
    virtual void draw() {
        cout << "Drawing Shape" << endl;
    }
    
    virtual double area() {
        return 0.0;
    }
    
    virtual ~Shape() { }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) { }
    
    void draw() override {
        cout << "Drawing Circle with radius " << radius << endl;
    }
    
    double area() override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) { }
    
    void draw() override {
        cout << "Drawing Rectangle " << width << "x" << height << endl;
    }
    
    double area() override {
        return width * height;
    }
};

void testPolymorphism() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  WHAT IS POLYMORPHISM?                 ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    // One interface, multiple implementations!
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5.0));
    shapes.push_back(new Rectangle(4.0, 6.0));
    shapes.push_back(new Circle(3.0));
    
    cout << "\nDrawing all shapes polymorphically:" << endl;
    for (Shape* shape : shapes) {
        shape->draw();  // ✅ Calls correct version based on actual type!
        cout << "Area: " << shape->area() << endl;
    }
    
    // Cleanup
    for (Shape* shape : shapes) {
        delete shape;
    }
    
    cout << "\n📝 Polymorphism: 'Many forms' - one interface, multiple implementations" << endl;
}

// ============================================================================
// EXAMPLE 2: Pure Virtual Functions & Abstract Classes
// ============================================================================

class Animal {
public:
    // Pure virtual function (= 0 makes it pure virtual)
    virtual void sound() = 0;
    
    // Regular virtual function
    virtual void eat() {
        cout << "Animal is eating" << endl;
    }
    
    // Virtual destructor (always in abstract classes!)
    virtual ~Animal() { }
};

class Dog : public Animal {
public:
    void sound() override {  // MUST implement pure virtual
        cout << "Woof!" << endl;
    }
    
    void eat() override {
        cout << "Dog is eating bones" << endl;
    }
};

class Cat : public Animal {
public:
    void sound() override {  // MUST implement pure virtual
        cout << "Meow!" << endl;
    }
    
    // eat() not overridden, uses Animal's version
};

void testAbstractClasses() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  PURE VIRTUAL FUNCTIONS & ABSTRACT CLASSES         ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    // Animal a;  // ❌ ERROR! Cannot instantiate abstract class
    
    Animal* animals[2];
    animals[0] = new Dog();
    animals[1] = new Cat();
    
    cout << "\nCalling polymorphic functions:" << endl;
    for (int i = 0; i < 2; i++) {
        animals[i]->sound();
        animals[i]->eat();
        cout << "---" << endl;
    }
    
    delete animals[0];
    delete animals[1];
    
    cout << "\n📝 Pure virtual (= 0) makes class abstract" << endl;
    cout << "   Derived classes MUST implement pure virtual functions" << endl;
}

// ============================================================================
// EXAMPLE 3: How Virtual Functions Work (vtable/vptr)
// ============================================================================

class Base {
public:
    virtual void func1() { cout << "Base::func1()" << endl; }
    virtual void func2() { cout << "Base::func2()" << endl; }
    void func3() { cout << "Base::func3()" << endl; }  // NOT virtual
    
    virtual ~Base() { }
};

class Derived : public Base {
public:
    void func1() override { cout << "Derived::func1()" << endl; }
    void func2() override { cout << "Derived::func2()" << endl; }
    void func3() { cout << "Derived::func3()" << endl; }
};

void testVtableMechanism() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  HOW VIRTUAL FUNCTIONS WORK (vtable/vptr)         ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nSize comparison:" << endl;
    cout << "sizeof(int) = " << sizeof(int) << " bytes" << endl;
    
    class NoVirtual {
        int x;
    };
    cout << "sizeof(NoVirtual) = " << sizeof(NoVirtual) << " bytes" << endl;
    
    class WithVirtual {
        int x;
        virtual void func() { }
    };
    cout << "sizeof(WithVirtual) = " << sizeof(WithVirtual) << " bytes" << endl;
    cout << "   (Extra " << sizeof(WithVirtual) - sizeof(NoVirtual) 
         << " bytes for vptr!)" << endl;
    
    cout << "\n--- Virtual function calls ---" << endl;
    Base* b = new Derived();
    b->func1();  // ✅ Virtual - calls Derived version
    b->func2();  // ✅ Virtual - calls Derived version
    b->func3();  // ❌ NOT virtual - calls Base version
    delete b;
    
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  INTERNAL MECHANISM:                               ║" << endl;
    cout << "║                                                    ║" << endl;
    cout << "║  Each object with virtual functions has:          ║" << endl;
    cout << "║  • vptr (virtual pointer) - points to vtable      ║" << endl;
    cout << "║                                                    ║" << endl;
    cout << "║  Each class has:                                   ║" << endl;
    cout << "║  • vtable (virtual table) - array of function ptrs║" << endl;
    cout << "║                                                    ║" << endl;
    cout << "║  When calling b->func1():                          ║" << endl;
    cout << "║  1. Follow b's vptr to find vtable                ║" << endl;
    cout << "║  2. Look up func1 in vtable                       ║" << endl;
    cout << "║  3. Call the function pointer found               ║" << endl;
    cout << "║                                                    ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
}

// ============================================================================
// EXAMPLE 4: Runtime vs Compile-time Polymorphism
// ============================================================================

// Compile-time polymorphism (Function Overloading)
class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
    
    double add(double a, double b) {
        return a + b;
    }
    
    int add(int a, int b, int c) {
        return a + b + c;
    }
};

// Runtime polymorphism (Virtual Functions)
class Payment {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~Payment() { }
};

class CreditCard : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing credit card payment: $" << amount << endl;
    }
};

class PayPal : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment: $" << amount << endl;
    }
};

void testPolymorphismTypes() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  RUNTIME vs COMPILE-TIME POLYMORPHISM              ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n--- Compile-time (Function Overloading) ---" << endl;
    Calculator calc;
    cout << "add(2, 3) = " << calc.add(2, 3) << endl;
    cout << "add(2.5, 3.7) = " << calc.add(2.5, 3.7) << endl;
    cout << "add(1, 2, 3) = " << calc.add(1, 2, 3) << endl;
    cout << "Decision made at: COMPILE TIME" << endl;
    
    cout << "\n--- Runtime (Virtual Functions) ---" << endl;
    Payment* payment;
    
    // Decision made at RUNTIME based on user input
    int choice = 1;  // Simulate user choice
    if (choice == 1) {
        payment = new CreditCard();
    } else {
        payment = new PayPal();
    }
    
    payment->processPayment(100.0);
    cout << "Decision made at: RUNTIME" << endl;
    
    delete payment;
    
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  COMPILE-TIME: Function selected during compilation║" << endl;
    cout << "║  RUNTIME: Function selected during execution       ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
}

// ============================================================================
// EXAMPLE 5: Virtual Function Rules & Best Practices
// ============================================================================

class Rules_Base {
public:
    // Rule 1: Virtual destructor if class has virtual functions
    virtual ~Rules_Base() { }
    
    // Rule 2: Pure virtual for interface
    virtual void mustImplement() = 0;
    
    // Rule 3: Virtual with default implementation
    virtual void canOverride() {
        cout << "Default implementation" << endl;
    }
    
    // Rule 4: Non-virtual for fixed behavior
    void dontOverride() {
        cout << "Fixed behavior - don't override" << endl;
    }
    
    // Rule 5: Final prevents further overriding
    virtual void lastLevel() final {
        cout << "Cannot override this in derived classes" << endl;
    }
};

class Rules_Derived : public Rules_Base {
public:
    void mustImplement() override {
        cout << "Implemented in derived" << endl;
    }
    
    void canOverride() override {
        cout << "Overridden in derived" << endl;
    }
    
    // void lastLevel() override { }  // ❌ ERROR! Marked final in base
};

void testVirtualRules() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  VIRTUAL FUNCTION RULES & BEST PRACTICES           ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    Rules_Base* obj = new Rules_Derived();
    obj->mustImplement();
    obj->canOverride();
    obj->dontOverride();
    obj->lastLevel();
    delete obj;
    
    cout << "\n📝 Rules:" << endl;
    cout << "   1. Virtual destructor if class has any virtual function" << endl;
    cout << "   2. Pure virtual (= 0) for interface/abstract behavior" << endl;
    cout << "   3. Virtual with body for optional override" << endl;
    cout << "   4. Non-virtual for fixed behavior" << endl;
    cout << "   5. 'final' keyword prevents further overriding" << endl;
}

// ============================================================================
// EXAMPLE 6: Real-World Example - Plugin System
// ============================================================================

class Plugin {
protected:
    string name;
    
public:
    Plugin(string n) : name(n) { }
    
    virtual void initialize() = 0;
    virtual void execute() = 0;
    virtual void cleanup() = 0;
    
    string getName() { return name; }
    
    virtual ~Plugin() { }
};

class LoggerPlugin : public Plugin {
public:
    LoggerPlugin() : Plugin("Logger") { }
    
    void initialize() override {
        cout << "[" << name << "] Initializing logger..." << endl;
    }
    
    void execute() override {
        cout << "[" << name << "] Logging data..." << endl;
    }
    
    void cleanup() override {
        cout << "[" << name << "] Closing log files..." << endl;
    }
};

class DatabasePlugin : public Plugin {
public:
    DatabasePlugin() : Plugin("Database") { }
    
    void initialize() override {
        cout << "[" << name << "] Connecting to database..." << endl;
    }
    
    void execute() override {
        cout << "[" << name << "] Querying data..." << endl;
    }
    
    void cleanup() override {
        cout << "[" << name << "] Closing connections..." << endl;
    }
};

void testRealWorldExample() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  REAL-WORLD EXAMPLE: PLUGIN SYSTEM                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    vector<Plugin*> plugins;
    plugins.push_back(new LoggerPlugin());
    plugins.push_back(new DatabasePlugin());
    
    cout << "\n--- Loading plugins ---" << endl;
    for (Plugin* plugin : plugins) {
        plugin->initialize();
    }
    
    cout << "\n--- Running plugins ---" << endl;
    for (Plugin* plugin : plugins) {
        plugin->execute();
    }
    
    cout << "\n--- Unloading plugins ---" << endl;
    for (Plugin* plugin : plugins) {
        plugin->cleanup();
        delete plugin;
    }
    
    cout << "\n💡 Polymorphism allows dynamic plugin loading without knowing types at compile time!" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║            VIRTUAL FUNCTIONS & POLYMORPHISM                    ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    // Example 1: What is polymorphism
    testPolymorphism();
    
    // Example 2: Abstract classes
    testAbstractClasses();
    
    // Example 3: vtable mechanism
    testVtableMechanism();
    
    // Example 4: Runtime vs compile-time
    testPolymorphismTypes();
    
    // Example 5: Virtual rules
    testVirtualRules();
    
    // Example 6: Real-world example
    testRealWorldExample();
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    INTERVIEW TIPS                              ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What is polymorphism?                                      ║" << endl;
    cout << "║  A: 'Many forms' - ability to call derived class methods      ║" << endl;
    cout << "║     through base class pointer/reference at runtime           ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: How do virtual functions work internally?                  ║" << endl;
    cout << "║  A: Via vtable (virtual table) and vptr (virtual pointer)     ║" << endl;
    cout << "║     Each object has vptr pointing to class's vtable            ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What's a pure virtual function?                            ║" << endl;
    cout << "║  A: virtual void func() = 0; Makes class abstract              ║" << endl;
    cout << "║     Derived classes MUST implement it                          ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: Compile-time vs Runtime polymorphism?                      ║" << endl;
    cout << "║  A: Compile: Function overloading                              ║" << endl;
    cout << "║     Runtime: Virtual functions (more flexible)                 ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: Cost of virtual functions?                                 ║" << endl;
    cout << "║  A: 8 bytes per object (vptr) + slight call overhead           ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

/*
 * SUMMARY - Virtual Functions & Polymorphism:
 * ============================================
 * 
 * POLYMORPHISM:
 * - "Many forms" - one interface, multiple implementations
 * - Base pointer can call derived class methods
 * - Enables writing flexible, extensible code
 * 
 * VIRTUAL FUNCTIONS:
 * - Enable runtime polymorphism
 * - Use 'virtual' keyword in base class
 * - Use 'override' keyword in derived class (C++11)
 * - Always make destructor virtual if class has virtual functions
 * 
 * PURE VIRTUAL FUNCTIONS:
 * - Syntax: virtual void func() = 0;
 * - Makes class abstract (cannot instantiate)
 * - Derived classes MUST implement
 * - Used for interfaces/contracts
 * 
 * INTERNAL MECHANISM:
 * - vtable: Array of function pointers per class
 * - vptr: Pointer in each object pointing to class's vtable
 * - Runtime lookup: Follow vptr → find function in vtable → call it
 * - Cost: 8 bytes per object + slight overhead
 * 
 * TWO TYPES OF POLYMORPHISM:
 * 1. Compile-time: Function overloading, templates
 * 2. Runtime: Virtual functions (more flexible)
 * 
 * BEST PRACTICES:
 * - Always use virtual destructor in polymorphic base classes
 * - Use 'override' keyword for clarity and safety
 * - Use 'final' to prevent further overriding if needed
 * - Pure virtual for interfaces, virtual for optional override
 */
