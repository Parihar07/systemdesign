#include <iostream>
#include <string>
using namespace std;

/*
 * TYPES OF INHERITANCE IN C++
 * ============================
 * C++ supports 5 types of inheritance:
 * 1. Single Inheritance
 * 2. Multiple Inheritance
 * 3. Multilevel Inheritance
 * 4. Hierarchical Inheritance
 * 5. Hybrid Inheritance (Combination)
 * 
 * INTERVIEW NOTE: C++ supports multiple inheritance (unlike Java/C#)
 * This can lead to the "Diamond Problem" which we'll explore.
 */

// ============================================================================
// TYPE 1: SINGLE INHERITANCE
// ============================================================================
// One base class → One derived class
// A → B

class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {
        cout << "Animal constructor: " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
};

class Dog : public Animal {  // Dog inherits from Animal
private:
    string breed;
    
public:
    Dog(string n, string b) : Animal(n), breed(b) {
        cout << "Dog constructor: " << breed << endl;
    }
    
    void bark() {
        cout << name << " (" << breed << ") says: Woof!" << endl;
    }
};

// ============================================================================
// TYPE 2: MULTIPLE INHERITANCE
// ============================================================================
// Multiple base classes → One derived class
// A + B → C

class Flyer {
public:
    void fly() {
        cout << "I can fly!" << endl;
    }
};

class Swimmer {
public:
    void swim() {
        cout << "I can swim!" << endl;
    }
};

class Duck : public Flyer, public Swimmer {  // Inherits from BOTH
public:
    void quack() {
        cout << "Quack! Quack!" << endl;
    }
};

// ============================================================================
// TYPE 3: MULTILEVEL INHERITANCE
// ============================================================================
// Chain of inheritance: A → B → C
// Grandparent → Parent → Child

class LivingBeing {
protected:
    bool isAlive;
    
public:
    LivingBeing() : isAlive(true) {
        cout << "LivingBeing created" << endl;
    }
    
    void breathe() {
        cout << "Breathing..." << endl;
    }
};

class Mammal : public LivingBeing {  // Mammal inherits from LivingBeing
protected:
    int bodyTemperature;
    
public:
    Mammal() : bodyTemperature(37) {
        cout << "Mammal created" << endl;
    }
    
    void regulateTemp() {
        cout << "Maintaining body temperature at " << bodyTemperature << "°C" << endl;
    }
};

class Human : public Mammal {  // Human inherits from Mammal (which inherits from LivingBeing)
private:
    string name;
    
public:
    Human(string n) : name(n) {
        cout << "Human created: " << name << endl;
    }
    
    void speak() {
        cout << name << " is speaking" << endl;
    }
    
    void showInheritance() {
        cout << "\nHuman has access to:" << endl;
        breathe();      // From LivingBeing (grandparent)
        regulateTemp(); // From Mammal (parent)
        speak();        // Own method
    }
};

// ============================================================================
// TYPE 4: HIERARCHICAL INHERITANCE
// ============================================================================
// One base class → Multiple derived classes
// A → B, C, D

class Shape {
protected:
    string color;
    
public:
    Shape(string c) : color(c) {
        cout << "Shape created with color: " << color << endl;
    }
    
    void displayColor() {
        cout << "Color: " << color << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(string c, double r) : Shape(c), radius(r) {
    }
    
    double getArea() {
        return 3.14159 * radius * radius;
    }
    
    void display() {
        cout << "Circle - ";
        displayColor();
        cout << "Radius: " << radius << ", Area: " << getArea() << endl;
    }
};

class Rectangle : public Shape {
private:
    double length, width;
    
public:
    Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
    }
    
    double getArea() {
        return length * width;
    }
    
    void display() {
        cout << "Rectangle - ";
        displayColor();
        cout << "Dimensions: " << length << "x" << width;
        cout << ", Area: " << getArea() << endl;
    }
};

class Triangle : public Shape {
private:
    double base, height;
    
public:
    Triangle(string c, double b, double h) : Shape(c), base(b), height(h) {
    }
    
    double getArea() {
        return 0.5 * base * height;
    }
    
    void display() {
        cout << "Triangle - ";
        displayColor();
        cout << "Base: " << base << ", Height: " << height;
        cout << ", Area: " << getArea() << endl;
    }
};

// ============================================================================
// TYPE 5: HYBRID INHERITANCE (COMBINATION)
// ============================================================================
// Combination of two or more types of inheritance

class Device {
protected:
    string brand;
    
public:
    Device(string b) : brand(b) {
        cout << "Device: " << brand << endl;
    }
    
    void powerOn() {
        cout << brand << " device powered on" << endl;
    }
};

class Phone : public Device {
protected:
    string phoneNumber;
    
public:
    Phone(string b, string num) : Device(b), phoneNumber(num) {
        cout << "Phone: " << phoneNumber << endl;
    }
    
    void call() {
        cout << "Calling from " << phoneNumber << endl;
    }
};

class Camera {
protected:
    int megapixels;
    
public:
    Camera(int mp) : megapixels(mp) {
        cout << "Camera: " << mp << "MP" << endl;
    }
    
