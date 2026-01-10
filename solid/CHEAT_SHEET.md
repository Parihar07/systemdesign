# SOLID Principles - Quick Reference Cheat Sheet

```
╔══════════════════════════════════════════════════════════════════════════╗
║                        SOLID PRINCIPLES CHEAT SHEET                       ║
╚══════════════════════════════════════════════════════════════════════════╝

┌─────────────────────────────────────────────────────────────────────────┐
│ S - SINGLE RESPONSIBILITY PRINCIPLE                                      │
├─────────────────────────────────────────────────────────────────────────┤
│ "A class should have one, and only one, reason to change"               │
│                                                                           │
│ ❌ BAD:  class User { save(); email(); validate(); report(); }          │
│ ✅ GOOD: class User { }                                                  │
│          class UserRepository { save(); }                                │
│          class EmailService { send(); }                                  │
│          class UserValidator { validate(); }                             │
│                                                                           │
│ KEY: One class = One responsibility = One reason to change               │
└─────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────┐
│ O - OPEN/CLOSED PRINCIPLE                                                │
├─────────────────────────────────────────────────────────────────────────┤
│ "Open for extension, closed for modification"                            │
│                                                                           │
│ ❌ BAD:  switch(type) { case A: ...; case B: ...; }                     │
│          // Adding C requires modifying this code                        │
│                                                                           │
│ ✅ GOOD: class Shape { virtual area() = 0; }                            │
│          class Circle : Shape { area() { ... } }                         │
│          class Square : Shape { area() { ... } }                         │
│          // Add Triangle without changing existing code                  │
│                                                                           │
│ KEY: Extend via inheritance/composition, not by modifying                │
└─────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────┐
│ L - LISKOV SUBSTITUTION PRINCIPLE                                        │
├─────────────────────────────────────────────────────────────────────────┤
│ "Subtypes must be substitutable for their base types"                    │
│                                                                           │
│ ❌ BAD:  void process(Rectangle& r) {                                   │
│            r.setWidth(5); r.setHeight(4);                                │
│            assert(r.area() == 20); // Fails if r is Square!              │
│          }                                                                │
│                                                                           │
│ ✅ GOOD: Don't inherit Square from Rectangle                            │
│          Both should inherit from Shape                                  │
│                                                                           │
│ KEY: Child class must honor parent's contract                            │
│      Can strengthen postconditions, weaken preconditions                 │
└─────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────┐
│ I - INTERFACE SEGREGATION PRINCIPLE                                      │
├─────────────────────────────────────────────────────────────────────────┤
│ "Clients shouldn't depend on interfaces they don't use"                  │
│                                                                           │
│ ❌ BAD:  class Worker { work(); eat(); sleep(); getSalary(); }          │
│          class Robot : Worker {                                          │
│            eat() { throw "Can't eat!"; } // Forced to implement          │
│          }                                                                │
│                                                                           │
│ ✅ GOOD: class Workable { work(); }                                     │
│          class Eatable { eat(); }                                        │
│          class Payable { getSalary(); }                                  │
│          class Robot : Workable { } // Only what it needs                │
│                                                                           │
│ KEY: Many small interfaces > One large interface                         │
└─────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────┐
│ D - DEPENDENCY INVERSION PRINCIPLE                                       │
├─────────────────────────────────────────────────────────────────────────┤
│ "Depend on abstractions, not concretions"                                │
│                                                                           │
│ ❌ BAD:  class Service {                                                │
│            MySQLDatabase db; // Tightly coupled                          │
│            Service() { db = new MySQLDatabase(); }                       │
│          }                                                                │
│                                                                           │
│ ✅ GOOD: class IDatabase { virtual save() = 0; }                        │
│          class Service {                                                 │
│            IDatabase* db; // Depends on abstraction                      │
│            Service(IDatabase* d) : db(d) {} // DI                        │
│          }                                                                │
│                                                                           │
│ KEY: High-level ← abstraction → Low-level                                │
│      Inject dependencies, don't create them                              │
└─────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════╗
║                              QUICK DIAGNOSTICS                            ║
╚══════════════════════════════════════════════════════════════════════════╝

🚩 VIOLATES SRP IF:
   • Class name has "And", "Manager", "Handler"
   • Class > 300 lines
   • Many unrelated public methods
   • Multiple reasons to change

🚩 VIOLATES OCP IF:
   • Switch/if-else on type codes
   • Must modify existing code for new features
   • Copy-paste to extend behavior

🚩 VIOLATES LSP IF:
   • Subclass throws unexpected exceptions
   • Can't substitute child for parent
   • Empty/no-op overrides
   • Subclass weakens guarantees

🚩 VIOLATES ISP IF:
   • Interface has >10 methods
   • Clients implement unused methods
   • Lots of empty implementations
   • NotImplementedException thrown

🚩 VIOLATES DIP IF:
   • Concrete classes in constructor
   • "new" keyword in business logic
   • Hard to mock for testing
   • Can't swap implementations

╔══════════════════════════════════════════════════════════════════════════╗
║                           INTERVIEW MNEMONICS                             ║
╚══════════════════════════════════════════════════════════════════════════╝

S = "One class, one job"
O = "Extend, don't modify"
L = "Don't break parent's promises"
I = "Small interfaces, big flexibility"
D = "Abstractions are your friends"

╔══════════════════════════════════════════════════════════════════════════╗
║                              WHEN TO APPLY                                ║
╚══════════════════════════════════════════════════════════════════════════╝

✅ ALWAYS: SRP, DIP (fundamental to good design)
✅ LARGE SYSTEMS: OCP, ISP (prevents change ripples)
✅ INHERITANCE: LSP (ensures correctness)
⚠️  PROTOTYPES: Can defer, but plan to refactor
⚠️  TINY PROJECTS: Don't over-engineer

╔══════════════════════════════════════════════════════════════════════════╗
║                         BENEFITS OF SOLID                                 ║
╚══════════════════════════════════════════════════════════════════════════╝

📦 MAINTAINABILITY:  Easy to understand and modify
🧪 TESTABILITY:      Easy to write unit tests
🔄 FLEXIBILITY:      Easy to extend and adapt
🐛 DEBUGGABILITY:    Easy to isolate issues
👥 COLLABORATION:    Clear boundaries for team work
📈 SCALABILITY:      Grows without becoming mess

╔══════════════════════════════════════════════════════════════════════════╗
║                         RELATED PATTERNS                                  ║
╚══════════════════════════════════════════════════════════════════════════╝

Strategy Pattern      → OCP, DIP
Factory Pattern       → OCP, DIP
Decorator Pattern     → OCP, LSP
Adapter Pattern       → LSP, ISP
Observer Pattern      → OCP, DIP
Repository Pattern    → SRP, DIP
Service Layer         → SRP, DIP
Dependency Injection  → DIP

╔══════════════════════════════════════════════════════════════════════════╗
║                      INTERVIEW RESPONSE TEMPLATE                          ║
╚══════════════════════════════════════════════════════════════════════════╝

When asked about SOLID:

1. DEFINE: State the principle clearly
2. EXAMPLE: Provide code example (bad vs good)
3. BENEFIT: Explain why it matters
4. EXPERIENCE: Share when you've applied it
5. TRADEOFF: Mention when you might not use it

Example: "SOLID principles are five design principles for OOP..."
         [Show code example]
         "This makes code more maintainable because..."
         "In my last project, I applied SRP when..."
         "Though for small utilities, I might simplify..."

╔══════════════════════════════════════════════════════════════════════════╗
║                        COMMON MISTAKES TO AVOID                           ║
╚══════════════════════════════════════════════════════════════════════════╝

❌ Over-engineering simple code
❌ Creating interfaces for everything
❌ Too many small classes (analysis paralysis)
❌ Applying without understanding why
❌ Religious adherence without pragmatism

✅ Apply when complexity justifies it
✅ Balance theory with practical needs
✅ Refactor to SOLID as code grows
✅ Understand the "why" behind each principle

╔══════════════════════════════════════════════════════════════════════════╗
║                          FINAL WISDOM                                     ║
╚══════════════════════════════════════════════════════════════════════════╝

"SOLID principles are guidelines, not laws.
 Apply them where they add value.
 Know them well enough to explain why you deviate.
 Code that works today and adapts tomorrow wins."

            - Every Senior Engineer Ever
```
