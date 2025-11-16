# Hospital Management System - Interview Problem

## Task
Implement a Hospital Management System in C++ demonstrating all 4 OOP relationships.

---

## Entities

**Person (Base):** name, age, contact  
**Doctor (IS-A Person):** specialization, empID → can examine(Patient)  
**Patient (IS-A Person):** patientID, condition  
**MedicalRecord:** diagnosis, treatment (owned by Patient - dies with it)  
**Department:** name, list of doctors (doctors survive if dept is destroyed)


## Relationships Required

1. **Inheritance (IS-A):** Doctor IS-A Person, Patient IS-A Person
2. **Composition (Dies together):** Patient HAS MedicalRecord (use direct member or `unique_ptr`)
3. **Aggregation (Independent):** Department HAS Doctors (use `shared_ptr`)
4. **Association (Temporary):** Doctor examines Patient (pass as function parameter)

---

## Must Show

- Object creation with printed messages
- Doctor examining patient
- Department listing doctors
- Objects destroyed: departments die, doctors survive, medical records die with patients

---

## Quick Start

```cpp
class Person { /* name, age */ };
class Doctor : public Person { /* specialization */ void examine(Patient&); };
class Patient : public Person { MedicalRecord m_record; /* composition */ };
class MedicalRecord { /* diagnosis */ };
class Department { vector<shared_ptr<Doctor>> m_doctors; };
```.  

Compile: `make FILE=your_file.cpp run`
