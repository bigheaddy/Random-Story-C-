#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>


class Words{
private:
    std::map<std::string,std::vector<std::string> > words;
public:
    bool isAlpha(std::string &s); // Check if the string is composed of pure letters
    void add(std::istream & stream); // put the category name and word from words.txt
    std::string chooseWords(const std::string &name); // Enter name and whoever plays the corresponding word randomly
};

class Story{
private:
    std::vector<std::string> sentences;
    std::vector<std::string> cache; // store historic word(s).
    
public:
    Story() : sentences(0), cache(0) {}
    ~Story(){}
    
    // Find the end index of the valid content.
    // Pass the string after the first underscore, returning the ending index or an error signal (-1)
    int findWordEnding(std::string content);

    // If the string is a valid integer ( >= 1 or & <= the total number of recoding container), 
    // returns the corresponding int. otherwise, returns 0.
    size_t isValidInt(std::string content);

    // get history word.
    std::string getHistory(int number);

    // random story teller
    void tellStory(std::istream & story, Words &rhs);

    // print the whole story
    void printStory();
};

// print the error information
void printError(std::string word);
// check the command arguments
void argumentCheck(int argc, int want_argc);
// open the file
void openFile(char * name, std::ifstream &f);