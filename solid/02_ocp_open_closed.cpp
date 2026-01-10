/**
 * OPEN/CLOSED PRINCIPLE (OCP)
 *
 * Definition: Software entities should be open for extension but closed for modification.
 *
 * Key Points:
 * - Open for extension: Behavior can be extended
 * - Closed for modification: Existing code should not be changed
 * - Achieved through abstraction, polymorphism, and interfaces
 * - New features should be added via new code, not by changing old code
 * - Reduces risk of breaking existing functionality
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

// ============================================================================
// VIOLATION: Adding new types requires modifying existing code
// ============================================================================

namespace bad_design
{

    enum class ShapeType
    {
        CIRCLE,
        RECTANGLE,
        TRIANGLE
    };

    struct Shape
    {
        ShapeType type;
        double dimension1; // radius for circle, width for rectangle
        double dimension2; // unused for circle, height for rectangle
        double dimension3; // unused for circle/rectangle, base for triangle
    };

    // Problem: Every new shape requires modifying this class
    class AreaCalculator
    {
    public:
        double calculateArea(const Shape &shape)
        {
            switch (shape.type)
            {
            case ShapeType::CIRCLE:
                return 3.14159 * shape.dimension1 * shape.dimension1;

            case ShapeType::RECTANGLE:
                return shape.dimension1 * shape.dimension2;

            case ShapeType::TRIANGLE:
                return 0.5 * shape.dimension3 * shape.dimension2;

            // Adding a new shape? Must modify this function!
            // What if we want a Pentagon, Hexagon, etc.?
            default:
                return 0.0;
            }
        }
    };

    // Problems:
    // 1. Must modify AreaCalculator for every new shape
    // 2. Must recompile and retest everything
    // 3. Violates separation of concerns
    // 4. Error-prone (easy to forget updating all switch statements)
    // 5. Cannot extend without source code access
}

// ============================================================================
// CORRECT: Use abstraction and polymorphism
// ============================================================================

namespace good_design
{

    // Abstract base class - closed for modification
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual double area() const = 0;
        virtual string getName() const = 0;
        virtual void draw() const = 0;
    };

    // Each shape extends the base class - open for extension
    class Circle : public Shape
    {
    private:
        double radius;

    public:
        Circle(double r) : radius(r) {}

        double area() const override
        {
            return 3.14159 * radius * radius;
        }

        string getName() const override
        {
            return "Circle";
        }

        void draw() const override
        {
            cout << "Drawing a circle with radius " << radius << "\n";
        }
    };

    class Rectangle : public Shape
    {
    private:
        double width, height;

    public:
        Rectangle(double w, double h) : width(w), height(h) {}

        double area() const override
        {
            return width * height;
        }

        string getName() const override
        {
            return "Rectangle";
        }

        void draw() const override
        {
            cout << "Drawing a rectangle " << width << "x" << height << "\n";
        }
    };

    class Triangle : public Shape
    {
    private:
        double base, height;

    public:
        Triangle(double b, double h) : base(b), height(h) {}

        double area() const override
        {
            return 0.5 * base * height;
        }

        string getName() const override
        {
            return "Triangle";
        }

        void draw() const override
        {
            cout << "Drawing a triangle with base " << base << "\n";
        }
    };

    // NEW: Adding pentagon - NO modification to existing code!
    class Pentagon : public Shape
    {
    private:
        double side;

    public:
        Pentagon(double s) : side(s) {}

        double area() const override
        {
            return (sqrt(5 * (5 + 2 * sqrt(5))) / 4) * side * side;
        }

        string getName() const override
        {
            return "Pentagon";
        }

        void draw() const override
        {
            cout << "Drawing a pentagon with side " << side << "\n";
        }
    };

    // Calculator doesn't need to change when new shapes are added
    class AreaCalculator
    {
    public:
        double calculateTotal(const vector<unique_ptr<Shape>> &shapes)
        {
            double total = 0.0;
            for (const auto &shape : shapes)
            {
                total += shape->area();
            }
            return total;
        }

        void printAreas(const vector<unique_ptr<Shape>> &shapes)
        {
            for (const auto &shape : shapes)
            {
                cout << shape->getName() << " area: " << shape->area() << "\n";
            }
        }
    };
}

// ============================================================================
// REAL-WORLD EXAMPLE: Payment Processing System
// ============================================================================

namespace payment_system
{

    // Base payment method - closed for modification
    class PaymentMethod
    {
    public:
        virtual ~PaymentMethod() = default;
        virtual bool processPayment(double amount) = 0;
        virtual string getPaymentType() const = 0;
        virtual bool requiresAuthentication() const = 0;
    };

    // Extension: Credit Card Payment
    class CreditCardPayment : public PaymentMethod
    {
    private:
        string cardNumber;
        string cvv;

    public:
        CreditCardPayment(const string &card, const string &cvv)
            : cardNumber(card), cvv(cvv) {}

        bool processPayment(double amount) override
        {
            cout << "Processing credit card payment of $" << amount << "\n";
            cout << "Card ending in: " << cardNumber.substr(cardNumber.length() - 4) << "\n";
            // Connect to payment gateway
            return true;
        }

        string getPaymentType() const override
        {
            return "Credit Card";
        }

        bool requiresAuthentication() const override
        {
            return true;
        }
    };

    // Extension: PayPal Payment
    class PayPalPayment : public PaymentMethod
    {
    private:
        string email;

    public:
        PayPalPayment(const string &email) : email(email) {}

        bool processPayment(double amount) override
        {
            cout << "Processing PayPal payment of $" << amount << "\n";
            cout << "PayPal account: " << email << "\n";
            // Connect to PayPal API
            return true;
        }

        string getPaymentType() const override
        {
            return "PayPal";
        }

        bool requiresAuthentication() const override
        {
            return true;
        }
    };

    // Extension: Cryptocurrency Payment
    class CryptoPayment : public PaymentMethod
    {
    private:
        string walletAddress;
        string currency;

    public:
        CryptoPayment(const string &wallet, const string &curr)
            : walletAddress(wallet), currency(curr) {}

        bool processPayment(double amount) override
        {
            cout << "Processing " << currency << " payment of $" << amount << "\n";
            cout << "Wallet: " << walletAddress.substr(0, 10) << "...\n";
            // Connect to blockchain
            return true;
        }

        string getPaymentType() const override
        {
            return currency + " Cryptocurrency";
        }

        bool requiresAuthentication() const override
        {
            return true;
        }
    };

    // Extension: Bank Transfer (NEW - no modification to existing code!)
    class BankTransferPayment : public PaymentMethod
    {
    private:
        string accountNumber;
        string routingNumber;

    public:
        BankTransferPayment(const string &account, const string &routing)
            : accountNumber(account), routingNumber(routing) {}

        bool processPayment(double amount) override
        {
            cout << "Processing bank transfer of $" << amount << "\n";
            cout << "Account: " << accountNumber << "\n";
            // Connect to banking system
            return true;
        }

        string getPaymentType() const override
        {
            return "Bank Transfer";
        }

        bool requiresAuthentication() const override
        {
            return true;
        }
    };

    // Payment processor doesn't change when new payment methods are added
    class PaymentProcessor
    {
    public:
        bool executePayment(PaymentMethod *method, double amount)
        {
            if (method->requiresAuthentication())
            {
                cout << "Authenticating " << method->getPaymentType() << "...\n";
            }

            bool success = method->processPayment(amount);

            if (success)
            {
                cout << "Payment successful!\n";
            }
            else
            {
                cout << "Payment failed!\n";
            }

            return success;
        }
    };
}

// ============================================================================
// ADVANCED EXAMPLE: Notification System
// ============================================================================

namespace notification_system
{

    // Base notification channel
    class NotificationChannel
    {
    public:
        virtual ~NotificationChannel() = default;
        virtual void send(const string &recipient, const string &message) = 0;
        virtual string getChannelName() const = 0;
        virtual bool isAvailable() const { return true; }
    };

    // Email notification
    class EmailNotification : public NotificationChannel
    {
    public:
        void send(const string &recipient, const string &message) override
        {
            cout << "[EMAIL] To: " << recipient << "\n";
            cout << "Message: " << message << "\n";
        }

        string getChannelName() const override
        {
            return "Email";
        }
    };

    // SMS notification
    class SMSNotification : public NotificationChannel
    {
    public:
        void send(const string &recipient, const string &message) override
        {
            cout << "[SMS] To: " << recipient << "\n";
            cout << "Message: " << message.substr(0, 160) << "\n"; // SMS limit
        }

        string getChannelName() const override
        {
            return "SMS";
        }
    };

    // Push notification
    class PushNotification : public NotificationChannel
    {
    private:
        string appId;

    public:
        PushNotification(const string &app) : appId(app) {}

        void send(const string &recipient, const string &message) override
        {
            cout << "[PUSH] App: " << appId << " | User: " << recipient << "\n";
            cout << "Message: " << message << "\n";
        }

        string getChannelName() const override
        {
            return "Push Notification";
        }
    };

    // Slack notification (NEW - extends without modifying existing code)
    class SlackNotification : public NotificationChannel
    {
    private:
        string webhookUrl;

    public:
        SlackNotification(const string &webhook) : webhookUrl(webhook) {}

        void send(const string &recipient, const string &message) override
        {
            cout << "[SLACK] Channel: " << recipient << "\n";
            cout << "Webhook: " << webhookUrl << "\n";
            cout << "Message: " << message << "\n";
        }

        string getChannelName() const override
        {
            return "Slack";
        }
    };

    // Decorator pattern for retry logic (extends behavior)
    class RetryNotification : public NotificationChannel
    {
    private:
        unique_ptr<NotificationChannel> channel;
        int maxRetries;

    public:
        RetryNotification(unique_ptr<NotificationChannel> ch, int retries)
            : channel(move(ch)), maxRetries(retries) {}

        void send(const string &recipient, const string &message) override
        {
            for (int i = 0; i < maxRetries; ++i)
            {
                try
                {
                    channel->send(recipient, message);
                    return;
                }
                catch (...)
                {
                    cout << "Retry " << (i + 1) << " of " << maxRetries << "\n";
                }
            }
            cout << "All retries failed!\n";
        }

        string getChannelName() const override
        {
            return channel->getChannelName() + " (with retry)";
        }
    };

    // Notification manager doesn't change with new channels
    class NotificationManager
    {
    private:
        vector<unique_ptr<NotificationChannel>> channels;

    public:
        void addChannel(unique_ptr<NotificationChannel> channel)
        {
            channels.push_back(move(channel));
        }

        void broadcast(const string &recipient, const string &message)
        {
            cout << "\n--- Broadcasting message ---\n";
            for (const auto &channel : channels)
            {
                if (channel->isAvailable())
                {
                    cout << "\nUsing " << channel->getChannelName() << ":\n";
                    channel->send(recipient, message);
                }
            }
        }
    };
}

// ============================================================================
// EXAMPLE: Discount Strategy System
// ============================================================================

namespace discount_system
{

    // Base discount strategy
    class DiscountStrategy
    {
    public:
        virtual ~DiscountStrategy() = default;
        virtual double apply(double price) const = 0;
        virtual string getDescription() const = 0;
    };

    class NoDiscount : public DiscountStrategy
    {
    public:
        double apply(double price) const override
        {
            return price;
        }

        string getDescription() const override
        {
            return "No discount";
        }
    };

    class PercentageDiscount : public DiscountStrategy
    {
    private:
        double percentage;

    public:
        PercentageDiscount(double pct) : percentage(pct) {}

        double apply(double price) const override
        {
            return price * (1.0 - percentage / 100.0);
        }

        string getDescription() const override
        {
            return to_string(percentage) + "% off";
        }
    };

    class FixedAmountDiscount : public DiscountStrategy
    {
    private:
        double amount;

    public:
        FixedAmountDiscount(double amt) : amount(amt) {}

        double apply(double price) const override
        {
            return max(0.0, price - amount);
        }

        string getDescription() const override
        {
            return "$" + to_string(amount) + " off";
        }
    };

    // NEW: Buy-one-get-one discount (extends without modifying)
    class BOGODiscount : public DiscountStrategy
    {
    public:
        double apply(double price) const override
        {
            return price * 0.5; // 50% off for BOGO
        }

        string getDescription() const override
        {
            return "Buy One Get One Free";
        }
    };

    class ShoppingCart
    {
    private:
        vector<double> items;
        unique_ptr<DiscountStrategy> discount;

    public:
        ShoppingCart() : discount(make_unique<NoDiscount>()) {}

        void addItem(double price)
        {
            items.push_back(price);
        }

        void setDiscountStrategy(unique_ptr<DiscountStrategy> strategy)
        {
            discount = move(strategy);
        }

        double calculateTotal() const
        {
            double subtotal = 0.0;
            for (double price : items)
            {
                subtotal += price;
            }

            double total = discount->apply(subtotal);

            cout << "Subtotal: $" << subtotal << "\n";
            cout << "Discount: " << discount->getDescription() << "\n";
            cout << "Total: $" << total << "\n";

            return total;
        }
    };
}

// ============================================================================
// MAIN: Demonstration
// ============================================================================

int main()
{
    cout << "=== OPEN/CLOSED PRINCIPLE (OCP) ===\n\n";

    // Shape Demo
    cout << "--- SHAPE SYSTEM (Good Design) ---\n";
    vector<unique_ptr<good_design::Shape>> shapes;
    shapes.push_back(make_unique<good_design::Circle>(5.0));
    shapes.push_back(make_unique<good_design::Rectangle>(4.0, 6.0));
    shapes.push_back(make_unique<good_design::Triangle>(3.0, 4.0));
    shapes.push_back(make_unique<good_design::Pentagon>(5.0));

    good_design::AreaCalculator calc;
    calc.printAreas(shapes);
    cout << "Total area: " << calc.calculateTotal(shapes) << "\n";

    // Payment System Demo
    cout << "\n--- PAYMENT SYSTEM ---\n";
    payment_system::PaymentProcessor processor;

    payment_system::CreditCardPayment creditCard("1234-5678-9012-3456", "123");
    processor.executePayment(&creditCard, 99.99);

    cout << "\n";
    payment_system::CryptoPayment crypto("0x1234567890abcdef", "Bitcoin");
    processor.executePayment(&crypto, 150.00);

    cout << "\n";
    payment_system::BankTransferPayment bank("9876543210", "123456789");
    processor.executePayment(&bank, 500.00);

    // Notification System Demo
    cout << "\n--- NOTIFICATION SYSTEM ---\n";
    notification_system::NotificationManager manager;
    manager.addChannel(make_unique<notification_system::EmailNotification>());
    manager.addChannel(make_unique<notification_system::SMSNotification>());
    manager.addChannel(make_unique<notification_system::PushNotification>("MyApp"));
    manager.addChannel(make_unique<notification_system::SlackNotification>("https://hooks.slack.com/..."));

    manager.broadcast("user@example.com", "Your order has been shipped!");

    // Discount System Demo
    cout << "\n--- DISCOUNT SYSTEM ---\n";
    discount_system::ShoppingCart cart;
    cart.addItem(50.00);
    cart.addItem(30.00);
    cart.addItem(20.00);

    cout << "\nWith no discount:\n";
    cart.calculateTotal();

    cout << "\nWith 20% discount:\n";
    cart.setDiscountStrategy(make_unique<discount_system::PercentageDiscount>(20));
    cart.calculateTotal();

    cout << "\nWith $25 off:\n";
    cart.setDiscountStrategy(make_unique<discount_system::FixedAmountDiscount>(25));
    cart.calculateTotal();

    cout << "\nWith BOGO:\n";
    cart.setDiscountStrategy(make_unique<discount_system::BOGODiscount>());
    cart.calculateTotal();

    cout << "\n=== KEY TAKEAWAYS ===\n";
    cout << "1. Extend behavior through inheritance/composition\n";
    cout << "2. Don't modify existing, tested code\n";
    cout << "3. Use abstraction to achieve flexibility\n";
    cout << "4. New features = new classes, not modified classes\n";
    cout << "5. Strategy pattern exemplifies OCP perfectly\n";

    return 0;
}
