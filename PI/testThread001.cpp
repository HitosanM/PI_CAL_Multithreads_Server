#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>

double threadnomberOne(int k1k) {
    std::cout << "this is thread number oneone \n" << k1k << "\n" << std::endl;
    k1k = k1k + 50000;
    return k1k;
    }
double threadnomber2(int k2k) {
    std::cout << "this is thread number twotwo\n" << k2k << "\n" << std::endl;
    k2k = k2k + 80000;
    return k2k;
    }

int main() {
    int k,j;
    std::cout << std::thread::hardware_concurrency();
    std::cout << "\nEnter the number of terms (k):";
    std::cin >> k;
    j = k+10;
    double result1, result2;
    std::thread t1(threadnomberOne, k);
    std::thread t2(threadnomber2, j);
    t1.join();
    t2.join();

    std::cout << "number of (k): " << k << std::endl;
    return 0;
}