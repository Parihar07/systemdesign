
/*
 * ===============================
 *   C++ Templates: Basics Example
 * ===============================
 *
 * What is a Template?
 * -------------------
 * Templates in C++ let you write generic, reusable code. They allow functions and classes to work with any data type, reducing code duplication and increasing type safety.
 *
 * Basic Syntax:
 *   // Function template
 *   template <typename T>
 *   T functionName(T arg1, T arg2) {
 *       // ...
 *   }
 *
 *   // Class template
 *   template <class T>
 *   class ClassName {
 *       // ...
 *   };
 *
 * Usage Examples:
 *   // Instantiate function template
 *   int sum = functionName<int>(a, b);
 *   double dsum = functionName<double>(x, y);
 *
 *   // Instantiate class template
 *   ClassName<int> obj(5);
 *   ClassName<double> dobj(3.14);
 *
 * Why use Templates?
 * ------------------
 * - Avoids code duplication for different types (int, double, etc.)
 * - Enables type-safe, generic programming
 *
 * This file demonstrates:
 * - A function template for addition
 * - A class template for a simple Box
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function template: adds two values of any type T
template <typename T>
T addnum(T t1, T t2)
{
    return t1 + t2;
}

// Class template: represents a box with a single dimension (length)
template <class T>
class Box
{
private:
    T length;

public:
    Box(T len) : length(len) {};
    T area() { return length * length; }
};

int main()
{
    cout << "Hello templates basics..\n";
    // Using function template with int
    cout << "adding 3 + 4 - " << addnum(3, 4) << endl;
    // Using function template with double
    cout << "adding 3.7 + 4.8 - " << addnum(3.7, 4.8) << endl;

    // Using class template with int
    Box<int> box(6);
    cout << "Area of Box : " << box.area() << endl;

    return 0;
}