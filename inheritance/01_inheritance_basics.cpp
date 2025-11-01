#include <iostream>
#include <string>
using namespace std;

/*
 * INHERITANCE BASICS
 * ==================
 * Inheritance is a fundamental OOP concept where a class (derived/child) 
 * acquires properties and behaviors from another class (base/parent).
 * 
 * KEY CONCEPT: IS-A Relationship
 * - Dog IS-A Animal
 * - Car IS-A Vehicle
 * - Circle IS-A Shape
 * 
 * SYNTAX: class Derived : access_specifier Base { };
 */

// ============================================================================
// EXAMPLE 1: SIMPLE INHERITANCE - ANIMAL HIERARCHY
// ============================================================================

class Animal {
public:
    string name;
    int age;
    
    void eat() {
        cout << name << " is eating..." << endl;
    }
    
    void sleep() {
        cout << name << " is sleeping..." << endl;
    }
};

class Dog : public Animal {  // Dog inherits from Animal
public:
    void bark() {
        cout << name << " says: Woof! Woof!" << endl;
    }
};

class Cat : public Animal {  // Cat inherits from Animal
public:
    void meow() {
        cout << name << " says: Meow! Meow!" << endl;
    }
};

// ============================================================================
// EXAMPLE 2: VEHICLE HIERARCHY - CODE REUSE
// ============================================================================

class Vehicle {
protected:  // Accessible to derived classes
    string brand;
    int year;
    
public:
    Vehicle(string b, int y) : brand(b), year(y) {
        cout << "Vehicle constructor called" << endl;
    }
    
    void displayInfo() {
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
    
    void start() {
        cout << "Vehicle is starting..." << endl;
    }
};

class Car : public Vehicle {
private:
    int numDoors;
    
public:
    Car(string b, int y, int doors) : Vehicle(b, y), numDoors(doors) {
        cout << "Car constructor called" << endl;
    }
    
    void displayCarInfo() {
        displayInfo();  // Inherited method
        cout << "Doors: " << numDoors << endl;
    }
    
    void honk() {
        cout << brand << " car honking: Beep! Beep!" << endl;
    }
};

class Bike : public Vehicle {
private:
    bool hasCarrier;
    
public:
    Bike(string b, int y, bool carrier) : Vehicle(b, y), hasCarrier(carrier) {
        cout << "Bike constructor called" << endl;
    }
    
    void ringBell() {
        cout << brand << " bike ringing: Ring! Ring!" << endl;
    }
};

// ============================================================================
// EXAMPLE 3: EMPLOYEE HIERARCHY - REAL WORLD
// ============================================================================

class Employee {
protected:
    string name;
    int empId;
    double baseSalary;
    
public:
    Employee(string n, int id, double salary) 
        : name(n), empId(id), baseSalary(salary) {
    }
    
    void display() {
        cout << "Name: " << name << ", ID: " << empId;
        cout << ", Salary: ₹" << baseSalary << endl;
    }
    
    double getSalary() {
        return baseSalary;
    }
};

class Manager : public Employee {
private:
    double bonus;
    int teamSize;
    
public:
    Manager(string n, int id, double salary, double b, int team)
        : Employee(n, id, salary), bonus(b), teamSize(team) {
    }
    
    void displayManager() {
        display();  // Inherited method
        cout << "Bonus: ₹" << bonus << ", Team Size: " << teamSize << endl;
    }
    
    double getTotalSalary() {
        return getSalary() + bonus;  // Using inherited method
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, int id, double salary, string lang, int projects)
        : Employee(n, id, salary), programmingLanguage(lang), 
          projectsCompleted(projects) {
    }
    
    void displayDeveloper() {
        display();  // Inherited method
        cout << "Language: " << programmingLanguage;
        cout << ", Projects: " << projectsCompleted << endl;
    }
    
    void code() {
        cout << name << " is coding in " << programmingLanguage << endl;
    }
};

// ============================================================================
// EXAMPLE 4: BANK ACCOUNT HIERARCHY
// ============================================================================

class BankAccount {
protected:
    string accountNumber;
    string holderName;
    double balance;
    
public:
    BankAccount(string acc, string name, double bal)
        : accountNumber(acc), holderName(name), balance(bal) {
        cout << "Bank Account created: " << accountNumber << endl;
    }
    
