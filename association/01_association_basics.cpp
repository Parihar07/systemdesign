#include <iostream>
#include <string>

// =================================================================================
// Part 1: Association Basics (Uses-A Relationship)
// =================================================================================

/*
 * Association is a relationship where objects of one class are connected to
 * objects of another. It's a "uses-a" relationship, as opposed to inheritance's "is-a".
 *
 * In this example, a `Driver` uses a `Car`. The `Driver` is not a `Car`, and it
 * doesn't own the `Car`. The two objects are independent, but they interact.
 *
 * System-Level View:
 * - No Ownership: The `Driver` object does not manage the lifetime of the `Car` object.
 *   The `Car` is passed by reference, so no copy is made, and the `Driver` simply
 *   operates on the original `Car` object that exists elsewhere.
 * - Loose Coupling: This is a very flexible design. The same `Driver` can drive
 *   many different `Car` objects over its lifetime. The relationship is not fixed
 *   at compile time.
 */

// The Car class is a standalone entity.
class Car {
private:
    std::string m_model;

public:
    Car(const std::string& model) : m_model(model) {
        std::cout << "Car '" << m_model << "' created." << std::endl;
    }

    ~Car() {
        std::cout << "Car '" << m_model << "' destroyed." << std::endl;
    }

    void startEngine() const {
        std::cout << "Car '" << m_model << "' engine started." << std::endl;
    }

    std::string getModel() const {
        return m_model;
    }
};

// The Driver class is also a standalone entity.
class Driver {
private:
    std::string m_name;

public:
    Driver(const std::string& name) : m_name(name) {
        std::cout << "Driver '" << m_name << "' created." << std::endl;
    }

    ~Driver() {
        std::cout << "Driver '" << m_name << "' destroyed." << std::endl;
    }

    // This is the association: the drive function "uses" a Car object.
    // We pass by const reference because the driver doesn't own or modify the car's state,
    // just uses its functions.
    void drive(const Car& car) {
        std::cout << "Driver '" << m_name << "' is driving the '" << car.getModel() << "'." << std::endl;
        car.startEngine();
    }
};

int main() {
    std::cout << "--- Creating objects ---" << std::endl;
    Driver driver("Parihar");
    Car my_car("Toyota");

    std::cout << "\n--- Demonstrating Association ---" << std::endl;
    // The driver object interacts with (uses) the car object.
    driver.drive(my_car);

    std::cout << "\n--- Objects going out of scope ---" << std::endl;
    // The Car and Driver are destroyed independently.
    return 0;
}
