/**
 * LISKOV SUBSTITUTION PRINCIPLE (LSP)
 *
 * Definition: Objects of a superclass should be replaceable with objects of a
 * subclass without breaking the application.
 *
 * Key Points:
 * - Subtypes must be substitutable for their base types
 * - Derived classes must honor the contract of base classes
 * - Subclass should strengthen postconditions, not weaken them
 * - Subclass should weaken preconditions, not strengthen them
 * - Invariants of the base class must be preserved
 * - Proper inheritance: "IS-A" relationship must be behavioral, not just structural
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

// ============================================================================
// VIOLATION 1: Rectangle-Square Problem (Classic LSP Violation)
// ============================================================================

namespace bad_design_1
{

    class Rectangle
    {
    protected:
        int width;
        int height;

    public:
        virtual void setWidth(int w) { width = w; }
        virtual void setHeight(int h) { height = h; }

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        virtual int area() const
        {
            return width * height;
        }
    };

    // Problem: Square violates LSP
    class Square : public Rectangle
    {
    public:
        // Violates LSP: Changing width affects height (unexpected behavior)
        void setWidth(int w) override
        {
            width = w;
            height = w; // Side effect!
        }

        void setHeight(int h) override
        {
            height = h;
            width = h; // Side effect!
        }
    };

    // This function expects Rectangle's contract
    void processRectangle(Rectangle &rect)
    {
        rect.setWidth(5);
        rect.setHeight(4);

        // Expectation: area should be 5 * 4 = 20
        int expected = 5 * 4;
        int actual = rect.area();

        cout << "Expected area: " << expected << "\n";
        cout << "Actual area: " << actual << "\n";

        if (expected != actual)
        {
            cout << "ERROR: LSP Violation! Square broke Rectangle's contract!\n";
        }
    }
}

// ============================================================================
// CORRECT 1: Separate hierarchies for Rectangle and Square
// ============================================================================

namespace good_design_1
{

    // Abstract base for all shapes
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual int area() const = 0;
        virtual string getName() const = 0;
    };

    // Rectangle is a shape with independent width and height
    class Rectangle : public Shape
    {
    protected:
        int width;
        int height;

    public:
        Rectangle(int w, int h) : width(w), height(h) {}

        void setWidth(int w) { width = w; }
        void setHeight(int h) { height = h; }

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        int area() const override
        {
            return width * height;
        }

        string getName() const override
        {
            return "Rectangle";
        }
    };

    // Square is a shape with equal sides (NOT a Rectangle)
    class Square : public Shape
    {
    private:
        int side;

    public:
        Square(int s) : side(s) {}

        void setSide(int s) { side = s; }
        int getSide() const { return side; }

        int area() const override
        {
            return side * side;
        }

        string getName() const override
        {
            return "Square";
        }
    };

    // Now we can't pass Square where Rectangle is expected
    // This prevents the LSP violation
}

// ============================================================================
// VIOLATION 2: Bird Flying Problem
// ============================================================================

namespace bad_design_2
{

    class Bird
    {
    public:
        virtual ~Bird() = default;
        virtual void fly()
        {
            cout << "Flying high!\n";
        }

        virtual void eat()
        {
            cout << "Eating...\n";
        }
    };

    class Sparrow : public Bird
    {
    public:
        void fly() override
        {
            cout << "Sparrow flying!\n";
        }
    };

    // Problem: Penguin can't fly, but inherits fly()
    class Penguin : public Bird
    {
    public:
        void fly() override
        {
            // What to do here? Penguins can't fly!
            throw runtime_error("Penguins can't fly!"); // LSP violation!
            // or: do nothing (also a violation)
        }
    };

    class Ostrich : public Bird
    {
    public:
        void fly() override
        {
            // Same problem - ostriches can't fly
            cout << "I can't fly, I can only run!\n"; // LSP violation!
        }
    };

    void makeBirdFly(Bird &bird)
    {
        bird.fly(); // Crashes with Penguin, wrong behavior with Ostrich
    }
}

// ============================================================================
// CORRECT 2: Interface Segregation for Bird Types
// ============================================================================

namespace good_design_2
{

    // Base class for all birds
    class Bird
    {
    public:
        virtual ~Bird() = default;
        virtual void eat() = 0;
        virtual string getName() const = 0;
    };

    // Separate interface for flying capability
    class FlyingBird : public Bird
    {
    public:
        virtual void fly() = 0;
    };

    // Separate interface for swimming capability
    class SwimmingBird : public Bird
    {
    public:
        virtual void swim() = 0;
    };

    class Sparrow : public FlyingBird
    {
    public:
        void fly() override
        {
            cout << "Sparrow flying gracefully!\n";
        }

        void eat() override
        {
            cout << "Sparrow eating seeds...\n";
        }

        string getName() const override
        {
            return "Sparrow";
        }
    };

    class Eagle : public FlyingBird
    {
    public:
        void fly() override
        {
            cout << "Eagle soaring high!\n";
        }

        void eat() override
        {
            cout << "Eagle hunting prey...\n";
        }

        string getName() const override
        {
            return "Eagle";
        }
    };

    // Penguin can swim but can't fly
    class Penguin : public SwimmingBird
    {
    public:
        void swim() override
        {
            cout << "Penguin swimming underwater!\n";
        }

        void eat() override
        {
            cout << "Penguin eating fish...\n";
        }

        string getName() const override
        {
            return "Penguin";
        }
    };

    // Duck can both fly and swim
    class Duck : public FlyingBird, public SwimmingBird
    {
    public:
        void fly() override
        {
            cout << "Duck flying!\n";
        }

        void swim() override
        {
            cout << "Duck swimming!\n";
        }

        void eat() override
        {
            cout << "Duck eating...\n";
        }

        string getName() const override
        {
            return "Duck";
        }
    };

    // Now functions can be specific about requirements
    void makeFly(FlyingBird &bird)
    {
        bird.fly(); // Guaranteed to work
    }

    void makeSwim(SwimmingBird &bird)
    {
        bird.swim(); // Guaranteed to work
    }
}

// ============================================================================
// VIOLATION 3: Stack - ReadOnlyStack Problem
// ============================================================================

namespace bad_design_3
{

    class Stack
    {
    protected:
        vector<int> items;

    public:
        virtual void push(int item)
        {
            items.push_back(item);
        }

        virtual int pop()
        {
            if (items.empty())
                throw runtime_error("Stack empty");
            int item = items.back();
            items.pop_back();
            return item;
        }

        virtual int size() const
        {
            return items.size();
        }
    };

    // Problem: ReadOnlyStack can't fulfill Stack's contract
    class ReadOnlyStack : public Stack
    {
    public:
        void push(int item) override
        {
            // What to do? We're supposed to be read-only!
            throw runtime_error("Cannot push to read-only stack!"); // LSP violation!
        }
    };

    void useStack(Stack &stack)
    {
        stack.push(10); // Crashes with ReadOnlyStack!
        stack.push(20);
    }
}

// ============================================================================
// CORRECT 3: Proper Stack Hierarchy
// ============================================================================

namespace good_design_3
{

    // Base interface for reading from stack
    class ReadableStack
    {
    public:
        virtual ~ReadableStack() = default;
        virtual int peek() const = 0;
        virtual int size() const = 0;
        virtual bool isEmpty() const = 0;
    };

    // Full stack extends readable with write operations
    class Stack : public ReadableStack
    {
    protected:
        vector<int> items;

    public:
        void push(int item)
        {
            items.push_back(item);
        }

        int pop()
        {
            if (items.empty())
                throw runtime_error("Stack empty");
            int item = items.back();
            items.pop_back();
            return item;
        }

        int peek() const override
        {
            if (items.empty())
                throw runtime_error("Stack empty");
            return items.back();
        }

        int size() const override
        {
            return items.size();
        }

        bool isEmpty() const override
        {
            return items.empty();
        }
    };

    // Now we can use ReadableStack where we only need reading
    void printStackSize(const ReadableStack &stack)
    {
        cout << "Stack size: " << stack.size() << "\n";
    }
}

// ============================================================================
// REAL-WORLD EXAMPLE: Account System
// ============================================================================

namespace account_system
{

    // Base account with common operations
    class Account
    {
    protected:
        string accountNumber;
        double balance;

    public:
        Account(const string &accNum, double bal)
            : accountNumber(accNum), balance(bal) {}

        virtual ~Account() = default;

        string getAccountNumber() const { return accountNumber; }
        double getBalance() const { return balance; }

        // All accounts can be debited (with proper checks)
        virtual bool debit(double amount)
        {
            if (amount <= 0)
            {
                cout << "Invalid amount\n";
                return false;
            }
            if (balance >= amount)
            {
                balance -= amount;
                cout << "Debited $" << amount << " from " << accountNumber << "\n";
                return true;
            }
            cout << "Insufficient funds\n";
            return false;
        }

        // All accounts can be credited
        virtual void credit(double amount)
        {
            if (amount <= 0)
            {
                cout << "Invalid amount\n";
                return;
            }
            balance += amount;
            cout << "Credited $" << amount << " to " << accountNumber << "\n";
        }

        virtual string getAccountType() const = 0;
    };

    // Savings account - maintains base contract
    class SavingsAccount : public Account
    {
    private:
        double interestRate;

    public:
        SavingsAccount(const string &accNum, double bal, double rate)
            : Account(accNum, bal), interestRate(rate) {}

        void addInterest()
        {
            double interest = balance * interestRate;
            credit(interest);
        }

        string getAccountType() const override
        {
            return "Savings Account";
        }
    };

    // Checking account with overdraft - extends base behavior
    class CheckingAccount : public Account
    {
    private:
        double overdraftLimit;

    public:
        CheckingAccount(const string &accNum, double bal, double overdraft)
            : Account(accNum, bal), overdraftLimit(overdraft) {}

        // Overrides but maintains contract (strengthens postcondition)
        bool debit(double amount) override
        {
            if (amount <= 0)
            {
                cout << "Invalid amount\n";
                return false;
            }
            // Can go negative up to overdraft limit
            if (balance + overdraftLimit >= amount)
            {
                balance -= amount;
                cout << "Debited $" << amount << " from " << accountNumber;
                if (balance < 0)
                {
                    cout << " (using overdraft)";
                }
                cout << "\n";
                return true;
            }
            cout << "Exceeds overdraft limit\n";
            return false;
        }

        string getAccountType() const override
        {
            return "Checking Account";
        }
    };

    // Fixed deposit - properly restricts operations
    class FixedDepositAccount : public Account
    {
    private:
        int maturityMonths;
        int currentMonth;

    public:
        FixedDepositAccount(const string &accNum, double bal, int months)
            : Account(accNum, bal), maturityMonths(months), currentMonth(0) {}

        // Properly restricts debit until maturity
        bool debit(double amount) override
        {
            if (currentMonth < maturityMonths)
            {
                cout << "Cannot withdraw before maturity!\n";
                return false;
            }
            return Account::debit(amount);
        }

        void incrementMonth()
        {
            currentMonth++;
            cout << "Month " << currentMonth << " of " << maturityMonths << "\n";
        }

        string getAccountType() const override
        {
            return "Fixed Deposit Account";
        }
    };

    // Banking operations that work with any account
    class BankingService
    {
    public:
        void transfer(Account &from, Account &to, double amount)
        {
            cout << "\n--- Transfer Operation ---\n";
            if (from.debit(amount))
            {
                to.credit(amount);
                cout << "Transfer successful!\n";
            }
            else
            {
                cout << "Transfer failed!\n";
            }
        }

        void printAccountInfo(Account &account)
        {
            cout << "\n"
                 << account.getAccountType() << "\n";
            cout << "Account #: " << account.getAccountNumber() << "\n";
            cout << "Balance: $" << account.getBalance() << "\n";
        }
    };
}

// ============================================================================
// EXAMPLE: Collection Interfaces
// ============================================================================

namespace collection_system
{

    // Read-only collection
    class ReadOnlyCollection
    {
    public:
        virtual ~ReadOnlyCollection() = default;
        virtual int get(size_t index) const = 0;
        virtual size_t size() const = 0;
        virtual bool contains(int value) const = 0;
    };

    // Mutable collection extends read-only
    class MutableCollection : public ReadOnlyCollection
    {
    public:
        virtual void add(int value) = 0;
        virtual void remove(int value) = 0;
        virtual void clear() = 0;
    };

    // ArrayList implementation
    class ArrayList : public MutableCollection
    {
    private:
        vector<int> data;

    public:
        void add(int value) override
        {
            data.push_back(value);
        }

        void remove(int value) override
        {
            data.erase(std::remove(data.begin(), data.end(), value), data.end());
        }

        void clear() override
        {
            data.clear();
        }

        int get(size_t index) const override
        {
            if (index >= data.size())
                throw out_of_range("Index out of bounds");
            return data[index];
        }

        size_t size() const override
        {
            return data.size();
        }

        bool contains(int value) const override
        {
            return find(data.begin(), data.end(), value) != data.end();
        }
    };

    // Functions that accept appropriate abstraction levels
    void printCollection(const ReadOnlyCollection &collection)
    {
        cout << "Collection [";
        for (size_t i = 0; i < collection.size(); ++i)
        {
            cout << collection.get(i);
            if (i < collection.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
    }
}

// ============================================================================
// MAIN: Demonstration
// ============================================================================

int main()
{
    cout << "=== LISKOV SUBSTITUTION PRINCIPLE (LSP) ===\n\n";

    // Bad Design 1: Rectangle-Square
    cout << "--- BAD DESIGN: Rectangle-Square Problem ---\n";
    bad_design_1::Rectangle rect;
    cout << "Processing Rectangle:\n";
    bad_design_1::processRectangle(rect);

    cout << "\nProcessing Square (violates LSP):\n";
    bad_design_1::Square square;
    bad_design_1::processRectangle(square);

    // Good Design 1: Proper Shape Hierarchy
    cout << "\n--- GOOD DESIGN: Separate Shape Classes ---\n";
    good_design_1::Rectangle goodRect(5, 4);
    good_design_1::Square goodSquare(5);
    cout << goodRect.getName() << " area: " << goodRect.area() << "\n";
    cout << goodSquare.getName() << " area: " << goodSquare.area() << "\n";

    // Bad Design 2: Bird Flying
    cout << "\n--- BAD DESIGN: Bird Flying Problem ---\n";
    bad_design_2::Sparrow sparrow;
    bad_design_2::makeBirdFly(sparrow);

    try
    {
        bad_design_2::Penguin penguin;
        bad_design_2::makeBirdFly(penguin); // Throws exception!
    }
    catch (const exception &e)
    {
        cout << "Exception: " << e.what() << "\n";
    }

    // Good Design 2: Proper Bird Hierarchy
    cout << "\n--- GOOD DESIGN: Segregated Bird Interfaces ---\n";
    good_design_2::Sparrow goodSparrow;
    good_design_2::Eagle eagle;
    good_design_2::Penguin goodPenguin;
    good_design_2::Duck duck;

    good_design_2::makeFly(goodSparrow);
    good_design_2::makeFly(eagle);
    // Can't call makeFly with penguin - compile error (good!)
    good_design_2::makeSwim(goodPenguin);
    good_design_2::makeFly(duck);
    good_design_2::makeSwim(duck);

    // Account System Demo
    cout << "\n--- ACCOUNT SYSTEM (LSP Compliant) ---\n";
    account_system::SavingsAccount savings("SAV001", 1000.0, 0.05);
    account_system::CheckingAccount checking("CHK001", 500.0, 200.0);
    account_system::FixedDepositAccount fd("FD001", 5000.0, 12);

    account_system::BankingService bank;
    bank.printAccountInfo(savings);
    bank.printAccountInfo(checking);
    bank.printAccountInfo(fd);

    // All accounts can be used polymorphically
    bank.transfer(savings, checking, 300.0);
    bank.transfer(checking, savings, 100.0);

    // Fixed deposit respects its constraints
    fd.debit(1000.0); // Will fail - not matured

    // Collection System Demo
    cout << "\n--- COLLECTION SYSTEM ---\n";
    collection_system::ArrayList list;
    list.add(10);
    list.add(20);
    list.add(30);

    collection_system::printCollection(list);
    cout << "Contains 20? " << (list.contains(20) ? "Yes" : "No") << "\n";

    cout << "\n=== KEY TAKEAWAYS ===\n";
    cout << "1. Subclasses must honor base class contracts\n";
    cout << "2. Don't inherit when IS-A relationship is only structural\n";
    cout << "3. Subclass should strengthen postconditions (do more)\n";
    cout << "4. Subclass should weaken preconditions (accept more)\n";
    cout << "5. Throwing exceptions where base doesn't is a violation\n";
    cout << "6. Think about behavioral substitutability, not just structure\n";

    return 0;
}