    void deposit(double amount) {
        balance += amount;
        cout << "Deposited ₹" << amount << ", New balance: ₹" << balance << endl;
    }
    
    void displayBalance() {
        cout << "Account: " << accountNumber;
        cout << ", Holder: " << holderName;
        cout << ", Balance: ₹" << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;
    
public:
    SavingsAccount(string acc, string name, double bal, double rate)
        : BankAccount(acc, name, bal), interestRate(rate) {
        cout << "Savings Account created with " << rate << "% interest" << endl;
    }
    
    void addInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest added: ₹" << interest;
        cout << ", New balance: ₹" << balance << endl;
    }
};

class CurrentAccount : public BankAccount {
private:
    double overdraftLimit;
    
public:
    CurrentAccount(string acc, string name, double bal, double limit)
        : BankAccount(acc, name, bal), overdraftLimit(limit) {
        cout << "Current Account created with ₹" << limit << " overdraft" << endl;
    }
    
    void withdraw(double amount) {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
            cout << "Withdrawn ₹" << amount << ", Balance: ₹" << balance << endl;
        } else {
            cout << "Insufficient funds (even with overdraft)!" << endl;
        }
    }
};

// ============================================================================
// EXAMPLE 5: SHAPE HIERARCHY
// ============================================================================

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
        displayColor();  // Inherited
        cout << "Circle with radius: " << radius << endl;
        cout << "Area: " << getArea() << endl;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
    }
    
    double getArea() {
        return length * width;
    }
    
    void display() {
        displayColor();  // Inherited
        cout << "Rectangle: " << length << " x " << width << endl;
        cout << "Area: " << getArea() << endl;
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "=== EXAMPLE 1: SIMPLE INHERITANCE ===" << endl;
    Dog dog;
    dog.name = "Buddy";
    dog.age = 3;
    dog.eat();    // Inherited from Animal
    dog.sleep();  // Inherited from Animal
    dog.bark();   // Dog's own method
    
    cout << endl;
    Cat cat;
    cat.name = "Whiskers";
    cat.age = 2;
    cat.eat();    // Inherited from Animal
    cat.meow();   // Cat's own method
    
    cout << "\n=== EXAMPLE 2: VEHICLE HIERARCHY ===" << endl;
    Car car("Toyota", 2024, 4);
    car.displayCarInfo();
    car.start();  // Inherited
    car.honk();   // Car's own
    
    cout << endl;
    Bike bike("Hero", 2023, true);
    bike.displayInfo();  // Inherited
    bike.ringBell();     // Bike's own
    
    cout << "\n=== EXAMPLE 3: EMPLOYEE HIERARCHY ===" << endl;
    Manager mgr("Rajesh Kumar", 101, 80000, 20000, 5);
    mgr.displayManager();
    cout << "Total Salary: ₹" << mgr.getTotalSalary() << endl;
    
    cout << endl;
    Developer dev("Priya Singh", 102, 60000, "C++", 12);
    dev.displayDeveloper();
    dev.code();
    
    cout << "\n=== EXAMPLE 4: BANK ACCOUNT HIERARCHY ===" << endl;
    SavingsAccount savings("SA12345", "Amit Sharma", 50000, 4.5);
    savings.deposit(10000);
    savings.addInterest();
    savings.displayBalance();
    
    cout << endl;
    CurrentAccount current("CA67890", "Neha Patel", 100000, 50000);
    current.deposit(20000);
    current.withdraw(150000);  // Using overdraft
    current.displayBalance();
    
    cout << "\n=== EXAMPLE 5: SHAPE HIERARCHY ===" << endl;
    Circle circle("Red", 5.0);
    circle.display();
    
    cout << endl;
    Rectangle rect("Blue", 10.0, 5.0);
    rect.display();
    
    cout << "\n=== KEY CONCEPTS ===" << endl;
    cout << "1. Inheritance enables CODE REUSE" << endl;
    cout << "2. Derived class inherits all public/protected members" << endl;
    cout << "3. Derived class can add its own members" << endl;
    cout << "4. Use 'public' inheritance for IS-A relationship" << endl;
    cout << "5. Base constructor called first (initialization list)" << endl;
    cout << "6. Protected members accessible in derived classes" << endl;
    
    return 0;
}

