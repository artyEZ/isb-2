#include <iostream>
#include <vector>
#include <random>

std::vector<bool> generator()
{
    std::vector<bool> number;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned long long> dist(0, 1);

    for (int i = 0; i < 128; i++)
    {
        bool binary_num = dist(mt);
        number.push_back(binary_num);
    }

    return number;
}


int main() {
    setlocale(LC_ALL, "Russian");
    vector<bool> number = generator();

    for (const auto& num : generated_numbers)
    {
        std::cout << num << " ";
    }
}