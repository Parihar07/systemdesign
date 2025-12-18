#include <iostream>
#include <exception>
using namespace std;

int divide(int a, int b)
{
    if (b == 0)
    {
        throw invalid_argument("division by zero");
    }
    return a / b;
}

int main()
{
    cout << "-- Basic try/catch/throw --\n";
    try
    {
        cout << "10 / 2 = " << divide(10, 2) << "\n";
        cout << "10 / 0 = " << divide(10, 0) << "\n"; // throws
        cout << "This line won't execute after throw\n";
    }
    catch (const invalid_argument &e)
    {
        cerr << "Caught invalid_argument: " << e.what() << "\n";
    }
    catch (const exception &e)
    { // more general
        cerr << "Caught exception: " << e.what() << "\n";
    }
    catch (...)
    { // catch-all, always last
        cerr << "Caught unknown exception\n";
    }

    // Demonstrate catch-all
    try
    {
        throw 42; // non-exception type
    }
    catch (const exception &e)
    {
        cerr << "Will not catch int: " << e.what() << "\n";
    }
    catch (...)
    {
        cerr << "Caught non-exception type with catch-all (...)\n";
    }

    cout << "Program continues after handling exceptions.\n";
    return 0;
}
