#include <iostream>
#include <stdexcept>
#include <string>

int parse_int(const std::string &s)
{
    size_t idx = 0;
    int value = 0;
    try
    {
        value = std::stoi(s, &idx);
    }
    catch (const std::invalid_argument &)
    {
        // Wrap and rethrow with context
        throw std::invalid_argument("parse_int: not a number: '" + s + "'");
    }
    catch (const std::out_of_range &)
    {
        throw std::out_of_range("parse_int: out of range: '" + s + "'");
    }
    if (idx != s.size())
    {
        throw std::invalid_argument("parse_int: trailing characters in '" + s + "'");
    }
    return value;
}

void demo_rethrow()
{
    try
    {
        parse_int("abc");
    }
    catch (...)
    {
        std::cerr << "demo_rethrow: caught something, rethrowing...\n";
        throw; // preserve original dynamic type
    }
}

int main()
{
    std::cout << "-- Exceptions from functions & rethrow --\n";
    try
    {
        std::cout << "parse_int('123') = " << parse_int("123") << "\n";
        std::cout << "parse_int('123x') = " << parse_int("123x") << "\n"; // throws
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught: " << e.what() << "\n";
    }

    try
    {
        demo_rethrow();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Outer catch after rethrow: " << e.what() << "\n";
    }
}
