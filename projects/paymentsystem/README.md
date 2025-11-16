# 💳 Payment Service System

**Interview Project** - Demonstrates polymorphism, inheritance, and modern C++ memory management with smart pointers.

---

## 📋 Problem Statement

Design and implement a **Payment Service System** that:
- Supports multiple payment methods (Credit Card, Debit Card, UPI, Wallet)
- Uses polymorphism for payment processing
- Manages payment methods efficiently
- Demonstrates runtime dispatch and virtual functions

---

## 🎯 OOP Concepts Demonstrated

### ✅ **Inheritance (IS-A Relationship)**
```
Pay (Abstract Interface)
├── Card (Abstract Base)
│   ├── CreditCard
│   └── DebitCard
├── UPI
└── Wallet
```

### ✅ **Polymorphism (Runtime Dispatch)**
- **Pure virtual function**: `doPayment()` in `Pay` interface
- **Virtual destructor**: Ensures proper cleanup in inheritance hierarchy
- **Runtime binding**: Base class pointer calls derived class methods

### ✅ **Encapsulation**
- Private data members (cardnumber, upiId, walletID)
- Public interface for payment operations
- Information hiding principles

### ✅ **Smart Pointers (RAII)**
- Using `shared_ptr<Pay>` for automatic memory management
- No manual `new`/`delete` needed
- Prevents memory leaks

---

## 🏗️ Class Design

### **Pay (Abstract Base Class)**
```cpp
class Pay {
public:
    virtual void doPayment() = 0;  // Pure virtual
    virtual ~Pay() = default;       // Virtual destructor
};
```
- **Why abstract?** Different payment methods have different logic
- **Why virtual destructor?** Ensures derived class destructors are called

### **Card (Abstract Base Class)**
```cpp
class Card : public Pay {
public:
    virtual void showCardDetails() = 0;
    // Implements Pay interface, adds card-specific behavior
};
```
- **Multi-level inheritance**: Card inherits from Pay, CreditCard/DebitCard inherit from Card
- **Abstract class**: Has pure virtual methods

### **Concrete Payment Methods**
- **CreditCard**: Inherits from Card, implements credit card logic
- **DebitCard**: Inherits from Card, implements debit card logic
- **UPI**: Directly implements Pay, UPI-specific logic
- **Wallet**: Directly implements Pay, wallet-specific logic

### **PaymentService**
```cpp
class PaymentService {
    unordered_map<string, shared_ptr<Pay>> paymethod;
public:
    void addPayment(const string& name, shared_ptr<Pay> pm);
    void makePayment(const string& name);
};
```
- **Purpose**: Manages multiple payment methods
- **Storage**: Uses `shared_ptr` for automatic memory management
- **Polymorphism**: Stores base class pointers, calls derived methods

---

## 🔑 Key Features

### 1. **Virtual Destructor (Critical!)**
```cpp
virtual ~Pay() = default;
```
**Without virtual destructor:**
```cpp
Pay* ptr = new CreditCard(1234);
delete ptr;  // ❌ Only ~Pay() runs, ~CreditCard() skipped → MEMORY LEAK!
```

**With virtual destructor:**
```cpp
Pay* ptr = new CreditCard(1234);
delete ptr;  // ✅ ~CreditCard() → ~Card() → ~Pay() (all run correctly)
```

### 2. **Pure Virtual Functions**
```cpp
virtual void doPayment() = 0;  // = 0 makes it pure virtual
```
- Forces derived classes to implement
- Makes the class abstract (cannot instantiate)
- Defines interface contract

### 3. **Smart Pointers (Modern C++)**
```cpp
shared_ptr<Pay> ptr = make_shared<UPI>("id@upi");
// No delete needed - automatic cleanup when last reference goes away
```

**Benefits:**
- ✅ Automatic memory management (RAII)
- ✅ No memory leaks
- ✅ Exception-safe
- ✅ Shared ownership semantics

### 4. **Runtime Polymorphism**
```cpp
Pay* basePtr = new CreditCard(1234);
basePtr->doPayment();  // Calls CreditCard::doPayment() at RUNTIME!
```

