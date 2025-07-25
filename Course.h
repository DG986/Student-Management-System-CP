// In Course.h

#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>

class Course {
private:
    std::string courseId;
    std::string courseName;
    int credits; // NEW

public:
    Course(std::string id, std::string name, int courseCredits); // UPDATED
    std::string getId() const;
    std::string getName() const;
    int getCredits() const; // NEW
    void display() const;
};

#endif // COURSE_H
