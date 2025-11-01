#include <iostream>
#include <string>
using namespace std;

/*
 * PART 4: CONSTRUCTOR & DESTRUCTOR ORDER IN INHERITANCE 
 * ======================================================
 * Understanding the order of construction and destruction in inheritance
 * This is a VERY common interview question!
 */

// ============================================================================
// EXAMPLE 1: Basic Constructor/Destructor Order (Single Inheritance)
// ============================================================================

class Base {
public:
    Base() {
        cout << "1. Base Constructor" << endl;
    }
    
    ~Base() {
        cout << "4. Base Destructor" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "2. Derived Constructor" << endl;
    }
    
    ~Derived() {
        cout << "3. Derived Destructor" << endl;
    }
};

void testBasicOrder() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  BASIC ORDER (Single Inheritance)      ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\nCreating Derived object:" << endl;
    Derived d;
    cout << "\nObject going out of scope..." << endl;
    
    cout << "\n📝 Rule:" << endl;
    cout << "   Construction: Base → Derived (Top to Bottom)" << endl;
    cout << "   Destruction:  Derived → Base (Bottom to Top)" << endl;
}

// ============================================================================
// EXAMPLE 2: Multilevel Inheritance Order
// ============================================================================

class Grandparent {
public:
    Grandparent() {
        cout << "1. Grandparent Constructor" << endl;
    }
    
    ~Grandparent() {
        cout << "6. Grandparent Destructor" << endl;
    }
};

class Parent : public Grandparent {
public:
    Parent() {
        cout << "2. Parent Constructor" << endl;
    }
    
    ~Parent() {
        cout << "5. Parent Destructor" << endl;
    }
};

class Child : public Parent {
public:
    Child() {
        cout << "3. Child Constructor" << endl;
    }
    
    ~Child() {
        cout << "4. Child Destructor" << endl;
    }
};

void testMultilevelOrder() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  MULTILEVEL INHERITANCE ORDER          ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\nCreating Child object:" << endl;
    Child c;
    cout << "\nObject going out of scope..." << endl;
    
    cout << "\n📝 Construction: Grandparent → Parent → Child" << endl;
    cout << "   Destruction:  Child → Parent → Grandparent" << endl;
    cout << "   (Reverse of construction order!)" << endl;
}

// ============================================================================
// EXAMPLE 3: Multiple Inheritance Order (Left to Right)
// ============================================================================

class Base1 {
public:
    Base1() {
        cout << "1. Base1 Constructor" << endl;
    }
    
    ~Base1() {
        cout << "5. Base1 Destructor" << endl;
    }
};

class Base2 {
public:
    Base2() {
        cout << "2. Base2 Constructor" << endl;
    }
    
    ~Base2() {
        cout << "4. Base2 Destructor" << endl;
    }
};

class MultiDerived : public Base1, public Base2 {
public:
    MultiDerived() {
        cout << "3. MultiDerived Constructor" << endl;
    }
    
    ~MultiDerived() {
        cout << "3. MultiDerived Destructor" << endl;
    }
};

void testMultipleInheritanceOrder() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  MULTIPLE INHERITANCE ORDER            ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\nCreating MultiDerived object:" << endl;
    MultiDerived md;
    cout << "\nObject going out of scope..." << endl;
    
    cout << "\n📝 Rule: Base classes constructed LEFT to RIGHT" << endl;
    cout << "   class MultiDerived : public Base1, public Base2" << endl;
    cout << "                               ↑         ↑" << endl;
    cout << "                            First     Second" << endl;
}

// ============================================================================
// EXAMPLE 4: Constructor with Parameters
// ============================================================================

class Animal {
private:
    string name;
    
public:
    Animal(string n) : name(n) {
        cout << "Animal Constructor: " << name << endl;
    }
    
    ~Animal() {
        cout << "Animal Destructor: " << name << endl;
    }
};

class Dog : public Animal {
private:
    string breed;
    
public:
    // Must explicitly call base constructor in initialization list
    Dog(string n, string b) : Animal(n), breed(b) {
        cout << "Dog Constructor: " << breed << endl;
    }
    
    ~Dog() {
        cout << "Dog Destructor: " << breed << endl;
    }
};

void testParameterizedConstructors() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  PARAMETERIZED CONSTRUCTORS            ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\nCreating Dog object:" << endl;
    Dog myDog("Buddy", "Golden Retriever");
    cout << "\nObject going out of scope..." << endl;
    
    cout << "\n📝 Must call base constructor in initialization list!" << endl;
    cout << "   Dog(string n, string b) : Animal(n), breed(b) { }" << endl;
}

