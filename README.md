# System Design & C++ Interview Preparation

A comprehensive resource for mastering **System Design**, **Object-Oriented Programming (OOP)**, and **C++ fundamentals** for technical interviews.

## 🎯 Purpose

This repository is designed for:
- **Interview preparation**: Brush up on core concepts before technical rounds
- **Learning system design**: Step-by-step exploration of OOP principles
- **Hands-on practice**: Working code examples with detailed explanations
- **Community resource**: Anyone interested in strengthening their C++ and system design knowledge

## 📚 What's Inside

### Current Topics

#### 1. [Access Modifiers](./acessmodifiers/)
Complete guide to C++ access control mechanisms.

**Covers:**
- `public`, `protected`, `private` access specifiers
- Access vs Visibility (compilation phases)
- Friend mechanism (not an access specifier!)
- Protected access rules ("through what object?")
- Inheritance and access control
- Real-world examples and interview questions

**Includes 4 Working Examples:**
- `example1/` - Basic access control & visibility
- `example2/` - Protected "through what?" rule
- `example3/` - Real-world: Bank account system
- `example4/` - Inheritance types (public/protected/private)

📖 [Read the full guide →](./acessmodifiers/README.md)

---

#### 2. [Constructors & Destructors](./constructors/)
Deep dive into object lifecycle management in C++.

**Covers:**
- Default, Parameterized, and Copy Constructors
- Shallow vs Deep Copy (critical for interviews!)
- Constructor Overloading
- Initialization Lists
- Destructors and RAII
- Rule of Three/Five
- Memory management with dynamic allocation
- Constructor calling rules and delegation

**Includes Comprehensive Examples:**
- `01_basic_constructor.cpp` - Constructor fundamentals
- `02_parameterized_constructor.cpp` - Controlled object creation
- `03_copy_constructor.cpp` - Shallow vs Deep copy explained
 - `04_constructor_overloading.cpp` - Function overloading with 4 examples
- `05_initialization_list.cpp` - Performance optimization
- `06_destructor_basics.cpp` - Resource cleanup & RAII
- `07_constructor_destructor_order.cpp` - Inheritance order & virtual destructors
- `08_special_cases.cpp` - Explicit, Singleton, Factory patterns
- `cnstrs.cpp` - Working example with Rule of Three

**Status:** Parts 1-8 complete ✅ **CORE TOPICS DONE!**

📖 [Read the full guide →](./constructors-destructors/README.md)

---

#### 3. [Inheritance](./inheritance/)
Understanding class hierarchies and code reuse through inheritance.

**Covers:**
- Inheritance basics (IS-A relationship)
- Types of inheritance (Single, Multiple, Multilevel, Hierarchical, Hybrid)
- Access control in inheritance
- Constructor/Destructor order in inheritance
- Function overriding
- Virtual functions and polymorphism

**Includes Examples:**
- `01_inheritance_basics.cpp` - Fundamental inheritance concepts

**Status:** Part 1 in progress 🔄

📖 [Read the full guide →](./inheritance/README.md)

---

## 🗂️ Repository Structure

```
systemdesign/
├── README.md                    # This file
├── acessmodifiers/              # Access modifiers topic
│   ├── README.md               # Comprehensive guide
│   ├── example1/               # Basic examples
│   ├── example2/               # Protected rules
│   ├── example3/               # Real-world scenarios
│   └── example4/               # Inheritance types
├── constructors-destructors/    # Constructors & Destructors
│   ├── README.md               # Complete roadmap
│   ├── 01_basic_constructor.cpp
│   ├── 02_parameterized_constructor.cpp
│   ├── 03_copy_constructor.cpp
│   ├── 04_constructor_overloading.cpp
│   ├── 05_initialization_list.cpp
│   ├── 06_destructor_basics.cpp
│   ├── 07_constructor_destructor_order.cpp
│   ├── 08_special_cases.cpp
│   └── cnstrs.cpp              # Working example
├── inheritance/                 # Inheritance & Polymorphism
│   ├── README.md               # Complete roadmap
│   └── 01_inheritance_basics.cpp
├── ProductService/              # Java Spring Boot project (for practice)
└── backendproject/              # Other practice projects
```
└── backendproject/              # Other practice projects
```

---

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++, clang++)
- Basic understanding of C++ syntax
- Terminal/command line familiarity

### Running Examples

Each topic directory contains runnable examples:

```bash
# Navigate to a topic
cd acessmodifiers/example1

# Compile
g++ -o am.out am.cpp

