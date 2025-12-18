#include <iostream>
#include <memory>
#include <stdexcept>

struct Tracer
{
    const char *name;
    explicit Tracer(const char *n) : name(n) { std::cout << "Construct " << name << "\n"; }
    ~Tracer() { std::cout << "Destruct  " << name << "\n"; }
};

void work()
{
    Tracer a{"A"};
    std::unique_ptr<int> p(new int(42)); // RAII
    Tracer b{"B"};
    std::cout << "About to throw...\n";
    throw std::runtime_error("boom");
    Tracer c{"C"}; // not executed
}

int main()
{
    std::cout << "-- Stack unwinding & RAII --\n";
    try
    {
        work();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught: " << e.what() << "\n";
    }
    std::cout << "Note: RAII cleaned resources automatically during unwinding.\n";
}
