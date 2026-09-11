#include "../Header files/course.h"
#include "../Header files/student.h"
#include <iostream>
#include <string>

int main() {

    std::cout << "\033[34mVerifying basic object operations:\033[0m\n";

    Student singleStudent;
    singleStudent.initStudent(101, "John Doe");
    singleStudent.printInfo();
    singleStudent.setStudentName("John Smith");
    std::cout << "Updated name: \033[36m" << singleStudent.getStudentName() << "\033[0m\n\n";

    Course cppCourse;
    cppCourse.initCourse("C++ Programming", "Alex Sidorov", 10, 2);

    Course webCourse;
    webCourse.initCourse("Web Development", "Elena Kuznetsova", 8, 5);

    std::cout << "\033[34mEnrolling students in C++ course (capacity limit: 2):\033[0m\n";
    cppCourse.enrollStudent(5583001, "John Smith");
    cppCourse.enrollStudent(5583002, "Anna Smirnova");
    cppCourse.enrollStudent(5583003, "Paul Kovalev"); // Capacity limit error check

    std::cout << "\n\033[34mEnrolling students in Web Development course:\033[0m\n";
    webCourse.enrollStudent(5583001, "Anna Smirnova");
    webCourse.enrollStudent(5583003, "Paul Kovalev");

    std::cout << "\n\033[34mRecording completed tasks:\033[0m\n";
    cppCourse.recordTaskCompletion(5583001);
    cppCourse.recordTaskCompletion(5583001);
    cppCourse.recordTaskCompletion(5583002);

    webCourse.recordTaskCompletion(5583003);

    std::cout << "\n\033[34mCurrent course status:\033[0m\n";
    cppCourse.printFullCourseInfo();
    webCourse.printFullCourseInfo();

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\033[33mC++ Course Management:\033[0m\n";
        std::cout << "1. Enroll new student\n";
        std::cout << "2. Remove student from course\n";
        std::cout << "3. Record task completion\n";
        std::cout << "4. Assign new instructor\n";
        std::cout << "5. Display course summary\n";
        std::cout << "0. Exit program\n";
        std::cout << "Select an option: ";
        std::cin >> userChoice;

        switch (userChoice) {
        case 1: {
            int studentId;
            std::string studentName;
            std::cout << "Enter student ID: ";
            std::cin >> studentId;
            std::cin.ignore();
            std::cout << "Enter student name: ";
            std::getline(std::cin, studentName);
            cppCourse.enrollStudent(studentId, studentName);
            break;
        }
        case 2: {
            int studentId;
            std::cout << "Enter student ID to remove: ";
            std::cin >> studentId;
            cppCourse.removeStudent(studentId);
            break;
        }
        case 3: {
            int studentId;
            std::cout << "Enter student ID: ";
            std::cin >> studentId;
            cppCourse.recordTaskCompletion(studentId);
            break;
        }
        case 4: {
            std::string newTeacherName;
            std::cin.ignore();
            std::cout << "Enter new instructor name: ";
            std::getline(std::cin, newTeacherName);
            cppCourse.setTeacherName(newTeacherName);
            std::cout << "\033[32mCourse instructor updated.\033[0m\n";
            break;
        }
        case 5:
            cppCourse.printFullCourseInfo();
            break;
        case 0:
            std::cout << "Exiting application.\n";
            break;
        default:
            std::cout << "\033[31mInvalid option, please try again.\033[0m\n";
            break;
        }
        std::cout << "\n";
    }

    return 0;
}