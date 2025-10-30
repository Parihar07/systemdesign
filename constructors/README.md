# Constructors and Destructors - Interview Preparation

## 📚 Topics Covered

### Part 1: Constructor Basics ✅
- What is a Constructor?
- Default Constructor
- File: `01_basic_constructor.cpp`

### Part 2: Parameterized Constructors
- Passing arguments to constructors
- Multiple constructors (Function Overloading)
- File: `02_parameterized_constructor.cpp`

### Part 3: Copy Constructor
- What is a Copy Constructor?
- Shallow vs Deep Copy
- When is it called?
- File: `03_copy_constructor.cpp`

### Part 4: Constructor Overloading
- Multiple constructors with different signatures
- File: `04_constructor_overloading.cpp`

### Part 5: Constructor Initialization List
- Member initialization list syntax
- Why use it?
- When is it mandatory?
- File: `05_initialization_list.cpp`

### Part 6: Destructors
- What is a Destructor?
- When is it called?
- Resource cleanup
- File: `06_destructor_basics.cpp`

### Part 7: Constructor & Destructor Order
- Order of execution in inheritance
- File: `07_constructor_destructor_order.cpp`

### Part 8: Special Cases
- Private Constructors
- Explicit Constructors
- Delegating Constructors (C++11)
- File: `08_special_cases.cpp`

### Part 9: Real-World Examples
- Dynamic memory allocation
- RAII (Resource Acquisition Is Initialization)
- File: `09_realworld_examples.cpp`

### Part 10: Interview Questions
- Common interview questions and answers
- File: `10_interview_questions.cpp`

---

## 🎯 Interview Key Points to Remember

### Constructors:
- [ ] Same name as class, no return type
- [ ] Called automatically when object is created
- [ ] Can be overloaded
- [ ] Types: Default, Parameterized, Copy
- [ ] Initialization list vs assignment in constructor body
- [ ] Cannot be virtual

### Destructors:
- [ ] Name: ~ClassName()
- [ ] No parameters, no return type
- [ ] Only one destructor per class
- [ ] Called when object goes out of scope
- [ ] Should be virtual in base class if inheritance is used
- [ ] Used for cleanup (deallocate memory, close files, etc.)

---

## 🚀 Progress Tracker
- [x] Part 1: Basic Constructor
- [ ] Part 2: Parameterized Constructor
- [ ] Part 3: Copy Constructor
- [ ] Part 4: Constructor Overloading
- [ ] Part 5: Initialization List
- [ ] Part 6: Destructors
- [ ] Part 7: Constructor/Destructor Order
- [ ] Part 8: Special Cases
- [ ] Part 9: Real-World Examples
- [ ] Part 10: Interview Questions
