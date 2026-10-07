#include "../Header files/header.h"

void courseMenu(Course* course) {
    if (!course) return;

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << course->getCourseTitle() << " Course Management:\n";
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
            int studentId = 0;
            std::string studentName{};
            std::cout << "Enter student ID: ";
            std::cin >> studentId;
            std::cin.ignore();
            std::cout << "Enter student name: ";
            std::getline(std::cin, studentName);
            course->enrollStudent(studentId, studentName);
            break;
        }
        case 2: {
            int studentId = 0;
            std::cout << "Enter student ID to remove: ";
            std::cin >> studentId;
            course->removeStudent(studentId);
            break;
        }
        case 3: {
            int studentId = 0;
            std::cout << "Enter student ID: ";
            std::cin >> studentId;
            course->recordTaskCompletion(studentId);
            break;
        }
        case 4: {
            std::string newTeacherName{};
            std::cin.ignore();
            std::cout << "Enter new instructor name: ";
            std::getline(std::cin, newTeacherName);
            course->setTeacherName(newTeacherName);
            std::cout << "Course instructor updated.\n";
            break;
        }
        case 5:
            course->printFullCourseInfo();
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid option, please try again.\n";
            break;
        }
        std::cout << "\n";
    }
}

void mainMenu(CourseList& courseList)
{
    int userChoice = -1;

    while (userChoice != 0) {
        std::cout << "\nMain Menu / Course select\n";
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
            int typeChoice = 1;
            std::cout << "Select course type:\n";
            std::cout << "1. Standard Course\n";
            std::cout << "2. Interactive Course\n";
            std::cout << "3. Webinar Course\n";
            std::cout << "4. Mentored Course\n";
            std::cout << "Choice: ";
            std::cin >> typeChoice;

            int id = 0;
            int lessons = 0;
            int capacity = 0;
            std::string title{};
            std::string teacher{};

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

            if (typeChoice == 2)
            {
                int exercises = 0;
                int passingScore = 0;
                std::cout << "Enter total exercises: ";
                std::cin >> exercises;
                std::cout << "Enter passing score (%): ";
                std::cin >> passingScore;
                courseList.addCourse(std::make_unique<InteractiveCourse>(
                    id, title, teacher, lessons, capacity, exercises, passingScore));
            }
            else if (typeChoice == 3)
            {
                std::string url{};
                std::string schedule{};
                int webinars = 0;
                std::cin.ignore();
                std::cout << "Enter platform URL: ";
                std::getline(std::cin, url);
                std::cout << "Enter schedule: ";
                std::getline(std::cin, schedule);
                std::cout << "Enter total webinars: ";
                std::cin >> webinars;
                WebinarDetails details{ url, schedule, webinars };
                courseList.addCourse(std::make_unique<WebinarCourse>(
                    id, title, teacher, lessons, capacity, details));
            }
            else if (typeChoice == 4)
            {
                std::string mentor{};
                int reviewsLimit = 0;
                std::cin.ignore();
                std::cout << "Enter mentor name: ";
                std::getline(std::cin, mentor);
                std::cout << "Enter reviews limit: ";
                std::cin >> reviewsLimit;
                courseList.addCourse(std::make_unique<MentoredCourse>(
                    id, title, teacher, lessons, capacity, mentor, reviewsLimit));
            }
            else
            {
                courseList.addCourse(id, title, teacher, lessons, capacity);
            }

            std::cout << "Course added successfully!\n";
            break;
        }
        case 3: {
            int targetId = 0;
            std::cout << "Enter course ID to remove: ";
            std::cin >> targetId;

            if (courseList.removeCourseById(targetId)) {
                std::cout << "Course removed successfully.\n";
            }
            else {
                std::cout << "Course not found.\n";
            }
            break;
        }
        case 4: {
            int targetId = 0;
            std::cout << "Enter course ID: ";
            std::cin >> targetId;

            if (CourseNode* node = courseList.getCoursePointerById(targetId)) {
                std::cout << "\nCourse selected: " << node->data->getCourseTitle() << "\n";
                courseMenu(node->data.get());
            }
            else {
                std::cout << "Course not found.\n";
            }
            break;
        }
        case 5: {
            int targetId = 0;
            std::cout << "Enter course ID: ";
            std::cin >> targetId;

            if (const CourseNode* node = courseList.getCoursePointerById(targetId)) {
                node->data->printFullCourseInfo();
            }
            else {
                std::cout << "Course not found.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}