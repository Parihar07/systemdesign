#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

/*
 * Constraints: SFINAE vs Concepts
 *
 * Goal: Show how to constrain templates to accept only specific types.
 * This file demonstrates SFINAE (C++17, compilable) and documents
 * C++20 concepts approach as comments for learning.
 */

// -------- SFINAE (C++17 style) --------
// Uses enable_if and void_t to constrain templates

// void_t is available in C++17, but for C++14 compatibility:
#if __cplusplus < 201703L
namespace std
{
    template <typename...>
    using void_t = void;
}
#endif

template <typename, typename = void>
struct is_iterable : std::false_type
{
};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
                                  decltype(std::declval<T>().end()),
                                  typename T::value_type>> : std::true_type
{
};

template <typename T>
using value_type_t = typename T::value_type;

template <typename T>
typename std::enable_if<is_iterable<T>::value && std::is_arithmetic<value_type_t<T>>::value, void>::type
print_iterable_sfinae(const T &rng)
{
    std::cout << "[SFINAE] size=" << rng.size() << " values:";
    for (const auto &v : rng)
        std::cout << ' ' << v;
    std::cout << '\n';
}
/*
 * -------- C++20 Concepts (Theory) --------
 * Concepts provide cleaner syntax and better error messages.
 *
 * Example (not compiled, requires C++20):
 *
 * template <typename T>
 * concept Iterable = requires(T t) {
 *     { t.begin() } -> std::input_or_output_iterator;
 *     { t.end() } -> std::input_or_output_iterator;
 * };
 *
 * template <typename T>
 * concept ArithmeticRange = Iterable<T> &&
 *                           std::is_arithmetic_v<typename T::value_type>;
 *
 * template <ArithmeticRange T>
 * void print_iterable_concept(const T &rng) {
 *     std::cout << "[concept] size=" << rng.size() << " values:";
 *     for (const auto &v : rng) std::cout << ' ' << v;
 *     std::cout << '\n';
 * }
 */

// -------- Addable example: SFINAE vs concepts --------

template <typename T, typename U>
using add_result_t = decltype(std::declval<T>() + std::declval<U>());

template <typename, typename, typename = void>
struct is_addable : std::false_type
{
};

template <typename T, typename U>
struct is_addable<T, U, std::void_t<add_result_t<T, U>>> : std::true_type
{
};

// enable_if using detection
template <typename T, typename U,
          typename std::enable_if<is_addable<T, U>::value, int>::type = 0>
auto add_sfinae(T a, U b)
{
    return a + b;
}

/*
 * Addable concept (C++20, theory only):
 *
 * template <typename T, typename U>
 * concept Addable = requires(T a, U b) { a + b; };
 *
 * template <typename T, typename U>
 * requires Addable<T, U>
 * auto add_concept(T a, U b) {
 *     return a + b;
 * }
 */

int main()
{
    std::cout << "=== SFINAE Template Constraints (C++17) ===\n\n";

    std::vector<int> vi{1, 2, 3};
    print_iterable_sfinae(vi);

    std::vector<std::string> vs{"a", "b"};
    // print_iterable_sfinae(vs);  // Error: value_type not arithmetic

    std::cout << "\nadd_sfinae(2, 3) -> " << add_sfinae(2, 3) << '\n';
    std::cout << "add_sfinae(2.5, 1) -> " << add_sfinae(2.5, 1) << '\n';

    // Try uncommenting to see SFINAE error:
    // struct X {}; X x; add_sfinae(x, x);

    std::cout << "\nNote: C++20 concepts version documented in comments above.\n";

    return 0;
}
