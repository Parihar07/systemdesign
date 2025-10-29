# C++ Access Modifiers & Access Control

Complete guide to understanding access modifiers in C++ for system design and interviews.

---

## Table of Contents
1. [Access Specifiers Overview](#access-specifiers-overview)
2. [Access vs Visibility](#access-vs-visibility)
3. [Compilation Phases](#compilation-phases)
4. [Friend Mechanism](#friend-mechanism)
5. [Inheritance & Access Control](#inheritance--access-control)
6. [Protected: The Tricky One](#protected-the-tricky-one)
7. [Code Examples](#code-examples)
8. [Common Interview Questions](#common-interview-questions)
9. [Best Practices](#best-practices)

---

## Access Specifiers Overview

C++ provides three access specifiers to control member accessibility:

| Specifier | Accessible From | Use Case |
|-----------|----------------|----------|
| `public` | Anywhere the class is visible | Public API, interface |
| `protected` | Class itself, friends, derived classes | Inheritance hierarchy |
| `private` | Class itself and friends only | Implementation details, data hiding |

### Default Access

```cpp
class MyClass {
    int x;  // private by default
};

struct MyStruct {
    int x;  // public by default
};
```

**Rule**: `class` → private default, `struct` → public default

---

## Access vs Visibility

### Key Distinction

| Concept | What It Controls | When Checked | Phase |
|---------|-----------------|--------------|-------|
| **Visibility** | Can compiler see the name? | Name lookup | Preprocessing + Early compilation |
| **Access** | Can you use this member? | Semantic analysis | Compilation (after name lookup) |

### Example: Visibility Problem

```cpp
// main.cpp (no #include)
int main() {
    Box b;  // ❌ ERROR: 'Box' was not declared
            // Problem: VISIBILITY (compiler can't see Box)
}
```

**Fix**: `#include "box.h"` makes `Box` visible

### Example: Access Problem

```cpp
// main.cpp
#include "box.h"  // Box is now VISIBLE

int main() {
    Box b;
    b.len = 5;  // ❌ ERROR: 'int Box::len' is private
                // Problem: ACCESS (visible but not accessible)
}
```

**Fix**: Use public interface like `setLength()`

---

## Compilation Phases

```
┌─────────────────────────────────────────────┐
│ 1. PREPROCESSING                            │
│    - #include expands headers               │
│    - Makes names VISIBLE                    │
└─────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────┐
│ 2. COMPILATION (per translation unit)       │
│    ┌───────────────────────────────────┐    │
│    │ Name Lookup (Visibility Check)    │    │
│    │ "Does this name exist?"          │    │
│    └───────────────────────────────────┘    │
│              ↓                              │
│    ┌───────────────────────────────────┐    │
│    │ Semantic Analysis (Access Check)  │    │
│    │ "Am I allowed to use this?"      │    │
│    └───────────────────────────────────┘    │
│              ↓                              │
│    Code generation                          │
└─────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────┐
│ 3. LINKING                                  │
│    - Resolves symbols                       │
│    - No access checking (already done)      │
└─────────────────────────────────────────────┘
```

---

## Friend Mechanism

### Important: Friend is NOT an Access Specifier

`friend` is a **separate access-granting mechanism**, not an access specifier.

```cpp
class Box {
private:
    int secret = 42;
    
    // friend grants external access to private members
    friend void printSecret(const Box& b);
    friend class BoxPrinter;
};

void printSecret(const Box& b) {
    std::cout << b.secret;  // ✅ OK: friend can access private
}
```

### Key Properties of Friend

1. **Not inherited**: Child classes don't inherit friendships
2. **Not transitive**: If A is friend of B, and B is friend of C, A is NOT friend of C
3. **One-way**: Friendship is not mutual
4. **Grants full access**: Can access both private and protected members

### When to Use Friend

- Operator overloading (`operator<<`, `operator+`)
- Tightly coupled classes (e.g., Iterator and Container)
- Factory functions that need to call private constructors

---

## Inheritance & Access Control

### Inheritance Specifiers

```cpp
class Base {
public:    int pub;
protected: int prot;
private:   int priv;
};

class D1 : public Base {
    // pub    → public
    // prot   → protected
    // priv   → not accessible
};

class D2 : protected Base {
    // pub    → protected
    // prot   → protected
    // priv   → not accessible
};

class D3 : private Base {
    // pub    → private
    // prot   → private
    // priv   → not accessible
};
```

### Re-exposing Members

```cpp
class Derived : private Base {
public:
    using Base::pub;  // Make Base::pub public again in Derived
};
```

### Protected Access Rule (Tricky!)

Derived class can access protected members **only through Derived objects**, not Base objects:

```cpp
class Base {
protected:
    int x = 0;
};

class Derived : public Base {
    void ok(Derived& d) {
        d.x = 1;  // ✅ OK: d is Derived
    }
    
    void bad(Base& b) {
        // b.x = 2;  // ❌ ERROR: b might not be Derived
    }
};
```

---

## Protected: The Tricky One

### What is Protected?

`protected` is the **middle-ground** access specifier:
- **More restrictive than** `public`: External code cannot access
- **Less restrictive than** `private`: Derived classes can access

```cpp
class Base {
protected:
    int protectedData = 42;
    void protectedMethod() {}
};
```

**Who can access protected members?**
1. ✅ The class itself (Base)
2. ✅ Friends of the class
3. ✅ Derived classes (with important restrictions!)
4. ❌ External code (like main())

### The Critical Rule: "Through What Object?"

This is the **#1 interview gotcha** with protected:

**Rule**: You can only access a base class's protected member **through an object of your own derived type** (or further derived), NOT through a Base reference/pointer.

```cpp
class Base {
protected:
    int x = 10;
};

class Derived : public Base {
public:
    void test1() {
        x = 20;              // ✅ OK: accessing own inherited x
        this->x = 30;        // ✅ OK: accessing through 'this'
    }
    
    void test2(Derived& d) {
        d.x = 40;            // ✅ OK: d is a Derived object
    }
    
    void test3(Base& b) {
        b.x = 50;            // ❌ ERROR: b is a Base reference!
                             // Even though Derived inherits from Base,
                             // you can't access protected through Base&
    }
    
    void test4(Derived* d) {
        d->x = 60;           // ✅ OK: d is Derived*
    }
    
    void test5(Base* b) {
        b->x = 70;           // ❌ ERROR: b is Base*
    }
};
```

**See**: `example2/a.cpp` for full working code

### Why This Rule Exists?

**To prevent cross-hierarchy violations:**

```cpp
class Base {
protected:
    void dangerousOperation() {}
};

class SafeDerived : public Base {
    // Properly manages dangerousOperation
};

class EvilDerived : public Base {
public:
    void hackOtherDerived(Base& b) {
        // If this were allowed, EvilDerived could call
        // dangerousOperation on a SafeDerived object!
        // b.dangerousOperation();  // ❌ Blocked by C++
    }
};
```

This rule prevents one derived class from manipulating another derived class's protected members through a base reference.

### Real-World Example: Bank Accounts

**See**: `example3/realworld.cpp` for full implementation

```cpp
class BankAccount {
protected:
    double balance = 1000.0;
    void setBalance(double b) { balance = b; }
};

class CheckingAccount : public BankAccount {
public:
    void deposit(double amount) {
        balance += amount;  // ✅ OK: accessing own balance
    }
    
    void transferFrom(CheckingAccount& other, double amount) {
        other.balance -= amount;  // ✅ OK: other is CheckingAccount
        this->balance += amount;
    }
    
    void dangerousHack(BankAccount& anyAccount) {
        // anyAccount.balance = 0;  // ❌ ERROR: can't access through Base&
        // Good! We shouldn't be able to mess with arbitrary accounts
    }
};

class SavingsAccount : public BankAccount {
    // Has different rules for withdrawals
};
```

**Why it matters**: If `CheckingAccount` could access `BankAccount`'s protected members through a `BankAccount&`, it could bypass `SavingsAccount`'s withdrawal rules!

### Protected with Different Inheritance Types

**See**: `example4/inheritancetype.cpp` for full implementation

```cpp
class Base {
protected:
    int prot = 10;
};

// 1. Public Inheritance (most common)
class D1 : public Base {
    // prot stays protected in D1
    void test() { prot = 20; }  // ✅ OK
};

// 2. Protected Inheritance (rare)
class D2 : protected Base {
    // prot stays protected in D2
    void test() { prot = 30; }  // ✅ OK
};

// 3. Private Inheritance
class D3 : private Base {
    // prot becomes private in D3
    void test() { prot = 40; }  // ✅ OK
};

// Further inheritance:
class D1Child : public D1 {
    void test() { prot = 50; }  // ✅ OK: still protected
};

class D3Child : public D3 {
    void test() { 
        // prot = 60;  // ❌ ERROR: became private in D3
    }
};
```

### Protected vs Private: Decision Guide

| Use Case | Choose |
|----------|--------|
| Want derived classes to customize behavior | `protected` |
| Pure implementation detail, no inheritance needed | `private` |
| Template Method pattern (customizable steps) | `protected` virtual |
| External API should never touch | `private` |
| Data that defines class invariants | `private` with protected getters/setters |

### Common Protected Pitfalls

#### Pitfall 1: Protected Data = Tight Coupling

```cpp
// ❌ Bad: Exposes internal state
class BadBase {
protected:
    std::vector<int> data;  // Derived classes directly manipulate
};

// ✅ Better: Protected interface, private data
class GoodBase {
private:
    std::vector<int> data;  // Hidden
protected:
    void addItem(int item) { data.push_back(item); }  // Controlled access
    int getItem(size_t idx) const { return data[idx]; }
};
```

#### Pitfall 2: Protected Destructor Usage

```cpp
class Interface {
public:
    virtual void doWork() = 0;
protected:
    ~Interface() = default;  // ✅ Prevents delete through Interface*
};

class Impl : public Interface {
public:
    void doWork() override {}
    ~Impl() { /* cleanup */ }  // Can still delete Impl*
};

int main() {
    Interface* ptr = new Impl();
    ptr->doWork();
    // delete ptr;  // ❌ ERROR: destructor is protected
    
    Impl* impl = new Impl();
    delete impl;  // ✅ OK
}
```

---

## Code Examples

This repository contains 4 practical examples demonstrating access modifiers:

### Example 1: Basic Access Control & Visibility
**Location**: `example1/`
- **Files**: `box.h`, `am.cpp`
- **Demonstrates**:
  - Visibility through `#include`
  - Public vs private access
  - Const member functions
  - Access control enforcement at compile-time

```cpp
// box.h - Class definition
class Box {
private: 
    int len;
public:
    int getlength() const {
        return len;  // const ensures no modification
    }
};

// am.cpp - Usage
#include "box.h"  // Makes Box VISIBLE
Box box;
box.getlength();  // ✅ Accessible: public
// box.len = 6;   // ❌ Not accessible: private
```

**Compile**: 
```bash
cd example1
g++ -o am.out am.cpp
./am.out
```

---

### Example 2: Protected "Through What Object?" Rule
**Location**: `example2/`
- **Files**: `a.cpp`
- **Demonstrates**:
  - Protected member access rules
  - The critical "through what object?" constraint
  - Valid: accessing through Derived&/Derived*
  - Invalid: accessing through Base&/Base*

**Key Learning**: You cannot access protected members through a base class reference/pointer from a derived class method.

```cpp
class Derived : public Base {
    void test2(Derived& d) {
        d.x = 40;  // ✅ OK: Derived object
    }
    
    void test3(Base& b) {
        b.x = 50;  // ❌ ERROR: Base reference
    }
};
```

**Compile**: 
```bash
cd example2
g++ -o a.out a.cpp
# Will show compilation errors for test3() and test5()
```

---

### Example 3: Real-World Protected Usage (Bank Account)
**Location**: `example3/`
- **Files**: `realworld.cpp`
- **Demonstrates**:
  - Practical use of protected in inheritance
  - Why the "through what object?" rule prevents security bugs
  - Proper encapsulation in financial domain

**Scenario**: 
- `BankAccount` has protected `balance`
- `CheckingAccount` can modify its own balance
- `CheckingAccount` can transfer from another `CheckingAccount`
- `CheckingAccount` CANNOT mess with arbitrary `BankAccount` objects

**Security Feature**: This prevents `CheckingAccount` from bypassing `SavingsAccount`'s withdrawal rules.

**Compile**: 
```bash
cd example3
g++ -o realworld.out realworld.cpp
./realworld.out
```

---

### Example 4: Inheritance Types & Protected Members
**Location**: `example4/`
- **Files**: `inheritancetype.cpp`
- **Demonstrates**:
  - How protected members behave with different inheritance specifiers
  - Public inheritance: protected stays protected
  - Protected inheritance: protected stays protected (but base becomes protected)
  - Private inheritance: protected becomes private
  - Impact on further inheritance (grandchild classes)

**Key Learning**: Private inheritance makes everything private, blocking grandchild access.

```cpp
class D3 : private Base {  // private inheritance
    void test() { prot = 40; }  // ✅ OK in D3
};

class D3Child : public D3 {
    void test() {
        // prot = 60;  // ❌ ERROR: became private in D3
    }
};
```

**Compile**: 
```bash
cd example4
g++ -o inheritancetype.out inheritancetype.cpp
./inheritancetype.out
```

---

## Common Interview Questions

### Q1: What's the default access for `struct` vs `class`?

**Answer**: 
- `struct` → `public` (members and inheritance)
- `class` → `private` (members and inheritance)

### Q2: Can a derived class access base class private members?

**Answer**: No. Private members are not accessible in derived classes. Use `protected` if you want derived class access.

### Q3: Is `friend` an access specifier?

**Answer**: No. Access specifiers are `public`, `protected`, and `private`. `friend` is a separate mechanism that grants specific external functions/classes access to private and protected members.

### Q4: What's the difference between access and visibility?

**Answer**:
- **Visibility**: Whether the compiler can see a name during name lookup (controlled by `#include`, forward declarations)
- **Access**: Whether you're allowed to use a visible member (controlled by `public`/`protected`/`private`)

### Q5: When is access control checked?

**Answer**: At **compile-time** during semantic analysis, after name lookup succeeds.

### Q6: What does `const` after a member function mean?

**Answer**: It makes the function a **const member function**, which:
1. Promises not to modify member variables
2. Can be called on const objects
3. Is enforced at compile-time

```cpp
int getLength() const;  // const member function
```

### Q7: Can members of the same class access each other's private data?

**Answer**: Yes! Access control is **per-class, not per-object**. All instances of a class can access private members of other instances of the same class.

```cpp
class Box {
private:
    int len;
public:
    bool isBigger(const Box& other) const {
        return len > other.len;  // ✅ OK: accessing another Box's private member
    }
};
```

### Q8: Why can't I access a base's protected member through a Base reference in a derived class?

**Answer**: This is C++'s **protection against cross-hierarchy violations**. If `DerivedA` could access protected members through a `Base&`, it could manipulate `DerivedB`'s protected state through a base reference, violating encapsulation between sibling classes.

**See**: `example2/a.cpp` and `example3/realworld.cpp` for demonstrations

### Q9: What happens to protected members with private inheritance?

**Answer**: Protected members become **private** in the derived class. Further derived classes (grandchildren) cannot access them.

**See**: `example4/inheritancetype.cpp` for full demonstration

```cpp
class D3 : private Base {
    // Base's protected becomes private here
};

class D3Child : public D3 {
    // Cannot access Base's members - they're private in D3
};
```

### Q10: When should I use protected instead of private?

**Answer**: Use `protected` when:
- You're designing for inheritance and want derived classes to customize behavior
- Implementing Template Method pattern
- The member is part of the "interface for subclasses"

Use `private` when:
- It's an implementation detail
- You want to maintain full control over invariants
- No derived class should depend on it

**Best Practice**: Prefer `private` by default; use `protected` only when inheritance customization is intended.

---

## Best Practices

### 1. Encapsulation First
```cpp
class Account {
private:
    double balance;  // Hide implementation
public:
    void deposit(double amount);   // Public interface
    double getBalance() const;     // Const for read-only
};
```

### 2. Minimal Public Interface
- Keep data members `private`
- Expose only what clients need
- Use `protected` sparingly

### 3. Const Correctness
```cpp
class Box {
private:
    int len;
public:
    int getLength() const { return len; }     // ✅ const (read-only)
    void setLength(int l) { len = l; }        // Non-const (modifies)
};
```

### 4. Prefer Composition Over Inheritance
```cpp
// ❌ Avoid: Inheritance for code reuse
class Stack : private std::vector<int> { };

// ✅ Better: Composition
class Stack {
private:
    std::vector<int> data;  // Has-a relationship
};
```

### 5. Use `friend` Sparingly
Only when:
- Operator overloading requires it
- Tightly coupled design is justified
- Factory pattern needs private constructor access

---

## System Design Implications

### 1. Interface Stability
- Public API changes break client code
- Private changes don't affect clients
- Protected changes affect derived classes

### 2. Pimpl (Pointer to Implementation)
Hide implementation details to reduce compilation dependencies:

```cpp
// widget.h
class Widget {
public:
    Widget();
    ~Widget();
    void doSomething();
private:
    class Impl;  // Forward declaration
    Impl* pImpl; // Pointer to implementation
};
```

### 3. Abstract Interfaces
```cpp
class IShape {
public:
    virtual double area() const = 0;
    virtual ~IShape() = default;
protected:
    ~IShape() {}  // Protected destructor prevents deletion via interface
};
```

---

## Quick Reference Card

```cpp
// Access Specifiers
public:     // Accessible everywhere
protected:  // Class + friends + derived classes
private:    // Class + friends only

// Defaults
class → private
struct → public

// Friend (not an access specifier)
friend void func();
friend class Other;

// Const member function
int get() const;  // Won't modify members

// Inheritance
class D : public Base {};     // Most common
class D : protected Base {};  // Rare
class D : private Base {};    // Implementation inheritance
```

---

## Related Topics to Explore Next

1. **RAII** (Resource Acquisition Is Initialization)
2. **Const correctness** (const, constexpr, mutable)
3. **Virtual functions & Polymorphism**
4. **Smart pointers** (unique_ptr, shared_ptr)
5. **Move semantics** (rvalue references)
6. **Template metaprogramming**
7. **Design patterns** (Singleton, Factory, Observer)

---

## Summary: Example Directory Structure

```
acessmodifiers/
├── README.md                      # This file
├── example1/                      # Basic access & visibility
│   ├── box.h                     # Class with private/public
│   ├── am.cpp                    # Usage demonstrating access control
│   └── am.out                    # Compiled binary
├── example2/                      # Protected "through what?" rule
│   └── a.cpp                     # All 5 test cases for protected access
├── example3/                      # Real-world: Bank accounts
│   └── realworld.cpp             # CheckingAccount & SavingsAccount
└── example4/                      # Inheritance types
    └── inheritancetype.cpp       # Public/Protected/Private inheritance
```

**Learning Path**:
1. Start with `example1` → Understand basic access control & visibility
2. Move to `example2` → Master the tricky protected rules
3. Study `example3` → See why the rules matter in real systems
4. Finish with `example4` → Understand how inheritance changes access

---

**Interview Prep Tip**: Always distinguish between:
- **What** (access specifiers, friend, protected rules)
- **When** (compile-time phases: visibility → access)
- **Why** (encapsulation, const-correctness, security, interface design)

**Compile & Run All Examples**:
```bash
# Example 1
cd example1 && g++ -o am.out am.cpp && ./am.out

# Example 2 (will show compilation errors - that's expected!)
cd example2 && g++ -o a.out a.cpp

# Example 3
cd example3 && g++ -o realworld.out realworld.cpp && ./realworld.out

# Example 4
cd example4 && g++ -o inheritancetype.out inheritancetype.cpp && ./inheritancetype.out
```

Good luck with your system design interviews! 🚀
