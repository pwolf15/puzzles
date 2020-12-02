#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

struct PasswordMetadata
{
    std::string password;
    char target;
    std::vector<int> range;
};

PasswordMetadata getMetadata(std::string passwordString)
{
    PasswordMetadata metadata;
    metadata.range.resize(2);

    std::string minStr;
    {
        minStr = passwordString.substr(0, passwordString.find("-"));
    }
    
    std::string maxStr;
    {
        maxStr = passwordString.substr(passwordString.find("-") + 1, passwordString.find(" ") - passwordString.find("-"));
    }

    char c;
    {
        c = passwordString.substr(passwordString.find(":") - 1, 1)[0];
    }

    std::string password;
    {
        password = passwordString.substr(passwordString.find(":") + 1);
    }

    metadata.range[0] = std::atoi(minStr.c_str());
    metadata.range[1] = std::atoi(maxStr.c_str());
    metadata.target = c;
    metadata.password = password;

    std::cout << "Min: " << minStr << std::endl;
    std::cout << "Max: " << maxStr << std::endl;
    std::cout << "Target: " << c << std::endl;
    std::cout << "Password: " << password << std::endl;

    return metadata;
}

bool validatePassword(PasswordMetadata metadata)
{
    int targetCount = std::count(metadata.password.begin(), metadata.password.end(), metadata.target);

    if (targetCount >= metadata.range[0] && targetCount <= metadata.range[1])
    {
        return true;
    }

    return false;
}

bool validatePassword2(PasswordMetadata metadata)
{
    std::vector<int> positions;
    for (size_t i = 0; i < metadata.password.size(); ++i)
    {
        if (metadata.password[i] == metadata.target)
        {
            positions.push_back(i);
        }
    }

    if ((std::find(positions.begin(), positions.end(), metadata.range[0]) != positions.end()) &&
        (std::find(positions.begin(), positions.end(), metadata.range[1]) == positions.end()) ||
        (std::find(positions.begin(), positions.end(), metadata.range[0]) == positions.end()) &&
        (std::find(positions.begin(), positions.end(), metadata.range[1]) != positions.end()))
    {
        return true;
    }

    return false;
}

int numValidPasswords(std::string filename)
{
    int numValid = 0;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return numValid;
    }

    std::vector<std::string> passwordStrings;
    std::string line;

    while (getline(infile, line))
    {
        passwordStrings.push_back(line);
        auto metadata = getMetadata(line);
        if (validatePassword2(metadata)) numValid++;
    }

    std::cout << "Num password strings: " << passwordStrings.size() << std::endl;
    std::cout << "Num valid passwords: " << numValid << std::endl;

    return numValid;
}

int main()
{
    // computeProduct2("../day1.txt");
    // computeProduct3("../day1.txt");
    // numValidPasswords("../day2.txt");

    return 0;
}