#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
using namespace std;

/*
Problem Statement : Payment Service should be responsible for storing details and payments Methods(creditcard, debit card, UPI, Wallet)
that belong to user and also have makepayment method
*/
/*
UML Diagram (Corrected):

INHERITANCE (IS-A Relationships):
    Pay ◁--- Card          // Card IS-A Pay (implements interface)
    Card ◁--- DebitCard    // DebitCard IS-A Card
    Card ◁--- CreditCard   // CreditCard IS-A Card
    Pay ◁--- UPI           // UPI IS-A Pay (implements interface)
    Pay ◁--- Wallet        // Wallet IS-A Pay (implements interface)

POLYMORPHISM:
    - doPayment() is pure virtual in Pay
    - Each derived class provides its own implementation
    - Runtime dispatch via virtual function table (vtable)
*/
// ABSTRACT BASE CLASS: Pay interface for all payment methods
class Pay
{
public:
    virtual void doPayment() = 0; // Pure virtual - must be implemented by derived classes
    virtual ~Pay() = default;     // Virtual destructor for proper cleanup
};

// ABSTRACT BASE CLASS: Card (implements Pay and adds card-specific behavior)
class Card : public Pay
{
public:
    virtual void showCardDetails() = 0; // Pure virtual - card-specific details

    Card()
    {
        cout << "Card Constructor\n";
    }

    virtual ~Card()
    {
        cout << "Card Destructor\n";
    }
};

// INHERITANCE: DebitCard IS-A Card
class DebitCard : public Card
{
private:
    int cardnumber;
    // int cvv[4];
    // string expiry;

public:
    DebitCard(int dn) : cardnumber(dn)
    {
        cout << "DebitCard Constructor\n";
    }

    ~DebitCard()
    {
        cout << "DebitCard Destructor\n";
    }

    // POLYMORPHISM: Override showCardDetails()
    void showCardDetails() override
    {
        cout << "Debit Card Number: " << cardnumber << endl;
    }

    // POLYMORPHISM: Override doPayment() with debit card logic
    void doPayment() override
    {
        cout << "Processing Debit Card payment using card: " << cardnumber << endl;
    }
};

// INHERITANCE: CreditCard IS-A Card
class CreditCard : public Card
{
private:
    int cardnumber;
    // int cvv[4];
    // string expiry;

public:
    CreditCard(int dn) : cardnumber(dn)
    {
        cout << "CreditCard Constructor\n";
    }

    ~CreditCard()
    {
        cout << "CreditCard Destructor\n";
    }

    // POLYMORPHISM: Override showCardDetails()
    void showCardDetails() override
    {
        cout << "Credit Card Number: " << cardnumber << endl;
    }

    // POLYMORPHISM: Override doPayment() with credit card logic
    void doPayment() override
    {
        cout << "Processing Credit Card payment using card: " << cardnumber << endl;
    }
};

// INHERITANCE: UPI IS-A Pay
class UPI : public Pay
{
private:
    string upiId;

public:
    UPI(string id) : upiId(id)
    {
        cout << "UPI Constructor\n";
    }

    ~UPI()
    {
        cout << "UPI Destructor\n";
    }

    // POLYMORPHISM: Override doPayment() with UPI logic
    void doPayment() override
    {
        cout << "Processing UPI payment using ID: " << upiId << endl;
    }
};

// INHERITANCE: Wallet IS-A Pay
class Wallet : public Pay
{
private:
    string walletID;

public:
    Wallet(string id) : walletID(id)
    {
        cout << "Wallet Constructor\n";
    }

    ~Wallet()
    {
        cout << "Wallet Destructor\n";
    }

    // POLYMORPHISM: Override doPayment() with wallet logic
    void doPayment() override
    {
        cout << "Processing Wallet payment using ID: " << walletID << endl;
    }
};
// PaymentService: Manages multiple payment methods using smart pointers
class PaymentService
{
private:
    unordered_map<string, shared_ptr<Pay>> paymethod; // Store payment methods with RAII

public:
    // Add a payment method to the service (using smart pointer for memory management)
    void addPayment(const string &paymentname, shared_ptr<Pay> pm)
    {
        paymethod[paymentname] = pm; // Automatic memory management via shared_ptr
        cout << "Added payment method: " << paymentname << endl;
    }

    // Make payment using polymorphism (runtime dispatch to correct doPayment())
    void makePayment(const string &name)
    {
        if (paymethod.find(name) == paymethod.end())
        {
            cout << "Error: Payment method '" << name << "' not found!\n";
            return;
        }
        shared_ptr<Pay> p = paymethod[name];
        p->doPayment(); // POLYMORPHISM: Calls correct derived class method at runtime
    }
};

int main()
{
    cout << "========== Payment Service System ==========\n\n";

    PaymentService ps;

    cout << "\n----- Adding Payment Methods -----\n";
    ps.addPayment("pariharUpi", make_shared<UPI>("parihar07@yn"));
    ps.addPayment("pariharCC", make_shared<CreditCard>(1234));
    ps.addPayment("pariharDC", make_shared<DebitCard>(5678));
    ps.addPayment("pariharWallet", make_shared<Wallet>("WALLET123"));

    cout << "\n----- Making Payments (Polymorphism in Action) -----\n";
    ps.makePayment("pariharUpi");
    ps.makePayment("pariharCC");
    ps.makePayment("pariharDC");
    ps.makePayment("pariharWallet");

    cout << "\n----- Testing Error Handling -----\n";
    ps.makePayment("nonExistent"); // Should show error

    cout << "\n----- Demonstrating Polymorphism with Base Pointer -----\n";
    // Base class pointer pointing to derived class objects
    shared_ptr<Pay> payPtr1 = make_shared<CreditCard>(9999);
    shared_ptr<Pay> payPtr2 = make_shared<UPI>("test@upi");

    cout << "Using Pay* pointer to CreditCard:\n";
    payPtr1->doPayment(); // Calls CreditCard::doPayment() at runtime

    cout << "Using Pay* pointer to UPI:\n";
    payPtr2->doPayment(); // Calls UPI::doPayment() at runtime

    cout << "\n========== Destructors will be called automatically ==========\n";
    return 0;
}