/*
 * INTERVIEW QUESTIONS:
 * 
 * Q1: What is inheritance?
 * A1: Inheritance is an OOP mechanism where a new class (derived/child) 
 *     acquires properties and behaviors from an existing class (base/parent).
 *     It enables code reuse and establishes IS-A relationships.
 * 
 * Q2: Why use inheritance?
 * A2: Benefits of inheritance:
 *     - Code reuse (don't repeat common functionality)
 *     - Logical hierarchy (model real-world relationships)
 *     - Extensibility (add features without modifying base)
 *     - Polymorphism (treat derived objects as base objects)
 * 
 * Q3: What is the syntax for inheritance in C++?
 * A3: class Derived : access_specifier Base { };
 *     Example: class Dog : public Animal { };
 *     Access specifier can be public, protected, or private.
 * 
 * Q4: What is IS-A relationship?
 * A4: IS-A means the derived class is a type of base class.
 *     Examples: Dog IS-A Animal, Car IS-A Vehicle
 *     If relationship isn't IS-A, don't use inheritance!
 * 
 * Q5: What members are inherited?
 * A5: Public and protected members are inherited.
 *     Private members exist in derived object but aren't directly accessible.
 *     Constructors, destructors, and friend functions are NOT inherited.
 * 
 * Q6: How to call base class constructor?
 * A6: Use initialization list in derived class constructor:
 *     Derived(params) : Base(params) { }
 *     Base constructor is called first, then derived constructor.
 * 
 * Q7: What is the difference between inheritance and composition?
 * A7: Inheritance (IS-A): Dog IS-A Animal
 *     Composition (HAS-A): Car HAS-A Engine
 *     Use inheritance for type relationships, composition for containment.
 * 
 * Q8: Can a derived class access private members of base class?
 * A8: No. Private members are not accessible in derived class.
 *     Use protected if you want derived class access.
 *     Private members exist in memory but can only be accessed via public/protected methods.
 * 
 * Q9: What is protected access specifier used for?
 * A9: Protected members are:
 *     - Accessible in the class itself (like private)
 *     - Accessible in derived classes (unlike private)
 *     - Not accessible outside class hierarchy (like private)
 *     Perfect for inheritance where base wants to share with derived but not public.
 * 
 * Q10: When should you NOT use inheritance?
 * A10: Don't use inheritance if:
 *      - Relationship isn't IS-A (use composition instead)
 *      - You just want code reuse (use composition or helper functions)
 *      - Derived class violates base class contract
 *      - Creates tight coupling (prefer loose coupling)
 */

/*
 * KEY POINTS TO REMEMBER:
 * 
 * 1. SYNTAX:
 *    class Derived : public Base { };
 * 
 * 2. WHAT'S INHERITED:
 *    - Public members → Yes (as public)
 *    - Protected members → Yes (as protected)
 *    - Private members → Exist but not accessible
 *    - Constructors → No
 *    - Destructor → No
 *    - Friend functions → No
 *    - Assignment operator → No (but can be inherited if default)
 * 
 * 3. CONSTRUCTOR CALLING:
 *    Derived(params) : Base(base_params) {
 *        // Derived initialization
 *    }
 *    Order: Base constructor → Derived constructor
 * 
 * 4. ACCESS SPECIFIERS IN INHERITANCE:
 *    - public inheritance: public → public, protected → protected
 *    - protected inheritance: public → protected, protected → protected
 *    - private inheritance: public → private, protected → private
 * 
 * 5. WHEN TO USE:
 *    ✓ IS-A relationship (Dog IS-A Animal)
 *    ✓ Code reuse with logical hierarchy
 *    ✓ Need polymorphism
 *    
 *    ✗ Just code reuse (use composition)
 *    ✗ HAS-A relationship (Car HAS-A Engine)
 *    ✗ No logical relationship
 * 
 * 6. BEST PRACTICES:
 *    - Prefer composition over inheritance (when in doubt)
 *    - Use public inheritance for IS-A
 *    - Make base destructor virtual (if using polymorphism)
 *    - Keep inheritance hierarchy shallow (max 3-4 levels)
 *    - Don't inherit just for code reuse
 */
