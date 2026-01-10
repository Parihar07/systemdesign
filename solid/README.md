# SOLID Principles - Deep Dive

## Overview
SOLID is an acronym for five design principles intended to make software designs more understandable, flexible, and maintainable. These principles are fundamental for object-oriented design and critical for system design interviews.

## The Five Principles

### 1. **S**ingle Responsibility Principle (SRP)
**Definition**: A class should have one, and only one, reason to change.
- Each class should have a single, well-defined responsibility
- Changes to one aspect of the system should affect minimal classes
- Promotes high cohesion and low coupling

### 2. **O**pen/Closed Principle (OCP)
**Definition**: Software entities should be open for extension but closed for modification.
- You should be able to add new functionality without changing existing code
- Achieved through abstraction, inheritance, and polymorphism
- Reduces risk of breaking existing working code

### 3. **L**iskov Substitution Principle (LSP)
**Definition**: Objects of a superclass should be replaceable with objects of subclass without breaking the application.
- Subtypes must be substitutable for their base types
- Derived classes should extend, not replace, base class behavior
- Ensures proper inheritance hierarchies

### 4. **I**nterface Segregation Principle (ISP)
**Definition**: Clients should not be forced to depend on interfaces they don't use.
- Many specific interfaces are better than one general-purpose interface
- Prevents "fat" interfaces that force unnecessary dependencies
- Promotes focused, cohesive interfaces

### 5. **D**ependency Inversion Principle (DIP)
**Definition**: High-level modules should not depend on low-level modules. Both should depend on abstractions.
- Depend on abstractions, not concretions
- Abstractions should not depend on details; details should depend on abstractions
- Enables loose coupling and easier testing

## Structure

```
solid/
├── 01_srp_single_responsibility.cpp    # Single Responsibility examples
├── 02_ocp_open_closed.cpp              # Open/Closed examples
├── 03_lsp_liskov_substitution.cpp      # Liskov Substitution examples
├── 04_isp_interface_segregation.cpp    # Interface Segregation examples
├── 05_dip_dependency_inversion.cpp     # Dependency Inversion examples
├── 06_real_world_ecommerce.cpp         # Complete e-commerce system
├── 07_notification_system.cpp          # Notification system design
├── makefile                             # Build system
└── README.md                            # This file
```

## Building and Running

```bash
# Build all examples
make all

# Build specific example
make srp
make ocp
make lsp
make isp
make dip
make ecommerce
make notification

# Run examples
./01_srp_single_responsibility
./02_ocp_open_closed
# ... etc
```

## Interview Tips

1. **Recognize Violations**: Be able to identify when code violates SOLID principles
2. **Propose Refactoring**: Suggest how to refactor code to follow SOLID
3. **Trade-offs**: Understand when strict adherence might be over-engineering
4. **Real Examples**: Have concrete examples from your experience
5. **Benefits**: Articulate the benefits (maintainability, testability, extensibility)

## Common Interview Questions

1. Explain SOLID principles with examples
2. How would you refactor this code to follow SRP?
3. Design a payment system following SOLID principles
4. What's the difference between OCP and LSP?
5. When might you intentionally violate SOLID principles?
6. How do SOLID principles relate to design patterns?
7. Implement dependency injection using DIP

## Key Takeaways

- **SRP**: One class, one job, one reason to change
- **OCP**: Extend behavior without modifying existing code
- **LSP**: Subtypes must honor base type contracts
- **ISP**: Small, focused interfaces over large, general ones
- **DIP**: Depend on abstractions, inject dependencies

## Resources
- Robert C. Martin's "Clean Architecture"
- Design Patterns (Gang of Four)
- Effective C++ series by Scott Meyers
