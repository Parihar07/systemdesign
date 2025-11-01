#include <iostream>
#include <string>
using namespace std;

/*
 * PART 3: ACCESS CONTROL IN INHERITANCE
 * ======================================
 * Understanding how access specifiers work in inheritance:
 * - public inheritance (IS-A)
 * - protected inheritance (rare)
 * - private inheritance (HAS-A alternative)
 */

// ============================================================================
// EXAMPLE 1: PUBLIC INHERITANCE (Most Common - IS-A Relationship)
// ============================================================================

class Vehicle {
private:
    string engineNumber;  // Only Vehicle can access
    
protected:
    string model;         // Vehicle and derived classes can access
    
public:
    string brand;         // Everyone can access
    
    Vehicle(string b, string m, string e) : brand(b), model(m), engineNumber(e) {}
    
    void displayPublic() {
        cout << "Public method in Vehicle" << endl;
    }
    
protected:
    void displayProtected() {
        cout << "Protected method in Vehicle" << endl;
    }
    
private:
    void displayPrivate() {
        cout << "Private method in Vehicle" << endl;
    }
};

// PUBLIC INHERITANCE: class Derived : public Base
class Car : public Vehicle {
public:
    Car(string b, string m, string e) : Vehicle(b, m, e) {}
    
    void showAccess() {
        cout << "\n=== Car (public inheritance) ===" << endl;
        
        // ✅ Can access public members
        cout << "Brand (public): " << brand << endl;
        
        // ✅ Can access protected members
        cout << "Model (protected): " << model << endl;
        
        // ❌ Cannot access private members
        // cout << engineNumber;  // ERROR!
        
        // ✅ Can call public methods
        displayPublic();
        
        // ✅ Can call protected methods
        displayProtected();
        
        // ❌ Cannot call private methods
        // displayPrivate();  // ERROR!
    }
};

void testPublicInheritance() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  PUBLIC INHERITANCE (IS-A)             ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    Car myCar("Toyota", "Camry", "ENG123");
    
    // Outside world can access:
    cout << "\nFrom outside (main):" << endl;
    cout << "Brand: " << myCar.brand << endl;  // ✅ public remains public
    myCar.displayPublic();                      // ✅ public method accessible
    
    // cout << myCar.model;          // ❌ protected is NOT accessible outside
    // myCar.displayProtected();     // ❌ protected method NOT accessible
    
    myCar.showAccess();
}

// ============================================================================
// EXAMPLE 2: PROTECTED INHERITANCE (Rare - Used for Implementation Hiding)
// ============================================================================

class Engine {
public:
    int horsepower;
    
    Engine(int hp) : horsepower(hp) {}
    
    void start() {
        cout << "Engine started!" << endl;
    }
    
protected:
    void maintenance() {
        cout << "Engine maintenance" << endl;
    }
};

// PROTECTED INHERITANCE: class Derived : protected Base
// All public members of Base become protected in Derived
class Motorcycle : protected Engine {
private:
    string type;
    
public:
    Motorcycle(string t, int hp) : Engine(hp), type(t) {}
    
    void showDetails() {
        cout << "\n=== Motorcycle (protected inheritance) ===" << endl;
        cout << "Type: " << type << endl;
        
        // ✅ Can access base public members (now protected in Motorcycle)
        cout << "Horsepower: " << horsepower << endl;
        start();  // ✅ Can call
        
        // ✅ Can access base protected members
        maintenance();
    }
    
    // Expose specific base functionality if needed
    void startBike() {
        start();  // Wrapper to expose Engine's start()
    }
};

void testProtectedInheritance() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  PROTECTED INHERITANCE                 ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    Motorcycle bike("Sports", 150);
    
    // ❌ Cannot access Engine's public members from outside
    // cout << bike.horsepower;  // ERROR! Now protected
    // bike.start();             // ERROR! Now protected
    
    // ✅ Can only call Motorcycle's own public methods
    bike.showDetails();
    bike.startBike();  // Wrapper method
    
    cout << "\n⚠️  Engine's public members became protected in Motorcycle!" << endl;
}

// ============================================================================
// EXAMPLE 3: PRIVATE INHERITANCE (Alternative to Composition - HAS-A)
// ============================================================================

