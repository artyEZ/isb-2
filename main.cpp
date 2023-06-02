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
        if (i == 0) sum += -1;
        else sum += 1;
    }
    sum /= sqrt(input.size());

    std::cout << "Frequency beat test: " << erfc(sum / sqrt(2));
}

void NIST_2(std::vector<bool> input) {

    double counter = 0;
    for (auto i : input) {
        if (i == 1) counter++;
    }
    counter /= 128;
    if (fabs(counter - 0.5) >= 2 / sqrt(input.size())) std::cout << 0;

    else
    {
        int V_n = 0;
        for (size_t i = 0; i < input.size() - 1; i++) if (input[i] != input[i + 1]) V_n++;
        std::cout << "Test for identical consecutive bits: " << erfc(fabs(V_n - 2 * input.size() * counter * (1 - counter)) / (2 * sqrt(2 * input.size()) * counter * (1 - counter)));
    }
}

void NIST_3(std::vector<bool> input) {
    std::vector<size_t> v = { 0, 0, 0, 0 };

    for (size_t i = 0; i < input.size(); i += 8) {
        size_t count = 0, max = 0;

        for (size_t j = i; j < (i + 8); j++) {
            if (input[j] == 1) {
                count++;
            }
            else {
                if (count > max)max = count;
                count = 0;
            }
        }

        if (count > max)max = count;
        if (max <= 1)v[0] += 1;
        if (max == 2)v[1] += 1;
        if (max == 3)v[2] += 1;
        if (max >= 4)v[3] += 1;
    }
    double pi[4] = { 0.2148, 0.3672, 0.2305, 0.1875 }, Xi = 0;
    for (int i = 0; i < 4; i++) Xi += pow(v[i] - 16 * pi[i], 2) / (16 * pi[i]);
    std::cout << "Test for the longest sequence of units in a block : " << pow(Xi, 2) / 2;
}


int main() {

    std::vector<bool> generated_numbers = generator();

    for (const auto& num : generated_numbers)
    {
        std::cout << num;
    }

    std::cout << std::endl;

    NIST_1(generated_numbers);

    std::cout << std::endl;

    NIST_2(generated_numbers);

    std::cout << std::endl;

    NIST_3(generated_numbers);

    std::cout << std::endl;
}