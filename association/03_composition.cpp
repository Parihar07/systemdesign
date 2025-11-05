#include <iostream>
#include <string>
#include <memory> // Required for std::unique_ptr

// =================================================================================
// Part 3: Composition (Owned "Has-A" Relationship)
// =================================================================================

/*
 * Composition is a "has-a" relationship where the "part" CANNOT exist independently
 * of the "whole". The whole has exclusive ownership of the part.
 *
 * Example: A Car has an Engine. If the Car is destroyed, the Engine is also destroyed.
 * The Engine cannot exist without the Car.
 *
 * System-Level View:
 * - Exclusive Ownership: Only the Car owns the Engine. No other part of the system
 *   can hold a reference to it.
 * - Implementation: Two common approaches:
 *   1. Direct Member Variable: The Engine object is part of the Car's memory layout.
 *      Created when the Car is created, destroyed when the Car is destroyed.
 *   2. std::unique_ptr: For dynamic allocation. The unique_ptr ensures exclusive
 *      ownership and automatic cleanup. Cannot be copied, only moved.
 * - Memory: With a direct member, the Engine lives inside the Car's memory block.
 *   With unique_ptr, the Engine is on the heap, but the Car exclusively controls it.
 */

// --- Example 1: Composition with Direct Member Variable ---

class Engine {
private:
    int m_horsepower;
public:
    Engine(int hp) : m_horsepower(hp) {
        std::cout << "Engine (" << m_horsepower << " HP) created." << std::endl;
    }
    ~Engine() {
        std::cout << "Engine (" << m_horsepower << " HP) destroyed." << std::endl;
    }
    void start() const {
        std::cout << "Engine with " << m_horsepower << " HP started." << std::endl;
    }
};

class Car {
private:
    std::string m_model;
    Engine m_engine; // Direct member: Engine is part of Car's memory

public:
    // The Engine is constructed as part of the Car's construction
    Car(const std::string& model, int hp) : m_model(model), m_engine(hp) {
        std::cout << "Car '" << m_model << "' created." << std::endl;
    }
    ~Car() {
        std::cout << "Car '" << m_model << "' destroyed." << std::endl;
        // The Engine destructor is called automatically after this
    }
    void drive() const {
        std::cout << "Driving " << m_model << "..." << std::endl;
        m_engine.start();
    }
};

// --- Example 2: Composition with std::unique_ptr ---

class Battery {
private:
    int m_capacity;
public:
    Battery(int capacity) : m_capacity(capacity) {
        std::cout << "Battery (" << m_capacity << " mAh) created on heap." << std::endl;
    }
    ~Battery() {
        std::cout << "Battery (" << m_capacity << " mAh) destroyed." << std::endl;
    }
    void charge() const {
        std::cout << "Battery (" << m_capacity << " mAh) charging..." << std::endl;
    }
};

class Laptop {
private:
    std::string m_brand;
    std::unique_ptr<Battery> m_battery; // Exclusive ownership via unique_ptr

public:
    Laptop(const std::string& brand, int battery_capacity) 
        : m_brand(brand), m_battery(std::make_unique<Battery>(battery_capacity)) {
        std::cout << "Laptop '" << m_brand << "' created." << std::endl;
    }
    ~Laptop() {
        std::cout << "Laptop '" << m_brand << "' destroyed." << std::endl;
        // The unique_ptr automatically deletes the Battery
    }
    void use() const {
        std::cout << "Using " << m_brand << " laptop..." << std::endl;
        m_battery->charge();
    }
};

int main() {
    std::cout << "=== Example 1: Composition with Direct Member ===\n" << std::endl;
    {
        Car my_car("Tesla Model S", 670);
        my_car.drive();
        std::cout << "\n--- Car going out of scope ---" << std::endl;
    } // Car is destroyed, Engine is destroyed automatically with it

    std::cout << "\n\n=== Example 2: Composition with unique_ptr ===\n" << std::endl;
    {
        Laptop my_laptop("MacBook Pro", 5000);
        my_laptop.use();
        std::cout << "\n--- Laptop going out of scope ---" << std::endl;
    } // Laptop is destroyed, Battery is destroyed automatically via unique_ptr

    std::cout << "\n--- End of main ---" << std::endl;
    return 0;
}
