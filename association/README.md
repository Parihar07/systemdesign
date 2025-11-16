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

### Part 5: Hospital Management System (HMS)
- **Complete interview problem demonstrating all 4 OOP relationships**
- File: `hms.cpp`
- Status: **Work in Progress** (Basic implementation complete)

---

## 🏥 HMS Project - Current Implementation

### What's Implemented:
✅ **Inheritance (IS-A)**
   - `Doctor` inherits from `Person`
   - `Patient` inherits from `Person`
   - Virtual destructor in base class

✅ **Composition (Dies Together)**
   - `Person` HAS `Address` (direct member)
   - `Patient` HAS `MedicalRecord` (direct member)
   - When Person/Patient dies, Address/MedicalRecord dies too

✅ **Association (Temporary Relationship)**
   - Doctor can access Patient via pointers
   - `addPatient(Patient*)` demonstrates temporary relationship
   - No ownership transfer

⚠️ **Aggregation (Independent Lifetime)**
   - Department stores `Doctor*` (raw pointers)
   - Doctors can exist independently of Department
   - **Note**: Using basic raw pointers for now

### Current Approach:
- **Using raw pointers** for simplicity and learning
- **No smart pointers** (`shared_ptr`, `unique_ptr`) yet
- Focus is on understanding OOP relationships first

### Scope for Improvement:
📝 **Future Enhancements** (After covering RAII & Smart Pointers):
1. Replace `vector<Doctor*>` with `vector<shared_ptr<Doctor>>` (proper aggregation)
2. Use `unique_ptr<MedicalRecord>` for composition (exclusive ownership)
3. Add proper memory management and RAII principles
4. Add `examine(Patient*)` method for clearer association
5. Fix constructor parameter ordering
6. Update UML diagram directions

### Why This Approach?
- **Learning path**: Master OOP relationships before memory management
- **Interview focus**: Demonstrate understanding of concepts first
- **Incremental improvement**: Add smart pointers after RAII topic
- **Real-world scenario**: Many legacy codebases use raw pointers

---

