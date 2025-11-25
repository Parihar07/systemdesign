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
Complete guide to class hierarchies, polymorphism, and runtime dispatch in C++.

**Covers:**
- Inheritance basics (IS-A relationship)
- Types of inheritance (Single, Multiple, Multilevel, Hierarchical, Hybrid)
- Access control in inheritance (public, protected, private)
- Constructor/Destructor order in inheritance
- Function overriding and virtual functions
- Polymorphism and dynamic dispatch
- Abstract classes and pure virtual functions
- Diamond problem and virtual inheritance
- **vptr/vtable mechanism deep dive** (system-level understanding)
- Real-world examples (GUI toolkit, device drivers)
- Interview questions and best practices

**Includes 10 Complete Examples:**
- `01_inheritance_basics.cpp` - Fundamental concepts
- `02_types_of_inheritance.cpp` - All inheritance types
- `03_access_control.cpp` - Access specifier rules
- `04_constructor_destructor_order.cpp` - Object lifecycle
- `05_function_overriding.cpp` - Method overriding
- `06_virtual_functions.cpp` - Polymorphism basics
- `07_abstract_classes.cpp` - Pure virtual functions
- `08_multiple_inheritance.cpp` - Multiple base classes
- `09_real_world_example.cpp` - GUI toolkit demo
- `10_private_inheritance_example.cpp` - Advanced patterns
- `vptr_vtable_visual.cpp` - Internal mechanism visualization
- `diamondprob.cpp` - Diamond problem solution

**Status:** All 10 parts complete ✅ **FULLY DOCUMENTED!**

📖 [Read the full guide →](./inheritance/README.md)

---

#### 4. [Concurrency Fundamentals](./concurrency/)
Systems programming perspective on processes, threads, and memory management.

**Covers:**
- Process vs Thread (fundamental differences)
- IPC mechanisms (pipes, shared memory, signals)
- Memory layouts (stack, heap, TLS, code/data segments)
- TCB/PCB in kernel memory
- Thread creation basics (pthread, std::thread)
- Process creation (fork, exec, wait)
- Virtual memory and address translation
- Context switching internals

**Includes 9 Files:**
- `00_single_thread_basics.cpp` - Single thread timing demo
- `00_multi_thread_basics.cpp` - Work splitting with atomic
- `01_process_vs_thread.cpp` - fork vs thread comparison
- `02_ipc_internals.cpp` - IPC mechanisms demo
- `03_process_internals_deep_dive.md` - TCB/PCB kernel details
- `04_thread_memory_layout.cpp` - Stack/heap/TLS addresses
- `05_thread_vs_process_memory.md` - Memory layout comparison
- `06_thread_create_basics.cpp` - Simple thread syntax
- `07_process_create_basics.cpp` - fork/exec/wait basics

**Status:** Complete ✅ **Systems perspective!**

📖 [Read the full guide →](./concurrency/README.md)

---

#### 5. [OOP Relationships](./association/)
Demonstrating all 4 OOP relationships with real-world Hospital Management System.

**Covers:**
- **Inheritance (IS-A)**: Doctor/Patient inherit from Person
- **Composition (Dies Together)**: Address in Person, MedicalRecord in Patient
- **Aggregation (Independent)**: Department has Doctors
- **Association (Temporary)**: Doctor examines Patient
- UML diagrams and arrow directions
- Memory management with raw pointers (pre-RAII)
- Interview-ready implementation

**Project:**
- `hms.cpp` - Complete Hospital Management System
  - Person base class with Address composition
  - Doctor and Patient inheritance
  - Department aggregation using pointers
  - examine() method for association
  - All 4 relationships demonstrated

**Status:** Complete ✅ **Interview ready! Score: 9/10**

**Note:** Using raw pointers for learning; will upgrade to smart_ptr after RAII topic.

📖 [Read the full guide →](./association/README.md)

---

## 🏗️ Projects

**2 Complete Interview Projects** demonstrating different C++ concepts and design patterns.

📖 **[View All Projects →](./projects/)**

### Quick Overview:

| Project | Focus | Tech | Score |
|---------|-------|------|-------|
| [HMS](./projects/HMS/) | All 4 OOP Relationships | Raw Pointers | 9/10 |
| [Payment Service](./projects/paymentsystem/) | Polymorphism & RAII | Smart Pointers | 9.5/10 |

