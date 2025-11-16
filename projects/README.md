# 🏗️ Interview Projects

This folder contains **complete C++ projects** designed for interview preparation. Each project demonstrates specific OOP concepts, design patterns, and best practices.

---

## 📋 Project Index

### 1. [Hospital Management System (HMS)](./HMS/)
**Focus:** All 4 OOP Relationships  
**Difficulty:** Intermediate  
**Score:** 9/10 (Interview Ready)

**What You'll Learn:**
- ✅ Inheritance (IS-A): Doctor/Patient inherit from Person
- ✅ Composition (Dies Together): Address in Person, MedicalRecord in Patient
- ✅ Aggregation (Independent): Department has Doctors
- ✅ Association (Temporary): Doctor examines Patient
- ✅ UML diagram creation
- ✅ Raw pointer management (pre-RAII)

**Tech Stack:** C++17, Raw Pointers  
**Lines of Code:** ~200  
**Time to Complete:** 2-3 hours  

📖 [View Project →](./HMS/) | [View Code →](./HMS/hms.cpp)

**Interview Questions Covered:**
- What's the difference between composition and aggregation?
- How do you implement IS-A vs HAS-A relationships?
- When should you use inheritance vs composition?

---

### 2. [Payment Service System](./paymentsystem/)
**Focus:** Polymorphism & RAII  
**Difficulty:** Intermediate  
**Score:** 9.5/10 (Interview Ready)

**What You'll Learn:**
- ✅ Abstract base classes (pure virtual functions)
- ✅ Multi-level inheritance (Pay → Card → CreditCard/DebitCard)
- ✅ Virtual destructors (prevent memory leaks)
- ✅ Runtime polymorphism (vtable mechanism)
- ✅ Smart pointers (shared_ptr, RAII principles)
- ✅ Polymorphic storage and dispatch

**Tech Stack:** C++17, Smart Pointers, RAII  
**Lines of Code:** ~180  
**Time to Complete:** 2-3 hours  

📖 [View Project →](./paymentsystem/) | [View Code →](./paymentsystem/payment_system.cpp)

**Interview Questions Covered:**
- Why do you need virtual destructors?
- How does polymorphism work internally?
- What are smart pointers and why use them?
- Explain vtable and vptr mechanism

---

## 🎯 Learning Path

### For Beginners:
Start with **HMS** to understand OOP relationships basics, then move to **Payment Service** for advanced concepts.

### For Interview Prep:
Both projects are **interview-ready**. Practice explaining:
1. Design decisions (why this class structure?)
2. Trade-offs (raw pointers vs smart pointers)
3. Scalability (how would you extend this?)

---

## 📊 Project Comparison

| Feature | HMS | Payment Service |
|---------|-----|-----------------|
| **Primary Focus** | All 4 OOP relationships | Polymorphism & RAII |
| **Memory Management** | Raw pointers | Smart pointers (shared_ptr) |
| **Inheritance Depth** | 2 levels (Person → Doctor) | 3 levels (Pay → Card → CreditCard) |
| **Virtual Functions** | 1 (virtual destructor) | Multiple (doPayment, showCardDetails) |
| **Abstract Classes** | No | Yes (Pay, Card) |
| **Design Patterns** | None explicitly | Interface pattern |
| **Interview Score** | 9/10 | 9.5/10 |
| **Best For Learning** | OOP relationships | Polymorphism internals |

---

## 🚀 Running Projects

Each project has its own `makefile` for easy compilation:

```bash
# Hospital Management System
cd HMS
make run

# Payment Service System
cd paymentsystem
make run
```

---

## 🎓 Interview Strategy

### When Asked "Tell Me About a Project":

**Option 1: HMS (Focus on Design)**
> "I built a Hospital Management System demonstrating all 4 OOP relationships. The system has a Person base class that Doctor and Patient inherit from (inheritance). Person contains an Address object that dies with it (composition). Departments aggregate Doctors who can exist independently (aggregation). And Doctors can examine Patients through temporary associations. This project helped me understand when to use each relationship type in real-world scenarios."

**Option 2: Payment Service (Focus on Polymorphism)**
> "I implemented a Payment Service System showcasing runtime polymorphism. I created an abstract Pay interface with pure virtual functions, then derived concrete payment methods like CreditCard, UPI, and Wallet. The key was using virtual destructors to prevent memory leaks and smart pointers for RAII. I can explain how the vtable mechanism enables runtime dispatch if you'd like."

### Deep Dive Questions You Can Handle:

**From HMS:**
- ✅ Difference between composition and aggregation with examples
- ✅ When to use inheritance vs composition (IS-A vs HAS-A)
- ✅ How to design class hierarchies for real-world domains
- ✅ Memory management with raw pointers

**From Payment Service:**
- ✅ Virtual function mechanism (vtable/vptr)
- ✅ Why virtual destructors are critical
- ✅ Smart pointers and RAII principles
- ✅ Abstract classes and interface design
- ✅ Runtime vs compile-time polymorphism

---

## 🔍 Code Quality Metrics

Both projects feature:
- ✅ **No compiler warnings** (compiled with `-Wall -Wextra`)
- ✅ **Comprehensive comments** explaining design decisions
- ✅ **Clean separation of concerns** (single responsibility)
- ✅ **Proper constructor/destructor chains** (verified with output)
- ✅ **UML diagrams** for visual understanding
- ✅ **Error handling** where applicable

---

## 📝 Future Projects (Planned)

### 3. Library Management System
**Focus:** Design Patterns (Observer, Factory, Singleton)  
**Concepts:** Template classes, STL containers, Exception handling

### 4. Banking System
**Focus:** SOLID Principles  
**Concepts:** Dependency injection, Interface segregation, Open/Closed principle

### 5. Thread Pool Implementation
**Focus:** Concurrency & Multithreading  
**Concepts:** Mutex, Condition variables, Producer-consumer pattern

---

## 💡 Tips for Success

### Before the Interview:
1. **Run both projects** - Ensure you can compile and execute
2. **Explain the design** - Why each class exists, what it does
3. **Know the trade-offs** - Raw pointers vs smart pointers, when to use each
4. **Practice UML** - Draw class diagrams on whiteboard
5. **Understand internals** - How virtual functions work, memory layout

### During the Interview:
1. **Start with high-level design** - Don't jump into code immediately
2. **Explain your thought process** - "I'm using inheritance here because..."
3. **Discuss alternatives** - "We could also use composition, but..."
4. **Know the complexity** - Time/space complexity of operations
5. **Be honest** - If you don't know something, say so and explain how you'd learn

---

## 🔗 Related Topics

- [Inheritance](../inheritance/) - Deep dive into IS-A relationships
- [Constructors & Destructors](../constructors-destructors/) - Object lifecycle
- [OOP Relationships](../association/) - Composition, Aggregation, Association
- [Concurrency](../concurrency/) - For future thread pool project

---

## 📬 Contributing

Found a bug or want to suggest improvements?
- Add more error handling
- Implement additional features
- Optimize performance
- Add unit tests

---

**Last Updated:** November 16, 2025  
**Total Projects:** 2 (HMS, Payment Service)  
**Status:** Both Interview-Ready ✅

---

**Happy Coding! 🚀**
