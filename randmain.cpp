#include "randstory.hpp"
#include "exceptions.hpp"
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

int main(int argc, char** argv){
    
    // check whether the argc is valid.
    argumentCheck(argc, 3);

    // open the file.
    std::ifstream word_file;
    std::ifstream fstory;
    try{
        openFile(argv[1], word_file);
        openFile(argv[2], fstory);
        if(!word_file.is_open() || !fstory.is_open()){
            throw openFail();
        }
    }
    catch(openFail & e){
        printError(e.what());
    }

    Story story;
    Words category_word;
    category_word.add(word_file);
    story.tellStory(fstory, category_word);
    story.printStory();



    word_file.close();
    fstory.close();
    return EXIT_SUCCESS;
}
