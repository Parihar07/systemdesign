# UML Diagrams for Object Relationships

## Overview of Relationships

In Object-Oriented Design, we have several types of relationships between classes. Here's how they differ and how to represent them in UML.

---

## 1. Association (Uses-A)

**Definition:** A "uses-a" relationship. One object uses another, but neither owns the other.

**UML Notation:** Simple line connecting two classes

```
┌─────────────┐                    ┌─────────────┐
│   Driver    │ ───────────────>   │     Car     │
├─────────────┤                    ├─────────────┤
│ - name      │                    │ - model     │
├─────────────┤                    ├─────────────┤
│ + drive()   │                    │ + start()   │
└─────────────┘                    └─────────────┘
```

**Characteristics:**
- Independent lifetimes
- Loose coupling
- Typically implemented as a function parameter or temporary reference
- Arrow shows direction of dependency

**Code Pattern:**
```cpp
class Driver {
    void drive(const Car& car) {  // Uses a Car
        car.startEngine();
    }
};
```

---

## Association vs Aggregation: The Critical Difference

**Both use references/pointers and don't own the object, but:**

```
ASSOCIATION (Temporary):
┌─────────────┐
│   Reader    │
│             │ ─── read(Book&) ──> Uses Book temporarily
│ (no Book    │                     (only during function call)
│  member!)   │
└─────────────┘

AGGREGATION (Persistent):
┌─────────────────────┐
│   Library           │
│                     │
│  vector<Book*>  ◇───┼───> Stores Books persistently
│                     │     (can access anytime)
└─────────────────────┘
```

**Key Difference:**
- **Association:** No member variable stores the reference. Relationship exists only during a function call.
- **Aggregation:** A member variable (pointer/reference) stores the relationship. It persists.

---

## 2. Aggregation (Shared Has-A)

**Definition:** A "has-a" relationship where the part can exist independently of the whole.

**UML Notation:** Line with a **hollow diamond** on the container side

```
┌─────────────────┐                    ┌─────────────┐
│   Department    │ ◇─────────────────>│  Professor  │
├─────────────────┤                    ├─────────────┤
│ - name          │                    │ - name      │
├─────────────────┤                    ├─────────────┤
│ + addProf()     │                    │ + teach()   │
└─────────────────┘                    └─────────────┘
     (whole)                               (part)
```

**Characteristics:**
- Shared ownership (multiple objects can reference the same part)
- Part can exist independently
- Typically implemented with `std::shared_ptr`
- Hollow diamond (◇) indicates "weak" ownership

**Code Pattern:**
```cpp
class Department {
    std::vector<std::shared_ptr<Professor>> m_professors;
    // Professor can exist even if Department is destroyed
};
```

**Memory View:**
```
┌──────────────────┐
│   Department     │
│  ┌────────────┐  │       ┌──────────────┐
│  │ shared_ptr │──┼──────>│  Professor   │<─── Can be shared
│  │ shared_ptr │──┼───┐   └──────────────┘    by other objects
│  └────────────┘  │   │
└──────────────────┘   │   ┌──────────────┐
                       └──>│  Professor   │
                           └──────────────┘
```

---

## 3. Composition (Owned Has-A)

**Definition:** A "has-a" relationship where the part CANNOT exist independently of the whole.

**UML Notation:** Line with a **filled diamond** on the container side

```
┌─────────────────┐                    ┌─────────────┐
│      Car        │ ◆─────────────────>│   Engine    │
├─────────────────┤                    ├─────────────┤
│ - model         │                    │ - hp        │
├─────────────────┤                    ├─────────────┤
│ + drive()       │                    │ + start()   │
└─────────────────┘                    └─────────────┘
     (whole)                               (part)
```

**Characteristics:**
- Exclusive ownership (only one object owns the part)
- Part is destroyed when the whole is destroyed
- Typically implemented as direct member or `std::unique_ptr`
- Filled diamond (◆) indicates "strong" ownership

**Code Pattern (Direct Member):**
```cpp
class Car {
    Engine m_engine;  // Engine is part of Car's memory
    // Engine is destroyed when Car is destroyed
};
```

**Code Pattern (unique_ptr):**
```cpp
class Laptop {
    std::unique_ptr<Battery> m_battery;  // Exclusive ownership
    // Battery is destroyed when Laptop is destroyed
};
```

**Memory View (Direct Member):**
```
┌──────────────────────────┐
│         Car              │
│  ┌────────────────────┐  │
│  │      Engine        │  │  <── Engine lives inside Car's memory
│  │  - horsepower      │  │
│  └────────────────────┘  │
└──────────────────────────┘
```

