#include <iostream>
#include <string>

// =================================================================================
// Part 8: Multiple Inheritance
// =================================================================================

/*
 * Multiple inheritance allows a class to inherit from more than one base class,
 * combining their features.
 *
 * System-Level View:
 *
 * 1.  Memory Layout: When an object of a derived class is created, it contains the
 *     data members of its base classes in the order they are listed in the inheritance
 *     declaration. For `class C : public A, public B`, the memory layout of a C object
 *     will be the members of A, followed by the members of B, followed by C's own members.
 *
 * 2.  VTable Complexity: If multiple base classes have virtual functions, the derived
 *     object's memory layout becomes more complex. It will typically contain multiple
 *     vptrs, one for each base class that has a vtable. This can increase the object's
 *     size and adds a small overhead to pointer casting.
 *
 * 3.  Ambiguity: If two base classes have a method with the same name, calling that
 *     method from the derived class is ambiguous and will result in a compile error.
 *     This must be resolved using the scope resolution operator (e.g., `BaseA::method()`).
 *
 * 4.  The Diamond Problem: This is the most famous issue with multiple inheritance.
 *     If Class B and Class C inherit from Class A, and Class D inherits from both B and C,
 *     D will get two copies of A's members. We solve this with `virtual inheritance`.
 */

// --- Base Class 1 ---
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "[LOG]: " << message << std::endl;
    }

    virtual ~Logger() = default;
};

// --- Base Class 2 ---
class FileSystem {
public:
    void readFile(const std::string& path) {
        std::cout << "[FS]: Reading from " << path << std::endl;
    }

    void writeFile(const std::string& path) {
        std::cout << "[FS]: Writing to " << path << std::endl;
    }

    virtual ~FileSystem() = default;
};

// --- Derived Class using Multiple Inheritance ---
// BackupService inherits all public members from both Logger and FileSystem.
class BackupService : public Logger, public FileSystem {
public:
    void performBackup(const std::string& from, const std::string& to) {
        log("Starting backup operation."); // Inherited from Logger
        readFile(from);                   // Inherited from FileSystem
        writeFile(to);                    // Inherited from FileSystem
        log("Backup operation finished.");  // Inherited from Logger
    }
};

int main() {
    std::cout << "--- Demonstrating Multiple Inheritance ---" << std::endl;

    BackupService backup;
    backup.performBackup("/data/source.dat", "/backup/dest.dat");

    std::cout << "\n--- Calling inherited methods directly ---" << std::endl;
    // The BackupService object has access to methods from both base classes.
    backup.log("Performing a manual log check.");
    backup.readFile("/data/another_file.txt");

    // --- Pointer Casting and Ambiguity ---
    // A pointer to BackupService can be implicitly cast to a pointer of either base class.
    Logger* logger_ptr = &backup;
    FileSystem* fs_ptr = &backup;

    // The compiler automatically adjusts the pointer to the correct subobject address.
    // The address of `logger_ptr` and `fs_ptr` might be different!
    std::cout << "\n--- Pointer Addresses ---" << std::endl;
    std::cout << "Address of backup object:      " << &backup << std::endl;
    std::cout << "Address via Logger pointer:    " << logger_ptr << std::endl;
    std::cout << "Address via FileSystem pointer: " << fs_ptr << std::endl;

    // This demonstrates that the FileSystem subobject is located at an offset
    // within the BackupService object's memory.

    return 0;
}
