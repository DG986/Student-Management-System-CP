#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip> // For std::fixed and std::setprecision

#include "Student.h"
#include "Course.h"
#include "Enrollment.h"

//=============== Global Data Storage ===============
std::vector<Student> students;
std::vector<Course> courses;
std::vector<Enrollment> enrollments;
int nextStudentId = 1;

//=============== Function Prototypes ===============
void showMenu();
void addStudent();
void addCourse();
void viewAllStudents();
void viewAllCourses();
void enrollStudentInCourse();
void assignGrade();
void viewStudentEnrollmentsAndGPA(); // Function to be fixed
void viewRawData(); // NEW DEBUG FUNCTION

float getGradePoints(char grade);

//=============== Main Function ===============
int main() {
    int choice;

    students.push_back(Student(nextStudentId++, "Alice"));
    students.push_back(Student(nextStudentId++, "Bob"));
    courses.push_back(Course("CS101", "Intro to Programming", 3));
    courses.push_back(Course("MA202", "Calculus II", 4));
    courses.push_back(Course("PH150", "General Physics", 3));


    while (true) {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: addStudent(); break;
            case 2: addCourse(); break;
            case 3: viewAllStudents(); break;
            case 4: viewAllCourses(); break;
            case 5: enrollStudentInCourse(); break;
            case 6: assignGrade(); break;
            case 7: viewStudentEnrollmentsAndGPA(); break;
            case 8: // UPDATED
                std::cout << "Exiting program. Goodbye!\n";
                return 0;
            case 9: viewRawData(); break; // NEW DEBUG OPTION
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
        std::cout << std::endl;
    }
    return 0;
}

//=============== Function Implementations ===============
void showMenu() {
    std::cout << "===== Student Information System =====" << std::endl;
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Add Course" << std::endl;
    std::cout << "3. View All Students" << std::endl;
    std::cout << "4. View All Courses" << std::endl;
    std::cout << "5. Enroll Student in Course" << std::endl;
    std::cout << "6. Assign Grade" << std::endl;
    std::cout << "7. View Student Enrollments & GPA" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "9. (Debug) View Raw Data" << std::endl; // NEW
    std::cout << "======================================" << std::endl;
}

// ===== THE FIXED FUNCTION =====
void viewStudentEnrollmentsAndGPA() {
    int studentId;
    std::cout << "--- View Student Enrollments & GPA ---\n";
    viewAllStudents();
    std::cout << "Enter student ID: ";
    std::cin >> studentId;

    Student* studentPtr = nullptr;
    for (auto& s : students) {
        if (s.getId() == studentId) {
            studentPtr = &s;
            break;
        }
    }

    if (studentPtr == nullptr) {
        std::cout << "Error: Student with ID " << studentId << " not found.\n";
        return;
    }

    std::cout << "\n--- Report for " << studentPtr->getName() << " ---\n";

    std::vector<Enrollment> studentEnrollments;
    for (const auto& enrollment : enrollments) {
        if (enrollment.getStudentId() == studentId) {
            studentEnrollments.push_back(enrollment);
        }
    }

    if (studentEnrollments.empty()) {
        std::cout << "This student is not enrolled in any courses.\n";
    } else {
        float totalPoints = 0;
        int totalCredits = 0;

        // First, display all courses and grades
        for (const auto& enrollment : studentEnrollments) {
            for (const auto& course : courses) {
                if (course.getId() == enrollment.getCourseId()) {
                    course.display();
                    std::cout << ", Grade: " << enrollment.getGrade() << std::endl;

                    if (enrollment.getGrade() != '-') {
                        totalPoints += getGradePoints(enrollment.getGrade()) * course.getCredits();
                        totalCredits += course.getCredits();
                    }
                    break;
                }
            }
        }

        // Then, display the final GPA calculation
        std::cout << "\n---------------------------------\n";
        if (totalCredits > 0) {
            float gpa = totalPoints / totalCredits;
            std::cout << "Total Credits Attempted: " << totalCredits << std::endl;
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "GPA: " << gpa << std::endl;
        } else {
            std::cout << "No graded courses to calculate GPA.\n";
        }
    }
    std::cout << "---------------------------------\n";
}