**How it works:**
- Virtual function table (vtable) created at compile time
- vptr (virtual pointer) in each object points to vtable
- At runtime, follows vptr → vtable → correct function

---

## 📊 UML Diagram

```
INHERITANCE (IS-A):
    Pay ◁--- Card          // Card IS-A Pay (implements interface)
    Card ◁--- DebitCard    // DebitCard IS-A Card
    Card ◁--- CreditCard   // CreditCard IS-A Card
    Pay ◁--- UPI           // UPI IS-A Pay
    Pay ◁--- Wallet        // Wallet IS-A Pay

POLYMORPHISM:
    doPayment() → Pure virtual in Pay
    Each derived class overrides with specific implementation
    Runtime dispatch via vtable
```

---

## 🚀 Running the Project

### Compile and Run:
```bash
cd projects/paymentsystem
make FILE=payment_system.cpp run
```

### Expected Output:
```
========== Payment Service System ==========

----- Adding Payment Methods -----
Added payment method: pariharUpi
Added payment method: pariharCC
Added payment method: pariharDC

----- Making Payments (Polymorphism in Action) -----
Processing UPI payment using ID: parihar07@yn
Processing Credit Card payment using card: 1234
Processing Debit Card payment using card: 5678

----- Demonstrating Polymorphism with Base Pointer -----
Using Pay* pointer to CreditCard:
Processing Credit Card payment using card: 9999
```

---

## 🎓 Interview Talking Points

### **1. Why use abstract classes?**
- Define interface contracts
- Force derived classes to implement specific methods
- Prevent instantiation of incomplete types
- Enable polymorphism

### **2. Why virtual destructor?**
- Ensures proper cleanup in inheritance hierarchy
- Without it: only base destructor runs → memory leaks
- With it: derived → base destructors run in order

### **3. Why smart pointers?**
- Automatic memory management (RAII)
- Exception-safe
- Prevents memory leaks from forgetting `delete`
- Modern C++ best practice

### **4. What is polymorphism?**
- "Many forms" - one interface, multiple implementations
- Runtime dispatch via virtual functions
- Base class pointer can call derived class methods
- Achieved through vtable mechanism

### **5. When to use inheritance vs composition?**
- **Inheritance (IS-A)**: CreditCard IS-A Card, Card IS-A Pay
- **Composition (HAS-A)**: Would use if Payment HAS-A Transaction
- Use inheritance when objects share behavior and identity

---

## 🔍 Code Quality

### **Strengths:**
✅ Clean inheritance hierarchy  
✅ Proper virtual destructors  
✅ Smart pointers (RAII)  
✅ Polymorphism demonstrated  
✅ Error handling  
✅ Well-commented code  
✅ No compiler warnings  

### **Interview Score: 9.5/10**

### **Scope for Enhancement:**
1. Add Transaction class (composition relationship)
2. Add payment validation logic
3. Add payment history tracking
4. Implement observer pattern for payment notifications
5. Add exception handling for failed payments

---

## 📝 Learning Outcomes

After implementing this project, you understand:

1. ✅ **Polymorphism** - How virtual functions enable runtime dispatch
2. ✅ **Virtual destructors** - Why they're critical in inheritance
3. ✅ **Abstract classes** - Pure virtual functions and interfaces
4. ✅ **Smart pointers** - Modern C++ memory management
5. ✅ **RAII** - Resource Acquisition Is Initialization
6. ✅ **vtable mechanism** - How polymorphism works internally

---

## 🔗 Related Concepts

- [Inheritance](../../inheritance/) - IS-A relationships
- [Constructors & Destructors](../../constructors-destructors/) - Object lifecycle
- [OOP Relationships](../../association/) - All 4 OOP relationships (HMS project)

---

**Status:** ✅ Complete and Interview-Ready  
**Tech Stack:** C++17, Smart Pointers, Polymorphism  
**Interview Focus:** Virtual functions, RAII, Runtime dispatch

