# SOLID Principles - Interview Preparation Guide

## Quick Reference Card

### The Five Principles

1. **S**RP - Single Responsibility Principle
2. **O**CP - Open/Closed Principle  
3. **L**SP - Liskov Substitution Principle
4. **I**SP - Interface Segregation Principle
5. **D**IP - Dependency Inversion Principle

## Deep Dive

### 1. Single Responsibility Principle (SRP)

**Definition**: A class should have one, and only one, reason to change.

**Key Questions**:
- What is this class responsible for?
- How many reasons could cause this class to change?
- Can I describe this class in one sentence without using "and"?

**Interview Examples**:

❌ **Bad**:
```cpp
class Employee {
    void calculatePay();     // Reason 1: Business logic changes
    void saveToDatabase();   // Reason 2: Database changes
    void sendEmail();        // Reason 3: Email service changes
    void generateReport();   // Reason 4: Report format changes
};
```

✅ **Good**:
```cpp
class Employee { /* Data only */ };
class SalaryCalculator { void calculatePay(); };
class EmployeeRepository { void save(); };
class EmailService { void send(); };
class ReportGenerator { void generate(); };
```

**Red Flags**:
- Class names with "And", "Manager", "Handler", "Utils"
- Large classes (>300 lines)
- Many public methods
- Mixed concerns (UI + business logic + data access)

### 2. Open/Closed Principle (OCP)

**Definition**: Software entities should be open for extension but closed for modification.

**Key Questions**:
- Can I add new features without changing existing code?
- Am I using switch/if-else statements that would need modification for new types?
- Are my classes designed for inheritance or composition?

**Interview Examples**:

❌ **Bad**:
```cpp
double calculateArea(Shape shape) {
    switch(shape.type) {
        case CIRCLE: return PI * r * r;
        case RECTANGLE: return w * h;
        // Adding triangle requires modifying this function!
    }
}
```

✅ **Good**:
```cpp
class Shape {
    virtual double area() = 0;
};

class Circle : public Shape {
    double area() override { return PI * r * r; }
};

class Rectangle : public Shape {
    double area() override { return w * h; }
};

// New shapes don't modify existing code
class Triangle : public Shape {
    double area() override { return 0.5 * b * h; }
};
```

**Design Patterns That Support OCP**:
- Strategy Pattern
- Template Method Pattern
- Decorator Pattern
- Factory Pattern

### 3. Liskov Substitution Principle (LSP)

**Definition**: Objects of a superclass should be replaceable with objects of subclass without breaking the application.

**Key Questions**:
- Can I substitute a derived class for the base class?
- Does the subclass honor all contracts of the base class?
- Does the subclass throw exceptions that the base class doesn't?
- Does the subclass weaken postconditions or strengthen preconditions?

**Interview Examples**:

❌ **Bad** (Rectangle-Square Problem):
```cpp
class Rectangle {
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
};

class Square : public Rectangle {
    void setWidth(int w) override { 
        width = w; 
        height = w;  // Violates LSP!
    }
};

void process(Rectangle& r) {
    r.setWidth(5);
    r.setHeight(4);
    assert(r.area() == 20);  // Fails for Square!
}
```

✅ **Good**:
```cpp
class Shape {
    virtual int area() = 0;
};

class Rectangle : public Shape {
    void setWidth(int w);
    void setHeight(int h);
    int area() override { return w * h; }
};

class Square : public Shape {  // NOT derived from Rectangle
    void setSide(int s);
    int area() override { return s * s; }
};
```

**LSP Violations to Watch For**:
- Throwing new exceptions in overridden methods
- Strengthening preconditions (requiring more than parent)
- Weakening postconditions (guaranteeing less than parent)
- Changing method semantics
- Empty implementations or no-op overrides

### 4. Interface Segregation Principle (ISP)

**Definition**: Clients should not be forced to depend on interfaces they don't use.

**Key Questions**:
- Is my interface forcing clients to implement methods they don't need?
- Can I split this interface into smaller, focused interfaces?
- Are clients using only a subset of the interface?

**Interview Examples**:

❌ **Bad** (Fat Interface):
```cpp
class Worker {
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
    virtual void getSalary() = 0;
};

class Robot : public Worker {
    void work() override { /* OK */ }
    void eat() override { throw "Robots don't eat!"; }  // Forced to implement!
    void sleep() override { throw "Robots don't sleep!"; }
    void getSalary() override { throw "Robots don't get paid!"; }
};
```

✅ **Good** (Segregated Interfaces):
```cpp
class Workable { virtual void work() = 0; };
class Eatable { virtual void eat() = 0; };
class Sleepable { virtual void sleep() = 0; };
class Payable { virtual void getSalary() = 0; };

class Human : public Workable, Eatable, Sleepable, Payable {
    // Implements all
};

class Robot : public Workable {
    // Only implements what it needs
};
```

**Benefits**:
- Reduces coupling
- Increases cohesion
- Makes testing easier
- Prevents interface pollution

### 5. Dependency Inversion Principle (DIP)

**Definition**: 
- High-level modules should not depend on low-level modules. Both should depend on abstractions.
- Abstractions should not depend on details. Details should depend on abstractions.

**Key Questions**:
- Are my high-level classes depending on concrete low-level classes?
- Can I swap implementations without changing clients?
- Am I using dependency injection?
- Are my dependencies abstractions (interfaces) or concretions (classes)?

**Interview Examples**:

❌ **Bad** (Tight Coupling):
```cpp
class MySQLDatabase { /* ... */ };

class UserService {
    MySQLDatabase db;  // Tightly coupled to MySQL!
    
    void saveUser(User user) {
        db.save(user);  // Can't switch to PostgreSQL or MongoDB
    }
};
```

