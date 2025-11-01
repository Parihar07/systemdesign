#include <iostream>
#include <string>
using namespace std;

/*
 * PART 5: FUNCTION OVERRIDING
 * ============================
 * Understanding function overriding in inheritance:
 * - What is overriding?
 * - Overriding vs Overloading
 * - Virtual functions for runtime polymorphism
 * - override keyword (C++11)
 */

// ============================================================================
// EXAMPLE 1: Basic Function Overriding
// ============================================================================
 
class Animal {
public:
    void sound() {  // Non-virtual
        cout << "Animal makes a sound" << endl;
    }
    
    virtual void eat() {  // Virtual
        cout << "Animal eats" << endl;
    }
};

class Dog : public Animal {
public:
    void sound() {  // Overrides (but not polymorphic!)
        cout << "Dog barks: Woof!" << endl;
    }
    
    void eat() override {  // Overrides (polymorphic!)
        cout << "Dog eats bones" << endl;
    }
};

void testBasicOverriding() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  BASIC FUNCTION OVERRIDING             ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    Dog d;
    d.sound();  // Dog barks
    d.eat();    // Dog eats bones
    
    cout << "\n--- Polymorphic behavior (virtual) ---" << endl;
    Animal* a = &d;
    a->sound();  // ❌ Calls Animal::sound() (not virtual!)
    a->eat();    // ✅ Calls Dog::eat() (virtual!)
    
    cout << "\n📝 Key: virtual keyword enables runtime polymorphism" << endl;
}

// ============================================================================
// EXAMPLE 2: Overriding vs Overloading
// ============================================================================

class Calculator {
public:
    // Overloading (same function name, different parameters)
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

class Shape {
public:
    virtual void draw() {
        cout << "Drawing Shape" << endl;
    }
};

class Circle : public Shape {
public:
    // Overriding (same function name, same parameters, different implementation)
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

void testOverridingVsOverloading() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  OVERRIDING vs OVERLOADING                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n--- Overloading (same class, different parameters) ---" << endl;
    Calculator calc;
    cout << "add(2, 3) = " << calc.add(2, 3) << endl;
    cout << "add(2.5, 3.7) = " << calc.add(2.5, 3.7) << endl;
    cout << "add(1, 2, 3) = " << calc.add(1, 2, 3) << endl;
    
    cout << "\n--- Overriding (derived class, same signature) ---" << endl;
    Shape* s = new Circle();
    s->draw();  // Calls Circle::draw() due to virtual
    delete s;
    
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  OVERLOADING: Same name, different parameters      ║" << endl;
    cout << "║  OVERRIDING: Same name, same parameters, virtual   ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
}

// ============================================================================
// EXAMPLE 3: The Importance of 'virtual'
// ============================================================================

class Base_NoVirtual {
public:
    void show() {  // NOT virtual
        cout << "Base::show()" << endl;
    }
};

class Derived_NoVirtual : public Base_NoVirtual {
public:
    void show() {  // Overrides but not polymorphic
        cout << "Derived::show()" << endl;
    }
};

class Base_WithVirtual {
public:
    virtual void show() {  // Virtual
        cout << "Base::show()" << endl;
    }
};

class Derived_WithVirtual : public Base_WithVirtual {
public:
    void show() override {  // Polymorphic override
        cout << "Derived::show()" << endl;
    }
};

void testVirtualImportance() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  THE IMPORTANCE OF 'virtual'                       ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n❌ WITHOUT virtual:" << endl;
    Derived_NoVirtual d1;
    Base_NoVirtual* b1 = &d1;
    b1->show();  // Calls Base::show() - Static binding!
    
    cout << "\n✅ WITH virtual:" << endl;
    Derived_WithVirtual d2;
    Base_WithVirtual* b2 = &d2;
    b2->show();  // Calls Derived::show() - Dynamic binding!
    
    cout << "\n📝 Without 'virtual', compiler uses pointer type (static binding)" << endl;
    cout << "   With 'virtual', runtime checks actual object type (dynamic binding)" << endl;
}

