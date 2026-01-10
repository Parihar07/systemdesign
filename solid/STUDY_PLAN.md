# SOLID Principles - Morning Interview Prep Study Plan

## 30-Minute Quick Review (Day Of Interview)

### Minutes 0-5: Warm Up
- Open [CHEAT_SHEET.md](CHEAT_SHEET.md)
- Review the 5 principles with mnemonics
- Scan red flag diagnostics

### Minutes 5-15: Core Concepts
- Review each principle's definition
- Memorize one bad vs good example per principle
- Focus on the "why" behind each principle

### Minutes 15-25: Practice Articulation
Say out loud (or write):
1. "SOLID stands for..."
2. For each principle: "It means... For example... The benefit is..."
3. "They work together by..."

### Minutes 25-30: Real-World Connection
- Review the e-commerce example flow
- Think of one example from your own experience for each principle
- Prepare your "trade-offs" answer

---

## 2-Hour Deep Study Session

### Hour 1: Understanding

**00-15 min**: Single Responsibility Principle
- Run: `./01_srp_single_responsibility`
- Study: Employee, UserService, Invoice examples
- Exercise: Identify responsibilities in a class you wrote

**15-30 min**: Open/Closed Principle
- Run: `./02_ocp_open_closed`
- Study: Shape hierarchy, Payment processors
- Exercise: How would you add a new shape/payment method?

**30-45 min**: Liskov Substitution Principle
- Run: `./03_lsp_liskov_substitution`
- Study: Rectangle/Square problem, Bird hierarchy
- Exercise: Is Square really a Rectangle behaviorally?

**45-60 min**: Interface Segregation + Dependency Inversion
- Run: `./04_isp_interface_segregation`
- Run: `./05_dip_dependency_inversion`
- Study: Worker interfaces, Dependency injection patterns
- Exercise: Identify fat interfaces in code you know

### Hour 2: Integration & Practice

**00-30 min**: Complete E-Commerce System
- Run: `./06_real_world_ecommerce`
- Trace how all 5 principles work together
- Map: Which class demonstrates which principle(s)?

**30-45 min**: Interview Simulation
Read [INTERVIEW_GUIDE.md](INTERVIEW_GUIDE.md) and practice:
1. "Explain SOLID principles" (5 min answer)
2. "Design a payment system with SOLID" (whiteboard)
3. "Refactor this code" (pick a bad example)

**45-60 min**: Question Preparation
- Prepare answers for common questions
- Think of 2-3 experiences where you applied SOLID
- Prepare thoughtful "when to violate" answer

---

## 1-Week Study Plan

### Day 1: SRP & OCP
- Morning: Read theory, run examples
- Afternoon: Refactor your own code to apply SRP
- Evening: Add extension to existing code using OCP

### Day 2: LSP
- Morning: Study all LSP violations
- Afternoon: Find LSP violations in codebases you know
- Evening: Design proper inheritance hierarchies

### Day 3: ISP & DIP
- Morning: Study interface segregation
- Afternoon: Practice dependency injection
- Evening: Refactor code to use DI

### Day 4: Integration
- Study the complete e-commerce example
- Build your own mini-system using all 5 principles
- Example: Library management, Food delivery, etc.

### Day 5: Interview Practice
- Mock interview: Have someone ask you SOLID questions
- Whiteboard: Design systems from scratch
- Code review: Critique code for SOLID violations

### Day 6: Design Patterns Connection
- Study how Strategy pattern relates to OCP/DIP
- Study how Factory pattern uses SOLID
- Study Repository pattern and SRP/DIP

### Day 7: Review & Rest
- Quick review of CHEAT_SHEET.md
- Read your notes
- Get good sleep!

---

## Interview Question Categories

### Category 1: Definitions (Easy)
**Q**: "What does SOLID stand for?"
**A**: [Recite all 5 with brief definitions]

**Q**: "Explain Single Responsibility Principle"
**A**: [Definition + Example + Benefit]

### Category 2: Code Examples (Medium)
**Q**: "Show me an example of Open/Closed Principle"
**A**: [Write Shape hierarchy or Strategy pattern]

**Q**: "How does this code violate LSP?"
**A**: [Identify violation + explain why + fix it]