class GPS {
public:
    string location;
    
    GPS(string loc) : location(loc) {}
    
    void showLocation() {
        cout << "Current location: " << location << endl;
    }
    
    void updateLocation(string newLoc) {
        location = newLoc;
        cout << "Location updated to: " << location << endl;
    }
};

// PRIVATE INHERITANCE: class Derived : private Base
// All public/protected members of Base become private in Derived
class SmartPhone : private GPS {
private:
    string phoneModel;
    
public:
    SmartPhone(string model, string loc) : GPS(loc), phoneModel(model) {}
    
    void displayPhone() {
        cout << "\n=== SmartPhone (private inheritance) ===" << endl;
        cout << "Phone Model: " << phoneModel << endl;
        
        // ✅ Can access GPS members internally
        showLocation();
    }
    
    // Expose only specific GPS functionality through wrapper
    void checkLocation() {
        showLocation();  // Internal use of GPS
    }
    
    void setLocation(string newLoc) {
        updateLocation(newLoc);  // Internal use of GPS
    }
};

void testPrivateInheritance() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  PRIVATE INHERITANCE (HAS-A)           ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    SmartPhone phone("iPhone 15", "New York");
    
    // ❌ Cannot access GPS members from outside
    // cout << phone.location;       // ERROR! Now private
    // phone.showLocation();         // ERROR! Now private
    // phone.updateLocation("LA");   // ERROR! Now private
    
    // ✅ Can only use SmartPhone's public interface
    phone.displayPhone();
    phone.checkLocation();
    phone.setLocation("Los Angeles");
    
    cout << "\n⚠️  GPS is completely hidden! Only SmartPhone's interface visible." << endl;
    cout << "💡 This is HAS-A relationship (SmartPhone HAS-A GPS)" << endl;
}

// ============================================================================
// EXAMPLE 4: ACCESS SPECIFIER TRANSFORMATION TABLE
// ============================================================================

void showTransformationTable() {
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║       ACCESS SPECIFIER TRANSFORMATION TABLE                    ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Base Class    │  public      │  protected   │  private        ║" << endl;
    cout << "║  Member        │  inheritance │  inheritance │  inheritance    ║" << endl;
    cout << "║  ──────────────┼──────────────┼──────────────┼──────────────   ║" << endl;
    cout << "║  public        │  public      │  protected   │  private        ║" << endl;
    cout << "║  protected     │  protected   │  protected   │  private        ║" << endl;
    cout << "║  private       │  NOT ACCESS  │  NOT ACCESS  │  NOT ACCESS     ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n📝 Key Rules:" << endl;
    cout << "1. Private members are NEVER accessible in derived class" << endl;
    cout << "2. Public inheritance: Public stays public, Protected stays protected" << endl;
    cout << "3. Protected inheritance: Public becomes protected" << endl;
    cout << "4. Private inheritance: Everything becomes private" << endl;
}

// ============================================================================
// EXAMPLE 5: WHEN TO USE EACH TYPE?
// ============================================================================

void whenToUseEach() {
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              WHEN TO USE EACH TYPE?                            ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  1. PUBLIC INHERITANCE (99% of cases)                          ║" << endl;
    cout << "║     Use when: IS-A relationship                                ║" << endl;
    cout << "║     Example: Dog IS-A Animal, Car IS-A Vehicle                 ║" << endl;
    cout << "║     Result: Derived class can be used as Base class            ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  2. PROTECTED INHERITANCE (Rare - <1%)                         ║" << endl;
    cout << "║     Use when: Want to hide implementation from outside         ║" << endl;
    cout << "║              but allow further derivation                      ║" << endl;
    cout << "║     Example: Internal framework classes                        ║" << endl;
    cout << "║     Result: Base interface hidden from users                   ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  3. PRIVATE INHERITANCE (Alternative to composition)           ║" << endl;
    cout << "║     Use when: HAS-A relationship with need for base access     ║" << endl;
    cout << "║     Example: Stack HAS-A Vector (implementation detail)        ║" << endl;
    cout << "║     Result: Complete hiding of base class interface            ║" << endl;
    cout << "║     Better Alternative: Use composition (member object)        ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
}