**Memory View (unique_ptr):**
```
┌──────────────────┐
│     Laptop       │
│  ┌────────────┐  │       ┌──────────────┐
│  │ unique_ptr │──┼──────>│   Battery    │ <── Exclusively owned
│  └────────────┘  │       └──────────────┘    Cannot be shared
└──────────────────┘
```

---

## 4. Inheritance (Is-A)

**Definition:** A "is-a" relationship. The derived class is a specialized version of the base class.

**UML Notation:** Line with a **hollow triangle** pointing to the base class

```
        ┌─────────────┐
        │   Shape     │ <──────── Base class
        ├─────────────┤
        │ + draw()    │
        └─────────────┘
               △
               │
       ┌───────┴───────┐
       │               │
┌─────────────┐ ┌─────────────┐
│   Circle    │ │  Rectangle  │ <──── Derived classes
├─────────────┤ ├─────────────┤
│ + draw()    │ │ + draw()    │
└─────────────┘ └─────────────┘
```

**Characteristics:**
- "Is-a" relationship (Circle IS-A Shape)
- Tight coupling at compile time
- Enables polymorphism with virtual functions
- Hollow triangle (△) points to the base/parent class

---

## Quick Reference: When to Use What?

### Use **Association** when:
- One object temporarily uses another
- No ownership relationship
- Objects are completely independent
- Example: `Driver` uses a `Car`, `Student` registers for a `Course`

### Use **Aggregation** when:
- "Has-a" relationship with shared ownership
- Part can exist without the whole
- Multiple containers might reference the same part
- Example: `Department` has `Professor`s, `Playlist` has `Song`s

### Use **Composition** when:
- "Has-a" relationship with exclusive ownership
- Part cannot exist without the whole
- Part's lifetime is tied to the whole
- Example: `Car` has an `Engine`, `House` has `Room`s

### Use **Inheritance** when:
- "Is-a" relationship
- Need polymorphic behavior
- Shared interface and behavior
- Example: `Circle` is a `Shape`, `Dog` is an `Animal`

---

## Complete Example: University System

Here's how these relationships work together in a real system:

```
        ┌──────────────┐
        │   Person     │ <────────── Base class
        ├──────────────┤
        │ - name       │
        │ + getName()  │
        └──────────────┘
               △
               │
       ┌───────┴────────┐
       │                │
┌──────────────┐  ┌─────────────┐
│  Professor   │  │   Student   │ <── Inheritance (Is-A)
├──────────────┤  ├─────────────┤
│ - empID      │  │ - studentID │
└──────────────┘  └─────────────┘
       △                  │
       │                  │
       ◇                  │ (Association)
       │                  │
┌──────────────┐          │
│ Department   │          │
├──────────────┤          │
│ - name       │          ▽
│ - profs ◇────┼───> Professor teaches ────> Course
└──────────────┘          │
                          │
                          ◆
                          │
                    ┌─────────────┐
                    │   Syllabus  │ <── Composition (Owned Has-A)
                    ├─────────────┤
                    │ - topics    │
                    └─────────────┘
```

**Explanation:**
1. **Inheritance:** `Professor` and `Student` both inherit from `Person` (they ARE persons)
2. **Aggregation:** `Department` has `Professor`s (professors can exist without the department)
3. **Composition:** `Course` has a `Syllabus` (syllabus cannot exist without the course)
4. **Association:** `Professor` teaches `Course` (temporary relationship)

---

## Interview Tips

**Q: What's the difference between Aggregation and Composition?**

**A:** Both are "has-a" relationships, but:
- **Aggregation:** Shared ownership (◇). Part survives if whole is destroyed. Use `shared_ptr`.
- **Composition:** Exclusive ownership (◆). Part dies with whole. Use direct member or `unique_ptr`.

**Q: When should I prefer Composition over Inheritance?**

**A:** Follow the principle "Favor composition over inheritance":
- Composition is more flexible (can change at runtime)
- Inheritance creates tight coupling
- Use inheritance only for true "is-a" relationships
- Use composition for "has-a" or "implemented-in-terms-of" relationships

---

## Summary Table

| Relationship  | Symbol | Ownership      | Independence | C++ Implementation              |
|---------------|--------|----------------|--------------|----------------------------------|
| Association   | ───>   | None           | Both live    | Function parameter, reference   |
| Aggregation   | ◇───>  | Shared         | Part lives   | `std::shared_ptr`               |
| Composition   | ◆───>  | Exclusive      | Part dies    | Direct member, `std::unique_ptr`|
| Inheritance   | △───   | N/A            | N/A          | `: public BaseClass`            |