// ===== NEW DEBUG FUNCTION =====
void viewRawData() {
    std::cout << "\n--- DEBUG: Raw Enrollment Data ---\n";
    if (enrollments.empty()) {
        std::cout << "Enrollment vector is empty.\n";
    } else {
        for (const auto& e : enrollments) {
            std::cout << "Student ID: " << e.getStudentId()
                      << ", Course ID: " << e.getCourseId()
                      << ", Grade: " << e.getGrade() << std::endl;
        }
    }
    std::cout << "------------------------------------\n";
}


// (The other functions are unchanged but are included for completeness)
void addStudent() {
    std::string name;
    std::cout << "Enter student name: ";
    std::getline(std::cin, name);
    students.push_back(Student(nextStudentId, name));
    std::cout << "Student '" << name << "' added successfully with ID " << nextStudentId << ".\n";
    nextStudentId++;
}

void addCourse() {
    std::string courseId, courseName;
    int credits;
    std::cout << "Enter course ID (e.g., CS101): ";
    std::getline(std::cin, courseId);
    std::cout << "Enter course name: ";
    std::getline(std::cin, courseName);
    std::cout << "Enter course credits: ";
    std::cin >> credits;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    courses.push_back(Course(courseId, courseName, credits));
    std::cout << "Course '" << courseName << "' added successfully.\n";
}

void viewAllStudents() {
    std::cout << "--- All Students ---\n";
    if (students.empty()) {
        std::cout << "No students have been added yet.\n";
    } else {
        for (const auto& student : students) {
            student.display();
            std::cout << std::endl;
        }
    }
    std::cout << "--------------------\n";
}

void viewAllCourses() {
    std::cout << "--- All Courses ---\n";
    if (courses.empty()) {
        std::cout << "No courses have been added yet.\n";
    } else {
        for (const auto& course : courses) {
            course.display();
            std::cout << std::endl;
        }
    }
    std::cout << "-------------------\n";
}

void enrollStudentInCourse() {
    int studentId;
    std::string courseId;
    std::cout << "--- Available Students ---\n";
    viewAllStudents();
    std::cout << "Enter student ID to enroll: ";
    std::cin >> studentId;
    std::cout << "\n--- Available Courses ---\n";
    viewAllCourses();
    std::cout << "Enter course ID to enroll in: ";
    std::cin >> courseId;
    bool studentFound = false;
    for (const auto& student : students) {
        if (student.getId() == studentId) { studentFound = true; break; }
    }
    bool courseFound = false;
    for (const auto& course : courses) {
        if (course.getId() == courseId) { courseFound = true; break; }
    }
    if (!studentFound) { std::cout << "Error: Student with ID " << studentId << " not found.\n"; return; }
    if (!courseFound) { std::cout << "Error: Course with ID " << courseId << " not found.\n"; return; }
    for(const auto& enrollment : enrollments) {
        if(enrollment.getStudentId() == studentId && enrollment.getCourseId() == courseId) {
            std::cout << "Error: Student is already enrolled in this course.\n";
            return;
        }
    }
    enrollments.push_back(Enrollment(studentId, courseId));
    std::cout << "Enrollment successful!\n";
}

void assignGrade() {
    int studentId;
    std::string courseId;
    char grade;
    std::cout << "--- Assign Grade ---\n";
    viewAllStudents();
    std::cout << "Enter student ID: ";
    std::cin >> studentId;
    viewAllCourses();
    std::cout << "Enter course ID: ";
    std::cin >> courseId;
    std::cout << "Enter grade (A, B, C, D, F): ";
    std::cin >> grade;
    grade = toupper(grade);
    bool found = false;
    for (auto& enrollment : enrollments) {
        if (enrollment.getStudentId() == studentId && enrollment.getCourseId() == courseId) {
            enrollment.setGrade(grade);
            found = true;
            std::cout << "Grade assigned successfully.\n";
            break;
        }
    }
    if (!found) { std::cout << "Error: Student is not enrolled in this course. Cannot assign grade.\n"; }
}

float getGradePoints(char grade) {
    switch (grade) {
        case 'A': return 4.0f;
        case 'B': return 3.0f;
        case 'C': return 2.0f;
        case 'D': return 1.0f;
        case 'F': return 0.0f;
        default: return 0.0f;
    }
}