// ============================================================================
// EXAMPLE 6: PRIVATE INHERITANCE vs COMPOSITION
// ============================================================================

// Method 1: Private Inheritance
class Stack_PrivateInheritance : private std::vector<int> {
public:
    void push(int val) {
        push_back(val);  // Use vector's method internally
    }
    
    void pop() {
        if (!empty()) pop_back();
    }
    
    int top() {
        return back();
    }
    
    bool isEmpty() {
        return empty();
    }
};

// Method 2: Composition (PREFERRED!)
class Stack_Composition {
private:
    std::vector<int> data;  // HAS-A vector (composition)
    
public:
    void push(int val) {
        data.push_back(val);
    }
    
    void pop() {
        if (!data.empty()) data.pop_back();
    }
    
    int top() {
        return data.back();
    }
    
    bool isEmpty() {
        return data.empty();
    }
};

void testPrivateInheritanceVsComposition() {
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║       PRIVATE INHERITANCE vs COMPOSITION                       ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n📌 Both achieve HAS-A relationship:" << endl;
    cout << "   Stack HAS-A vector for storage" << endl;
    
    cout << "\n✅ Composition is PREFERRED because:" << endl;
    cout << "   1. More explicit (clearly shows HAS-A)" << endl;
    cout << "   2. Less coupling" << endl;
    cout << "   3. Can have multiple data members" << endl;
    cout << "   4. Easier to understand and maintain" << endl;
    
    cout << "\n⚠️  Private inheritance should be rare:" << endl;
    cout << "   - Only when you need to override virtual functions" << endl;
    cout << "   - Or access protected members of base class" << endl;
}

// ============================================================================
// MAIN - Run All Examples
// ============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║           ACCESS CONTROL IN INHERITANCE                        ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    // Example 1: Public Inheritance (IS-A)
    testPublicInheritance();
    
    // Example 2: Protected Inheritance
    testProtectedInheritance();
    
    // Example 3: Private Inheritance (HAS-A)
    testPrivateInheritance();
    
    // Example 4: Transformation Table
    showTransformationTable();
    
    // Example 5: When to use each
    whenToUseEach();
    
    // Example 6: Private Inheritance vs Composition
    testPrivateInheritanceVsComposition();
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    INTERVIEW TIPS                              ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: Which inheritance type should I use?                       ║" << endl;
    cout << "║  A: 99% of the time: PUBLIC inheritance (IS-A)                 ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: When to use private inheritance?                           ║" << endl;
    cout << "║  A: Almost never! Prefer composition instead.                  ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  Q: What's the difference between private inheritance          ║" << endl;
    cout << "║     and composition?                                           ║" << endl;
    cout << "║  A: Both implement HAS-A, but composition is clearer           ║" << endl;
    cout << "║     and preferred. Private inheritance only when you           ║" << endl;
    cout << "║     need to override virtual functions.                        ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

/*
 * SUMMARY - Access Control in Inheritance:
 * =========================================
 * 
 * 1. PUBLIC INHERITANCE: class Derived : public Base
 *    - Most common (99%)
 *    - IS-A relationship
 *    - Public stays public, Protected stays protected
 *    - Example: Dog IS-A Animal
 * 
 * 2. PROTECTED INHERITANCE: class Derived : protected Base
 *    - Rare (<1%)
 *    - Public becomes protected
 *    - Hides base interface from outside
 *    - Allows further derivation
 * 
 * 3. PRIVATE INHERITANCE: class Derived : private Base
 *    - Alternative to composition (HAS-A)
 *    - Everything becomes private
 *    - Complete hiding of base class
 *    - Prefer composition instead!
 * 
 * TRANSFORMATION RULES:
 * - Private members: NEVER accessible in derived class
 * - Public inheritance: Public→Public, Protected→Protected
 * - Protected inheritance: Public→Protected, Protected→Protected
 * - Private inheritance: Public→Private, Protected→Private
 * 
 * BEST PRACTICE:
 * - Use public inheritance for IS-A relationships
 * - Use composition (not private inheritance) for HAS-A
 * - Protected inheritance is rarely needed
 */