✅ **Good** (Loose Coupling via Abstraction):
```cpp
class IDatabase {
    virtual void save(User user) = 0;
};

class MySQLDatabase : public IDatabase { /* ... */ };
class PostgreSQLDatabase : public IDatabase { /* ... */ };
class MongoDBDatabase : public IDatabase { /* ... */ };

class UserService {
    IDatabase* db;  // Depends on abstraction!
    
    UserService(IDatabase* database) : db(database) {}  // Dependency Injection
    
    void saveUser(User user) {
        db->save(user);  // Works with any database!
    }
};

// Usage
MySQLDatabase mysql;
UserService service(&mysql);  // Inject dependency
```

**Dependency Injection Types**:
1. **Constructor Injection**: Pass via constructor (preferred)
2. **Setter Injection**: Pass via setter method
3. **Interface Injection**: Pass via interface method

## Common Interview Questions

### Question 1: "Explain SOLID principles"
**Answer Structure**:
1. Give definition of each principle
2. Provide a concrete example for each
3. Explain benefits (maintainability, testability, extensibility)
4. Mention real-world scenarios where you've applied them

### Question 2: "How do SOLID principles relate to each other?"
**Answer**:
- **SRP** and **ISP** both promote focused, cohesive components
- **OCP** is enabled by **LSP** and **DIP**
- **DIP** makes **OCP** possible through dependency injection
- **LSP** ensures **OCP** works correctly with inheritance
- All principles work together to create maintainable code

### Question 3: "Design a [system] following SOLID principles"
**Approach**:
1. Identify entities and their single responsibilities (SRP)
2. Define abstractions/interfaces (DIP, ISP)
3. Design for extension (OCP)
4. Ensure proper inheritance (LSP)
5. Inject dependencies (DIP)

Example: "Design a payment processing system"
```cpp
// Abstractions (DIP)
class IPaymentProcessor { virtual bool process(double amount) = 0; };
class INotifier { virtual void notify(string message) = 0; };
class ILogger { virtual void log(string message) = 0; };

// Implementations (OCP - can add new processors)
class StripeProcessor : public IPaymentProcessor { /* ... */ };
class PayPalProcessor : public IPaymentProcessor { /* ... */ };

// High-level service (SRP, DIP)
class PaymentService {
    IPaymentProcessor* processor;
    INotifier* notifier;
    ILogger* logger;
    
public:
    PaymentService(IPaymentProcessor* p, INotifier* n, ILogger* l)
        : processor(p), notifier(n), logger(l) {}  // DI
    
    bool processPayment(double amount) {
        logger->log("Processing payment");
        bool success = processor->process(amount);
        if (success) notifier->notify("Payment successful");
        return success;
    }
};
```

### Question 4: "When might you violate SOLID principles?"
**Honest Answer**:
- **Pragmatism**: Small, simple projects might not need full SOLID
- **Performance**: Sometimes abstraction adds overhead
- **Prototyping**: Quick prototypes can defer SOLID
- **Legacy Code**: Incremental refactoring may temporarily violate SOLID

**Key**: Know the principles, know when to apply them, and justify decisions.

## Code Smell Detection

### Violates SRP:
- "God" classes with too many responsibilities
- Classes with names like "Manager", "Handler", "Utils"
- Changes in one area break unrelated functionality

### Violates OCP:
- Frequent modifications to existing classes for new features
- Switch statements on type codes
- Cannot extend without modifying source

### Violates LSP:
- Subclass throws exceptions parent doesn't
- Subclass has empty/no-op implementations
- Cannot substitute child for parent

### Violates ISP:
- Interfaces with many methods
- Clients implementing methods they don't use
- Empty or stub implementations

### Violates DIP:
- High-level modules import low-level modules
- Hard to test due to concrete dependencies
- Cannot swap implementations

## Design Patterns and SOLID

| Pattern | SOLID Principles |
|---------|------------------|
| Strategy | OCP, DIP |
| Factory | OCP, DIP |
| Decorator | OCP, LSP |
| Adapter | LSP, ISP |
| Observer | OCP, DIP |
| Template Method | OCP, LSP |
| Dependency Injection | DIP |
| Repository | SRP, DIP |
| Service Layer | SRP, DIP |

## Practice Problems

1. **Refactor this code** to follow SRP:
   - Given a class that does validation, saves to DB, and sends emails
   - Split into separate classes

2. **Extend without modifying**: 
   - Add a new shape to a shape calculator
   - Add a new payment method to checkout

3. **Fix LSP violation**:
   - Given Rectangle/Square problem
   - Redesign hierarchy

4. **Segregate interfaces**:
   - Given a fat "Printer" interface
   - Split into focused interfaces

5. **Apply DIP**:
   - Given tightly coupled service classes
   - Introduce abstractions and dependency injection

## Tips for Technical Interviews

1. **Start with principles**: Mention which SOLID principle you're applying
2. **Draw diagrams**: UML class diagrams help visualize relationships
3. **Explain trade-offs**: No solution is perfect; discuss pros/cons
4. **Use real examples**: Reference your actual work experience
5. **Think out loud**: Explain your thought process
6. **Ask clarifying questions**: Requirements affect design decisions

## Key Takeaways

✅ **SRP**: One class, one job, one reason to change
✅ **OCP**: Extend behavior without modifying existing code  
✅ **LSP**: Subtypes must be substitutable for base types
✅ **ISP**: Many small interfaces > one large interface
✅ **DIP**: Depend on abstractions, not concretions

**Remember**: SOLID principles are **guidelines**, not strict rules. Apply them pragmatically based on context, but always understand the "why" behind each principle.
