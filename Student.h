#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
private:
    int studentId;
    std::string name;

public:
    Student(int id, std::string studentName);
    int getId() const;
    std::string getName() const;
    void display() const;
};

#endif // STUDENT_H