    void takePhoto() {
        cout << "Taking photo with " << megapixels << "MP camera" << endl;
    }
};

// Smartphone: Hierarchical (Device→Phone) + Multiple (Phone + Camera)
class Smartphone : public Phone, public Camera {
private:
    string model;
    
public:
    Smartphone(string b, string num, int mp, string m)
        : Phone(b, num), Camera(mp), model(m) {
        cout << "Smartphone: " << model << endl;
    }
    
    void showFeatures() {
        cout << "\n" << model << " Features:" << endl;
        powerOn();   // From Device (through Phone)
        call();      // From Phone
        takePhoto(); // From Camera
    }
};

// ============================================================================
// THE DIAMOND PROBLEM
// ============================================================================
// Problem occurs in multiple inheritance when two base classes inherit from same grandparent

class GrandParent {
protected:
    int value;
    
public:
    GrandParent() : value(100) {
        cout << "GrandParent constructor, value = " << value << endl;
    }
    
    void display() {
        cout << "GrandParent value: " << value << endl;
    }
};

class Parent1 : public GrandParent {
public:
    Parent1() {
        cout << "Parent1 constructor" << endl;
    }
};

class Parent2 : public GrandParent {
public:
    Parent2() {
        cout << "Parent2 constructor" << endl;
    }
};

class Child : public Parent1, public Parent2 {
public:
    Child() {
        cout << "Child constructor" << endl;
    }
    
    void showProblem() {
        // AMBIGUITY! Which GrandParent's value? Parent1's or Parent2's?
        // value = 200;     // ❌ ERROR: ambiguous
        // display();       // ❌ ERROR: ambiguous
        
        // Must specify which path:
        Parent1::value = 200;
        Parent2::value = 300;
        
        cout << "\nDiamond Problem Demonstration:" << endl;
        cout << "Value through Parent1: " << Parent1::value << endl;
        cout << "Value through Parent2: " << Parent2::value << endl;
        
        Parent1::display();
        Parent2::display();
    }
};

// ============================================================================
// SOLUTION: VIRTUAL INHERITANCE
// ============================================================================

class GrandParentV {
protected:
    int value;
    
public:
    GrandParentV() : value(100) {
        cout << "GrandParentV constructor, value = " << value << endl;
    }
    
    void display() {
        cout << "GrandParentV value: " << value << endl;
    }
};

class Parent1V : virtual public GrandParentV {  // virtual inheritance
public:
    Parent1V() {
        cout << "Parent1V constructor" << endl;
    }
};

class Parent2V : virtual public GrandParentV {  // virtual inheritance
public:
    Parent2V() {
        cout << "Parent2V constructor" << endl;
    }
};

class ChildV : public Parent1V, public Parent2V {
public:
    ChildV() {
        cout << "ChildV constructor" << endl;
    }
    
