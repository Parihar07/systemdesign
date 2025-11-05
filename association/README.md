# Association in C++ - Interview Preparation

## 📚 Topics Covered

### Part 1: Association Basics (Uses-A)
- What is Association?
- How it differs from Inheritance (IS-A vs. USES-A)
- Simple association example
- File: `01_association_basics.cpp`

### Part 2: Aggregation (Shared Has-A)
- Independent object lifetimes
- Implemented with pointers (`std::shared_ptr`)
- Real-world example (Department and Professors)
- File: `02_aggregation.cpp`

### Part 3: Composition (Owned Has-A)
- Dependent object lifetimes (Parent owns Child)
- Implemented with member variables or `std::unique_ptr`
- Real-world example (Car and Engine)
- File: `03_composition.cpp`

### Part 4: Real-World Example & Interview Questions
- Composition vs. Inheritance: A key design choice
- When to use Aggregation vs. Composition
- System design implications
- File: `04_interview_questions.md`

---
