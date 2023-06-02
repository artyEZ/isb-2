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

void NIST_1(std::vector<bool> input) {
    double sum = 0;
    for (auto i : input)
    {
        if (i == 0) sum_n += -1;
        else sum_n += 1;
    }
    sum /= sqrt(input.size());

    std::cout << "Frequency beat test: " << erfc(sum / sqrt(2));
}

int main() {

    setlocale(LC_ALL, "Russian");
    std::vector<bool> generated_numbers = generator();

    for (const auto& num : generated_numbers)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    NIST_1(generated_numbers);
}