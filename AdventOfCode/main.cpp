#include <iostream>
#include <fstream>
#include <vector>

int computeProduct2(std::string filename)
{
    int product = 0;
    int needle  = 2020;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return product;
    }
    
    std::vector<int> numbers;
    std::string line;

    while (getline(infile, line))
    {
        numbers.push_back(std::atoi(line.c_str()));
    }

    std::cout << "Numbers: " << numbers.size() << std::endl;

    for (size_t i = 0; i < numbers.size(); ++i)
    {
        for (size_t j = i; j < numbers.size(); ++j)
        {
            if (numbers[i] + numbers[j] == needle)
            {
                std::cout << "a: " << numbers[i] << std::endl;
                std::cout << "b: " << numbers[j] << std::endl;
                std::cout << "product: " << numbers[i] * numbers[j] << std::endl;
            }
        }
    }

    return product;
}

int computeProduct3(std::string filename)
{
    int product = 0;
    int needle  = 2020;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return product;
    }
    
    std::vector<int> numbers;
    std::string line;

    while (getline(infile, line))
    {
        numbers.push_back(std::atoi(line.c_str()));
    }

    std::cout << "Numbers: " << numbers.size() << std::endl;

    for (size_t i = 0; i < numbers.size(); ++i)
    {
        for (size_t j = i; j < numbers.size(); ++j)
        {
            for (size_t k = j; k < numbers.size(); ++k)
            {
                if ((numbers[i] + numbers[j] + numbers[k]) == needle)
                {
                    std::cout << "a: " << numbers[i] << std::endl;
                    std::cout << "b: " << numbers[j] << std::endl;
                    std::cout << "c: " << numbers[k] << std::endl;
                    std::cout << "product: " << numbers[i] * numbers[j] * numbers[k] << std::endl;
                }
            }
        }
    }

    return product;
}

int main()
{
    computeProduct2("../day1.txt");
    computeProduct3("../day1.txt");
    return 0;
}