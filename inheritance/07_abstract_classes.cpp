#include <iostream>

// =================================================================================
// Part 7: Abstract Classes and Interfaces
// =================================================================================

/*
 * From a systems programming perspective, an abstract class is a blueprint for other classes.
 * It enforces a specific interface (a set of methods) that derived classes MUST implement.
 *
 * Key Characteristics:
 * 1.  Cannot be Instantiated: You cannot create an object of an abstract class.
 *     Attempting `Shape s;` will result in a compile-time error. This is because its
 *     vtable is incomplete.
 *
 * 2.  Pure Virtual Function (`= 0`): A function declared with `= 0`. This tells the compiler:
 *     a) This class is abstract.
 *     b) There is no implementation for this function in the base class.
 *     c) The vtable for this class will have a placeholder (often a null pointer) for this
 *        function's entry, making it an incomplete type.
 *
 * 3.  Interface Enforcement: Any concrete (non-abstract) class inheriting from an abstract
 *     class MUST override all of its pure virtual functions. If it fails to do so, it
 *     too becomes an abstract class.
 *
 * An "Interface" in C++ is typically an abstract class that has ONLY pure virtual functions
 * and no data members. It's the strictest form of an API contract.
 */

// --- Abstract Base Class ---
// 'Shape' is abstract because it contains at least one pure virtual function.
class Shape {
public:
    // This is a pure virtual function.
    // The `= 0` signifies that this class provides no implementation.
    // It establishes a contract that all concrete derived classes must follow.
    virtual void draw() const = 0;

    // Abstract classes can still have regular virtual functions with implementations.
    virtual void log() const {
        std::cout << "Logging a shape operation." << std::endl;
    }

    // And non-virtual functions.
    void static_info() const {
        std::cout << "This is a shape." << std::endl;
    }

    // It's good practice to have a virtual destructor in a base class.
    virtual ~Shape() {
        std::cout << "Shape destructor called." << std::endl;
    }
};

// --- Concrete Derived Classes ---
// 'Circle' is a concrete class because it inherits from Shape and
// provides an implementation for the pure virtual function `draw()`.
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle: O" << std::endl;
    }

    ~Circle() {
        std::cout << "Circle destructor called." << std::endl;
    }
};

// 'Rectangle' is another concrete class.
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle: []" << std::endl;
    }

    ~Rectangle() {
        std::cout << "Rectangle destructor called." << std::endl;
    }
};


int main() {
    std::cout << "--- Demonstrating Abstract Classes and Polymorphism ---" << std::endl;

    // Shape s; // COMPILE ERROR! Cannot instantiate an abstract class.

    Circle circle;
    Rectangle rectangle;

    // We can use a base class pointer to achieve polymorphism.
    // The vptr of the object on the heap will point to the correct vtable.
    Shape* shape1 = new Circle();
    Shape* shape2 = new Rectangle();

    std::cout << "\nCalling draw() via base class pointers:" << std::endl;
    shape1->draw(); // Dynamically dispatches to Circle::draw()
    shape2->draw(); // Dynamically dispatches to Rectangle::draw()

    std::cout << "\nCalling other inherited methods:" << std::endl;
    shape1->log();         // Calls Shape::log()
    shape1->static_info(); // Calls Shape::static_info() (statically bound)

    // Clean up memory. The virtual destructor ensures the correct
    // derived destructor is called first, preventing memory leaks.
    std::cout << "\n--- Deletion Process ---" << std::endl;
    delete shape1;
    delete shape2;

    return 0;
}
