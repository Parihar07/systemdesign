# Templates & Generics (C++)

Learn how to write reusable, type-safe code using C++ templates.

## What & Why
- Templates let you write one function/class for many types.
- Avoids code duplication while staying type-safe (checked at compile time).
- Enables zero-cost abstractions (no runtime overhead when used well).

## Core Syntax (minimal)
```cpp
// Function template
template <typename T>
T add(T a, T b) { return a + b; }

// Class template
template <class T>
class Box {
    T side;
public:
    explicit Box(T s) : side(s) {}
    T area() const { return side * side; }
};

// Usage
int si = add<int>(2, 3);
double sd = add(2.5, 4.1);      // type deduced
auto bi = Box<int>(4);
auto bd = Box<double>(3.2);
```

## Files
- `genrics_basic.cpp` — basic function template (`addnum`) and class template (`Box<T>`), with simple I/O.
- `concepts_vs_sfinae.cpp` — SFINAE (`enable_if`/`void_t`) examples (C++17 compilable) + C++20 concepts documented as comments.
- `makefile` — supports `STD` override (defaults to C++17 for compatibility).

## Build & Run
```bash
cd generics
# basics
make FILE=genrics_basic.cpp run
# SFINAE constraints (C++17, concepts documented as theory)
make FILE=concepts_vs_sfinae.cpp run
```

## Next Steps (planned)
- Template specialization (full and partial).
- Perfect forwarding, `std::forward`, and move-aware templates.
- Type traits overview (`std::enable_if`, `std::bool_constant`, `std::is_*`).
- Variadic templates (packs) for flexible APIs.

## Interview Pointers
- Be ready to explain: why templates over macros; compile-time vs runtime polymorphism; instantiation and code bloat considerations.
- Mention constraint mechanisms (concepts/`requires`) to produce better errors and avoid unintended overloads.
- Know rule of 0/3/5 when templates manage resources.
