// In Enrollment.h

#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>

class Enrollment {
private:
    int studentId;
    std::string courseId;
    char grade; // NEW

public:
    Enrollment(int sId, std::string cId);
    int getStudentId() const;
    std::string getCourseId() const;
    char getGrade() const; // NEW
    void setGrade(char newGrade); // NEW
};

#endif // ENROLLMENT_H
