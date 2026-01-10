/**
 * INTERFACE SEGREGATION PRINCIPLE (ISP)
 *
 * Definition: Clients should not be forced to depend on interfaces they don't use.
 *
 * Key Points:
 * - Many specific interfaces are better than one general-purpose interface
 * - No client should be forced to implement methods it doesn't use
 * - Prevents "fat" interfaces that force unnecessary dependencies
 * - Promotes focused, cohesive interfaces
 * - Reduces coupling and increases flexibility
 * - Makes code easier to refactor and maintain
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

// ============================================================================
// VIOLATION: Fat Interface (All-in-One Worker)
// ============================================================================

namespace bad_design
{

    // Problem: This interface forces all workers to implement all methods
    class Worker
    {
    public:
        virtual ~Worker() = default;
        virtual void work() = 0;
        virtual void eat() = 0;
        virtual void sleep() = 0;
        virtual void getSalary() = 0;
        virtual void takeBreak() = 0;
        virtual void attendMeeting() = 0;
    };

    // Human worker can implement all methods
    class HumanWorker : public Worker
    {
    public:
        void work() override
        {
            cout << "Human working...\n";
        }

        void eat() override
        {
            cout << "Human eating lunch...\n";
        }

        void sleep() override
        {
            cout << "Human sleeping...\n";
        }

        void getSalary() override
        {
            cout << "Human getting paid...\n";
        }

        void takeBreak() override
        {
            cout << "Human taking a break...\n";
        }

        void attendMeeting() override
        {
            cout << "Human attending meeting...\n";
        }
    };

    // Problem: Robot doesn't eat, sleep, or take breaks!
    class RobotWorker : public Worker
    {
    public:
        void work() override
        {
            cout << "Robot working 24/7...\n";
        }

        // Forced to implement methods it doesn't need
        void eat() override
        {
            // What to do here? Robots don't eat!
            throw runtime_error("Robots don't eat!");
        }

        void sleep() override
        {
            throw runtime_error("Robots don't sleep!");
        }

        void getSalary() override
        {
            throw runtime_error("Robots don't get paid!");
        }

        void takeBreak() override
        {
            throw runtime_error("Robots don't take breaks!");
        }

        void attendMeeting() override
        {
            throw runtime_error("Robots don't attend meetings!");
        }
    };

    // This function depends on the fat interface
    void manageWorker(Worker &worker)
    {
        worker.work();
        worker.eat(); // Will crash if it's a robot!
    }
}

// ============================================================================
// CORRECT: Segregated Interfaces
// ============================================================================

namespace good_design
{

    // Base interface for all workers
    class Workable
    {
    public:
        virtual ~Workable() = default;
        virtual void work() = 0;
    };

    // Separate interface for eating
    class Eatable
    {
    public:
        virtual ~Eatable() = default;
        virtual void eat() = 0;
    };

    // Separate interface for sleeping
    class Sleepable
    {
    public:
        virtual ~Sleepable() = default;
        virtual void sleep() = 0;
    };

    // Separate interface for getting paid
    class Payable
    {
    public:
        virtual ~Payable() = default;
        virtual void getSalary() = 0;
    };

    // Separate interface for breaks
    class Breakable
    {
    public:
        virtual ~Breakable() = default;
        virtual void takeBreak() = 0;
    };

    // Separate interface for meetings
    class MeetingParticipant
    {
    public:
        virtual ~MeetingParticipant() = default;
        virtual void attendMeeting() = 0;
    };

    // Human worker implements all relevant interfaces
    class HumanWorker : public Workable, public Eatable, public Sleepable, public Payable, public Breakable, public MeetingParticipant
    {
    public:
        void work() override
        {
            cout << "Human working...\n";
        }

        void eat() override
        {
            cout << "Human eating lunch...\n";
        }

        void sleep() override
        {
            cout << "Human sleeping...\n";
        }

        void getSalary() override
        {
            cout << "Human getting paid...\n";
        }

        void takeBreak() override
        {
            cout << "Human taking a break...\n";
        }

        void attendMeeting() override
        {
            cout << "Human attending meeting...\n";
        }
    };

    // Robot only implements what it needs
    class RobotWorker : public Workable
    {
    public:
        void work() override
        {
            cout << "Robot working 24/7...\n";
        }
    };

    // Contractor gets paid but doesn't attend meetings
    class ContractorWorker : public Workable, public Payable
    {
    public:
        void work() override
        {
            cout << "Contractor working remotely...\n";
        }

        void getSalary() override
        {
            cout << "Contractor invoicing client...\n";
        }
    };

    // Functions depend only on what they need
    void makeWork(Workable &worker)
    {
        worker.work(); // Works with any worker type
    }

    void serveLunch(Eatable &worker)
    {
        worker.eat(); // Only works with workers who eat
    }

    void processPayroll(Payable &worker)
    {
        worker.getSalary(); // Only works with workers who get paid
    }
}

// ============================================================================
// REAL-WORLD EXAMPLE: Printer Interfaces
// ============================================================================

namespace printer_system
{

    // Fat interface violation
    namespace bad
    {
        class MultiFunctionDevice
        {
        public:
            virtual ~MultiFunctionDevice() = default;
            virtual void print() = 0;
            virtual void scan() = 0;
            virtual void fax() = 0;
            virtual void photocopy() = 0;
        };

        // Problem: Simple printer forced to implement scan, fax, copy
        class SimplePrinter : public MultiFunctionDevice
        {
        public:
            void print() override
            {
                cout << "Printing...\n";
            }

            void scan() override
            {
                throw runtime_error("This printer can't scan!");
            }

            void fax() override
            {
                throw runtime_error("This printer can't fax!");
            }

            void photocopy() override
            {
                throw runtime_error("This printer can't photocopy!");
            }
        };
    }

    // Segregated interfaces
    namespace good
    {
        // Separate capability interfaces
        class Printable
        {
        public:
            virtual ~Printable() = default;
            virtual void print(const string &document) = 0;
        };

        class Scannable
        {
        public:
            virtual ~Scannable() = default;
            virtual string scan() = 0;
        };

        class Faxable
        {
        public:
            virtual ~Faxable() = default;
            virtual void fax(const string &document, const string &number) = 0;
        };

        class Photocopiable
        {
        public:
            virtual ~Photocopiable() = default;
            virtual void photocopy(int copies) = 0;
        };

        // Simple printer only implements what it can do
        class SimplePrinter : public Printable
        {
        public:
            void print(const string &document) override
            {
                cout << "Printing: " << document << "\n";
            }
        };

        // Scanner only implements scanning
        class SimpleScanner : public Scannable
        {
        public:
            string scan() override
            {
                cout << "Scanning document...\n";
                return "scanned_document.pdf";
            }
        };

        // All-in-one printer implements all interfaces
        class MultiFunctionPrinter : public Printable, public Scannable, public Faxable, public Photocopiable
        {
        public:
            void print(const string &document) override
            {
                cout << "MFP Printing: " << document << "\n";
            }

            string scan() override
            {
                cout << "MFP Scanning...\n";
                return "scanned.pdf";
            }

            void fax(const string &document, const string &number) override
            {
                cout << "MFP Faxing " << document << " to " << number << "\n";
            }

            void photocopy(int copies) override
            {
                cout << "MFP Photocopying " << copies << " copies\n";
            }
        };

        // Functions depend only on required capability
        void printDocument(Printable &printer, const string &doc)
        {
            printer.print(doc);
        }

        void scanAndEmail(Scannable &scanner)
        {
            string file = scanner.scan();
            cout << "Emailing " << file << "\n";
        }
    }
}

// ============================================================================
// EXAMPLE: Database Operations
// ============================================================================

namespace database_system
{

    // Fat interface (BAD)
    namespace bad
    {
        class DatabaseOperations
        {
        public:
            virtual ~DatabaseOperations() = default;
            virtual void connect() = 0;
            virtual void disconnect() = 0;
            virtual void read() = 0;
            virtual void write() = 0;
            virtual void delete_data() = 0;
            virtual void backup() = 0;
            virtual void restore() = 0;
            virtual void migrate() = 0;
        };

        // ReadOnlyUser forced to implement write operations
        class ReadOnlyUser : public DatabaseOperations
        {
        public:
            void connect() override { cout << "Connected\n"; }
            void disconnect() override { cout << "Disconnected\n"; }

            void read() override
            {
                cout << "Reading data...\n";
            }

            // Forced to implement these
            void write() override { throw runtime_error("No write permission!"); }
            void delete_data() override { throw runtime_error("No delete permission!"); }
            void backup() override { throw runtime_error("No backup permission!"); }
            void restore() override { throw runtime_error("No restore permission!"); }
            void migrate() override { throw runtime_error("No migrate permission!"); }
        };
    }

    // Segregated interfaces (GOOD)
    namespace good
    {
        // Connection management
        class Connectable
        {
        public:
            virtual ~Connectable() = default;
            virtual void connect() = 0;
            virtual void disconnect() = 0;
            virtual bool isConnected() const = 0;
        };

        // Read operations
        class Readable
        {
        public:
            virtual ~Readable() = default;
            virtual string read(const string &query) = 0;
        };

        // Write operations
        class Writable
        {
        public:
            virtual ~Writable() = default;
            virtual void write(const string &data) = 0;
        };

        // Delete operations
        class Deletable
        {
        public:
            virtual ~Deletable() = default;
            virtual void remove(const string &id) = 0;
        };

        // Backup operations
        class Backupable
        {
        public:
            virtual ~Backupable() = default;
            virtual void backup(const string &path) = 0;
            virtual void restore(const string &path) = 0;
        };

        // Migration operations
        class Migratable
        {
        public:
            virtual ~Migratable() = default;
            virtual void migrate(const string &version) = 0;
        };

        // Read-only database connection
        class ReadOnlyConnection : public Connectable, public Readable
        {
        private:
            bool connected = false;

        public:
            void connect() override
            {
                connected = true;
                cout << "Read-only connection established\n";
            }

            void disconnect() override
            {
                connected = false;
                cout << "Connection closed\n";
            }

            bool isConnected() const override
            {
                return connected;
            }

            string read(const string &query) override
            {
                cout << "Executing query: " << query << "\n";
                return "result_data";
            }
        };

        // Full access database connection
        class FullAccessConnection : public Connectable, public Readable, public Writable, public Deletable
        {
        private:
            bool connected = false;

        public:
            void connect() override
            {
                connected = true;
                cout << "Full access connection established\n";
            }

            void disconnect() override
            {
                connected = false;
                cout << "Connection closed\n";
            }

            bool isConnected() const override
            {
                return connected;
            }

            string read(const string &query) override
            {
                cout << "Reading: " << query << "\n";
                return "data";
            }

            void write(const string &data) override
            {
                cout << "Writing: " << data << "\n";
            }

            void remove(const string &id) override
            {
                cout << "Deleting record: " << id << "\n";
            }
        };

        // Admin connection with backup capabilities
        class AdminConnection : public FullAccessConnection,
                                public Backupable,
                                public Migratable
        {
        public:
            void backup(const string &path) override
            {
                cout << "Backing up database to: " << path << "\n";
            }

            void restore(const string &path) override
            {
                cout << "Restoring database from: " << path << "\n";
            }

            void migrate(const string &version) override
            {
                cout << "Migrating database to version: " << version << "\n";
            }
        };

        // Service that only needs read access
        class ReportingService
        {
        public:
            void generateReport(Readable &db)
            {
                cout << "Generating report...\n";
                db.read("SELECT * FROM sales");
            }
        };

        // Service that needs write access
        class DataImportService
        {
        public:
            void importData(Writable &db, const string &data)
            {
                cout << "Importing data...\n";
                db.write(data);
            }
        };
    }
}

// ============================================================================
// EXAMPLE: Document Management
// ============================================================================

namespace document_system
{

    // Document capabilities
    class Readable
    {
    public:
        virtual ~Readable() = default;
        virtual string getContent() const = 0;
    };

    class Editable
    {
    public:
        virtual ~Editable() = default;
        virtual void setContent(const string &content) = 0;
    };

    class Searchable
    {
    public:
        virtual ~Searchable() = default;
        virtual vector<int> search(const string &keyword) const = 0;
    };

    class Commentable
    {
    public:
        virtual ~Commentable() = default;
        virtual void addComment(const string &comment) = 0;
        virtual vector<string> getComments() const = 0;
    };

    class Shareable
    {
    public:
        virtual ~Shareable() = default;
        virtual void share(const string &user) = 0;
        virtual vector<string> getSharedWith() const = 0;
    };

    // Read-only document
    class ReadOnlyDocument : public Readable, public Searchable
    {
    private:
        string content;

    public:
        ReadOnlyDocument(const string &c) : content(c) {}

        string getContent() const override
        {
            return content;
        }

        vector<int> search(const string &keyword) const override
        {
            vector<int> positions;
            size_t pos = content.find(keyword);
            while (pos != string::npos)
            {
                positions.push_back(pos);
                pos = content.find(keyword, pos + 1);
            }
            return positions;
        }
    };

    // Editable document
    class EditableDocument : public Readable, public Editable, public Searchable, public Commentable
    {
    private:
        string content;
        vector<string> comments;

    public:
        EditableDocument(const string &c) : content(c) {}

        string getContent() const override
        {
            return content;
        }

        void setContent(const string &c) override
        {
            content = c;
            cout << "Document updated\n";
        }

        vector<int> search(const string &keyword) const override
        {
            vector<int> positions;
            size_t pos = content.find(keyword);
            while (pos != string::npos)
            {
                positions.push_back(pos);
                pos = content.find(keyword, pos + 1);
            }
            return positions;
        }

        void addComment(const string &comment) override
        {
            comments.push_back(comment);
        }

        vector<string> getComments() const override
        {
            return comments;
        }
    };

    // Collaborative document
    class CollaborativeDocument : public EditableDocument, public Shareable
    {
    private:
        vector<string> sharedUsers;

    public:
        CollaborativeDocument(const string &c) : EditableDocument(c) {}

        void share(const string &user) override
        {
            sharedUsers.push_back(user);
            cout << "Document shared with " << user << "\n";
        }

        vector<string> getSharedWith() const override
        {
            return sharedUsers;
        }
    };

    // Document viewer only needs read access
    class DocumentViewer
    {
    public:
        void display(const Readable &doc)
        {
            cout << "Document Content:\n"
                 << doc.getContent() << "\n";
        }
    };

    // Document editor needs edit access
    class DocumentEditor
    {
    public:
        void edit(Editable &doc, const string &newContent)
        {
            doc.setContent(newContent);
        }
    };

    // Search engine only needs search capability
    class SearchEngine
    {
    public:
        void find(const Searchable &doc, const string &keyword)
        {
            auto positions = doc.search(keyword);
            cout << "Found '" << keyword << "' at " << positions.size()
                 << " positions\n";
        }
    };
}

// ============================================================================
// MAIN: Demonstration
// ============================================================================

int main()
{
    cout << "=== INTERFACE SEGREGATION PRINCIPLE (ISP) ===\n\n";

    // Worker System
    cout << "--- WORKER SYSTEM (Good Design) ---\n";
    good_design::HumanWorker human;
    good_design::RobotWorker robot;
    good_design::ContractorWorker contractor;

    good_design::makeWork(human);
    good_design::makeWork(robot);
    good_design::makeWork(contractor);

    cout << "\n";
    good_design::serveLunch(human);
    // Can't call serveLunch with robot - compile error (good!)

    good_design::processPayroll(human);
    good_design::processPayroll(contractor);

    // Printer System
    cout << "\n--- PRINTER SYSTEM ---\n";
    printer_system::good::SimplePrinter simplePrinter;
    printer_system::good::MultiFunctionPrinter mfp;

    printer_system::good::printDocument(simplePrinter, "report.pdf");
    printer_system::good::printDocument(mfp, "invoice.pdf");
    printer_system::good::scanAndEmail(mfp);

    // Database System
    cout << "\n--- DATABASE SYSTEM ---\n";
    database_system::good::ReadOnlyConnection readConn;
    database_system::good::FullAccessConnection fullConn;
    database_system::good::AdminConnection adminConn;

    readConn.connect();
    database_system::good::ReportingService reporting;
    reporting.generateReport(readConn);

    cout << "\n";
    fullConn.connect();
    database_system::good::DataImportService importer;
    importer.importData(fullConn, "new_data");

    cout << "\n";
    adminConn.connect();
    adminConn.backup("/backup/db.bak");

    // Document System
    cout << "\n--- DOCUMENT SYSTEM ---\n";
    document_system::ReadOnlyDocument readDoc("This is a read-only document.");
    document_system::EditableDocument editDoc("This is an editable document.");
    document_system::CollaborativeDocument collabDoc("Shared document.");

    document_system::DocumentViewer viewer;
    viewer.display(readDoc);
    viewer.display(editDoc);

    cout << "\n";
    document_system::DocumentEditor editor;
    editor.edit(editDoc, "Updated content.");

    cout << "\n";
    document_system::SearchEngine search;
    search.find(readDoc, "read-only");

    collabDoc.share("alice@example.com");
    collabDoc.share("bob@example.com");

    cout << "\n=== KEY TAKEAWAYS ===\n";
    cout << "1. Split large interfaces into smaller, focused ones\n";
    cout << "2. Clients depend only on interfaces they actually use\n";
    cout << "3. Reduces coupling and increases flexibility\n";
    cout << "4. Makes code easier to understand and maintain\n";
    cout << "5. Prevents forcing clients to implement unused methods\n";
    cout << "6. Use composition of interfaces over fat interfaces\n";

    return 0;
}
