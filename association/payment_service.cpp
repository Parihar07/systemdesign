/*
Payment Service System - Interview Problem
Task:
Implement a Payment Service System demonstrating OOP relationships and polymorphism.

Entities:
PaymentMethod (Base/Abstract): abstract base for all payment methods
  - makePayment(amount) - pure virtual
  - getPaymentType() - pure virtual

CreditCard (IS-A PaymentMethod): cardNumber, cvv, expiryDate
DebitCard (IS-A PaymentMethod): cardNumber, pin, bankName
UPI (IS-A PaymentMethod): upiId, phoneNumber
Wallet (IS-A PaymentMethod): walletId, balance

Transaction: transactionId, amount, status, timestamp (owned by Payment)
Payment: paymentId, amount, PaymentMethod*, Transaction (composition)

PaymentService: list of Payment history (aggregation)

Relationships Required:
Inheritance (IS-A): CreditCard/DebitCard/UPI/Wallet IS-A PaymentMethod
Polymorphism: makePayment() - runtime dispatch based on payment type
Composition (Dies together): Payment HAS Transaction (dies with Payment)
Aggregation (Independent): PaymentService HAS Payments (payments can exist independently)
Association (Temporary): PaymentService processes PaymentMethod
*/

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// COMPOSITION: Transaction is owned by Payment - dies with Payment
class Transaction {
private:
    string transactionId;
    double amount;
    string status;  // "SUCCESS", "FAILED", "PENDING"
    time_t timestamp;

public:
    Transaction(string txnId, double amt, string stat)
        : transactionId(txnId), amount(amt), status(stat) {
        timestamp = time(nullptr);
        cout << "Transaction Constructor: " << transactionId << endl;
    }

    ~Transaction() {
        cout << "Transaction Destructor: " << transactionId << endl;
    }

    void showInfo() {
        cout << "  Transaction ID: " << transactionId << endl;
        cout << "  Amount: Rs. " << amount << endl;
        cout << "  Status: " << status << endl;
        cout << "  Timestamp: " << ctime(&timestamp);
    }

    string getStatus() { return status; }
};

// ABSTRACT BASE CLASS: PaymentMethod (for polymorphism)
class PaymentMethod {
protected:
    string paymentType;

public:
    PaymentMethod(string type) : paymentType(type) {
        cout << "PaymentMethod Constructor: " << type << endl;
    }

    virtual ~PaymentMethod() {
        cout << "PaymentMethod Destructor: " << paymentType << endl;
    }

    // Pure virtual - MUST be implemented by derived classes
    virtual bool makePayment(double amount) = 0;
    virtual void showInfo() = 0;
    
    string getPaymentType() { return paymentType; }
};

// INHERITANCE: CreditCard IS-A PaymentMethod
class CreditCard : public PaymentMethod {
private:
    string cardNumber;
    string cvv;
    string expiryDate;
    double creditLimit;

public:
    CreditCard(string cardNum, string cv, string expiry, double limit)
        : PaymentMethod("Credit Card"), cardNumber(cardNum), cvv(cv), 
          expiryDate(expiry), creditLimit(limit) {
        cout << "CreditCard Constructor" << endl;
    }

    ~CreditCard() {
        cout << "CreditCard Destructor" << endl;
    }

    // POLYMORPHISM: Override makePayment
    bool makePayment(double amount) override {
        cout << "\nProcessing Credit Card payment..." << endl;
        if (amount <= creditLimit) {
            cout << "Payment of Rs. " << amount << " successful via Credit Card!" << endl;
            creditLimit -= amount;
            return true;
        } else {
            cout << "Payment failed! Insufficient credit limit." << endl;
            return false;
        }
    }

    void showInfo() override {
        cout << "Payment Type: " << paymentType << endl;
        cout << "Card Number: XXXX-XXXX-XXXX-" << cardNumber.substr(cardNumber.length() - 4) << endl;
        cout << "Expiry: " << expiryDate << endl;
        cout << "Available Credit: Rs. " << creditLimit << endl;
    }
};

