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

bool checkPos(std::string slope, int& curPos, int& row)
{
    if (curPos >= slope.size())
    {
        curPos = curPos % slope.size();
    }

    bool isTree = slope[curPos] == '#';
    curPos += 3;
    row++;
    return isTree;
}

int countTrees(std::vector<std::string> slopes, int curXPos, int curYPos, int slopeX, int slopeY)
{
    int numTrees = 0;

    while (curYPos < slopes.size())
    {
        if (curXPos >= slopes[0].size())
        {
            curXPos = curXPos % slopes[0].size();
        }

        if (slopes[curYPos][curXPos] == '#') numTrees++;

        curXPos += slopeX;
        curYPos += slopeY;
    }

    std::cout << "Num trees: " << numTrees << std::endl;

    return numTrees;
}

int countTrees(std::string filename)
{
    int numTrees = 0;
    std::vector<std::string> slopes;
    std::string line;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return numTrees;
    }

    int curPos = 0;
    int row = 0;
    while (getline(infile, line))
    {
        slopes.push_back(line);
    }

    long long product = 1;
    product *= countTrees(slopes, 0, 0, 3, 1);
    product *= countTrees(slopes, 0, 0, 1, 1);
    product *= countTrees(slopes, 0, 0, 5, 1);
    product *= countTrees(slopes, 0, 0, 7, 1);
    product *= countTrees(slopes, 0, 0, 1, 2);

    std::cout << "Num trees: " << product << std::endl;
    return numTrees;
}

struct Passport
{
    std::vector<std::string> lines;
};

#include <unordered_map>

