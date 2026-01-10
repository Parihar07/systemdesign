/**
 * DEPENDENCY INVERSION PRINCIPLE (DIP)
 *
 * Definition:
 * 1. High-level modules should not depend on low-level modules.
 *    Both should depend on abstractions.
 * 2. Abstractions should not depend on details.
 *    Details should depend on abstractions.
 *
 * Key Points:
 * - Depend on interfaces/abstract classes, not concrete implementations
 * - Enables loose coupling between components
 * - Makes code more testable (can inject mocks)
 * - Facilitates changing implementations without affecting clients
 * - Inverts the traditional dependency flow
 * - Core principle behind dependency injection
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

// ============================================================================
// VIOLATION: High-level module depends on low-level details
// ============================================================================

namespace bad_design
{

    // Low-level module - concrete email sender
    class EmailService
    {
    public:
        void sendEmail(const string &to, const string &message)
        {
            cout << "Sending email to " << to << ": " << message << "\n";
            // SMTP connection logic here
        }
    };

    // Problem: UserNotifier depends on concrete EmailService
    class UserNotifier
    {
    private:
        EmailService emailService; // Hard dependency on concrete class!

    public:
        void notifyUser(const string &email, const string &message)
        {
            emailService.sendEmail(email, message);
        }
    };

    // Problems:
    // 1. UserNotifier is tightly coupled to EmailService
    // 2. Can't switch to SMS without modifying UserNotifier
    // 3. Hard to test - can't mock EmailService
    // 4. Can't reuse UserNotifier with different notification methods
    // 5. Violates Open/Closed Principle
}

// ============================================================================
// CORRECT: Depend on abstraction, not concretion
// ============================================================================

namespace good_design
{

    // Abstraction - high-level policy
    class MessageService
    {
    public:
        virtual ~MessageService() = default;
        virtual void send(const string &recipient, const string &message) = 0;
    };

    // Low-level detail - Email implementation
    class EmailService : public MessageService
    {
    public:
        void send(const string &recipient, const string &message) override
        {
            cout << "[EMAIL] To: " << recipient << "\n";
            cout << "Message: " << message << "\n";
        }
    };

    // Low-level detail - SMS implementation
    class SMSService : public MessageService
    {
    public:
        void send(const string &recipient, const string &message) override
        {
            cout << "[SMS] To: " << recipient << "\n";
            cout << "Message: " << message << "\n";
        }
    };

    // Low-level detail - Push notification implementation
    class PushNotificationService : public MessageService
    {
    public:
        void send(const string &recipient, const string &message) override
        {
            cout << "[PUSH] To: " << recipient << "\n";
            cout << "Message: " << message << "\n";
        }
    };

    // High-level module depends on abstraction (Dependency Injection)
    class UserNotifier
    {
    private:
        MessageService *messageService; // Depends on abstraction!

    public:
        UserNotifier(MessageService *service) : messageService(service) {}

        void notifyUser(const string &recipient, const string &message)
        {
            messageService->send(recipient, message);
        }

        // Can change notification method at runtime
        void setMessageService(MessageService *service)
        {
            messageService = service;
        }
    };

    // Benefits:
    // 1. UserNotifier is decoupled from specific implementations
    // 2. Easy to switch between Email, SMS, Push, etc.
    // 3. Easy to test with mock implementations
    // 4. Can add new notification types without changing UserNotifier
    // 5. Follows Open/Closed Principle
}

// ============================================================================
// REAL-WORLD EXAMPLE: Payment Processing
// ============================================================================

namespace payment_system
{

    // High-level abstraction
    class PaymentProcessor
    {
    public:
        virtual ~PaymentProcessor() = default;
        virtual bool processPayment(double amount) = 0;
        virtual string getProcessorName() const = 0;
    };

    // Low-level implementations
    class StripeProcessor : public PaymentProcessor
    {
    public:
        bool processPayment(double amount) override
        {
            cout << "Processing $" << amount << " via Stripe\n";
            // Stripe API calls
            return true;
        }

        string getProcessorName() const override
        {
            return "Stripe";
        }
    };

    class PayPalProcessor : public PaymentProcessor
    {
    public:
        bool processPayment(double amount) override
        {
            cout << "Processing $" << amount << " via PayPal\n";
            // PayPal API calls
            return true;
        }

        string getProcessorName() const override
        {
            return "PayPal";
        }
    };

    class SquareProcessor : public PaymentProcessor
    {
    public:
        bool processPayment(double amount) override
        {
            cout << "Processing $" << amount << " via Square\n";
            // Square API calls
            return true;
        }

        string getProcessorName() const override
        {
            return "Square";
        }
    };

    // High-level business logic depends on abstraction
    class OrderService
    {
    private:
        PaymentProcessor *processor;

    public:
        OrderService(PaymentProcessor *proc) : processor(proc) {}

        void checkout(double amount)
        {
            cout << "\n=== Checkout Process ===\n";
            cout << "Using payment processor: "
                 << processor->getProcessorName() << "\n";

            bool success = processor->processPayment(amount);

            if (success)
            {
                cout << "Order completed successfully!\n";
            }
            else
            {
                cout << "Payment failed!\n";
            }
        }

        void setPaymentProcessor(PaymentProcessor *proc)
        {
            processor = proc;
        }
    };
}

// ============================================================================
// EXAMPLE: Data Storage
// ============================================================================

namespace storage_system
{

    // Abstraction for data storage
    class DataRepository
    {
    public:
        virtual ~DataRepository() = default;
        virtual void save(const string &key, const string &data) = 0;
        virtual string load(const string &key) = 0;
        virtual void remove(const string &key) = 0;
    };

    // Concrete implementations
    class MySQLRepository : public DataRepository
    {
    public:
        void save(const string &key, const string &data) override
        {
            cout << "Saving to MySQL: " << key << " = " << data << "\n";
        }

        string load(const string &key) override
        {
            cout << "Loading from MySQL: " << key << "\n";
            return "data_from_mysql";
        }

        void remove(const string &key) override
        {
            cout << "Deleting from MySQL: " << key << "\n";
        }
    };

    class MongoDBRepository : public DataRepository
    {
    public:
        void save(const string &key, const string &data) override
        {
            cout << "Saving to MongoDB: " << key << " = " << data << "\n";
        }

        string load(const string &key) override
        {
            cout << "Loading from MongoDB: " << key << "\n";
            return "data_from_mongodb";
        }

        void remove(const string &key) override
        {
            cout << "Deleting from MongoDB: " << key << "\n";
        }
    };

    class RedisRepository : public DataRepository
    {
    public:
        void save(const string &key, const string &data) override
        {
            cout << "Caching in Redis: " << key << " = " << data << "\n";
        }

        string load(const string &key) override
        {
            cout << "Loading from Redis cache: " << key << "\n";
            return "data_from_redis";
        }

        void remove(const string &key) override
        {
            cout << "Removing from Redis: " << key << "\n";
        }
    };

    // High-level user service depends on abstraction
    class UserService
    {
    private:
        DataRepository *repository;

    public:
        UserService(DataRepository *repo) : repository(repo) {}

        void createUser(const string &username, const string &email)
        {
            string userData = "User:" + username + ",Email:" + email;
            repository->save(username, userData);
            cout << "User created successfully\n";
        }

        void getUser(const string &username)
        {
            string data = repository->load(username);
            cout << "User data: " << data << "\n";
        }

        void deleteUser(const string &username)
        {
            repository->remove(username);
            cout << "User deleted successfully\n";
        }
    };
}

// ============================================================================
// EXAMPLE: Logging System
// ============================================================================

namespace logging_system
{

    // Logging abstraction
    class Logger
    {
    public:
        virtual ~Logger() = default;
        virtual void log(const string &message) = 0;
        virtual void error(const string &message) = 0;
        virtual void warning(const string &message) = 0;
    };

    // Console logger
    class ConsoleLogger : public Logger
    {
    public:
        void log(const string &message) override
        {
            cout << "[LOG] " << message << "\n";
        }

        void error(const string &message) override
        {
            cout << "[ERROR] " << message << "\n";
        }

        void warning(const string &message) override
        {
            cout << "[WARNING] " << message << "\n";
        }
    };

    // File logger
    class FileLogger : public Logger
    {
    private:
        string filename;

    public:
        FileLogger(const string &file) : filename(file) {}

        void log(const string &message) override
        {
            cout << "[FILE LOG to " << filename << "] " << message << "\n";
        }

        void error(const string &message) override
        {
            cout << "[FILE ERROR to " << filename << "] " << message << "\n";
        }

        void warning(const string &message) override
        {
            cout << "[FILE WARNING to " << filename << "] " << message << "\n";
        }
    };

    // Cloud logger
    class CloudLogger : public Logger
    {
    private:
        string endpoint;

    public:
        CloudLogger(const string &ep) : endpoint(ep) {}

        void log(const string &message) override
        {
            cout << "[CLOUD LOG to " << endpoint << "] " << message << "\n";
        }

        void error(const string &message) override
        {
            cout << "[CLOUD ERROR to " << endpoint << "] " << message << "\n";
        }

        void warning(const string &message) override
        {
            cout << "[CLOUD WARNING to " << endpoint << "] " << message << "\n";
        }
    };

    // Application service depends on logger abstraction
    class ApplicationService
    {
    private:
        Logger *logger;

    public:
        ApplicationService(Logger *log) : logger(log) {}

        void performOperation()
        {
            logger->log("Starting operation...");

            try
            {
                // Simulate operation
                logger->log("Processing data...");
                logger->warning("Low memory warning");
                logger->log("Operation completed successfully");
            }
            catch (...)
            {
                logger->error("Operation failed!");
            }
        }

        void setLogger(Logger *log)
        {
            logger = log;
        }
    };
}

// ============================================================================
// ADVANCED EXAMPLE: Multi-Layer Dependency Injection
// ============================================================================

namespace multilayer_system
{

    // Data layer abstraction
    class IDatabase
    {
    public:
        virtual ~IDatabase() = default;
        virtual void connect() = 0;
        virtual string query(const string &sql) = 0;
    };

    // Cache layer abstraction
    class ICache
    {
    public:
        virtual ~ICache() = default;
        virtual void set(const string &key, const string &value) = 0;
        virtual string get(const string &key) = 0;
        virtual bool has(const string &key) = 0;
    };

    // Logging abstraction
    class ILogger
    {
    public:
        virtual ~ILogger() = default;
        virtual void log(const string &message) = 0;
    };

    // Concrete implementations
    class PostgreSQL : public IDatabase
    {
    public:
        void connect() override
        {
            cout << "Connected to PostgreSQL\n";
        }

        string query(const string &sql) override
        {
            cout << "Executing SQL: " << sql << "\n";
            return "result_from_postgres";
        }
    };

    class RedisCache : public ICache
    {
    private:
        vector<pair<string, string>> cache;

    public:
        void set(const string &key, const string &value) override
        {
            cache.push_back({key, value});
            cout << "Cached: " << key << "\n";
        }

        string get(const string &key) override
        {
            cout << "Cache hit: " << key << "\n";
            return "cached_value";
        }

        bool has(const string &key) override
        {
            return !cache.empty(); // Simplified
        }
    };

    class SimpleLogger : public ILogger
    {
    public:
        void log(const string &message) override
        {
            cout << "[LOG] " << message << "\n";
        }
    };

    // Repository layer depends on database and cache abstractions
    class ProductRepository
    {
    private:
        IDatabase *database;
        ICache *cache;
        ILogger *logger;

    public:
        ProductRepository(IDatabase *db, ICache *c, ILogger *log)
            : database(db), cache(c), logger(log) {}

        string getProduct(const string &id)
        {
            logger->log("Fetching product: " + id);

            // Check cache first
            if (cache->has(id))
            {
                logger->log("Cache hit");
                return cache->get(id);
            }

            // Query database
            logger->log("Cache miss, querying database");
            database->connect();
            string result = database->query("SELECT * FROM products WHERE id=" + id);

            // Update cache
            cache->set(id, result);

            return result;
        }
    };

    // Service layer depends on repository abstraction
    class ProductService
    {
    private:
        ProductRepository *repository;
        ILogger *logger;

    public:
        ProductService(ProductRepository *repo, ILogger *log)
            : repository(repo), logger(log) {}

        void displayProduct(const string &id)
        {
            logger->log("Displaying product: " + id);
            string product = repository->getProduct(id);
            cout << "Product data: " << product << "\n";
        }
    };
}

// ============================================================================
// EXAMPLE: Testing with Dependency Injection
// ============================================================================

namespace testing_example
{

    // Email service abstraction
    class IEmailService
    {
    public:
        virtual ~IEmailService() = default;
        virtual bool send(const string &to, const string &subject,
                          const string &body) = 0;
    };

    // Real implementation
    class SmtpEmailService : public IEmailService
    {
    public:
        bool send(const string &to, const string &subject,
                  const string &body) override
        {
            cout << "Sending real email via SMTP\n";
            cout << "To: " << to << "\n";
            cout << "Subject: " << subject << "\n";
            // Actual SMTP logic
            return true;
        }
    };

    // Mock implementation for testing
    class MockEmailService : public IEmailService
    {
    private:
        int sendCount = 0;

    public:
        bool send(const string &to, const string &subject,
                  const string &body) override
        {
            sendCount++;
            cout << "MOCK: Email sent (count: " << sendCount << ")\n";
            cout << "To: " << to << "\n";
            cout << "Subject: " << subject << "\n";
            return true;
        }

        int getSendCount() const { return sendCount; }
    };

    // User registration service
    class UserRegistration
    {
    private:
        IEmailService *emailService;

    public:
        UserRegistration(IEmailService *service) : emailService(service) {}

        bool registerUser(const string &email, const string &username)
        {
            cout << "\nRegistering user: " << username << "\n";

            // Business logic here...

            // Send welcome email
            bool sent = emailService->send(
                email,
                "Welcome!",
                "Welcome to our service, " + username);

            return sent;
        }
    };
}

// ============================================================================
// MAIN: Demonstration
// ============================================================================

int main()
{
    cout << "=== DEPENDENCY INVERSION PRINCIPLE (DIP) ===\n\n";

    // Notification System Demo
    cout << "--- NOTIFICATION SYSTEM ---\n";
    good_design::EmailService email;
    good_design::SMSService sms;
    good_design::PushNotificationService push;

    good_design::UserNotifier notifier(&email);
    notifier.notifyUser("user@example.com", "Your order has shipped!");

    cout << "\nSwitching to SMS:\n";
    notifier.setMessageService(&sms);
    notifier.notifyUser("+1234567890", "Your order has shipped!");

    cout << "\nSwitching to Push:\n";
    notifier.setMessageService(&push);
    notifier.notifyUser("user_device_id", "Your order has shipped!");

    // Payment Processing Demo
    cout << "\n--- PAYMENT PROCESSING ---\n";
    payment_system::StripeProcessor stripe;
    payment_system::PayPalProcessor paypal;
    payment_system::SquareProcessor square;

    payment_system::OrderService order(&stripe);
    order.checkout(99.99);

    order.setPaymentProcessor(&paypal);
    order.checkout(149.99);

    order.setPaymentProcessor(&square);
    order.checkout(79.99);

    // Storage System Demo
    cout << "\n--- STORAGE SYSTEM ---\n";
    storage_system::MySQLRepository mysql;
    storage_system::MongoDBRepository mongodb;
    storage_system::RedisRepository redis;

    storage_system::UserService userService(&mysql);
    userService.createUser("alice", "alice@example.com");
    userService.getUser("alice");

    cout << "\nSwitching to MongoDB:\n";
    storage_system::UserService userService2(&mongodb);
    userService2.createUser("bob", "bob@example.com");

    cout << "\nSwitching to Redis:\n";
    storage_system::UserService userService3(&redis);
    userService3.createUser("charlie", "charlie@example.com");

    // Logging System Demo
    cout << "\n--- LOGGING SYSTEM ---\n";
    logging_system::ConsoleLogger consoleLog;
    logging_system::FileLogger fileLog("app.log");
    logging_system::CloudLogger cloudLog("https://logs.example.com");

    logging_system::ApplicationService app(&consoleLog);
    cout << "\nWith Console Logger:\n";
    app.performOperation();

    cout << "\nWith File Logger:\n";
    app.setLogger(&fileLog);
    app.performOperation();

    cout << "\nWith Cloud Logger:\n";
    app.setLogger(&cloudLog);
    app.performOperation();

    // Multi-layer System Demo
    cout << "\n--- MULTI-LAYER SYSTEM ---\n";
    multilayer_system::PostgreSQL postgres;
    multilayer_system::RedisCache cache;
    multilayer_system::SimpleLogger logger;

    multilayer_system::ProductRepository repo(&postgres, &cache, &logger);
    multilayer_system::ProductService productService(&repo, &logger);

    productService.displayProduct("12345");

    // Testing Demo
    cout << "\n--- TESTING WITH DEPENDENCY INJECTION ---\n";
    testing_example::SmtpEmailService realEmail;
    testing_example::MockEmailService mockEmail;

    cout << "Production environment:\n";
    testing_example::UserRegistration prodReg(&realEmail);
    prodReg.registerUser("user@example.com", "John Doe");

    cout << "\nTest environment:\n";
    testing_example::UserRegistration testReg(&mockEmail);
    testReg.registerUser("test@example.com", "Test User");
    cout << "Emails sent in test: " << mockEmail.getSendCount() << "\n";

    cout << "\n=== KEY TAKEAWAYS ===\n";
    cout << "1. Depend on abstractions (interfaces), not concrete classes\n";
    cout << "2. High-level modules should not depend on low-level modules\n";
    cout << "3. Both should depend on abstractions\n";
    cout << "4. Enables loose coupling and easier testing\n";
    cout << "5. Dependency Injection is a key implementation technique\n";
    cout << "6. Makes code more flexible and maintainable\n";
    cout << "7. Core principle of IoC (Inversion of Control) containers\n";

    return 0;
}