// ============================================================================
// EXAMPLE 5: Member Objects Construction Order
// ============================================================================

class Engine {
public:
    Engine() {
        cout << "  → Engine Constructor" << endl;
    }
    
    ~Engine() {
        cout << "  → Engine Destructor" << endl;
    }
};

class Wheel {
public:
    Wheel() {
        cout << "  → Wheel Constructor" << endl;
    }
    
    ~Wheel() {
        cout << "  → Wheel Destructor" << endl;
    }
};

class Vehicle_Base {
public:
    Vehicle_Base() {
        cout << "1. Vehicle_Base Constructor" << endl;
    }
    
    ~Vehicle_Base() {
        cout << "4. Vehicle_Base Destructor" << endl;
    }
};

class Car_WithMembers : public Vehicle_Base {
private:
    Engine engine;  // Member object 1
    Wheel wheel;    // Member object 2
    
public:
    Car_WithMembers() {
        cout << "2. Car_WithMembers Constructor" << endl;
    }
    
    ~Car_WithMembers() {
        cout << "3. Car_WithMembers Destructor" << endl;
    }
};

void testMemberObjectOrder() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  MEMBER OBJECTS ORDER                  ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\nCreating Car_WithMembers object:" << endl;
    Car_WithMembers car;
    cout << "\nObject going out of scope..." << endl;
    
    cout << "\n📝 Order:" << endl;
    cout << "   1. Base class constructor" << endl;
    cout << "   2. Member objects (in declaration order)" << endl;
    cout << "   3. Derived class constructor" << endl;
    cout << "   Destruction: Reverse order!" << endl;
}

// ============================================================================
// EXAMPLE 6: Virtual Destructor (CRITICAL for Polymorphism!)
// ============================================================================

class Shape_NoVirtual {
public:
    Shape_NoVirtual() {
        cout << "Shape Constructor" << endl;
    }
    
    ~Shape_NoVirtual() {  // ❌ NOT virtual!                                      
        cout << "Shape Destructor" << endl;
    }
};

class Circle_NoVirtual : public Shape_NoVirtual {
private:
    int* data;  // Dynamically allocated memory
    
public:
    Circle_NoVirtual() {
        data = new int[100];
        cout << "Circle Constructor (allocated memory)" << endl;
    }
    
    ~Circle_NoVirtual() {
        delete[] data;
        cout << "Circle Destructor (freed memory)" << endl;
    }
};

class Shape_WithVirtual {
public:
    Shape_WithVirtual() {
        cout << "Shape Constructor" << endl;
    }
    
    virtual ~Shape_WithVirtual() {  // ✅ Virtual destructor!
        cout << "Shape Destructor" << endl;
    }
};

class Circle_WithVirtual : public Shape_WithVirtual {
private:
    int* data;
    
public:
    Circle_WithVirtual() {
        data = new int[100];
        cout << "Circle Constructor (allocated memory)" << endl;
    }
    
    ~Circle_WithVirtual() {
        delete[] data;
        cout << "Circle Destructor (freed memory)" << endl;
    }
};

void testVirtualDestructor() {
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║  VIRTUAL DESTRUCTOR (CRITICAL!)                        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n❌ WITHOUT Virtual Destructor:" << endl;
    {
        Shape_NoVirtual* shape = new Circle_NoVirtual();
        delete shape;  // ⚠️ Only Shape destructor called! MEMORY LEAK!
    }
    
    cout << "\n✅ WITH Virtual Destructor:" << endl;
    {
        Shape_WithVirtual* shape = new Circle_WithVirtual();
        delete shape;  // ✅ Both destructors called! No leak!
    }
    
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║  🔥 GOLDEN RULE:                                       ║" << endl;
    cout << "║  If a class is meant to be inherited,                 ║" << endl;
    cout << "║  ALWAYS make destructor virtual!                      ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
}

// ============================================================================
// EXAMPLE 7: Virtual Inheritance Constructor Order
// ============================================================================

class VirtualBase {
public:
    VirtualBase() {
        cout << "1. VirtualBase Constructor (constructed by most derived)" << endl;
    }
    
    ~VirtualBase() {
        cout << "6. VirtualBase Destructor" << endl;
    }
};

class Derived1_Virtual : virtual public VirtualBase {
public:
    Derived1_Virtual() {
        cout << "2. Derived1_Virtual Constructor" << endl;
    }
    
