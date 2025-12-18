#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Simulate an operation that can throw
struct MaybeThrow
{
    bool should_throw;
    explicit MaybeThrow(bool t) : should_throw(t) {}
    void operator()() const
    {
        if (should_throw)
            throw std::runtime_error("simulated failure");
    }
};

// A container with two add methods illustrating guarantees
struct StringBag
{
    std::vector<std::string> data;

    // Basic guarantee: state remains valid but may be modified
    void add_basic(const std::string &s, const MaybeThrow &op)
    {
        data.push_back(s); // mutate first
        op();              // may throw; data already mutated
        // continue work...
    }

    // Strong guarantee: commit only after all operations succeed
    void add_strong(const std::string &s, const MaybeThrow &op)
    {
        auto snapshot = data;  // copy current state
        snapshot.push_back(s); // mutate snapshot
        op();                  // may throw; original data unchanged
        data.swap(snapshot);   // commit
    }
};

int main()
{
    std::cout << "-- Exception safety: basic vs strong --\n";
    StringBag bag;

    try
    {
        bag.add_basic("alpha", MaybeThrow(true));
    }
    catch (const std::exception &e)
    {
        std::cerr << "add_basic failed: " << e.what() << "\n";
    }
    std::cout << "Size after add_basic failure: " << bag.data.size() << " (modified)\n";

    try
    {
        bag.add_strong("beta", MaybeThrow(true));
    }
    catch (const std::exception &e)
    {
        std::cerr << "add_strong failed: " << e.what() << "\n";
    }
    std::cout << "Size after add_strong failure: " << bag.data.size() << " (unchanged)\n";

    // Success path
    bag.add_strong("gamma", MaybeThrow(false));
    std::cout << "Final contents:";
    for (const auto &s : bag.data)
        std::cout << ' ' << s;
    std::cout << "\n";
}