### Category 3: Design Problems (Hard)
**Q**: "Design a notification system following SOLID"
**A**: 
```cpp
// Abstraction (DIP)
class INotificationChannel {
    virtual void send(string msg) = 0;
};

// Extensions (OCP)
class EmailChannel : public INotificationChannel { };
class SMSChannel : public INotificationChannel { };

// Service (SRP + DIP)
class NotificationService {
    vector<INotificationChannel*> channels;
public:
    void notify(string msg) {
        for (auto* ch : channels) ch->send(msg);
    }
};
```

### Category 4: Experience (Behavioral)
**Q**: "Tell me about a time you applied SOLID principles"
**Prepare**: 2-3 stories with:
- Situation: What was the problem?
- Action: Which principle did you apply?
- Result: What improved?

### Category 5: Trade-offs (Senior)
**Q**: "When would you NOT follow SOLID?"
**Good Answer**: 
- Small utility classes might not need full SOLID
- Prototypes can defer for speed
- Performance-critical code might skip abstractions
- BUT: Always plan to refactor as code grows
- Key: Know principles well enough to justify deviations

---

## Practice Exercises

### Exercise 1: Identify Violations
Look at this code and identify SOLID violations:
```cpp
class OrderProcessor {
    void processOrder(Order o) {
        // Validate
        if (o.items.empty()) throw "Empty";
        
        // Calculate
        double total = 0;
        for (auto i : o.items) total += i.price;
        
        // Save to DB
        db.execute("INSERT INTO orders...");
        
        // Send email
        smtp.send(o.customer, "Order confirmed");
        
        // Print receipt
        cout << "Receipt: " << total;
    }
};
```

**Answer**: Violates SRP (5+ responsibilities)

### Exercise 2: Design Challenge
Design a payment processing system that:
- Supports credit card, PayPal, crypto
- Sends notifications
- Logs transactions
- Is testable
- Can add new payment methods easily

Use all SOLID principles.

### Exercise 3: Refactoring
Take a "God class" from your codebase and refactor it to follow SRP.
- List all responsibilities
- Create separate classes for each
- Use DIP to compose them

---

## Key Mantras for Interview

1. **SRP**: "One class, one job, one reason to change"
2. **OCP**: "Extend, don't modify"
3. **LSP**: "Child must honor parent's contract"
4. **ISP**: "Many small interfaces > one large"
5. **DIP**: "Depend on abstractions, inject dependencies"

---

## Final Checklist

Before interview, can you:

- [ ] Recite all 5 SOLID principles from memory?
- [ ] Give a code example for each principle?
- [ ] Explain why each principle matters?
- [ ] Identify violations in code?
- [ ] Design a system using SOLID?
- [ ] Discuss trade-offs intelligently?
- [ ] Share personal experience applying SOLID?
- [ ] Connect SOLID to design patterns?

If you can do all 8, you're ready! 🚀

---

## Resources in This Module

📖 Theory:
- [README.md](README.md) - Overview
- [INTERVIEW_GUIDE.md](INTERVIEW_GUIDE.md) - Deep dive
- [CHEAT_SHEET.md](CHEAT_SHEET.md) - Quick reference

💻 Code:
- `01_srp_single_responsibility.cpp` - SRP examples
- `02_ocp_open_closed.cpp` - OCP examples
- `03_lsp_liskov_substitution.cpp` - LSP examples
- `04_isp_interface_segregation.cpp` - ISP examples
- `05_dip_dependency_inversion.cpp` - DIP examples
- `06_real_world_ecommerce.cpp` - Complete system

🛠️ Tools:
- `makefile` - Build and run

---

## Success Tips

✅ **Do**:
- Explain the "why" behind principles
- Use concrete examples
- Admit trade-offs exist
- Connect to your experience
- Draw diagrams

❌ **Don't**:
- Be dogmatic ("SOLID is always right")
- Over-engineer in interviews
- Just memorize definitions
- Ignore context and requirements
- Forget that working code matters most

---

**Remember**: SOLID principles are tools in your toolbox. 
Show you understand them deeply and can apply them pragmatically.

Good luck with your interview! 🎯
