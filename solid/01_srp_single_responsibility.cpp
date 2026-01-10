/**
 * SINGLE RESPONSIBILITY PRINCIPLE (SRP)
 *
 * Definition: A class should have one, and only one, reason to change.
 *
 * Key Points:
 * - Each class should have a single, well-defined responsibility
 * - Responsibilities = reasons to change
 * - Promotes high cohesion and low coupling
 * - Makes code easier to understand, test, and maintain
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>

using namespace std;

// ============================================================================
// VIOLATION: Class with multiple responsibilities
// ============================================================================

namespace bad_design
{
    class Employee
    {
    private:
        string name;
        string email;
        double salary;

    public:
        Employee(const string &n, const string &e, double s)
            : name(n), email(e), salary(s) {}

        // Responsibility 1: Business logic
        double calculateBonus()
        {
            return salary * 0.1;
        }

        // Responsibility 2: Database operations
        void saveToDatabase()
        {
            cout << "Saving " << name << " to database...\n";
            // Database connection, SQL queries, etc.
        }

        // Responsibility 3: Email notifications
        void sendWelcomeEmail()
        {
            cout << "Sending welcome email to " << email << "\n";
            // SMTP connection, email formatting, etc.
        }

        // Responsibility 4: Report generation
        string generatePayslip()
        {
            stringstream ss;
            ss << "=== PAYSLIP ===\n";
            ss << "Name: " << name << "\n";
            ss << "Salary: $" << salary << "\n";
            ss << "Bonus: $" << calculateBonus() << "\n";
            return ss.str();
        }

        // Responsibility 5: Validation
        bool validateEmail()
        {
            return email.find('@') != string::npos;
        }
    };

    // Problems with this design:
    // 1. If database schema changes, Employee class changes
    // 2. If email service changes, Employee class changes
    // 3. If payslip format changes, Employee class changes
    // 4. If validation rules change, Employee class changes
    // 5. Hard to test individual responsibilities
    // 6. Class becomes large and complex
}

// ============================================================================
// CORRECT: Separate responsibilities into different classes
// ============================================================================

namespace good_design
{

    // Pure data model - only represents employee data
    class Employee
    {
    private:
        string name;
        string email;
        double salary;

    public:
        Employee(const string &n, const string &e, double s)
            : name(n), email(e), salary(s) {}

        string getName() const { return name; }
        string getEmail() const { return email; }
        double getSalary() const { return salary; }

        void setSalary(double s) { salary = s; }
    };

    // Responsibility 1: Business logic calculations
    class SalaryCalculator
    {
    public:
        double calculateBonus(const Employee &emp)
        {
            return emp.getSalary() * 0.1;
        }

        double calculateTax(const Employee &emp)
        {
            return emp.getSalary() * 0.3;
        }

        double calculateNetSalary(const Employee &emp)
        {
            return emp.getSalary() - calculateTax(emp);
        }
    };

    // Responsibility 2: Database operations
    class EmployeeRepository
    {
    public:
        void save(const Employee &emp)
        {
            cout << "Saving " << emp.getName() << " to database...\n";
            // Database-specific code here
        }

        Employee *findByEmail(const string &email)
        {
            cout << "Finding employee by email: " << email << "\n";
            // Database query here
            return nullptr;
        }

        void remove(const Employee &emp)
        {
            cout << "Removing " << emp.getName() << " from database...\n";
        }
    };

    // Responsibility 3: Email notifications
    class EmailService
    {
    public:
        void sendWelcomeEmail(const Employee &emp)
        {
            cout << "Sending welcome email to " << emp.getEmail() << "\n";
            // SMTP logic here
        }

        void sendPayslipEmail(const Employee &emp, const string &payslip)
        {
            cout << "Sending payslip to " << emp.getEmail() << "\n";
            // Email with attachment logic
        }
    };

    // Responsibility 4: Report generation
    class PayslipGenerator
    {
    private:
        SalaryCalculator calculator;

    public:
        string generate(const Employee &emp)
        {
            stringstream ss;
            ss << "=== PAYSLIP ===\n";
            ss << "Name: " << emp.getName() << "\n";
            ss << "Salary: $" << emp.getSalary() << "\n";
            ss << "Bonus: $" << calculator.calculateBonus(emp) << "\n";
            ss << "Tax: $" << calculator.calculateTax(emp) << "\n";
            ss << "Net: $" << calculator.calculateNetSalary(emp) << "\n";
            return ss.str();
        }
    };

    // Responsibility 5: Validation
    class EmailValidator
    {
    public:
        bool isValid(const string &email)
        {
            // Basic validation
            if (email.empty())
                return false;
            size_t atPos = email.find('@');
            if (atPos == string::npos)
                return false;
            size_t dotPos = email.find('.', atPos);
            return dotPos != string::npos;
        }
    };

    // Benefits of this design:
    // 1. Each class has ONE reason to change
    // 2. Easy to test each responsibility in isolation
    // 3. Can replace implementations independently
    // 4. Easy to understand what each class does
    // 5. Promotes reusability (EmailService can be used for any entity)
}

// ============================================================================
// REAL-WORLD EXAMPLE: User Management System
// ============================================================================

namespace user_management
{

    class User
    {
    private:
        int id;
        string username;
        string passwordHash;
        string email;

    public:
        User(int id, const string &user, const string &pass, const string &mail)
            : id(id), username(user), passwordHash(pass), email(mail) {}

        int getId() const { return id; }
        string getUsername() const { return username; }
        string getPasswordHash() const { return passwordHash; }
        string getEmail() const { return email; }
    };

    // Authentication logic only
    class AuthenticationService
    {
    public:
        bool authenticate(const string &username, const string &password)
        {
            cout << "Authenticating user: " << username << "\n";
            // Hash password and compare
            return true; // Simplified
        }

        string generateToken(const User &user)
        {
            return "token_" + to_string(user.getId());
        }
    };

    // Authorization logic only
    class AuthorizationService
    {
    private:
        vector<string> userRoles;

    public:
        bool hasPermission(const User &user, const string &resource)
        {
            cout << "Checking " << user.getUsername() << " permission for " << resource << "\n";
            // Check roles and permissions
            return true; // Simplified
        }

        void grantRole(const User &user, const string &role)
        {
            cout << "Granting role '" << role << "' to " << user.getUsername() << "\n";
        }
    };

    // Password management only
    class PasswordService
    {
    public:
        string hashPassword(const string &plainPassword)
        {
            cout << "Hashing password...\n";
            // Use bcrypt, argon2, etc.
            return "hashed_" + plainPassword;
        }

        bool verifyPassword(const string &plain, const string &hash)
        {
            return hashPassword(plain) == hash;
        }

        bool isStrongPassword(const string &password)
        {
            return password.length() >= 8; // Simplified
        }
    };

    // User persistence only
    class UserRepository
    {
    public:
        void save(const User &user)
        {
            cout << "Saving user: " << user.getUsername() << "\n";
        }

        User *findByUsername(const string &username)
        {
            cout << "Finding user: " << username << "\n";
            return nullptr; // Simplified
        }

        void deleteUser(int userId)
        {
            cout << "Deleting user: " << userId << "\n";
        }
    };

    // Notification logic only
    class NotificationService
    {
    public:
        void notifyPasswordChange(const User &user)
        {
            cout << "Notifying " << user.getEmail() << " of password change\n";
        }

        void notifyLogin(const User &user)
        {
            cout << "Notifying " << user.getEmail() << " of new login\n";
        }
    };

    // Orchestrator that uses all services
    class UserService
    {
    private:
        AuthenticationService authService;
        AuthorizationService authzService;
        PasswordService passwordService;
        UserRepository repository;
        NotificationService notificationService;

    public:
        bool registerUser(const string &username, const string &password, const string &email)
        {
            if (!passwordService.isStrongPassword(password))
            {
                cout << "Password is too weak!\n";
                return false;
            }

            string hashedPassword = passwordService.hashPassword(password);
            User user(1, username, hashedPassword, email); // Simplified ID

            repository.save(user);
            notificationService.notifyPasswordChange(user);

            cout << "User registered successfully!\n";
            return true;
        }

        bool loginUser(const string &username, const string &password)
        {
            if (!authService.authenticate(username, password))
            {
                return false;
            }

            User *user = repository.findByUsername(username);
            if (user)
            {
                notificationService.notifyLogin(*user);
                return true;
            }
            return false;
        }
    };
}

// ============================================================================
// ADVANCED EXAMPLE: Invoice System
// ============================================================================

namespace invoice_system
{

    struct InvoiceItem
    {
        string description;
        double price;
        int quantity;
    };

    class Invoice
    {
    private:
        int id;
        string customerName;
        vector<InvoiceItem> items;

    public:
        Invoice(int id, const string &customer) : id(id), customerName(customer) {}

        void addItem(const InvoiceItem &item) { items.push_back(item); }

        int getId() const { return id; }
        string getCustomerName() const { return customerName; }
        const vector<InvoiceItem> &getItems() const { return items; }
    };

    // Calculate totals
    class InvoiceCalculator
    {
    public:
        double calculateSubtotal(const Invoice &invoice)
        {
            double total = 0.0;
            for (const auto &item : invoice.getItems())
            {
                total += item.price * item.quantity;
            }
            return total;
        }

        double calculateTax(const Invoice &invoice, double taxRate)
        {
            return calculateSubtotal(invoice) * taxRate;
        }

        double calculateTotal(const Invoice &invoice, double taxRate)
        {
            return calculateSubtotal(invoice) + calculateTax(invoice, taxRate);
        }
    };

    // Save invoices
    class InvoiceRepository
    {
    public:
        void save(const Invoice &invoice)
        {
            cout << "Saving invoice #" << invoice.getId() << " to database\n";
        }

        Invoice *findById(int id)
        {
            cout << "Loading invoice #" << id << " from database\n";
            return nullptr;
        }
    };

    // Print invoices to different formats
    class InvoicePrinter
    {
    private:
        InvoiceCalculator calculator;

    public:
        void printText(const Invoice &invoice)
        {
            cout << "\n=== INVOICE #" << invoice.getId() << " ===\n";
            cout << "Customer: " << invoice.getCustomerName() << "\n";
            cout << "Items:\n";

            for (const auto &item : invoice.getItems())
            {
                cout << "  " << item.description << " - $" << item.price
                     << " x " << item.quantity << "\n";
            }

            cout << "Subtotal: $" << calculator.calculateSubtotal(invoice) << "\n";
            cout << "Tax: $" << calculator.calculateTax(invoice, 0.1) << "\n";
            cout << "Total: $" << calculator.calculateTotal(invoice, 0.1) << "\n";
        }

        void printHTML(const Invoice &invoice)
        {
            cout << "\n<html><body><h1>Invoice #" << invoice.getId() << "</h1>\n";
            cout << "<p>Customer: " << invoice.getCustomerName() << "</p>\n";
            cout << "<table><tr><th>Item</th><th>Price</th><th>Qty</th></tr>\n";

            for (const auto &item : invoice.getItems())
            {
                cout << "<tr><td>" << item.description << "</td>"
                     << "<td>$" << item.price << "</td>"
                     << "<td>" << item.quantity << "</td></tr>\n";
            }

            cout << "</table></body></html>\n";
        }
    };

    // Send invoices via email
    class InvoiceEmailer
    {
    public:
        void sendEmail(const Invoice &invoice, const string &email)
        {
            cout << "Emailing invoice #" << invoice.getId() << " to " << email << "\n";
        }
    };
}

// ============================================================================
// MAIN: Demonstration
// ============================================================================

int main()
{
    cout << "=== SINGLE RESPONSIBILITY PRINCIPLE (SRP) ===\n\n";

    // Bad Design Demo
    cout << "--- BAD DESIGN (Multiple Responsibilities) ---\n";
    bad_design::Employee badEmp("John Doe", "john@example.com", 50000);
    badEmp.calculateBonus();
    badEmp.saveToDatabase();
    badEmp.sendWelcomeEmail();
    cout << badEmp.generatePayslip() << "\n";

    // Good Design Demo
    cout << "\n--- GOOD DESIGN (Separated Responsibilities) ---\n";
    good_design::Employee goodEmp("Jane Smith", "jane@example.com", 60000);
    good_design::SalaryCalculator calculator;
    good_design::EmployeeRepository repo;
    good_design::EmailService emailService;
    good_design::PayslipGenerator payslipGen;

    cout << "Bonus: $" << calculator.calculateBonus(goodEmp) << "\n";
    repo.save(goodEmp);
    emailService.sendWelcomeEmail(goodEmp);
    string payslip = payslipGen.generate(goodEmp);
    cout << payslip << "\n";
    emailService.sendPayslipEmail(goodEmp, payslip);

    // User Management Demo
    cout << "\n--- USER MANAGEMENT SYSTEM ---\n";
    user_management::UserService userService;
    userService.registerUser("alice", "SecurePass123!", "alice@example.com");
    userService.loginUser("alice", "SecurePass123!");

    // Invoice System Demo
    cout << "\n--- INVOICE SYSTEM ---\n";
    invoice_system::Invoice invoice(101, "Acme Corp");
    invoice.addItem({"Widget", 25.00, 5});
    invoice.addItem({"Gadget", 50.00, 2});

    invoice_system::InvoiceCalculator invoiceCalc;
    invoice_system::InvoicePrinter printer;
    invoice_system::InvoiceRepository invoiceRepo;
    invoice_system::InvoiceEmailer emailer;

    printer.printText(invoice);
    printer.printHTML(invoice);
    invoiceRepo.save(invoice);
    emailer.sendEmail(invoice, "billing@acme.com");

    cout << "\n=== KEY TAKEAWAYS ===\n";
    cout << "1. Each class has ONE reason to change\n";
    cout << "2. Responsibilities are clearly separated\n";
    cout << "3. Easy to test each component independently\n";
    cout << "4. Changes to one responsibility don't affect others\n";
    cout << "5. Promotes code reusability and maintainability\n";

    return 0;
}
