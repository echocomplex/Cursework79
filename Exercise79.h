#ifndef EXERCISE_79
#define EXERCISE_79


#include "List.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <map>
#include "Student.h"
#include <ctime>


class Exercise79 {
private:
    List <Student> database;
public:
    Exercise79 () {}
    Exercise79 (const Exercise79& unit);
    Exercise79 (const std::string filename);
    Exercise79& operator= (const Exercise79& unit);
    friend std::ostream& operator<< (std::ostream& os, Exercise79& unit);
    ~Exercise79 () {}
    void toFile (const std::string filename);
    void append (const Student unit);
    void remove (const unsigned int index);
    unsigned int find (const Student unit);
    Student get (const unsigned int index);
    bool isExists (const Student unit);
    List <Student> sortGroup (std::string group);
    void sortList (List <Student>& unit) const;
    static void encrypt (const std::string filenameIn, const std::string filenameOut);
    static void decrypt (const std::string filenameIn, const std::string filenameOut);
};

#endif // EXERCISE_79