    ~Derived1_Virtual() {
        cout << "5. Derived1_Virtual Destructor" << endl;
    }
};

class Derived2_Virtual : virtual public VirtualBase {
public:
    Derived2_Virtual() {
        cout << "3. Derived2_Virtual Constructor" << endl;
    }
    
    ~Derived2_Virtual() {
        cout << "4. Derived2_Virtual Destructor" << endl;
    }
};

class Final_Virtual : public Derived1_Virtual, public Derived2_Virtual {
public:
    Final_Virtual() {
        cout << "4. Final_Virtual Constructor" << endl;
    }
    
    ~Final_Virtual() {
        cout << "3. Final_Virtual Destructor" << endl;
    }
};

void testVirtualInheritanceOrder() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  VIRTUAL INHERITANCE ORDER             ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\nCreating Final_Virtual object:" << endl;
    Final_Virtual fv;
    cout << "\nObject going out of scope..." << endl;
    
    cout << "\n📝 Special Rule for Virtual Inheritance:" << endl;
    cout << "   Virtual base constructed FIRST by most derived class" << endl;
    cout << "   Order: VirtualBase → Derived1 → Derived2 → Final" << endl;
}

// ============================================================================
// SUMMARY TABLE
// ============================================================================

void showSummaryTable() {
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           CONSTRUCTOR/DESTRUCTOR ORDER SUMMARY                 ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  CONSTRUCTION ORDER:                                           ║" << endl;
    cout << "║  ────────────────────────────────────────────────────────────  ║" << endl;
    cout << "║  1. Virtual base classes (if any)                              ║" << endl;
    cout << "║  2. Non-virtual base classes (left to right)                   ║" << endl;
    cout << "║  3. Member objects (in declaration order)                      ║" << endl;
    cout << "║  4. Derived class constructor body                             ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  DESTRUCTION ORDER:                                            ║" << endl;
    cout << "║  ────────────────────────────────────────────────────────────  ║" << endl;
    cout << "║  Exactly REVERSE of construction order!                        ║" << endl;
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
    cout << "║      CONSTRUCTOR & DESTRUCTOR ORDER IN INHERITANCE             ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    // Example 1: Basic order
    testBasicOrder();
    
    // Example 2: Multilevel inheritance
    testMultilevelOrder();
    
    // Example 3: Multiple inheritance
    testMultipleInheritanceOrder();
    
    // Example 4: Parameterized constructors
    testParameterizedConstructors();
    
    // Example 5: Member objects
    testMemberObjectOrder();
    
    // Example 6: Virtual destructor
    testVirtualDestructor();
    
    // Example 7: Virtual inheritance
    testVirtualInheritanceOrder();
    
    // Summary
    showSummaryTable();
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    INTERVIEW TIPS                              ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What's the order of constructor calls?                     ║" << endl;
    cout << "║  A: Base → Derived (Top to Bottom)                             ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What's the order of destructor calls?                      ║" << endl;
    cout << "║  A: Derived → Base (Bottom to Top, reverse!)                   ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: When should destructor be virtual?                         ║" << endl;
    cout << "║  A: ALWAYS when class is meant to be inherited!                ║" << endl;
    cout << "║     Otherwise: Memory leaks with polymorphic deletion          ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What happens without virtual destructor?                   ║" << endl;
    cout << "║  A: Only base destructor called → Memory leak!                 ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: In multiple inheritance, which base constructed first?     ║" << endl;
    cout << "║  A: Left to right as declared in class definition              ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

/*
 * SUMMARY - Constructor/Destructor Order:
 * ========================================
 * 
 * CONSTRUCTION ORDER:
 * 1. Virtual base classes (most derived class constructs them)
 * 2. Non-virtual base classes (left to right)
 * 3. Member objects (in declaration order)
 * 4. Derived class constructor body
 * 
 * DESTRUCTION ORDER:
 * - Exact REVERSE of construction!
 * 
 * VIRTUAL DESTRUCTOR:
 * - CRITICAL for inheritance with polymorphism
 * - Without it: Only base destructor called → MEMORY LEAK
 * - Rule: If class can be inherited, make destructor virtual
 * 
 * INTERVIEW ANSWERS:
 * Q: Constructor order? A: Base → Derived
 * Q: Destructor order? A: Derived → Base (reverse!)
 * Q: When virtual destructor? A: When class is meant to be inherited
 * Q: What if no virtual destructor? A: Memory leak with polymorphic delete
 */
