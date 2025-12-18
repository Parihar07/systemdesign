#include <iostream>
#include <stdexcept>

void f() noexcept
{
    // guaranteed not to throw (or will call std::terminate)
}

void g() noexcept(false)
{
    throw std::runtime_error("g throws");
}

struct Widget
{
    int *p;
    Widget()
    try : p(new int[10])
    {
        std::cout << "Widget ctor body\n";
        throw std::runtime_error("construction failed");
    }
    catch (...)
    {
        std::cerr << "Widget ctor caught exception; cleaning up\n";
        delete[] p; // cleanup
        throw;      // rethrow to caller
    }
    ~Widget() noexcept { delete[] p; }
};

int main()
{
    std::cout << "-- noexcept & function try blocks --\n";
    std::cout << "noexcept(f()): " << noexcept(f()) << "\n";
    std::cout << "noexcept(g()): " << noexcept(g()) << "\n";

    try
    {
        g();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught from g: " << e.what() << "\n";
    }

    try
    {
        Widget w; // constructor throws, cleanup happens in catch
    }
    catch (const std::exception &e)
    {
        std::cerr << "Widget construction failed: " << e.what() << "\n";
    }
}
