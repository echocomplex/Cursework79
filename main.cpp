#include <iostream>
#include "List.h"
#include "Exercise79.h"
#include "Student.h"


void addStudent (Exercise79& unit) {
    std::string studentInfo;
    std::cout << std::endl << "Enter student info splitted by space. Rows: 1) number" << std::endl << 
        "2) first_name" << std::endl << "3) middle_name" << std::endl << "4) last_name" << std::endl << 
        "5) year" << std::endl << "6) birthday" << std::endl << "7) faculty" << std::endl << 
        "8) department" << std::endl << "9) group" << std::endl << "10) gender" << std::endl << 
        "11) subject" << std::endl << "12) date" << std::endl << "13) mark" << std::endl << ">>> ";
    std::cin >> studentInfo;
    std::istringstream iss(studentInfo);
    std::string token;
    unsigned int count = 0;
    Student student;
    grade g;
    while (std::getline(iss, token, ' ')) {
        if (count == 0) { student.setNumber(token); }
            else if (count == 1) { student.setFirstName(token); }
            else if (count == 2) { student.setMiddleName(token); }
            else if (count == 3) { student.setLastName(token); }
            else if (count == 4) { student.setYear(std::stoi(token)); }
            else if (count == 5) { student.setBirthday(token); }
            else if (count == 6) { student.setFaculty(token); }
            else if (count == 7) { student.setDepartment(token); }
            else if (count == 8) { student.setGroup(token); }
            else if (count == 9) { student.setNumber(token); }
            else if (count == 10) { g.subject = token; }
            else if (count == 11) { g.date = token; }
            else if (count == 12) { g.mark = std::stoi(token); }
            ++count;
    }
    student.appendGrade(g);
    unit.append(student);
    std::cout << "Success!" << std::endl;
}

void deleteStudent (Exercise79& unit) {
    std::string number;
    std::cout << "Enter student's number >>> ";
    std::cin >> number;
    Student student;
    student.setNumber(number);
    if (unit.isExists(student)) {
        unit.remove(unit.find(student));
        std::cout << "Success!" << std::endl;
    }
    else {
        std::cerr << "Student does not exists!" << std::endl;
    }
}

void sortGroup (Exercise79& unit) {
    std::string group;
    std::cout << "Enter group number >>> ";
    std::cin >> group;
    List <Student> result = unit.sortGroup(group);
    if (result.length() == 0) {
        throw std::logic_error("Group doesn't exist!");
    }
    for (int i = 0; i < result.length(); ++i) {
        std::cout << result[i].getNumber() << " >>> " << result[i].getYear() << std::endl;
    }
}


int main () {
    Exercise79::decrypt("data.enc", "data.txt");
    Exercise79 unit("data.txt");

    int choice;
    std::cout << 
        "1. Add student" << std::endl << 
        "2. Delete student" << std::endl << 
        "3. Sort group" << std::endl << 
        "4. Show table" << std::endl << std::endl << 
        ">>> ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cerr << "You entered not num! Try again." << std::endl;
        return 1;
    }

    switch (choice) {
        case 1:
            addStudent(unit);
            break;
        case 2:
            deleteStudent(unit);
            break;
        case 3:
            sortGroup(unit);
            break;
        case 4:
            std::cout << unit << std::endl;
            break;
        default:
            std::cerr << "You entered wrong num! Try again." << std::endl;
            return 1;
    }
    
    unit.toFile("data.txt");

    Exercise79::encrypt("data.txt", "data.enc");

    return 0;
}