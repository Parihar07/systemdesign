#include <iostream>
#include <string>
#include <vector>
#include <memory>

// =================================================================================
// Association vs Aggregation - The Key Difference
// =================================================================================

/*
 * BOTH use references/pointers and DON'T own the object, BUT:
 * 
 * ASSOCIATION: Temporary "uses" relationship
 * - The reference exists only during a function call
 * - No member variable stores the reference
 * - Relationship ends when the function returns
 * 
 * AGGREGATION: Persistent "has" relationship
 * - The reference is stored as a member variable
 * - The relationship persists for the object's lifetime
 * - Container can call methods on the part anytime
 */

class Book {
private:
    std::string m_title;
public:
    Book(const std::string& title) : m_title(title) {
        std::cout << "Book '" << m_title << "' created." << std::endl;
    }
    ~Book() {
        std::cout << "Book '" << m_title << "' destroyed." << std::endl;
    }
    std::string getTitle() const { return m_title; }
};

// --- ASSOCIATION Example (Temporary) ---
class Reader {
private:
    std::string m_name;
    // NOTE: No Book member variable!
public:
    Reader(const std::string& name) : m_name(name) {}
    
    // ASSOCIATION: Book is passed in, used, and the relationship ends
    void read(const Book& book) {
        std::cout << m_name << " is reading '" << book.getTitle() << "'" << std::endl;
        // When this function returns, the Reader no longer has any connection to the Book
    }
};

// --- AGGREGATION Example (Persistent) ---
class Library {
private:
    std::string m_name;
    // AGGREGATION: Library stores references to Books
    std::vector<std::shared_ptr<Book>> m_books; // Persistent relationship!
    
public:
    Library(const std::string& name) : m_name(name) {}
    
    void addBook(std::shared_ptr<Book> book) {
        m_books.push_back(book);
        std::cout << "Book '" << book->getTitle() << "' added to " << m_name << std::endl;
    }
    
    void listBooks() const {
        std::cout << "\nBooks in " << m_name << ":" << std::endl;
        for (const auto& book : m_books) {
            std::cout << "  - " << book->getTitle() << std::endl;
        }
    }
    
    // The Library can access its books ANYTIME, not just during one function call
};

int main() {
    auto book1 = std::make_shared<Book>("Clean Code");
    auto book2 = std::make_shared<Book>("Design Patterns");
    
    std::cout << "\n=== ASSOCIATION (Temporary) ===" << std::endl;
    Reader alice("Alice");
    alice.read(*book1);  // Alice uses book1 temporarily
    alice.read(*book2);  // Alice uses book2 temporarily
    // After these calls, Alice has NO stored relationship with the books
    
    std::cout << "\n=== AGGREGATION (Persistent) ===" << std::endl;
    Library city_library("City Library");
    city_library.addBook(book1);  // Library stores the book
    city_library.addBook(book2);  // Library stores the book
    
    // The library can access its books at ANY time
    city_library.listBooks();
    
    std::cout << "\n--- Demonstrating the difference ---" << std::endl;
    std::cout << "Alice (Association): Has NO persistent connection to books" << std::endl;
    std::cout << "Library (Aggregation): MAINTAINS connection to books" << std::endl;
    
    std::cout << "\n--- End of main ---" << std::endl;
    // Books are destroyed last (when shared_ptrs go out of scope)
    return 0;
}
