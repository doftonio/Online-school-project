#include "../Header files/header.h"

void courseMenu(Course* course) {
    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << Color::yellow << course->getCourseTitle() << " Course Management : " << Color::reset << "\n";
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
            std::cout << Color::green << "Course instructor updated." << Color::reset << "\n";
            break;
        }
        case 5:
            course->printFullCourseInfo();
            break;
        case 0:
            std::cout << "Exiting application.\n";
            break;
        default:
            std::cout << Color::red << "Invalid option, please try again." << Color::reset << "\n";
            break;
        }
        std::cout << "\n";
    }
}

void mainMenu(CourseList& courseList)
{
    int userChoice = -1;

    while (userChoice != 0) {
        std::cout << "\n" << Color::yellow << "Main Menu / Course select" << Color::reset << "\n";
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
            std::cout << Color::green << "Course added successfully!" << Color::reset << "\n";
            break;
        }
        case 3: {
            int targetId;
            std::cout << "Enter course ID to remove: ";
            std::cin >> targetId;

            if (courseList.removeCourseById(targetId)) {
                std::cout << Color::green << "Course removed successfully." << Color::reset << "\n";
            }
            else {
                std::cout << Color::red << "Course not found." << Color::reset << "\n";
            }
            break;
        }
        case 4: {
            int targetId;
            std::cout << "Enter course ID: ";
            std::cin >> targetId;

            if (CourseNode* node = courseList.getCoursePointerById(targetId)) {
                std::cout << Color::green << "Course selected: " << node->data.getCourseTitle() << Color::reset << "\n";
                courseMenu(&(node->data));
            }
            else {
                std::cout << Color::red << "Course not found." << Color::reset << "\n";
            }
            break;
        }
        case 5: {
            int targetId;
            std::cout << "Enter course ID: ";
            std::cin >> targetId;

            if (const CourseNode* node = courseList.getCoursePointerById(targetId)) {
                node->data.printFullCourseInfo();
            }
            else {
                std::cout << Color::red << "Course not found." << Color::reset << "\n";
            }
            break;
        }
        case 0:
            std::cout << Color::green << "Exiting program..." << Color::reset << "\n";
            break;
        default:
            std::cout << Color::red << "Invalid choice. Please try again." << Color::reset << "\n";
            break;
        }
    }
}