    void showSolution() {
        // NO AMBIGUITY! Only ONE GrandParentV exists
        value = 500;  // ✅ OK!
        display();    // ✅ OK!
        
        cout << "Virtual inheritance - only one GrandParentV!" << endl;
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "=== TYPE 1: SINGLE INHERITANCE ===" << endl;
    Dog dog("Buddy", "Golden Retriever");
    dog.eat();   // Inherited from Animal
    dog.bark();  // Dog's own method
    
    cout << "\n=== TYPE 2: MULTIPLE INHERITANCE ===" << endl;
    Duck duck;
    duck.fly();   // From Flyer
    duck.swim();  // From Swimmer
    duck.quack(); // Duck's own
    cout << "Duck inherits from BOTH Flyer and Swimmer!" << endl;
    
    cout << "\n=== TYPE 3: MULTILEVEL INHERITANCE ===" << endl;
    Human human("Alice");
    human.showInheritance();
    cout << "Human → Mammal → LivingBeing (3 levels!)" << endl;
    
    cout << "\n=== TYPE 4: HIERARCHICAL INHERITANCE ===" << endl;
    Circle circle("Red", 5.0);
    Rectangle rect("Blue", 10.0, 5.0);
    Triangle tri("Green", 6.0, 4.0);
    
    circle.display();
    rect.display();
    tri.display();
    cout << "All inherit from Shape!" << endl;
    
    cout << "\n=== TYPE 5: HYBRID INHERITANCE ===" << endl;
    Smartphone phone("Apple", "+91-9876543210", 48, "iPhone 15");
    phone.showFeatures();
    
    cout << "\n=== DIAMOND PROBLEM ===" << endl;
    cout << "\nWithout virtual inheritance:" << endl;
    Child child;
    child.showProblem();
    cout << "\nProblem: TWO copies of GrandParent!" << endl;
    
    cout << "\n\nWith virtual inheritance (Solution):" << endl;
    ChildV childV;
    childV.showSolution();
    
    cout << "\n=== SUMMARY ===" << endl;
    cout << "1. Single:       A → B" << endl;
    cout << "2. Multiple:     A + B → C" << endl;
    cout << "3. Multilevel:   A → B → C" << endl;
    cout << "4. Hierarchical: A → B, C, D" << endl;
    cout << "5. Hybrid:       Combination of above" << endl;
    cout << "\n6. Diamond Problem: Solved with virtual inheritance!" << endl;
    
    return 0;
}

/*
 * INTERVIEW QUESTIONS:
 * 
 * Q1: What are the types of inheritance in C++?
 * A1: Five types:
 *     1. Single: One base → One derived
 *     2. Multiple: Multiple bases → One derived
 *     3. Multilevel: Chain A → B → C
 *     4. Hierarchical: One base → Multiple derived
 *     5. Hybrid: Combination of above types
 * 
 * Q2: Does C++ support multiple inheritance?
 * A2: YES! C++ supports multiple inheritance (unlike Java/C#).
 *     A class can inherit from multiple base classes.
 *     Example: class Duck : public Flyer, public Swimmer { };
 * 
 * Q3: What is the diamond problem?
 * A3: In multiple inheritance, if two base classes inherit from same grandparent,
 *     the derived class ends up with TWO copies of grandparent members.
 *     This creates ambiguity - which copy to use?
 *     
 *     Diagram:
 *          GrandParent
 *           /      \
 *       Parent1  Parent2
 *           \      /
 *            Child
 *     
 *     Child has TWO copies of GrandParent!
 * 
 * Q4: How to solve the diamond problem?
 * A4: Use VIRTUAL INHERITANCE:
 *     class Parent1 : virtual public GrandParent { };
 *     class Parent2 : virtual public GrandParent { };
 *     
 *     Now Child has only ONE copy of GrandParent.
 *     The 'virtual' keyword tells compiler to share the base class.
 * 
 * Q5: What is multilevel inheritance?
 * A5: Chain of inheritance where a derived class becomes base for another class.
 *     Example: LivingBeing → Mammal → Human
 *     Human inherits from Mammal, Mammal inherits from LivingBeing.
 *     Human has access to members of both!
 * 
 * Q6: What is hierarchical inheritance?
 * A6: One base class with multiple derived classes.
 *     Example: Shape → Circle, Rectangle, Triangle
 *     All shapes inherit common properties from Shape.
 * 
 * Q7: When would you use multiple inheritance?
 * A7: When a class genuinely needs features from multiple unrelated classes.
 *     Example: Duck can fly (Flyer) and swim (Swimmer)
 *     But be careful - avoid if possible, prefer composition!
 * 
 * Q8: What's the difference between multilevel and multiple inheritance?
 * A8: Multilevel: Chain (A → B → C) - linear hierarchy
 *     Multiple: Merge (A + B → C) - combines unrelated classes
 * 
 * Q9: Can you have hybrid inheritance?
 * A9: Yes! It's a combination of two or more types.
 *     Example: Smartphone uses both hierarchical (Device→Phone) 
 *     and multiple (Phone + Camera → Smartphone)
 * 
 * Q10: What are the risks of multiple inheritance?
 * A10: - Diamond problem (ambiguity)
 *      - Complexity (hard to understand)
 *      - Name conflicts (same method in multiple bases)
 *      - Increased coupling
 *      - Virtual inheritance overhead
 *      Prefer composition over multiple inheritance when possible!
 */

/*
 * KEY POINTS:
 * 
 * 1. TYPES OF INHERITANCE:
 *    Single:       Most common, simple
 *    Multiple:     Powerful but dangerous
 *    Multilevel:   Natural hierarchies
 *    Hierarchical: Common base for related classes
 *    Hybrid:       Real-world complexity
 * 
 * 2. MULTIPLE INHERITANCE:
 *    - C++ allows it (Java/C# don't)
 *    - Use with caution
 *    - Can cause diamond problem
 *    - Syntax: class C : public A, public B { };
 * 
 * 3. DIAMOND PROBLEM:
 *    Problem: Two copies of grandparent
 *    Solution: Virtual inheritance
 *    Syntax: class Parent : virtual public GrandParent { };
 * 
 * 4. VIRTUAL INHERITANCE:
 *    - Use 'virtual' keyword in inheritance
 *    - Ensures single copy of base class
 *    - Slight performance overhead
 *    - Most derived class initializes virtual base
 * 
 * 5. CONSTRUCTOR CALLING ORDER:
 *    Multiple inheritance: Left to right in declaration
 *    class C : public A, public B { };
 *    Order: A → B → C
 *    
 *    Virtual inheritance: Virtual bases first
 *    Order: Virtual bases → Regular bases → Derived
 * 
 * 6. BEST PRACTICES:
 *    ✓ Prefer single inheritance
 *    ✓ Use multiple inheritance sparingly
 *    ✓ Consider composition over multiple inheritance
 *    ✓ Use virtual inheritance for diamond scenarios
 *    ✓ Document multiple inheritance clearly
 *    ✓ Keep hierarchies shallow (max 3-4 levels)
 * 
 * 7. COMMON PITFALLS:
 *    - Forgetting virtual keyword (diamond problem)
 *    - Deep inheritance hierarchies (hard to maintain)
 *    - Multiple inheritance for convenience (bad design)
 *    - Not handling ambiguity in multiple inheritance
 */
