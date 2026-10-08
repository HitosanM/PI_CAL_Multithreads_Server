#include <iostream>
#include <iomanip>
#include <chrono>
#include <limits>
#include <thread>

double sumPositiveTerms(long long terms) {
    double sum = 0.0;

    for (long long n = 1; n <= terms; n += 2) {
        sum += 1.0 / (2 * n - 1);
    }

    return sum;
}

double sumNegativeTerms(long long terms) {
    double sum = 0.0;

    for (long long n = 2; n <= terms; n += 2) {
        sum -= 1.0 / (2 * n - 1);
    }

    return sum;
}

int main() {
    int zeroCount = 0;
    long long terms = 1;

    std::cout << "========================================\n"
              << "        Pi Approximation (Threads)\n"
              << "========================================\n"
              << "Enter the number of zeros (2 = 100 terms): ";

    if (!(std::cin >> zeroCount) || zeroCount < 0) {
        std::cerr << "\nError: please enter a non-negative integer.\n";
        return 1;
    }

    for (int i = 0; i < zeroCount; ++i) {
        if (terms > std::numeric_limits<long long>::max() / 10) {
            std::cerr << "\nError: the number of zeros is too large.\n";
            return 1;
        }
        terms *= 10;
    }

    double positiveSum = 0.0;
    double negativeSum = 0.0;
    long long positiveElapsed = 0;
    long long negativeElapsed = 0;

    const auto startTime = std::chrono::steady_clock::now();

    std::thread positiveThread([&]() {
        const auto threadStart = std::chrono::steady_clock::now();
        positiveSum = sumPositiveTerms(terms);
        const auto threadEnd = std::chrono::steady_clock::now();
        positiveElapsed = std::chrono::duration_cast<std::chrono::microseconds>(
            threadEnd - threadStart
        ).count();
    });

    std::thread negativeThread([&]() {
        const auto threadStart = std::chrono::steady_clock::now();
        negativeSum = sumNegativeTerms(terms);
        const auto threadEnd = std::chrono::steady_clock::now();
        negativeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(
            threadEnd - threadStart
        ).count();
    });

    positiveThread.join();
    negativeThread.join();

    const double pi = 4.0 * (positiveSum + negativeSum);
    const auto endTime = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
        endTime - startTime
    );

    std::cout << std::fixed << std::setprecision(15)
              << "\n----------------------------------------\n"
              << "Calculation results\n"
              << "----------------------------------------\n"
              << std::left << std::setw(24) << "Number of zeros" << ": "
              << zeroCount << '\n'
              << std::setw(24) << "Terms (10^zeros)" << ": " << terms << '\n'
              << std::setw(24) << "Positive sum" << ": " << positiveSum << '\n'
              << std::setw(24) << "Negative sum" << ": " << negativeSum << '\n'
              << std::setw(24) << "Pi approximation" << ": " << pi << '\n'
              << std::setw(24) << "Positive thread time" << ": "
              << positiveElapsed << " microseconds\n"
              << std::setw(24) << "Negative thread time" << ": "
              << negativeElapsed << " microseconds\n"
              << std::setw(24) << "Total execution time" << ": "
              << elapsed.count() << " microseconds\n"
              << "----------------------------------------\n";

    return 0;
}