bool validateField(std::string field, std::string value, std::string units = "")
{
    bool valid = true;
    if (field == "byr")
    {
        int valueInt = std::stoi(value);
        if (valueInt >= 1920 && valueInt <= 2002)
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
        
    }
    else if (field == "iyr")
    {
        int valueInt = std::stoi(value);
        if (valueInt >= 2010 && valueInt <= 2020)
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else if (field == "eyr")
    {
        int valueInt = std::stoi(value);
        if (valueInt >= 2020 && valueInt <= 2030)
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else if (field == "hgt")
    {
        int valueInt = std::stoi(value);
        if (units == "cm" && (valueInt >= 150 && valueInt <= 193))
        {
            valid = true;
        }
        else if (units == "in" && (valueInt >= 59 && valueInt <= 76))
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else if (field == "hcl")
    {
        for (int i = 0; i < 6; i++)
        {
            if (isdigit(value[i]) || value[i] == 'a' || value[i] == 'b' ||
                value[i] == 'c' || value[i] == 'd' || value[i] == 'e' ||
                value[i] == 'f')
            {
                valid = true;
            }
            else
            {
                valid = false;
                break;
            }
        }
    }
    else if (field == "ecl")
    {
        if (value == "amb" || value == "blu" || value == "brn" ||
            value == "gry" || value == "grn" || value == "hzl" || value == "oth")
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else if (field == "pid")
    {
        for (int i = 0; i < 9; i++)
        {
            if (!isdigit(value[i]))
            {
                valid = false;
            }
        }
    }

    return valid;
}

bool isValidPassport(Passport passport)
{
    std::unordered_map<std::string, int> fields;
    fields["byr"] = 0;
    fields["iyr"] = 0;
    fields["eyr"] = 0;
    fields["hgt"] = 0;
    fields["hcl"] = 0;
    fields["ecl"] = 0;
    fields["pid"] = 0;

    std::string passportString = "";
    for (auto line: passport.lines)
    {
        passportString += line;
        passportString += " ";
    }

    // std::cout << passportString << std::endl;
    for (auto& field: fields)
    {
        if (passportString.find(field.first) == std::string::npos)
        {
            return false;
        }
        else
        {
            std::string passportField = field.first;
            std::string value = "";
            std::string units = "";
            // std::cout << "idx: " <<  << std::endl;
            int startIdx = passportString.find(field.first);
            int fieldLen = field.first.size() + 1;
            int valLength = 4;

            int valueLen = 0;
            
            if (passportField == "byr" || passportField == "eyr" || passportField == "iyr")
            {
                value = passportString.substr(passportString.find(field.first) + 4, 4);
            }
            else if (passportField == "hgt")
            {
                int startIdx = passportString.find(field.first) + 4;
                if ((startIdx + 3) >= passportString.size()) { return false; }

                int endIdx = passportString[startIdx + 3] == 'c' ? 3 : 2;
                value = passportString.substr(startIdx, endIdx);

                units = passportString.substr(startIdx + endIdx, 2);
            }
            else if (passportField == "hcl")
            {
                value = passportString.substr(passportString.find(field.first) + 5, 6);
            }
            else if (passportField == "ecl")
            {
                value = passportString.substr(passportString.find(field.first) + 4, 3);
            }
            else if (passportField =="pid")
            {
                value = passportString.substr(passportString.find(field.first) + 4, 9);
                if (passportString[passportString.find(field.first) + 4 + 9] != ' ') { return false; }
            }

            if (!validateField(passportField, value, units)) { return false; }
    
            field.second++;
        }
    }

    for (auto field: fields)
    {
        if (field.second > 1) return false;
    }

    return true;
}

int countValidPassports(std::string filename)
{
    int numPassports = 0;
    std::string line;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return numPassports;
    }

    bool isPassport = false;
    int blankLines = 0;
    std::vector<Passport> passports;
    std::vector<std::string> lines;

    while (getline(infile, line))
    {
        if (line == "") 
        {
            Passport passport;
            std::copy(lines.begin(), lines.end(), std::back_inserter(passport.lines));
            passports.push_back(passport);
            lines.clear();
            blankLines++;
            continue;
        }

        lines.push_back(line);
    }

    Passport passport;
    std::copy(lines.begin(), lines.end(), std::back_inserter(passport.lines));
    passports.push_back(passport);
    lines.clear();
    blankLines++;

    int i = 0;
    for (auto passport: passports)
    {
        if (isValidPassport(passport)) {
            numPassports++;
        }

        i++;
    }

    std::cout << "Number of passports: " << numPassports << std::endl;

    return numPassports;
}

int getSeatId(std::string seat)
{
    int id = 0;
    int row = 0;
    int col = 0;
    int numRows = 7;
    int numCols = 3;
    for (int i = 0; i < seat.size(); i++)
    {
        if (numRows)
        {
            int mult = seat[i] == 'B' ? 1 : 0;
            row += mult << --numRows;
        }
        else if (numCols)
        {
            int mult = seat[i] == 'R' ? 1 : 0;
            col += mult << --numCols;
        }
    }

    id = row * 8 + col;
    std::cout << "row: " << row << ", " << "col: " << col << ", " << "seat: " << seat << ", " << "ID: " << id << std::endl;

    return id;
}

int getHighestSeatId(std::string filename)
{
    int highestId = 0;
    std::string line;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return highestId;
    }

    std::vector<int> seatIds;
    std::vector<std::string> lines;

    while (getline(infile, line))
    {
        lines.push_back(line);
        seatIds.push_back(getSeatId(line));
    }


    std::sort(seatIds.begin(), seatIds.end());

    if (seatIds.size())
    {
        highestId = seatIds[seatIds.size() - 1];
    }

    int counter = 0;
    for (int i = 8; i < highestId; i++)
    {
        auto seat = seatIds[counter++];
        std::cout << "seat id: " << seat << ", i " << i << std::endl;
        if (seat != i)
        {
            std::cout << "Not equal: " << seat << "!= " << i << std::endl;
        }

    }
    std::cout << "Highest seat id: " << highestId << std::endl;

    return highestId;
}

#include <unordered_map>

int getGroupCount(std::string group, int numMembers)
{
    int groupCount = 0;
    std::cout << group << std::endl;
    std::unordered_map<char, int> groups;
    for (auto c: group)
    {
        if (groups.find(c) == groups.end())
        {
            groups[c] = 1;
        }
        else
        {
            groups[c]++;
        }  
    }

    for (auto group: groups)
    {
        if (group.second == numMembers)
        {
            groupCount++;
        }
    }

    return groupCount;
}

int getCustomCount(std::string filename)
{
    int customCount = 0;
    std::string line;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return customCount;
    }

    std::vector<std::string> lines;
    int numGroups = 0;
    int totalGroupCount = 0;

    while (getline(infile, line))
    {
        lines.push_back(line);

        if (line == "") 
        {
            std::string currentGroup;
            for (auto line: lines)
            {
                currentGroup += line;
            }
            int groupCount = getGroupCount(currentGroup, lines.size() - 1);
            std::cout << "Num members: " << lines.size() << std::endl;
            std::cout << "groupCount: " << groupCount << std::endl;
            totalGroupCount += groupCount;
            numGroups++;
            lines.clear();
            continue;
        }
    }

    // last group
    std::string currentGroup;
    for (auto line: lines)
    {
        currentGroup += line;
    }
    int groupCount = getGroupCount(currentGroup, lines.size());
    std::cout << "groupCount: " << groupCount << std::endl;
    totalGroupCount += groupCount;
    numGroups++;
    lines.clear();

    std::cout << "Total groupCount: " << totalGroupCount << std::endl;

    std::cout << "Num groups: " << numGroups << std::endl;

    return customCount;
}

int main()
{
    // computeProduct2("../day1.txt");
    // computeProduct3("../day1.txt");
    // numValidPasswords("../day2.txt");
    // countTrees("../day3.txt");
    // countValidPassports("../day4.txt");
    // getHighestSeatId("../day5.txt");
    getCustomCount("../day6.txt");

    return 0;
}