#include <iostream>
#include <system_error>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    std::cout << "-- Error codes vs exceptions (filesystem) --\n";

    // Error code style: never throws
    std::error_code ec;
    bool ok = fs::remove("no_such_file.txt", ec);
    std::cout << "remove (error_code) ok=" << ok << ", ec.value=" << ec.value()
              << ", message='" << ec.message() << "'\n";

    // Exception style: throws on errors
    try
    {
        fs::remove("no_such_file.txt");
        std::cout << "remove (exception) succeeded\n";
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "filesystem_error: path='" << e.path1().string() << "' msg='" << e.what() << "'\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "std::exception: " << e.what() << "\n";
    }

    return 0;
}