// INHERITANCE: DebitCard IS-A PaymentMethod
class DebitCard : public PaymentMethod {
private:
    string cardNumber;
    string pin;
    string bankName;
    double balance;

public:
    DebitCard(string cardNum, string p, string bank, double bal)
        : PaymentMethod("Debit Card"), cardNumber(cardNum), pin(p), 
          bankName(bank), balance(bal) {
        cout << "DebitCard Constructor" << endl;
    }

    ~DebitCard() {
        cout << "DebitCard Destructor" << endl;
    }

    // POLYMORPHISM: Override makePayment
    bool makePayment(double amount) override {
        cout << "\nProcessing Debit Card payment..." << endl;
        if (amount <= balance) {
            cout << "Payment of Rs. " << amount << " successful via Debit Card!" << endl;
            balance -= amount;
            return true;
        } else {
            cout << "Payment failed! Insufficient balance." << endl;
            return false;
        }
    }

    void showInfo() override {
        cout << "Payment Type: " << paymentType << endl;
        cout << "Card Number: XXXX-XXXX-XXXX-" << cardNumber.substr(cardNumber.length() - 4) << endl;
        cout << "Bank: " << bankName << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

// INHERITANCE: UPI IS-A PaymentMethod
class UPI : public PaymentMethod {
private:
    string upiId;
    string phoneNumber;
    double balance;

public:
    UPI(string upi, string phone, double bal)
        : PaymentMethod("UPI"), upiId(upi), phoneNumber(phone), balance(bal) {
        cout << "UPI Constructor" << endl;
    }

    ~UPI() {
        cout << "UPI Destructor" << endl;
    }

    // POLYMORPHISM: Override makePayment
    bool makePayment(double amount) override {
        cout << "\nProcessing UPI payment..." << endl;
        if (amount <= balance) {
            cout << "Payment of Rs. " << amount << " successful via UPI!" << endl;
            balance -= amount;
            return true;
        } else {
            cout << "Payment failed! Insufficient UPI balance." << endl;
            return false;
        }
    }

    void showInfo() override {
        cout << "Payment Type: " << paymentType << endl;
        cout << "UPI ID: " << upiId << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

// INHERITANCE: Wallet IS-A PaymentMethod
class Wallet : public PaymentMethod {
private:
    string walletId;
    string walletName;
    double balance;

public:
    Wallet(string wId, string wName, double bal)
        : PaymentMethod("Wallet"), walletId(wId), walletName(wName), balance(bal) {
        cout << "Wallet Constructor" << endl;
    }

    ~Wallet() {
        cout << "Wallet Destructor" << endl;
    }

    // POLYMORPHISM: Override makePayment
    bool makePayment(double amount) override {
        cout << "\nProcessing Wallet payment..." << endl;
        if (amount <= balance) {
            cout << "Payment of Rs. " << amount << " successful via " << walletName << "!" << endl;
            balance -= amount;
            return true;
        } else {
            cout << "Payment failed! Insufficient wallet balance." << endl;
            return false;
        }
    }

    void showInfo() override {
        cout << "Payment Type: " << paymentType << endl;
        cout << "Wallet: " << walletName << endl;
        cout << "Wallet ID: " << walletId << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

// Payment class with composition (HAS Transaction)
class Payment {
private:
    string paymentId;
    double amount;
    PaymentMethod* method;  // ASSOCIATION: Payment uses PaymentMethod (no ownership)
    Transaction txn;        // COMPOSITION: Payment owns Transaction (dies together)

public:
    // Constructor: name, amount, paymentMethod pointer, and create Transaction
    Payment(string pId, double amt, PaymentMethod* pm)
        : paymentId(pId), amount(amt), method(pm), 
          txn("TXN" + pId, amt, "PENDING") {
        cout << "Payment Constructor: " << paymentId << endl;
    }

    ~Payment() {
        cout << "Payment Destructor: " << paymentId << endl;
    }

    // ASSOCIATION: Process payment using PaymentMethod (polymorphism in action)
    bool processPayment() {
        cout << "\n========== Processing Payment " << paymentId << " ==========\n";
        bool success = method->makePayment(amount);
        return success;
    }

    void showInfo() {
        cout << "\n----- Payment Details -----" << endl;
        cout << "Payment ID: " << paymentId << endl;
        cout << "Amount: Rs. " << amount << endl;
        cout << "\nPayment Method Details:" << endl;
        method->showInfo();
        cout << "\nTransaction Details:" << endl;
        txn.showInfo();
    }

    string getPaymentId() { return paymentId; }
};

// AGGREGATION: PaymentService HAS Payments (payments can exist independently)
class PaymentService {
private:
    vector<Payment*> paymentHistory;  // AGGREGATION: Using raw pointers (TODO: use shared_ptr after RAII)
    string serviceName;

public:
    PaymentService(string name) : serviceName(name) {
        cout << "PaymentService Constructor: " << serviceName << endl;
    }

    ~PaymentService() {
        cout << "PaymentService Destructor: " << serviceName << endl;
    }

    // AGGREGATION: Add payment to history (payments survive if service is destroyed)
    void addPayment(Payment* payment) {
        paymentHistory.push_back(payment);
        cout << "Payment " << payment->getPaymentId() << " added to service history" << endl;
    }

    void showAllPayments() {
        cout << "\n========== " << serviceName << " - Payment History ==========\n";
        cout << "Total Payments: " << paymentHistory.size() << endl;
        for (auto payment : paymentHistory) {
            payment->showInfo();
            cout << "----------------------------" << endl;
        }
    }
};

/*
UML Representation (Corrected)

INHERITANCE (IS-A):
    PaymentMethod ◁--- CreditCard
    PaymentMethod ◁--- DebitCard
    PaymentMethod ◁--- UPI
    PaymentMethod ◁--- Wallet

COMPOSITION (Dies Together - filled diamond):
    Payment ◆--- Transaction

AGGREGATION (Independent Lifetime - hollow diamond):
    PaymentService ◇--- Payment

ASSOCIATION (Temporary Relationship):
    Payment ---- PaymentMethod (via processPayment())

POLYMORPHISM:
    makePayment() - Pure virtual function
    Runtime dispatch based on actual payment type
*/

int main() {
    cout << "========== Payment Service System ==========\n\n";

    // Create different payment methods
    CreditCard creditCard("1234567890123456", "123", "12/2027", 50000.0);
    DebitCard debitCard("9876543210987654", "1234", "HDFC Bank", 25000.0);
    UPI upi("user@paytm", "9876543210", 10000.0);
    Wallet wallet("WALLET001", "Paytm Wallet", 5000.0);

    cout << "\n========== Creating Payment Service ==========\n";
    PaymentService paymentService("XYZ Payment Gateway");

    cout << "\n========== Creating Payments ==========\n";
    // Create payments: paymentId, amount, paymentMethod pointer
    Payment p1("PAY001", 15000.0, &creditCard);
    Payment p2("PAY002", 8000.0, &debitCard);
    Payment p3("PAY003", 5000.0, &upi);
    Payment p4("PAY004", 2000.0, &wallet);

    cout << "\n========== Adding Payments to Service (AGGREGATION) ==========\n";
    paymentService.addPayment(&p1);
    paymentService.addPayment(&p2);
    paymentService.addPayment(&p3);
    paymentService.addPayment(&p4);

    cout << "\n========== Processing Payments (POLYMORPHISM + ASSOCIATION) ==========\n";
    p1.processPayment();  // Calls CreditCard::makePayment() at runtime
    p2.processPayment();  // Calls DebitCard::makePayment() at runtime
    p3.processPayment();  // Calls UPI::makePayment() at runtime
    p4.processPayment();  // Calls Wallet::makePayment() at runtime

    cout << "\n========== Payment History ==========\n";
    paymentService.showAllPayments();

    cout << "\n========== Demonstrating Polymorphism ==========\n";
    // Base class pointer to demonstrate polymorphism
    PaymentMethod* paymentPtr = &creditCard;
    cout << "\nUsing base class pointer to CreditCard:" << endl;
    paymentPtr->showInfo();
    paymentPtr->makePayment(5000.0);

    paymentPtr = &upi;
    cout << "\nUsing base class pointer to UPI:" << endl;
    paymentPtr->showInfo();
    paymentPtr->makePayment(3000.0);

    cout << "\n========== END (Destructors will be called) ==========\n";
    return 0;
}