// ============================================================================
// EXAMPLE 4: The 'override' Keyword (C++11)
// ============================================================================

class Vehicle {
public:
    virtual void start() {
        cout << "Vehicle starting" << endl;
    }
    
    virtual void stop() {
        cout << "Vehicle stopping" << endl;
    }
};

class Car : public Vehicle {
public:
    // ✅ Good: override keyword catches mistakes
    void start() override {
        cout << "Car starting with key" << endl;
    }
    
    // ❌ This would cause compile error (catches typos!)
    // void stpo() override {  // Typo: stpo instead of stop
    //     cout << "Car stopping" << endl;
    // }
    
    void stop() override {
        cout << "Car stopping with brake" << endl;
    }
};

void testOverrideKeyword() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  THE 'override' KEYWORD (C++11)                    ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    Vehicle* v = new Car();
    v->start();
    v->stop();
    delete v;
    
    cout << "\n📝 Benefits of 'override' keyword:" << endl;
    cout << "   1. Catches typos at compile time" << endl;
    cout << "   2. Makes intent clear (this IS an override)" << endl;
    cout << "   3. Catches signature mismatches" << endl;
    cout << "   4. Better code readability" << endl;
    
    cout << "\n✅ Always use 'override' keyword!" << endl;
}

// ============================================================================
// EXAMPLE 5: Covariant Return Types
// ============================================================================

class Animal_Base {
public:
    virtual Animal_Base* clone() {
        cout << "Cloning Animal" << endl;
        return new Animal_Base();
    }
    
    virtual ~Animal_Base() { }
};

class Dog_Derived : public Animal_Base {
public:
    // Covariant return type (Dog_Derived* instead of Animal_Base*)
    Dog_Derived* clone() override {
        cout << "Cloning Dog" << endl;
        return new Dog_Derived();
    }
};

void testCovariantReturnTypes() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  COVARIANT RETURN TYPES                            ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    Animal_Base* a = new Dog_Derived();
    Animal_Base* cloned = a->clone();  // Returns Dog_Derived* but assigns to Animal_Base*
    
    Dog_Derived d;
    Dog_Derived* clonedDog = d.clone();  // Returns Dog_Derived* directly
    
    delete a;
    delete cloned;
    delete clonedDog;
    
    cout << "\n📝 Covariant return type: Override can return derived type" << endl;
    cout << "   Base returns: Animal_Base*" << endl;
    cout << "   Derived returns: Dog_Derived* (more specific!)" << endl;
}

// ============================================================================
// EXAMPLE 6: Calling Base Class Version from Derived
// ============================================================================

class Employee {
protected:
    string name;
    double salary;
    
public:
    Employee(string n, double s) : name(n), salary(s) { }
    
    virtual void display() {
        cout << "Name: " << name << ", Salary: $" << salary << endl;
    }
};

class Manager : public Employee {
private:
    int teamSize;
    
public:
    Manager(string n, double s, int t) : Employee(n, s), teamSize(t) { }
    
    void display() override {
        Employee::display();  // ← Call base class version
        cout << "Team Size: " << teamSize << endl;
    }
};

void testCallingBaseVersion() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  CALLING BASE CLASS VERSION                        ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    Manager m("Alice", 80000, 5);
    m.display();
    
    cout << "\n📝 Use Base::function() to call base class version" << endl;
    cout << "   Common pattern: Extend base behavior, don't replace it" << endl;
}

// ============================================================================
// EXAMPLE 7: Common Mistakes
// ============================================================================

class Base_Mistakes {
public:
    virtual void func(int x) {
        cout << "Base::func(int)" << endl;
    }
};

class Derived_Mistakes : public Base_Mistakes {
public:
    // ❌ Mistake 1: Different parameter (this is overloading, not overriding!)
    void func(double x) {
        cout << "Derived::func(double)" << endl;
    }
    
    // ✅ Correct: Same signature
    void func(int x) override {
        cout << "Derived::func(int)" << endl;
    }
};

