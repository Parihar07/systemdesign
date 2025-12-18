#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

void low_level()
{
    throw std::runtime_error("disk read failed");
}

void mid_level()
{
    try
    {
        low_level();
    }
    catch (...)
    {
        std::throw_with_nested(std::runtime_error("cache layer error"));
    }
}

void high_level()
{
    try
    {
        mid_level();
    }
    catch (...)
    {
        std::throw_with_nested(std::runtime_error("service unavailable"));
    }
}

void print_nested(const std::exception &e, int depth = 0)
{
    std::cerr << std::string(depth * 2, ' ') << "- " << e.what() << "\n";
    try
    {
        std::rethrow_if_nested(e);
    }
    catch (const std::exception &nested)
    {
        print_nested(nested, depth + 1);
    }
    catch (...)
    {
        // no further nested info
    }
}

int main()
{
    std::cout << "-- Nested exceptions --\n";
    try
    {
        high_level();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception chain:\n";
        print_nested(e);
    }
}
