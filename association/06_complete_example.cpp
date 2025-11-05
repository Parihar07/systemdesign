#include <iostream>
#include <string>
#include <vector>
#include <memory>

// =================================================================================
// Complete Example: Hospital Management System
// Demonstrates all 4 OOP relationships working together
// =================================================================================

/*
 * This example shows:
 * 1. INHERITANCE (IS-A): Doctor IS-A Person, Patient IS-A Person
 * 2. COMPOSITION (Strong HAS-A): Person HAS-A Address (dies with Person)
 * 3. AGGREGATION (Weak HAS-A): Department HAS Doctors (doctors can exist independently)
 * 4. ASSOCIATION (USES-A): Doctor treats Patient (temporary interaction)
 */

// --- COMPOSITION: Address is part of Person ---
class Address {
private:
    std::string m_street;
    std::string m_city;
public:
    Address(const std::string& street, const std::string& city) 
        : m_street(street), m_city(city) {
        std::cout << "  Address created: " << m_street << ", " << m_city << std::endl;
    }
    ~Address() {
        std::cout << "  Address destroyed: " << m_street << ", " << m_city << std::endl;
    }
    std::string getFullAddress() const {
        return m_street + ", " + m_city;
    }
};

// --- INHERITANCE Base: Person ---
class Person {
protected:
    std::string m_name;
    int m_age;
    Address m_address;  // COMPOSITION: Address is owned by Person
public:
    Person(const std::string& name, int age, const Address& addr) 
        : m_name(name), m_age(age), m_address(addr) {
        std::cout << "Person '" << m_name << "' created." << std::endl;
    }
    virtual ~Person() {
        std::cout << "Person '" << m_name << "' destroyed." << std::endl;
        // Address will be destroyed automatically after this
    }
    std::string getName() const { return m_name; }
    std::string getAddress() const { return m_address.getFullAddress(); }
};

// --- INHERITANCE: Doctor IS-A Person ---
class Doctor : public Person {
private:
    std::string m_specialization;
public:
    Doctor(const std::string& name, int age, const Address& addr, 
           const std::string& spec)
        : Person(name, age, addr), m_specialization(spec) {
        std::cout << "Doctor (specialization: " << m_specialization << ") created." << std::endl;
    }
    ~Doctor() {
        std::cout << "Doctor '" << m_name << "' destroyed." << std::endl;
    }
    
    // ASSOCIATION: Doctor "uses" Patient (temporary interaction)
    void treat(const Person& patient) const {
        std::cout << "Dr. " << m_name << " (" << m_specialization 
                  << ") is treating patient: " << patient.getName() << std::endl;
    }
    
    std::string getSpecialization() const { return m_specialization; }
};

// --- INHERITANCE: Patient IS-A Person ---
class Patient : public Person {
private:
    std::string m_condition;
public:
    Patient(const std::string& name, int age, const Address& addr, 
            const std::string& condition)
        : Person(name, age, addr), m_condition(condition) {
        std::cout << "Patient (condition: " << m_condition << ") created." << std::endl;
    }
    ~Patient() {
        std::cout << "Patient '" << m_name << "' destroyed." << std::endl;
    }
};

// --- AGGREGATION: Department HAS Doctors (shared ownership) ---
class Department {
private:
    std::string m_name;
    std::vector<std::shared_ptr<Doctor>> m_doctors;  // AGGREGATION
public:
    Department(const std::string& name) : m_name(name) {
        std::cout << "Department '" << m_name << "' created." << std::endl;
    }
    ~Department() {
        std::cout << "Department '" << m_name << "' destroyed (doctors still exist)." << std::endl;
    }
    
    void addDoctor(std::shared_ptr<Doctor> doctor) {
        m_doctors.push_back(doctor);
        std::cout << "Dr. " << doctor->getName() << " added to " << m_name << std::endl;
    }
    
    void listDoctors() const {
        std::cout << "\nDoctors in " << m_name << ":" << std::endl;
        for (const auto& doc : m_doctors) {
            std::cout << "  - Dr. " << doc->getName() 
                      << " (" << doc->getSpecialization() << ")" << std::endl;
        }
    }
};

int main() {
    std::cout << "=== Hospital Management System ===" << std::endl;
    std::cout << "\n--- Creating Doctors (with Addresses via Composition) ---" << std::endl;
    
    // COMPOSITION: Address is created as part of Doctor
    auto dr_smith = std::make_shared<Doctor>(
        "Smith", 45, Address("123 Main St", "Boston"), "Cardiology"
    );
    
    auto dr_jones = std::make_shared<Doctor>(
        "Jones", 38, Address("456 Oak Ave", "Boston"), "Neurology"
    );
    
    std::cout << "\n--- Creating Patient ---" << std::endl;
    Patient patient1("Alice", 30, Address("789 Elm St", "Boston"), "Headache");
    
    {
        std::cout << "\n--- Creating Department (Aggregation) ---" << std::endl;
        Department cardiology_dept("Cardiology Department");
        cardiology_dept.addDoctor(dr_smith);
        
        Department neurology_dept("Neurology Department");
        neurology_dept.addDoctor(dr_jones);
        
        neurology_dept.listDoctors();
        
        std::cout << "\n--- Doctor treating Patient (Association) ---" << std::endl;
        dr_jones->treat(patient1);  // ASSOCIATION: temporary "uses" relationship
        
        std::cout << "\n--- Departments going out of scope ---" << std::endl;
    } // Departments destroyed, but doctors still exist!
    
    std::cout << "\n--- Doctors still exist after departments are gone ---" << std::endl;
    std::cout << "Dr. Smith still practicing at: " << dr_smith->getAddress() << std::endl;
    
    std::cout << "\n--- End of main (all objects destroyed) ---" << std::endl;
    // Order: Patient -> Doctors -> their Addresses
    return 0;
}
