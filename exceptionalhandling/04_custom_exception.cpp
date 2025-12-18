#include <exception>
#include <iostream>
#include <string>

class MyError : public std::exception
{
    std::string msg_;

public:
    explicit MyError(std::string msg) : msg_(std::move(msg)) {}
    const char *what() const noexcept override { return msg_.c_str(); }
};

void risky() { throw MyError("MyError: something went wrong"); }

int main()
{
    std::cout << "-- Custom exception type --\n";
    try
    {
        risky();
    }
    catch (const MyError &e)
    {
        std::cerr << "Caught MyError: " << e.what() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught std::exception: " << e.what() << "\n";
    }
}
