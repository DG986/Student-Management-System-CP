#include "Student.h"

Student::Student(int id, std::string studentName) : studentId(id), name(studentName) {}

int Student::getId() const {
    return studentId;
}

std::string Student::getName() const {
    return name;
}

void Student::display() const {
    std::cout << "  ID: " << studentId << ", Name: " << name;
}
