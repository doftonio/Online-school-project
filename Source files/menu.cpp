#include "../Header files/menu.h"
#include "../Header files/faculty.h"
#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include "../Header files/student.h"
#include "../Header files/studyGroup.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/lectureActivity.h"
#include <iostream>
#include <string>

static int readIntChoice() {
    int choice = -1;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::string dummy;
        std::cin >> dummy;
        return -1;
    }
    return choice;
}

void handleCourseActivities(const Course* course) {
    if (!course) return;
    std::cout << "\nActivities for course: " << course->getTitle() << "\n";
    const LabActivity* labAct = static_cast<const LabActivity*>(course->findActivity("550501", ActivityType::Lab));
    if (labAct) {
        labAct->printDetails();
    }
}

void handleAddGrade(const Course* course) {
    if (!course) return;
    std::cout << "\nAdd grade in course: " << course->getTitle() << "\n";
    const PracticeActivity* practiceAct = static_cast<const PracticeActivity*>(course->findActivity("550501", ActivityType::Practice));
    if (practiceAct) {
        practiceAct->printDetails();
    }
}

void handleRemoveGrade(const Course* course) {
    if (!course) return;
    std::cout << "\nRemove grade in course: " << course->getTitle() << "\n";
    const LabActivity* labAct = static_cast<const LabActivity*>(course->findActivity("550501", ActivityType::Lab));
    const PracticeActivity* practiceAct = static_cast<const PracticeActivity*>(course->findActivity("550501", ActivityType::Practice));
    if (labAct) {
        labAct->printDetails();
    }
    if (practiceAct) {
        practiceAct->printDetails();
    }
}

void handlePrintGrades(const Course* course) {
    if (!course) return;
    std::cout << "\nCourse summary for: " << course->getTitle() << "\n";
    course->printFullCourseInfo();
}

void showCourseDetailsSubmenu(Faculty& /*faculty*/, const Course* course) {
    if (!course) return;
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Course: " << course->getTitle() << " ---\n"
                  << "1. View activities\n"
                  << "2. Add grade\n"
                  << "3. Remove grade\n"
                  << "4. Print course report\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readIntChoice();
        if (choice == 1) handleCourseActivities(course);
        else if (choice == 2) handleAddGrade(course);
        else if (choice == 3) handleRemoveGrade(course);
        else if (choice == 4) handlePrintGrades(course);
    }
}

void showTeachersSubmenu(Faculty& faculty) {
    std::cout << "\n--- Faculty Teachers (" << faculty.getTeachers().size() << ") ---\n";
    for (const std::unique_ptr<Teacher>& t : faculty.getTeachers()) {
        if (t) t->printInfo();
    }
}

void showGroupsSubmenu(Faculty& faculty) {
    std::cout << "\n--- Faculty Groups (" << faculty.getGroups().size() << ") ---\n";
    for (const std::unique_ptr<StudyGroup>& g : faculty.getGroups()) {
        if (g) g->printInfo();
    }
}

void showCoursesSubmenu(Faculty& faculty) {
    std::cout << "\n--- Faculty Courses (" << faculty.getCourses().size() << ") ---\n";
    for (const std::unique_ptr<Course>& c : faculty.getCourses()) {
        if (c) std::cout << "ID: " << c->getId() << " | Title: " << c->getTitle() << "\n";
    }
}

void runMainMenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Online School System: " << faculty.getName() << " ===\n"
                  << "1. Teachers\n"
                  << "2. Study Groups\n"
                  << "3. Courses\n"
                  << "0. Exit\n"
                  << "Select: ";
        choice = readIntChoice();
        if (choice == 1) showTeachersSubmenu(faculty);
        else if (choice == 2) showGroupsSubmenu(faculty);
        else if (choice == 3) showCoursesSubmenu(faculty);
    }
}