void testCommonMistakes() {
    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║  COMMON MISTAKES                                   ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    
    Derived_Mistakes d;
    Base_Mistakes* b = &d;
    
    b->func(5);      // Calls Derived::func(int) ✅
    d.func(5);       // Calls Derived::func(int) ✅
    d.func(5.5);     // Calls Derived::func(double) (overloading, not overriding)
    
    cout << "\n⚠️  Common mistakes:" << endl;
    cout << "   1. Forgetting 'virtual' in base class" << endl;
    cout << "   2. Different parameters (overloading ≠ overriding)" << endl;
    cout << "   3. Different const-ness (const/non-const)" << endl;
    cout << "   4. Not using 'override' keyword" << endl;
}

// ============================================================================
// SUMMARY TABLE
// ============================================================================

void showSummaryTable() {
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              OVERRIDING vs OVERLOADING SUMMARY                 ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Feature        │  Overloading      │  Overriding             ║" << endl;
    cout << "║  ───────────────┼───────────────────┼─────────────────────    ║" << endl;
    cout << "║  Location       │  Same class       │  Base & Derived         ║" << endl;
    cout << "║  Parameters     │  Must differ      │  Must be same           ║" << endl;
    cout << "║  virtual needed │  No               │  Yes (for polymorphism) ║" << endl;
    cout << "║  Binding        │  Compile-time     │  Runtime (if virtual)   ║" << endl;
    cout << "║  Purpose        │  Multiple options │  Change behavior        ║" << endl;
    cout << "║  Example        │  add(int,int)     │  draw() in Circle       ║" << endl;
    cout << "║                 │  add(double,...)  │  overrides Shape::draw()║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║                  FUNCTION OVERRIDING                           ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    // Example 1: Basic overriding
    testBasicOverriding();
    
    // Example 2: Overriding vs Overloading
    testOverridingVsOverloading();
    
    // Example 3: Importance of virtual
    testVirtualImportance();
    
    // Example 4: override keyword
    testOverrideKeyword();
    
    // Example 5: Covariant return types
    testCovariantReturnTypes();
    
    // Example 6: Calling base version
    testCallingBaseVersion();
    
    // Example 7: Common mistakes
    testCommonMistakes();
    
    // Summary
    showSummaryTable();
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    INTERVIEW TIPS                              ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What's the difference between overriding and overloading?  ║" << endl;
    cout << "║  A: Overloading: Same name, different parameters, same class   ║" << endl;
    cout << "║     Overriding: Same name, same parameters, inheritance        ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: Do you need 'virtual' for overriding?                      ║" << endl;
    cout << "║  A: Not required, but needed for runtime polymorphism          ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What's the 'override' keyword for?                         ║" << endl;
    cout << "║  A: C++11 feature to catch mistakes at compile time            ║" << endl;
    cout << "║     Always use it for clarity and safety!                      ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: Can you call base class version from derived?              ║" << endl;
    cout << "║  A: Yes, using Base::function() syntax                         ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

/*
 * SUMMARY - Function Overriding:
 * ===============================
 * 
 * OVERRIDING:
 * - Same function name, same parameters
 * - In base and derived classes
 * - Needs 'virtual' for runtime polymorphism
 * - Changes behavior in derived class
 * 
 * OVERLOADING:
 * - Same function name, different parameters
 * - In same class
 * - No 'virtual' needed
 * - Provides multiple options
 * 
 * VIRTUAL KEYWORD:
 * - Enables runtime polymorphism
 * - Allows derived class function to be called via base pointer
 * - Without it: static binding (compile-time decision)
 * - With it: dynamic binding (runtime decision)
 * 
 * OVERRIDE KEYWORD (C++11):
 * - Explicitly marks function as override
 * - Catches mistakes at compile time
 * - Makes code more readable
 * - Always use it!
 * 
 * BEST PRACTICES:
 * 1. Always use 'virtual' in base class for polymorphism
 * 2. Always use 'override' in derived class
 * 3. Match signatures exactly (including const)
 * 4. Can call base version using Base::function()
 */
