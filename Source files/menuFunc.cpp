#include "../Header files/header.h"

void courseMenu(Course* course) {
    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\o{33}[33m" << course->getCourseTitle() << " Course Management : \o{33}[0m\n";
        std::cout << "1. Enroll new student\n";
        std::cout << "2. Remove student from course\n";
        std::cout << "3. Record task completion\n";
        std::cout << "4. Assign new instructor\n";
        std::cout << "5. Display course summary\n";
        std::cout << "0. Back\n";
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
            course->enrollStudent(studentId, studentName);
            break;
        }
        case 2: {
            int studentId;
            std::cout << "Enter student ID to remove: ";
            std::cin >> studentId;
            course->removeStudent(studentId);
            break;
        }
        case 3: {
            int studentId;
            std::cout << "Enter student ID: ";
            std::cin >> studentId;
            course->recordTaskCompletion(studentId);
            break;
        }
        case 4: {
            std::string newTeacherName;
            std::cin.ignore();
            std::cout << "Enter new instructor name: ";
            std::getline(std::cin, newTeacherName);
            course->setTeacherName(newTeacherName);
            std::cout << "\o{33}[32mCourse instructor updated.\o{33}[0m\n";
            break;
        }
        case 5:
            course->printFullCourseInfo();
            break;
        case 0:
            std::cout << "Exiting application.\n";
            break;
        default:
            std::cout << "\o{33}[31mInvalid option, please try again.\o{33}[0m\n";
            break;
        }
        std::cout << "\n";
    }
}

void mainMenu(CourseList& courseList)
{
    int userChoice = -1;

    while (userChoice != 0) {
        std::cout << "\n\o{33}[33mMain Menu / Course select\o{33}[0m\n";
        std::cout << "1. Display list of courses\n";
        std::cout << "2. Add course\n";
        std::cout << "3. Remove course\n";
        std::cout << "4. Select course by id\n";
        std::cout << "5. Display course summary\n";
        std::cout << "0. Close program\n";
        std::cout << "Select an option: ";
        std::cin >> userChoice;

        switch (userChoice) {
        case 1:
            courseList.displayListOfCourses();
            break;
        case 2: {
            int id;
            int lessons;
            int capacity;
            std::string title;
            std::string teacher;

            std::cout << "Enter course ID: ";
            std::cin >> id;
            std::cout << "Enter course title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter teacher name: ";
            std::getline(std::cin, teacher);
            std::cout << "Enter total lessons: ";
            std::cin >> lessons;
            std::cout << "Enter max capacity: ";
            std::cin >> capacity;

            courseList.addCourse(id, title, teacher, lessons, capacity);
            std::cout << "\o{33}[32mCourse added successfully!\o{33}[0m\n";
            break;
        }
        case 3: {
            int targetId;
            std::cout << "Enter course ID to remove: ";
            std::cin >> targetId;

            if (courseList.removeCourseById(targetId)) {
                std::cout << "\o{33}[32mCourse removed successfully.\o{33}[0m\n";
            }
            else {
                std::cout << "\o{33}[31mCourse not found.\o{33}[0m\n";
            }
            break;
        }
        case 4: {
            int targetId;
            std::cout << "Enter course ID: ";
            std::cin >> targetId;

            if (CourseNode* node = courseList.getCoursePointerById(targetId)) {
                std::cout << "\o{33}[32mCourse selected: " << node->data.getCourseTitle() << "\o{33}[0m\n";
                courseMenu(&(node->data));
            }
            else {
                std::cout << "\o{33}[31mCourse not found.\o{33}[0m\n";
            }
            break;
        }
        case 5: {
            int targetId;
            std::cout << "Enter course ID: ";
            std::cin >> targetId;

            if (CourseNode* node = courseList.getCoursePointerById(targetId)) {
                node->data.printFullCourseInfo();
            }
            else {
                std::cout << "\o{33}[31mCourse not found.\o{33}[0m\n";
            }
            break;
        }
        case 0:
            std::cout << "\o{33}[32mExiting program...\o{33}[0m\n";
            break;
        default:
            std::cout << "\o{33}[31mInvalid choice. Please try again.\o{33}[0m\n";
            break;
        }
    }
}