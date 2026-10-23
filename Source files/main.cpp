#include "../Header files/faculty.h"
#include "../Header files/teacher.h"
#include "../Header files/course.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/menu.h"
#include <iostream>
#include <memory>
#include <vector>

void demonstratePolymorphism(Teacher* t1, Teacher* t2, Teacher* t3) {
    std::cout << "\n=======================================================\n"
              << "  DEMONSTRATION OF DYNAMIC POLYMORPHISM (LAB 4)\n"
              << "=======================================================\n";

    // Heterogeneous collection of abstract base class pointers
    std::vector<std::unique_ptr<CourseActivity>> activities;
    activities.push_back(std::make_unique<LectureActivity>(16, t1, 8, 32));
    activities.push_back(std::make_unique<LabActivity>(16, t2, 8, 4));
    activities.push_back(std::make_unique<PracticeActivity>(16, t3, 4, 12, 6));

    std::cout << "\n[1] Dynamic dispatch via CourseActivity* interface:\n";
    int totalAcademicHours = 0;
    for (const auto& act : activities) {
        if (act) {
            act->printDetails(); // Virtual call
            int hours = act->calculateHours(); // Pure virtual call overridden in subclasses
            totalAcademicHours += hours;
            std::cout << "    --> Calculated academic hours: " << hours << "\n";
        }
    }
    std::cout << "Total academic hours for all activities: " << totalAcademicHours << "\n";

    std::cout << "\n[2] Virtual destructor demo (automatic memory deallocation via RAII)\n";
}

void demonstrateOperatorsAndFriends(const Teacher& t1, const Teacher& t2) {
    std::cout << "\n=======================================================\n"
              << "  DEMONSTRATION OF OPERATORS AND FRIEND FUNCTIONS\n"
              << "=======================================================\n";

    Teacher tClone(101, "Alexey", "Sidorov", "Clone", "SEIT");

    std::cout << "Teacher 1: " << t1 << "\n";
    std::cout << "Teacher 2: " << t2 << "\n";
    std::cout << "Teacher 1 == Teacher Clone (by ID): " << (t1 == tClone ? "true" : "false") << "\n";
    std::cout << "Teacher 1 <=> Teacher 2: " << ((t1 <=> t2) < 0 ? "t1 < t2" : "t1 >= t2") << "\n";

    std::cout << "Friend function inspectTeacherInternals:\n";
    inspectTeacherInternals(t1);
}

int main() {
    // 1. Initialize domain model
    Faculty faculty("Faculty of Computer Systems and Networks");

    Teacher* t1 = faculty.createTeacher(101, "Alexey", "Sidorov", "Ivanovich", "SEIT");
    Teacher* t2 = faculty.createTeacher(102, "Elena", "Kuznetsova", "Vasilyevna", "IIT");
    Teacher* t3 = faculty.createTeacher(103, "Mikhail", "Gromov", "Petrovich", "Higher Math");

    // 2. Run clear polymorphic & operators demonstration for Lab 4
    demonstratePolymorphism(t1, t2, t3);
    demonstrateOperatorsAndFriends(*t1, *t2);

    Course* course = faculty.createCourse(1, "Object-Oriented Programming");
    *course += t1;
    *course += t2;
    *course += t3;

    course->addActivity(std::make_unique<LectureActivity>(16, t1, 8, 32));
    course->addActivity(std::make_unique<LabActivity>(16, t2, 8, 4));
    course->addActivity(std::make_unique<PracticeActivity>(16, t3, 4, 12, 6));

    // 3. Run interactive management menu
    runMainMenu(faculty);
    return 0;
}
