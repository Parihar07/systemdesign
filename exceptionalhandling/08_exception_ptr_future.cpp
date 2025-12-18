#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

int background()
{
    throw std::runtime_error("background task failed");
}

void capture_exception(std::exception_ptr &eptr)
{
    try
    {
        throw std::logic_error("captured logic error");
    }
    catch (...)
    {
        eptr = std::current_exception();
    }
}

int main()
{
    std::cout << "-- Exceptions with std::async and exception_ptr --\n";

    // std::async propagates exception to future::get
    auto fut = std::async(std::launch::async, background);
    try
    {
        fut.get();
    }
    catch (const std::exception &e)
    {
        std::cerr << "async caught: " << e.what() << "\n";
    }

    // exception_ptr manual capture and rethrow
    std::exception_ptr eptr;
    capture_exception(eptr);
    try
    {
        if (eptr)
            std::rethrow_exception(eptr);
    }
    catch (const std::exception &e)
    {
        std::cerr << "rethrow_exception caught: " << e.what() << "\n";
    }
}
