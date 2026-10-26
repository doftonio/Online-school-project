#include "../Header files/menu.h"
#include "../Header files/faculty.h"
#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/lectureActivity.h"
#include <iostream>
#include <string>
#include <memory>
#include <limits>

static int readInt(const std::string& prompt) {
    std::cout << prompt;
    int val = 0;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter an integer: ";
    }
    return val;
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::cin >> std::ws;
    std::getline(std::cin, val);
    return val;
}

void handleAddTeacher(Faculty& faculty) {
    std::cout << "\n--- Add New Teacher (via operator>>) ---\n";
    Teacher tempTeacher;
    if (!(std::cin >> tempTeacher)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: invalid input data for teacher.\n";
        return;
    }

    const Teacher* created = faculty.createTeacher(
        tempTeacher.getId(),
        tempTeacher.getFirstName(),
        tempTeacher.getLastName(),
        tempTeacher.getMiddleName(),
        tempTeacher.getDepartment()
    );

    if (created) {
        std::cout << "Teacher added successfully: " << *created << "\n";
    }
}

void handleCreateCourse(Faculty& faculty) {
    std::cout << "\n--- Create New Course ---\n";
    int id = readInt("Enter Course ID: ");
    std::string title = readLine("Enter Course Title: ");

    const Course* created = faculty.createCourse(id, title);
    if (created) {
        std::cout << "Course created successfully.\n";
    }
}

void handleAssignTeacherToCourse(const Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Assign Teacher to Course ---\n";
    int teacherId = readInt("Enter Teacher ID: ");
    Teacher* teacher = faculty.findTeacher(teacherId);
    if (!teacher) {
        std::cout << "Teacher with ID " << teacherId << " not found.\n";
        return;
    }
    *course += teacher;
    std::cout << "Assignment attempt completed via operator+=\n";
}

void handleRemoveTeacherFromCourse(Course* course) {
    if (!course) return;
    std::cout << "\n--- Remove Teacher from Course ---\n";
    int teacherId = readInt("Enter Teacher ID to remove: ");
    *course -= teacherId;
    std::cout << "Removal attempt completed via operator-=(int).\n";
}

void handleAddActivityToCourse(const Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Add Activity to Course (Polymorphic) ---\n"
              << "1. Lecture Activity\n"
              << "2. Lab Activity\n"
              << "3. Practice Activity\n"
              << "Select type: ";
    int typeChoice = readInt("");
    int lessons = readInt("Enter number of lessons: ");
    int teacherId = readInt("Enter Teacher ID for this activity: ");
    Teacher* teacher = faculty.findTeacher(teacherId);

    if (typeChoice == 1) {
        int topics = readInt("Enter topics count: ");
        int hours = readInt("Enter lecture hours: ");
        course->addActivity(std::make_unique<LectureActivity>(lessons, teacher, topics, hours));
        std::cout << "Lecture activity added polymorphically.\n";
    } else if (typeChoice == 2) {
        int labs = readInt("Enter total labs count: ");
        int minScore = readInt("Enter minimum passing score: ");
        course->addActivity(std::make_unique<LabActivity>(lessons, teacher, labs, minScore));
        std::cout << "Lab activity added polymorphically.\n";
    } else if (typeChoice == 3) {
        int tests = readInt("Enter tests count: ");
        int tasks = readInt("Enter tasks count: ");
        int calcs = readInt("Enter calculations count: ");
        course->addActivity(std::make_unique<PracticeActivity>(lessons, teacher, tests, tasks, calcs));
        std::cout << "Practice activity added polymorphically.\n";
    } else {
        std::cout << "Invalid activity type choice.\n";
    }
}

void showCourseDetailsSubmenu(const Faculty& faculty, Course* course) {
    if (!course) return;
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Course: " << course->getTitle() << " (ID: " << course->getId() << ") ===\n"
                  << "1. Print full course info & activities (Polymorphic)\n"
                  << "2. Assign teacher to course (*course += teacher)\n"
                  << "3. Remove teacher from course (*course -= id)\n"
                  << "4. Add activity to course (Polymorphic)\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) course->printFullCourseInfo();
        else if (choice == 2) handleAssignTeacherToCourse(faculty, course);
        else if (choice == 3) handleRemoveTeacherFromCourse(course);
        else if (choice == 4) handleAddActivityToCourse(faculty, course);
    }
}

void showTeachersSubmenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Faculty Teachers (" << faculty.getTeachers().size() << ") ---\n";
        for (const auto& t : faculty.getTeachers()) {
            if (t) t->printInfo();
        }
        std::cout << "1. Add new teacher\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) handleAddTeacher(faculty);
    }
}

void showCoursesSubmenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Faculty Courses (" << faculty.getCourses().size() << ") ---\n";
        for (const auto& c : faculty.getCourses()) {
            if (c) std::cout << "ID: " << c->getId() << " | Title: " << c->getTitle() << "\n";
        }
        std::cout << "1. Create new course\n"
                  << "2. Open course management\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) {
            handleCreateCourse(faculty);
        } else if (choice == 2) {
            int cId = readInt("Enter course ID: ");
            Course* c = faculty.findCourse(cId);
            if (c) {
                showCourseDetailsSubmenu(faculty, c);
            } else {
                std::cout << "Course with ID " << cId << " not found.\n";
            }
        }
    }
}

void runMainMenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n========================================\n"
                  << "   Online School System: " << faculty.getName() << "\n"
                  << "========================================\n"
                  << "1. Teachers Management\n"
                  << "2. Courses & Activities Management\n"
                  << "0. Exit\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) showTeachersSubmenu(faculty);
        else if (choice == 2) showCoursesSubmenu(faculty);
    }
}
