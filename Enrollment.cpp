// In Enrollment.cpp

#include "Enrollment.h"

// UPDATED constructor to initialize grade
Enrollment::Enrollment(int sId, std::string cId)
    : studentId(sId), courseId(cId), grade('-') {}

int Enrollment::getStudentId() const {
    return studentId;
}

std::string Enrollment::getCourseId() const {
    return courseId;
}

// NEW method
char Enrollment::getGrade() const {
    return grade;
}

// NEW method
void Enrollment::setGrade(char newGrade) {
    grade = newGrade;
}