# Run
./am.out

# Or for constructors
cd constructors
g++ -o basic.out 01_basic_constructor.cpp
./basic.out
```

Refer to individual README files for specific compilation instructions.

---

## 📖 Learning Path

### For Interview Prep:
1. **Start with fundamentals**: Access modifiers, encapsulation
2. **Move to OOP concepts**: Inheritance, polymorphism, abstraction
3. **Study design patterns**: Singleton, Factory, Observer, etc.
4. **Practice system design**: Design real-world systems

### Recommended Order:
- ✅ Access Modifiers (Complete)
- ✅ Constructors & Destructors (Parts 1-8 complete - Core topics done!)
- 🔜 Inheritance & Polymorphism
- 🔜 Virtual Functions & Abstract Classes
- 🔜 Const Correctness
- 🔜 RAII & Smart Pointers
- 🔜 Move Semantics
- 🔜 Design Patterns
- 🔜 System Design Case Studies

---

## 🎓 How to Use This Repo

### For Self-Study:
1. Read the topic's README for theory
2. Study the code examples
3. Compile and run the examples yourself
4. Modify the code to test your understanding
5. Practice the interview questions

### For Interview Prep:
1. Review the "Common Interview Questions" sections
2. Understand the "why" behind each concept
3. Practice explaining concepts out loud
4. Code examples from memory
5. Focus on real-world applications

### For Contributors:
- Each topic should have a comprehensive README
- Include working, compilable examples
- Add interview questions with answers
- Provide real-world use cases

---

## 🤝 Contributing

This is a living resource that will grow over time. Topics will be added gradually based on interview relevance and community needs.

**Contribution Guidelines:**
- Keep explanations clear and concise
- Include working code examples
- Add compilation instructions
- Cover common interview gotchas
- Reference real-world scenarios

---

## 📝 Topics Roadmap

### ✅ Completed
- [x] Access Modifiers (public, protected, private, friend)

### 🔄 In Progress
- [ ] Const Correctness (const, constexpr, mutable)

### 📋 Planned
- [ ] Virtual Functions & Polymorphism
- [ ] RAII & Resource Management
- [ ] Smart Pointers (unique_ptr, shared_ptr, weak_ptr)
- [ ] Move Semantics & Perfect Forwarding
- [ ] Templates & Generic Programming
- [ ] Design Patterns (Gang of Four)
- [ ] Exception Handling
- [ ] Memory Management
- [ ] Concurrency & Threading
- [ ] System Design Case Studies

---

## 💡 Interview Tips

**Key Principles to Remember:**
1. **Understand the "why"**: Don't just memorize—understand the reasoning
2. **Practice explaining**: Can you explain it to someone else?
3. **Code without IDE**: Practice writing code by hand or in simple editors
4. **Think about trade-offs**: Every design decision has pros and cons
5. **Real-world context**: Connect concepts to actual software problems

**During Interviews:**
- Clarify requirements before coding
- Think out loud—show your thought process
- Start with a simple solution, then optimize
- Discuss edge cases and error handling
- Know the time/space complexity

---

## 🔗 Related Projects

- **ProductService/**: Java Spring Boot service (for backend practice)
- **backendproject/**: Additional backend examples

---

## 📬 Feedback & Questions

This repository is designed to help developers prepare for technical interviews. If you find it helpful, consider:
- ⭐ Starring the repo
- 🐛 Reporting issues or unclear explanations
- 💡 Suggesting new topics
- 🤝 Contributing examples or improvements

---

## ⚠️ Disclaimer

**This is a learning resource created for educational purposes.**

- 📖 **Learning in Progress**: Content is created as part of ongoing interview preparation and learning
- 🐛 **Corrections Welcome**: If you find any errors, inaccuracies, or better explanations, please feel free to:
  - Open an issue
  - Submit a pull request
  - Start a discussion
- 🤝 **Community Driven**: This repository benefits from collective knowledge—your corrections help everyone learn
- 🎓 **Educational Intent**: All content is meant for learning and skill development
- 📚 **No Guarantees**: While we strive for accuracy, always cross-reference with official documentation and authoritative sources

**We're all learning together!** If something doesn't seem right, it probably needs correction. Don't hesitate to point it out—that's how we all improve. 🚀

---

## 📜 License

This is an educational resource. Feel free to use, modify, and share for learning purposes.

---

**Happy Learning! 🚀**

*Last Updated: October 2025*
*Topics will be added gradually as we progress through interview preparation.*
