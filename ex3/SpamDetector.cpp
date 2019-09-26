#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include "HashMap.hpp"

using std::string;

/**
 * checks if a given string is an integer
 * @param numStr the string that we want to check
 * @return true if it was a string, false otherwise.
 */
bool checkIfNumber(const string &numStr)
{
    for (const auto &i : numStr)
    {
        if (i - '0' > 9 || i - '0' < 0)
        {
            return false;
        }
    }
    return true;
}


void removeNewLines(std::string &line)
{
    std::string token1 = "\r";
    std::string token2 = "\n";
    std::string token3 = "\r\n";
    line = line.substr(0, line.find(token1));
    line = line.substr(0, line.find(token2));
}

/**
 * checks if the file is legal
 * @param fileName the name of the file
 * @return true if the file is legal, false if it is not.
 */
bool checkFile(const string &fileName)
{
    string line;
    std::ifstream myFile(fileName);
    if (myFile.good())
    {
        while (getline(myFile, line))
        {
            if (line[0] == ' ')
            {
                myFile.close();

                return false;
            }
            removeNewLines(line);
            size_t first = line.find(',');
            if (first == string::npos)
            {
                myFile.close();
                return false;
            }
            size_t second = line.find(',', first + 1);
            if (second != string::npos)
            {
                myFile.close();
                return false;
            }
            string number = line.substr(first + 1, line.size() - 1);
            if (!checkIfNumber(number))
            {
                myFile.close();
                return false;
            }
            if (first == 0 || first == line.size() - 1)
            {
                return false;
            }
        }
        myFile.close();
        return true;
    }
    return false;
}

/**
 * reads the csv and adds the words and their values in a hashmap
 * @param fileMap the map we want to add to
 * @param fileName the name of the csv file
 * @return true if the words were successfully added, false otherwise
 */
void addToHashmap(HashMap<string, int> &fileMap, const string &fileName)
{
    if (checkFile(fileName))
    {
        string line;
        std::ifstream myFile(fileName);

        while (getline(myFile, line))
        {
            removeNewLines(line);
            size_t indexOfComma = line.find(',');
            string word = line.substr(0, indexOfComma);
            for (char &i : word)
            {
                i = (char) (tolower(i));
            }
            string number = line.substr(indexOfComma + 1, line.size() - 1);
            fileMap.insert(word, std::stoi(number));
        };
        return;
    }
    throw std::invalid_argument("Invalid input");

}

/**
 * adds the whole content of the file to a string
 * @param fileName the name of the file
 * @return a string that has all the contents of the file
 */
string readTextFile(const string &fileName)
{
    string line;
    string fileText;
    std::ifstream myFile(fileName);
    if (myFile.good())
    {
        while (getline(myFile, line))
        {
            removeNewLines(line);
            fileText += (line + " ");
        }
        for (char &i : fileText)
        {
            i = (char) (tolower(i));
        }
        return fileText;
    }
    throw std::invalid_argument("Invalid input");
}

/**
 * calculates the score of a given string based on the values of each spam word.
 * @param csvMap a map containing the contents of the csv file
 * @param fileText the text that we want to search in.
 * @return the score for that text.
 */
int calculateScore(const HashMap<string, int> &csvMap, const string &fileText)
{
    int score = 0;
    for (const auto &pair:csvMap)
    {
        size_t indexOfString = fileText.find(pair.first);
        while (indexOfString != string::npos)
        {
            score += pair.second;
            indexOfString = fileText.find(pair.first, indexOfString + 1);
        }
    }
    return score;

}

/**
 * the main function, runs the whole program
 * @param argc the number of arguments
 * @param argv the program arguments
 * @return EXIT_SUCCESS if everything was okay, EXIT_FAILURE if there is something wrong
 */
int main(int argc, char *argv[])
{
    const string PARAMETER_ERROR =
            "Usage: SpamDetector <database path> <message path> <threshold>";
    if (argc != 4)
    {
        std::cerr << PARAMETER_ERROR << std::endl;
        return EXIT_FAILURE;
    }
    string textString;
    HashMap<string, int> inputMap;
    try
    {
        if (!checkIfNumber(argv[3]))
        {
            throw std::invalid_argument("Invalid input");
        }
        if (std::stoi(argv[3]) <= 0)
        {
            throw std::invalid_argument("Invalid input");
        }
        addToHashmap(inputMap, argv[1]);
        textString = readTextFile(argv[2]);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    int threshold = std::stoi(argv[3]);
    int score = calculateScore(inputMap, textString);
    std::cout << (score >= threshold ? "SPAM" : "NOT_SPAM") << std::endl;
    return EXIT_SUCCESS;

}
