#include "Exercise79.h"

Exercise79::Exercise79 (const Exercise79& unit) {
    this->database = unit.database;
}

Exercise79::Exercise79 (const std::string filename) {
    std::ifstream file (filename, std::ios::in);
    if (file.is_open()) {
        std::string row;
        while (std::getline(file, row)) {
            std::istringstream iss(row);
            std::string word;
            Student unit;
            int count = 0;
            grade g;
            while (iss >> word) {
                if (count == 0) { unit.setNumber(word); }
                else if (count == 1) { unit.setFirstName(word); }
                else if (count == 2) { unit.setMiddleName(word); }
                else if (count == 3) { unit.setLastName(word); }
                else if (count == 4) { unit.setYear(std::stoi(word)); }
                else if (count == 5) { unit.setBirthday(word); }
                else if (count == 6) { unit.setFaculty(word); }
                else if (count == 7) { unit.setDepartment(word); }
                else if (count == 8) { unit.setGroup(word); }
                else if (count == 9) { unit.setGender(word); }
                else if (count == 10) { g.subject = word; }
                else if (count == 11) { g.date = word; }
                else if (count == 12) { g.mark = std::stoi(word); }
                ++count;
            }
            if (this->database.isExists(unit)) {
                this->database[this->database.find(unit)].appendGrade(g);
            }
            else {
                unit.appendGrade(g);
                this->database.append(unit);
            }
        }
    }
    else {
        throw std::runtime_error("File does not exist");
    }
    file.close();
}

Exercise79& Exercise79::operator= (const Exercise79& unit) {
    this->database = unit.database;
    return *this;
}

std::ostream& operator<< (std::ostream& os, Exercise79& unit) {
    std::string toOut;
    for (int i = 0; i < unit.database.length(); ++i) {
        List <grade> grades = unit.database[i].getGrades();
        for (int b = 0; b < grades.length(); ++b) {
            std::string row = 
                unit.database[i].getNumber() + " " + 
                unit.database[i].getFirstName() + " " + 
                unit.database[i].getMiddleName() + " " + 
                unit.database[i].getLastName() + " " + 
                std::to_string(unit.database[i].getYear()) + " " + 
                unit.database[i].getBirthday() + " " + 
                unit.database[i].getFaculty() + " " + 
                unit.database[i].getDepartment() + " " + 
                unit.database[i].getGroup() + " " + 
                unit.database[i].getGender() + " " + 
                grades[b].subject + " " + 
                grades[b].date + " " + 
                std::to_string(grades[b].mark) + "\n";
            toOut += row;
        }
    }
    os << toOut;
    return os;
}

void Exercise79::toFile (const std::string filename) {
    std::string toOut;
    for (int i = 0; i < this->database.length(); ++i) {
        List <grade> grades = this->database[i].getGrades();
        for (int j = 0; j < grades.length(); ++j) {
            std::string row = 
                this->database[i].getNumber() + " " + 
                this->database[i].getFirstName() + " " + 
                this->database[i].getMiddleName() + " " + 
                this->database[i].getLastName() + " " + 
                std::to_string(this->database[i].getYear()) + " " + 
                this->database[i].getBirthday() + " " + 
                this->database[i].getFaculty() + " " + 
                this->database[i].getDepartment() + " " + 
                this->database[i].getGroup() + " " + 
                this->database[i].getGender() + " " + 
                grades[j].subject + " " + 
                grades[j].date + " " + 
                std::to_string(grades[j].mark) + "\n";
            toOut += row;
        }
    }
    std::ofstream file(filename.c_str(), std::ios::trunc);
    file << toOut;
    file.close();
}

void Exercise79::append (const Student unit) {
    this->database.append(unit);
}

void Exercise79::remove (const unsigned int index) {
    this->database.remove(index);
} 

unsigned int Exercise79::find (const Student unit) {
    return this->database.find(unit);
}

bool Exercise79::isExists (const Student unit) {
    return this->database.isExists(unit);
}

Student Exercise79::get (const unsigned int index) {
    return this->database[index];
}

List <Student> Exercise79::sortGroup (std::string group) {
    List <Student> result;
    for (int i = 0; i < this->database.length(); ++i) {
        if (this->database[i].getGroup() == group) {
            result.append(this->database[i]);
        }
    }
    this->sortList(result);
    return result;
}

void Exercise79::sortList (List <Student>& unit) const {
    for (int i = 0; i < unit.length() - 1; ++i) {
        for (int j = 0; j < unit.length() - i - 1; ++j) {
            if (unit[j].getYear() > unit[j + 1].getYear()) {
                Student temp = unit[j];
                unit[j] = unit[j + 1];
                unit[j + 1] = temp;
            }
        }
    }
}

void Exercise79::encrypt (const std::string filenameIn, const std::string filenameOut) {
    std::string key;
    char alphabet[63] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890";
    srand(time(NULL));
    for (int i = 0; i < 16; ++i) {
        key += alphabet[rand() % 62];
    }
    std::ofstream file("key.txt", std::ios::trunc);
    file << key;
    file.close();
    std::string commandAES = "openssl aes-128-cbc -salt -in " + filenameIn + " -out " + filenameOut + " -pass pass:" + key;
    std::system(commandAES.c_str());
    if (std::remove(filenameIn.c_str()) != 0) {
        std::cerr << "CANNOT DELETE >>> " + filenameIn << std::endl;
    }
    std::string commandRSA = "openssl rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
    std::system(commandRSA.c_str());
    if (std::remove("key.txt") != 0) {
        std::cerr << "CANNOT DELETE >>> key.txt" << std::endl;
    }
}

void Exercise79::decrypt (std::string filenameIn, std::string filenameOut) {
    std::string commandRSA = "openssl rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
    std::system(commandRSA.c_str());
    std::string key;
    std::ifstream file("key.txt", std::ios::in);
    file >> key;
    file.close();
    if (std::remove("key.txt.enc") != 0) {
        std::cerr << "CANNOT DELETE >>> key.txt.enc" << std::endl;
    }
    std::string commandAES = "openssl aes-128-cbc -d -in " + filenameIn + " -out " + filenameOut + " -pass pass:" + key;
    std::system(commandAES.c_str());
    if (std::remove(filenameIn.c_str()) != 0) {
        std::cerr << "CANNOT DELETE >>> " + filenameIn << std::endl;
    }
}