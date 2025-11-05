#include <iostream>
#include <string>
#include <vector>
#include <memory> // Required for std::shared_ptr

// =================================================================================
// Part 2: Aggregation (Shared "Has-A" Relationship)
// =================================================================================

/*
 * Aggregation is a "has-a" relationship where the "part" can exist independently
 * of the "whole". The whole does not own the part.
 *
 * Example: A Department has Professors. If the Department is dissolved, the
 * Professors still exist.
 *
 * System-Level View:
 * - Shared Ownership: The Department does not have exclusive ownership of the
 *   Professors. Other parts of the system can also hold a reference to them.
 * - Implementation: This is typically implemented using pointers. In modern C++,
 *   `std::shared_ptr` is the ideal tool. It uses reference counting to manage the
 *   lifetime of the object. The object is only destroyed when the last `shared_ptr`
 *   pointing to it goes out of scope.
 * - Memory: The Department object contains a list of pointers. The actual Professor
 *   objects exist separately on the heap.
 */

class Professor {
private:
    std::string m_name;
public:
    Professor(const std::string& name) : m_name(name) {
        std::cout << "Professor '" << m_name << "' created." << std::endl;
    }
    ~Professor() {
        std::cout << "Professor '" << m_name << "' destroyed." << std::endl;
    }
    std::string getName() const { return m_name; }
};

class Department {
private:
    std::string m_name;
    // The Department holds a list of shared pointers to Professors.
    std::vector<std::shared_ptr<Professor>> m_professors;

public:
    Department(const std::string& name) : m_name(name) {
        std::cout << "Department '" << m_name << "' created." << std::endl;
    }
    ~Department() {
        std::cout << "Department '" << m_name << "' destroyed. (Professors may still exist)" << std::endl;
    }

    void addProfessor(std::shared_ptr<Professor> prof) {
        m_professors.push_back(prof);
    }
};

int main() {
    std::cout << "--- Creating Professors (owned by main) ---" << std::endl;
    // Create professors as shared_ptrs. `main` is the first owner.
    auto prof1 = std::make_shared<Professor>("Dr. Smith");
    auto prof2 = std::make_shared<Professor>("Dr. Jones");

    std::cout << "\nReference count for Dr. Smith: " << prof1.use_count() << std::endl; // Should be 1

    { // Create a new scope for the department
        std::cout << "\n--- Department scope begins ---" << std::endl;
        Department cs_dept("Computer Science");
        
        // The department now also shares ownership of the professors.
        cs_dept.addProfessor(prof1);
        cs_dept.addProfessor(prof2);

        std::cout << "Reference count for Dr. Smith inside scope: " << prof1.use_count() << std::endl; // Should be 2
        
        std::cout << "--- Department scope ends ---" << std::endl;
    } // cs_dept is destroyed here. Its shared_ptrs are released.

    std::cout << "\n--- Back in main scope ---" << std::endl;
    std::cout << "Reference count for Dr. Smith after department destruction: " << prof1.use_count() << std::endl; // Should be 1 again

    std::cout << "Professor '" << prof1->getName() << "' still exists." << std::endl;

    std::cout << "\n--- End of main ---" << std::endl;
    // The last shared_ptrs (in main) go out of scope, and the professors are finally destroyed.
    return 0;
}
