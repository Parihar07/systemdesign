/**
 * COMPLETE E-COMMERCE SYSTEM
 * Demonstrating ALL SOLID Principles Together
 *
 * This is a comprehensive example showing how all five SOLID principles
 * work together in a real-world e-commerce system.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>

using namespace std;

// ============================================================================
// DOMAIN MODELS (Simple data classes - SRP)
// ============================================================================

class Product
{
private:
    string id;
    string name;
    double price;
    int stock;

public:
    Product(const string &id, const string &name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    string getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void decreaseStock(int amount)
    {
        if (amount > stock)
            throw runtime_error("Insufficient stock");
        stock -= amount;
    }

    void increaseStock(int amount)
    {
        stock += amount;
    }
};

class OrderItem
{
private:
    Product *product;
    int quantity;

public:
    OrderItem(Product *prod, int qty) : product(prod), quantity(qty) {}

    Product *getProduct() const { return product; }
    int getQuantity() const { return quantity; }
    double getSubtotal() const { return product->getPrice() * quantity; }
};

class Order
{
private:
    string orderId;
    string customerId;
    vector<OrderItem> items;

public:
    Order(const string &orderId, const string &customerId)
        : orderId(orderId), customerId(customerId) {}

    void addItem(const OrderItem &item) { items.push_back(item); }

    string getOrderId() const { return orderId; }
    string getCustomerId() const { return customerId; }
    const vector<OrderItem> &getItems() const { return items; }

    double getSubtotal() const
    {
        double total = 0.0;
        for (const auto &item : items)
        {
            total += item.getSubtotal();
        }
        return total;
    }
};

// ============================================================================
// ABSTRACTIONS (DIP - Depend on abstractions, not concretions)
// ============================================================================

// Repository abstraction
class IProductRepository
{
public:
    virtual ~IProductRepository() = default;
    virtual Product *findById(const string &id) = 0;
    virtual void save(const Product &product) = 0;
    virtual vector<Product *> findAll() = 0;
};

class IOrderRepository
{
public:
    virtual ~IOrderRepository() = default;
    virtual void save(const Order &order) = 0;
    virtual Order *findById(const string &id) = 0;
};

// Payment processor abstraction
class IPaymentProcessor
{
public:
    virtual ~IPaymentProcessor() = default;
    virtual bool process(double amount, const string &paymentDetails) = 0;
    virtual string getProcessorName() const = 0;
};

// Notification service abstraction
class INotificationService
{
public:
    virtual ~INotificationService() = default;
    virtual void send(const string &recipient, const string &message) = 0;
};

// Logger abstraction
class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual void info(const string &message) = 0;
    virtual void error(const string &message) = 0;
};

// Discount strategy abstraction (OCP - Open for extension)
class IDiscountStrategy
{
public:
    virtual ~IDiscountStrategy() = default;
    virtual double apply(double amount) const = 0;
    virtual string getDescription() const = 0;
};

// Shipping calculator abstraction
class IShippingCalculator
{
public:
    virtual ~IShippingCalculator() = default;
    virtual double calculate(double weight, const string &destination) = 0;
    virtual string getShippingMethod() const = 0;
};

// ============================================================================
// CONCRETE IMPLEMENTATIONS (ISP & OCP - Small interfaces, extensible)
// ============================================================================

// Payment Processors (OCP - can add new processors without modifying existing code)
class CreditCardProcessor : public IPaymentProcessor
{
public:
    bool process(double amount, const string &paymentDetails) override
    {
        cout << "Processing $" << fixed << setprecision(2) << amount
             << " via Credit Card\n";
        cout << "Card: " << paymentDetails << "\n";
        return true;
    }

    string getProcessorName() const override { return "Credit Card"; }
};

class PayPalProcessor : public IPaymentProcessor
{
public:
    bool process(double amount, const string &paymentDetails) override
    {
        cout << "Processing $" << fixed << setprecision(2) << amount
             << " via PayPal\n";
        cout << "Account: " << paymentDetails << "\n";
        return true;
    }

    string getProcessorName() const override { return "PayPal"; }
};

class CryptoProcessor : public IPaymentProcessor
{
public:
    bool process(double amount, const string &paymentDetails) override
    {
        cout << "Processing $" << fixed << setprecision(2) << amount
             << " via Cryptocurrency\n";
        cout << "Wallet: " << paymentDetails << "\n";
        return true;
    }

    string getProcessorName() const override { return "Cryptocurrency"; }
};

// Notification Services (OCP - extensible)
class EmailNotification : public INotificationService
{
public:
    void send(const string &recipient, const string &message) override
    {
        cout << "[EMAIL] To: " << recipient << "\n";
        cout << "Message: " << message << "\n";
    }
};

class SMSNotification : public INotificationService
{
public:
    void send(const string &recipient, const string &message) override
    {
        cout << "[SMS] To: " << recipient << "\n";
        cout << "Message: " << message << "\n";
    }
};

// Logger Implementation
class ConsoleLogger : public ILogger
{
public:
    void info(const string &message) override
    {
        cout << "[INFO] " << message << "\n";
    }

    void error(const string &message) override
    {
        cout << "[ERROR] " << message << "\n";
    }
};

// Discount Strategies (OCP - Strategy pattern)
class NoDiscount : public IDiscountStrategy
{
public:
    double apply(double amount) const override { return amount; }
    string getDescription() const override { return "No discount"; }
};

class PercentageDiscount : public IDiscountStrategy
{
private:
    double percentage;

public:
    PercentageDiscount(double pct) : percentage(pct) {}

    double apply(double amount) const override
    {
        return amount * (1.0 - percentage / 100.0);
    }

    string getDescription() const override
    {
        return to_string((int)percentage) + "% off";
    }
};

class SeasonalDiscount : public IDiscountStrategy
{
private:
    double amount;
    double threshold;

public:
    SeasonalDiscount(double amt, double thresh) : amount(amt), threshold(thresh) {}

    double apply(double price) const override
    {
        if (price >= threshold)
        {
            return max(0.0, price - amount);
        }
        return price;
    }

    string getDescription() const override
    {
        return "$" + to_string((int)amount) + " off orders over $" +
               to_string((int)threshold);
    }
};

// Shipping Calculators
class StandardShipping : public IShippingCalculator
{
public:
    double calculate(double weight, const string &destination) override
    {
        return 5.0 + (weight * 0.5);
    }

    string getShippingMethod() const override { return "Standard Shipping"; }
};

class ExpressShipping : public IShippingCalculator
{
public:
    double calculate(double weight, const string &destination) override
    {
        return 15.0 + (weight * 1.0);
    }

    string getShippingMethod() const override { return "Express Shipping"; }
};

class FreeShipping : public IShippingCalculator
{
public:
    double calculate(double weight, const string &destination) override
    {
        return 0.0;
    }

    string getShippingMethod() const override { return "Free Shipping"; }
};

// In-memory repository implementations
class InMemoryProductRepository : public IProductRepository
{
private:
    vector<unique_ptr<Product>> products;

public:
    Product *findById(const string &id) override
    {
        for (auto &product : products)
        {
            if (product->getId() == id)
            {
                return product.get();
            }
        }
        return nullptr;
    }

    void save(const Product &product) override
    {
        products.push_back(make_unique<Product>(product));
    }

    vector<Product *> findAll() override
    {
        vector<Product *> result;
        for (auto &product : products)
        {
            result.push_back(product.get());
        }
        return result;
    }
};

class InMemoryOrderRepository : public IOrderRepository
{
private:
    vector<unique_ptr<Order>> orders;

public:
    void save(const Order &order) override
    {
        orders.push_back(make_unique<Order>(order));
    }

    Order *findById(const string &id) override
    {
        for (auto &order : orders)
        {
            if (order->getOrderId() == id)
            {
                return order.get();
            }
        }
        return nullptr;
    }
};

// ============================================================================
// BUSINESS SERVICES (SRP - Each service has one responsibility)
// ============================================================================

// Inventory Service (SRP - manages product inventory only)
class InventoryService
{
private:
    IProductRepository *productRepo;
    ILogger *logger;

public:
    InventoryService(IProductRepository *repo, ILogger *log)
        : productRepo(repo), logger(log) {}

    bool checkAvailability(const string &productId, int quantity)
    {
        Product *product = productRepo->findById(productId);
        if (!product)
        {
            logger->error("Product not found: " + productId);
            return false;
        }

        if (product->getStock() < quantity)
        {
            logger->info("Insufficient stock for product: " + product->getName());
            return false;
        }

        return true;
    }

    void reduceStock(const string &productId, int quantity)
    {
        Product *product = productRepo->findById(productId);
        if (product)
        {
            product->decreaseStock(quantity);
            logger->info("Stock reduced for " + product->getName());
        }
    }

    void addStock(const string &productId, int quantity)
    {
        Product *product = productRepo->findById(productId);
        if (product)
        {
            product->increaseStock(quantity);
            logger->info("Stock added for " + product->getName());
        }
    }
};

// Pricing Service (SRP - handles pricing calculations only)
class PricingService
{
private:
    IDiscountStrategy *discountStrategy;
    IShippingCalculator *shippingCalculator;
    ILogger *logger;

public:
    PricingService(IDiscountStrategy *discount, IShippingCalculator *shipping, ILogger *log)
        : discountStrategy(discount), shippingCalculator(shipping), logger(log) {}

    double calculateTotal(const Order &order, double weight, const string &destination)
    {
        double subtotal = order.getSubtotal();
        double discounted = discountStrategy->apply(subtotal);
        double shipping = shippingCalculator->calculate(weight, destination);
        double total = discounted + shipping;

        logger->info("Pricing calculation completed");
        return total;
    }

    void setDiscountStrategy(IDiscountStrategy *strategy)
    {
        discountStrategy = strategy;
    }

    void setShippingCalculator(IShippingCalculator *calculator)
    {
        shippingCalculator = calculator;
    }

    IDiscountStrategy *getDiscountStrategy() const { return discountStrategy; }
    IShippingCalculator *getShippingCalculator() const { return shippingCalculator; }
};

// Payment Service (SRP - handles payments only)
class PaymentService
{
private:
    IPaymentProcessor *processor;
    ILogger *logger;

public:
    PaymentService(IPaymentProcessor *proc, ILogger *log)
        : processor(proc), logger(log) {}

    bool processPayment(double amount, const string &paymentDetails)
    {
        logger->info("Processing payment of $" + to_string(amount));

        bool success = processor->process(amount, paymentDetails);

        if (success)
        {
            logger->info("Payment successful via " + processor->getProcessorName());
        }
        else
        {
            logger->error("Payment failed");
        }

        return success;
    }

    void setProcessor(IPaymentProcessor *proc)
    {
        processor = proc;
    }
};

// Notification Service (SRP - handles notifications only)
class NotificationManager
{
private:
    vector<INotificationService *> notificationServices;
    ILogger *logger;

public:
    NotificationManager(ILogger *log) : logger(log) {}

    void addNotificationChannel(INotificationService *service)
    {
        notificationServices.push_back(service);
    }

    void notifyOrderConfirmation(const string &recipient, const Order &order)
    {
        stringstream message;
        message << "Order " << order.getOrderId() << " confirmed. "
                << "Total: $" << fixed << setprecision(2) << order.getSubtotal();

        for (auto *service : notificationServices)
        {
            service->send(recipient, message.str());
        }

        logger->info("Order confirmation sent to " + recipient);
    }
};

// ============================================================================
// ORCHESTRATOR SERVICE (DIP - Depends on abstractions)
// ============================================================================

class OrderService
{
private:
    IProductRepository *productRepo;
    IOrderRepository *orderRepo;
    InventoryService *inventoryService;
    PricingService *pricingService;
    PaymentService *paymentService;
    NotificationManager *notificationManager;
    ILogger *logger;

public:
    OrderService(
        IProductRepository *prodRepo,
        IOrderRepository *ordRepo,
        InventoryService *inventory,
        PricingService *pricing,
        PaymentService *payment,
        NotificationManager *notification,
        ILogger *log) : productRepo(prodRepo), orderRepo(ordRepo), inventoryService(inventory),
                        pricingService(pricing), paymentService(payment),
                        notificationManager(notification), logger(log) {}

    bool placeOrder(const string &orderId, const string &customerId,
                    const vector<pair<string, int>> &items, // productId, quantity
                    const string &paymentDetails,
                    const string &shippingAddress)
    {

        logger->info("=== Processing Order " + orderId + " ===");

        // Create order
        Order order(orderId, customerId);

        // Check inventory and add items
        for (const auto &[productId, quantity] : items)
        {
            if (!inventoryService->checkAvailability(productId, quantity))
            {
                logger->error("Order failed: Product unavailable");
                return false;
            }

            Product *product = productRepo->findById(productId);
            if (!product)
                continue;

            order.addItem(OrderItem(product, quantity));
        }

        // Calculate total
        double weight = items.size() * 2.0; // Simplified
        double total = pricingService->calculateTotal(order, weight, shippingAddress);

        logger->info("Order subtotal: $" + to_string(order.getSubtotal()));
        logger->info("Discount: " + pricingService->getDiscountStrategy()->getDescription());
        logger->info("Shipping: " + pricingService->getShippingCalculator()->getShippingMethod());
        logger->info("Total: $" + to_string(total));

        // Process payment
        if (!paymentService->processPayment(total, paymentDetails))
        {
            logger->error("Order failed: Payment declined");
            return false;
        }

        // Reduce inventory
        for (const auto &[productId, quantity] : items)
        {
            inventoryService->reduceStock(productId, quantity);
        }

        // Save order
        orderRepo->save(order);
        logger->info("Order saved successfully");

        // Send notifications
        notificationManager->notifyOrderConfirmation(customerId, order);

        logger->info("=== Order " + orderId + " completed successfully ===\n");
        return true;
    }
};

// ============================================================================
// MAIN: Comprehensive Demo
// ============================================================================

int main()
{
    cout << "=== E-COMMERCE SYSTEM - ALL SOLID PRINCIPLES ===\n\n";

    // Setup infrastructure (DIP - inject dependencies)
    ConsoleLogger logger;
    InMemoryProductRepository productRepo;
    InMemoryOrderRepository orderRepo;

    // Add products
    productRepo.save(Product("P001", "Laptop", 999.99, 10));
    productRepo.save(Product("P002", "Mouse", 29.99, 50));
    productRepo.save(Product("P003", "Keyboard", 79.99, 30));

    // Setup services with dependency injection
    InventoryService inventory(&productRepo, &logger);

    NoDiscount noDiscount;
    StandardShipping standardShip;
    PricingService pricing(&noDiscount, &standardShip, &logger);

    CreditCardProcessor creditCard;
    PaymentService payment(&creditCard, &logger);

    NotificationManager notifications(&logger);
    EmailNotification email;
    SMSNotification sms;
    notifications.addNotificationChannel(&email);
    notifications.addNotificationChannel(&sms);

    OrderService orderService(
        &productRepo, &orderRepo, &inventory, &pricing,
        &payment, &notifications, &logger);

    // Scenario 1: Standard order
    cout << "SCENARIO 1: Standard Order\n";
    cout << "----------------------------\n";
    orderService.placeOrder(
        "ORD001",
        "customer@example.com",
        {{"P001", 1}, {"P002", 2}},
        "4111-1111-1111-1111",
        "123 Main St, City, State");

    // Scenario 2: Order with percentage discount
    cout << "\nSCENARIO 2: Order with 20% Discount\n";
    cout << "------------------------------------\n";
    PercentageDiscount percentDiscount(20);
    pricing.setDiscountStrategy(&percentDiscount);

    orderService.placeOrder(
        "ORD002",
        "customer2@example.com",
        {{"P003", 1}},
        "4111-1111-1111-1111",
        "456 Oak Ave, City, State");

    // Scenario 3: Express shipping with PayPal
    cout << "\nSCENARIO 3: Express Shipping + PayPal\n";
    cout << "--------------------------------------\n";
    ExpressShipping expressShip;
    pricing.setShippingCalculator(&expressShip);
    pricing.setDiscountStrategy(&noDiscount);

    PayPalProcessor paypal;
    payment.setProcessor(&paypal);

    orderService.placeOrder(
        "ORD003",
        "customer3@example.com",
        {{"P001", 1}, {"P002", 1}, {"P003", 1}},
        "paypal@example.com",
        "789 Pine Rd, City, State");

    // Scenario 4: Seasonal discount + Crypto payment
    cout << "\nSCENARIO 4: Seasonal Discount + Cryptocurrency\n";
    cout << "-----------------------------------------------\n";
    SeasonalDiscount seasonal(50, 100);
    pricing.setDiscountStrategy(&seasonal);

    FreeShipping freeShip;
    pricing.setShippingCalculator(&freeShip);

    CryptoProcessor crypto;
    payment.setProcessor(&crypto);

    orderService.placeOrder(
        "ORD004",
        "customer4@example.com",
        {{"P001", 1}},
        "0x1234567890abcdef",
        "321 Elm St, City, State");

    // Summary
    cout << "\n=== SOLID PRINCIPLES DEMONSTRATED ===\n";
    cout << "✓ SRP: Each class has single responsibility\n";
    cout << "  - Product, Order: Domain models\n";
    cout << "  - InventoryService: Manages inventory only\n";
    cout << "  - PricingService: Handles pricing only\n";
    cout << "  - PaymentService: Processes payments only\n";
    cout << "  - NotificationManager: Sends notifications only\n\n";

    cout << "✓ OCP: System open for extension, closed for modification\n";
    cout << "  - Add new payment processors without changing PaymentService\n";
    cout << "  - Add new discount strategies without changing PricingService\n";
    cout << "  - Add new notification channels without changing NotificationManager\n\n";

    cout << "✓ LSP: All implementations are substitutable\n";
    cout << "  - Any IPaymentProcessor can replace another\n";
    cout << "  - Any IShippingCalculator is interchangeable\n";
    cout << "  - All follow their interface contracts\n\n";

    cout << "✓ ISP: Small, focused interfaces\n";
    cout << "  - IPaymentProcessor: Only payment methods\n";
    cout << "  - INotificationService: Only send method\n";
    cout << "  - No client forced to implement unused methods\n\n";

    cout << "✓ DIP: Depend on abstractions, not concretions\n";
    cout << "  - OrderService depends on interfaces, not implementations\n";
    cout << "  - Can swap implementations via dependency injection\n";
    cout << "  - Easy to test with mocks\n";

    return 0;
}
