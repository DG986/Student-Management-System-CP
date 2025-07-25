// In Course.cpp

#include "Course.h"

// UPDATED constructor
Course::Course(std::string id, std::string name, int courseCredits)
    : courseId(id), courseName(name), credits(courseCredits) {}

std::string Course::getId() const {
    return courseId;
}

std::string Course::getName() const {
    return courseName;
}

// NEW method
int Course::getCredits() const {
    return credits;
}

// UPDATED display method
void Course::display() const {
    std::cout << "  Course ID: " << courseId
              << ", Name: " << courseName
              << ", Credits: " << credits; // UPDATED
}
