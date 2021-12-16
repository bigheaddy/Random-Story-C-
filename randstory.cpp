#include "randstory.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <time.h>
#include <iostream>
#include <sstream>


/**
 * @brief check the command arguments
 * 
 * @param argc the number of command argument
 * @param want_argc the number of argc you want
 */
void argumentCheck(int argc, int want_argc){
    if(argc != want_argc){
        printError("Wrong number of input arguments");
    }
}

/**
 * @brief open the file
 * 
 * @param name  file name
 * @param f  stream
 */
void openFile(char * name, std::ifstream &f){
    f.open(name);
}

/**
 * @brief  Check if the string is composed of pure letters
 * 
 * @param s  String to be checked
 * @return true  the String is consist of pure letter(s)
 * @return false  the string isn't consist of pure letter(s)
 */
bool Words::isAlpha(std::string &s){
    for(size_t i = 0;i < s.size(); i++){
        if(isalpha(s[i]) == false){
            return false;
        }
    }
    return true;
}

/**
 * @brief   put the category name and word from words.txt
 * 
 * @param stream  the content of words.txt
 */
void Words::add(std::istream & stream){
    size_t ind=0;
    int count=0;
    while(!stream.eof()){
        std::string line;
        std::string name;
        std::string word;
        getline(stream,line);
        if(stream.eof()){
            break;
        }
        count++;
        ind=line.find(':');
        if(ind==line.npos){
            std::cerr<<count<<": "<<"Invalid format!"<<std::endl;
            continue;
        }
        name=line.substr(0,ind);
        word=line.substr(ind+1);
        if(name.empty()){
            std::cerr<<count<<": "<<"Warning : empty name(word)!"<<std::endl;
            continue;
        }
        if(!isAlpha(name)){
            std::cerr<<count<<": "<<"Warning : The format of "<<name<<" is wrong!"<<std::endl;
            continue;
        }
        std::map<std::string,std::vector<std::string> > :: iterator iter;
        iter=words.find(name);
        if(iter!=words.end()){
            iter->second.push_back(word);
        }
        else{
            std::vector<std::string> wl;
            wl.push_back(word);
            words.insert(std::pair<std::string,std::vector<std::string> >(name,wl));
        }
    }
    if(count==0){
        printError("The file is empty!");
    }
}


/**
 * @brief   Enter name and whoever plays the corresponding word randomly
 * 
 * @param name  category name
 * @return std::string  the word corresponding to the category
 */
std::string Words::chooseWords(const std::string &name){
    srand( (unsigned)time( NULL ) );
    std::vector<std::string> ans;
    size_t index;
    std::map<std::string,std::vector<std::string> > ::iterator iter;
    iter=words.find(name);
    if(iter==words.end()){
        printError("Cannot find the category name!");

    }
    else{
        ans = iter->second;
    }
    if(ans.size()>1){
        index=rand()%ans.size();
        return ans[index];
    }
    else{
        return ans[0];
    }
}

/**
 * @brief  Find the end index of the valid content.
 * 
 * @param content  the string after the first underscore
 * @return int   the ending index or an error signal (-1)
 */
int Story::findWordEnding(std::string content){
    int str_len = content.length();
    
    if(str_len != 0){
        int i = 0;
        if(isdigit(content[i])){
            while(isdigit(content[i]) && i < str_len){
                ++i;
            }
            return i;
        }
        else if(isalpha(content[i])){
            while(isalpha(content[i]) && i < str_len){
                ++i;
            }
            return i;
        }
    }
    return -1;
}


/**
 * @brief check whether the string is valid integer
 * 
 * @param content  the string to be checked
 * @return size_t  if valid, returnthe corresponding int. otherwise, returns 0.
 */
size_t Story::isValidInt(std::string content){
    if(content.length() == 0 || cache.size() == 0){
        return 0;
    }
    size_t content_len = content.length();
    for(size_t i = 0; i < content_len; i++){
        if(!isdigit(content[i])){
            return 0;
        }
    }
    size_t number = atoi(content.c_str());
    return (number >=1 && number <= cache.size())? number : 0;
}


/**
 * @brief  get history word.
 * 
 * @param number  the previous N (blanks)
 * @return std::string  the word used in the previous Nth blank
 */
std::string Story::getHistory(int number){
    size_t index = cache.size() - number;
    std::string word = cache[index];
    return word;
}

/**
 * @brief tell random story 
 * 
 * @param story  the story template
 * @param rhs  the class of Words(store category name & words)
 */
void Story::tellStory(std::istream & story, Words &rhs){
    int emptyfile = 1;
    while(!story.eof()){
        emptyfile = 0;
        std::string line;
        std::string word;
        size_t ind1 = 0;
        int ind2 = -1;
        getline(story,line);
        std::string sentence = "";
        size_t scan_index = 0;
        while(1){
            ind1=line.find("_", scan_index);
            if(ind1==line.npos){ // if there isn't any '_'
                sentence = sentence + line.substr(scan_index);
                sentences.push_back(sentence);
                break;
            }
            else{
                sentence = sentence + line.substr(scan_index, ind1 - scan_index); // Save everything before the first '_'
            }
            int ind2_label = Story::findWordEnding(line.substr(ind1 + 1)); // if find the font '_', find the close '_'
            if(ind2_label == -1) { // find a unmatching underscore
                printError("Wrong format of story! There is no valid content after the underscore.");
            }
            else{
                ind2 = ind1 + 1 + ind2_label;
                scan_index = ind2;
                std::string name=line.substr(ind1+1,ind2-ind1-1); // take content within underscores
                int number = isValidInt(name);
                if(number != 0){
                    word = getHistory(number);
                }
                else{
                    word=rhs.chooseWords(name);
                }
                cache.push_back(word);
                sentence = sentence + word;
            }
        }
    }
    // if it's an empty file.
    if(emptyfile == 1){
        printError("It's an empty story template, illegal input!");
    }
}

/**
 * @brief  print the whole story
 * 
 */
void Story::printStory(){
    for(size_t i=0;i < sentences.size(); i++){
        std::cout << sentences[i];
        if(i != sentences.size() - 1){
            std::cout<< std::endl;
        }
    }
}

/**
 * @brief  print the error information
 * 
 * @param word  the error information
 */
void printError(std::string word){
    std::cerr << word << std::endl;
    exit(EXIT_FAILURE);
}