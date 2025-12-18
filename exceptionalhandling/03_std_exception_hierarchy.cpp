#include <iostream>
#include <stdexcept>

void logic_demo() { throw std::domain_error("Domain error: invalid input domain"); }
void runtime_demo() { throw std::runtime_error("Runtime error: failed operation"); }

int main()
{
    std::cout << "-- std::exception hierarchy --\n";

    try
    {
        logic_demo();
    }
    catch (const std::domain_error &e)
    {
        std::cerr << "Caught domain_error specifically: " << e.what() << "\n";
    }

    try
    {
        runtime_demo();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Caught runtime_error specifically: " << e.what() << "\n";
    }

    // Order matters: more specific before general
    try
    {
        logic_demo();
    }
    catch (const std::logic_error &e)
    {
        std::cerr << "Caught logic_error (base of domain_error): " << e.what() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught std::exception: " << e.what() << "\n";
    }
}
