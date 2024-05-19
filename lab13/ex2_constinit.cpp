
#include <array>
#include <iostream>
#include <cmath>


/**
 * Exercise 2a:
 * Implement function power that computes x^n
 * during compilation using recurrent formula
   x^2n = (x^n)^2
   x^2n+1 = (x^2n)*x
  */
consteval auto power(auto x, int n) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return x;
    } else if (n % 2 == 0) {
        auto halfPower = power(x, n / 2);
        return halfPower * halfPower;
    } else {
        auto halfPower = power(x, n / 2);
        return halfPower * halfPower * x;
    }
}

constinit double fiveToPowerFour = power(5, 4);

/**
 *  Exercise 2b:
 * Implement function generate_triangle that during compilation
 * generates the Pascal trriangle of the given size N.
 * Pascal triangle
 * https://en.wikipedia.org/wiki/Pascal%27s_triangle
 *
 */


template <size_t N>
struct PascalTriangle {
    std::array<std::array<int, N>, N> triangle;

    constexpr PascalTriangle() : triangle(generate()) {}

    constexpr int operator()(size_t n, size_t m) const {
        return triangle[n][m];
    }

private:
    static constexpr std::array<std::array<int, N>, N> generate() {
        std::array<std::array<int, N>, N> triangle{};
        for (size_t i = 0; i < N; ++i) {
            triangle[i][0] = triangle[i][i] = 1;
            for (size_t j = 1; j < i; ++j) {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
        return triangle;
    }
};

template <size_t N>
constexpr PascalTriangle<N> generatePascalTriangle() {
    return PascalTriangle<N>();
}


constexpr size_t n = 10;
constexpr auto triangle = generatePascalTriangle<n>();




int main(){

    static_assert(triangle(0,0) == 1);
    static_assert(triangle(5,3) == 10);
    static_assert(triangle(9,4) == 126);

}