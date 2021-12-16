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

// if the file is open unsuccessfully
class openFail : public std::exception {
public:
    virtual const char * what() const throw() {
        return "Open file unsuccessfully!";
    }
};
