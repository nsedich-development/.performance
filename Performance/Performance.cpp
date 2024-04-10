// Performance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
    double sum = 0;
    double sum2 = 0;
    double sum3 = 0;
       
    for (double i = 0; i < 1500000000; i++) {
        sum += i;
        for (int k = 0; k < 5; k++) {
            sum2 += k;
            for (int n = 0; n < k; n++) {
                sum3 += n;
            }
        }
    }

    std::cout << sum << " " << sum2 << " " << sum3 << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start) / 1000000;
    std::cout << duration.count();
    system("pause");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
