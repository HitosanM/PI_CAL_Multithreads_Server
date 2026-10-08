#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

int main() {
    double sum = 0.0;
    double pi = 0.0;
    long long k;

    std::cout << "Enter the number of terms (k): ";
    std::cin >> k;

    std::cout << std::fixed << std::setprecision(15);
    auto t_S = std::chrono::steady_clock::now();

    for (long long n = 1; n <= k; ++n) {
        long long denominator = 2 * n - 1;
        double term = 1.0 / denominator;
// std::cout << n << " " << denominator << " = " << term << std::endl;
        sum += (n % 2 == 0) ? -term : term;
    }
//        if (n > 1) {
//            series += n % 2 == 0 ? " - " : " + ";
//        }
//        series += n == 1 ? "1" : "1/" + std::to_string(denominator);

//        if (n % 2 == 0) {
//            sum -= term;
//        } else {
//            sum += term;
//        }
    
    pi = 4 * sum;

    auto t_E = std::chrono::steady_clock::now();
    std::cout << " pi = " << pi << '\n';
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(t_E - t_S).count() << " microseconds" << '\n';

    return 0;
}