**Key Highlights:**
- ✅ Interview-ready implementations with comprehensive documentation
- ✅ UML diagrams and design explanations
- ✅ Practice questions and talking points included
- ✅ No compiler warnings, clean code quality
- ✅ Makefile for easy compilation

📖 [Explore Projects →](./projects/) | [See Comparison Table →](./projects/README.md#-project-comparison)

---

## 🗂️ Repository Structure


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
│   ├── README.md               # Complete roadmap with navigation
│   ├── 01_inheritance_basics.cpp
│   ├── 02_types_of_inheritance.cpp
│   ├── 03_access_control.cpp
│   ├── 04_constructor_destructor_order.cpp
│   ├── 05_function_overriding.cpp
│   ├── 06_virtual_functions.cpp
│   ├── 07_abstract_classes.cpp
│   ├── 08_multiple_inheritance.cpp
│   ├── 09_real_world_example.cpp
│   ├── 10_private_inheritance_example.cpp
│   ├── vptr_vtable_visual.cpp
│   └── diamondprob.cpp
├── concurrency/                 # Concurrency Fundamentals
│   ├── README.md               # Systems programming perspective
│   ├── 00_single_thread_basics.cpp
│   ├── 00_multi_thread_basics.cpp
│   ├── 01_process_vs_thread.cpp
│   ├── 02_ipc_internals.cpp
│   ├── 03_process_internals_deep_dive.md
│   ├── 04_thread_memory_layout.cpp
│   ├── 05_thread_vs_process_memory.md
│   ├── 06_thread_create_basics.cpp
│   ├── 07_process_create_basics.cpp
│   └── makefile
├── association/                 # OOP Relationships
│   ├── README.md               # All 4 OOP relationships guide
│   ├── hms.cpp                 # Hospital Management System (Interview Project)
│   ├── HMS.png                 # UML diagram
│   └── makefile
├── functorsExecutioners/           # Function pointers, functors, lambdas
│   ├── README.md                   # Index for function pointer & lambda topics
│   ├── fp.cpp                      # Function pointer examples
│   ├── lambda_explanation.cpp      # Lambda examples
│   └── lambda_explanation.md       # Lambda explanations & guide
├── projects/                    # Interview Projects
│   └── paymentsystem/          # Payment Service System
│       ├── README.md           # Complete documentation
│       ├── payment_system.cpp  # Polymorphism & RAII demo
│       └── makefile
├── ProductService/              # Java Spring Boot project (for practice)
└── backendproject/              # Other practice projects
```
### Function Pointers, Functors, and Lambdas

Explore modern C++ callable objects, including:
- Function pointers (basic, callback, arrays, strategy)
- Lambdas (syntax, captures, STL, threading, generic, etc.)

See [`functorsExecutioners/README.md`](./functorsExecutioners/README.md) for a full index and [`lambda_explanation.md`](./functorsExecutioners/lambda_explanation.md) for detailed lambda explanations and examples.

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
- ✅ Constructors & Destructors (Complete - All 8 parts done!)
- ✅ Inheritance & Polymorphism (Complete - All 10 parts done!)
- ✅ Concurrency Fundamentals (Complete - Systems perspective!)
- ✅ OOP Relationships (Complete - HMS project!)
- 🔜 Templates & Generic Programming
- 🔜 RAII & Smart Pointers
- 🔜 Move Semantics & Perfect Forwarding
- 🔜 Design Patterns
- 🔜 Exception Handling
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
- [x] Constructors & Destructors (All 8 parts)
- [x] Inheritance & Polymorphism (All 10 parts + vptr/vtable deep dive)
- [x] Concurrency Fundamentals (Processes, Threads, IPC, Memory Layouts)
- [x] OOP Relationships (Inheritance, Composition, Aggregation, Association)
- [x] **Project**: Hospital Management System (HMS)

### 🚧 In Progress
- [ ] RAII & Smart Pointers

### 📋 Planned
- [ ] RAII & Resource Management
- [ ] Smart Pointers (unique_ptr, shared_ptr, weak_ptr)
- [ ] Move Semantics & Perfect Forwarding
- [ ] STL Containers & Algorithms
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

*Last Updated: November 16, 2025*
*Topics will be added gradually as we progress through interview preparation.*
