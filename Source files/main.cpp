#include "../Header files/faculty.h"
#include "../Header files/teacher.h"
#include "../Header files/student.h"
#include "../Header files/studyGroup.h"
#include "../Header files/course.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/menu.h"
#include <iostream>
#include <memory>
#include <vector>

void demonstratePolymorphism() {
    std::cout << "\n=======================================================\n"
              << "  DEMONSTRATION OF DYNAMIC POLYMORPHISM (LAB 4)\n"
              << "=======================================================\n";

    // Heterogeneous collection of abstract base class pointers
    std::vector<std::unique_ptr<CourseActivity>> activities;
    activities.push_back(std::make_unique<LectureActivity>(16, 101, 8, 32));
    activities.push_back(std::make_unique<LabActivity>(16, 102, 8, 4));
    activities.push_back(std::make_unique<PracticeActivity>(16, 103, 4, 12, 6));

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

void demonstrateOperatorsAndFriends() {
    std::cout << "\n=======================================================\n"
              << "  DEMONSTRATION OF OPERATORS AND FRIEND FUNCTIONS\n"
              << "=======================================================\n";

    Student s1(1, "Ivan", "Ivanov", "Ivanovich", 5);
    Student s2(2, "Petr", "Petrov", "Petrovich", 3);
    Student s3(1, "Ivan", "Ivanov", "Clone", 10);

    std::cout << "Student 1: " << s1 << "\n";
    std::cout << "Student 2: " << s2 << "\n";
    std::cout << "Student 1 == Student 3 (by ID): " << (s1 == s3 ? "true" : "false") << "\n";
    std::cout << "Student 1 <=> Student 2: " << ((s1 <=> s2) < 0 ? "s1 < s2" : "s1 >= s2") << "\n";

    std::cout << "Friend function inspectStudentInternals:\n";
    inspectStudentInternals(s1);
}

int main() {
    // 1. Run clear, rich polymorphic & operators demonstration for Lab 4
    demonstratePolymorphism();
    demonstrateOperatorsAndFriends();

    // 2. Initialize domain model
    Faculty faculty("Faculty of Computer Systems and Networks");

    Teacher* t1 = faculty.createTeacher(101, "Alexey", "Sidorov", "Ivanovich", "SEIT");
    Teacher* t2 = faculty.createTeacher(102, "Elena", "Kuznetsova", "Vasilyevna", "IIT");
    Teacher* t3 = faculty.createTeacher(103, "Mikhail", "Gromov", "Petrovich", "Higher Math");

    StudyGroup* g1 = faculty.createGroup("550501", 2, 30);
    faculty.enrollStudentInGroup(1, "Ivan", "Ivanov", "Ivanovich", g1);
    faculty.enrollStudentInGroup(2, "Petr", "Petrov", "Petrovich", g1);
    faculty.enrollStudentInGroup(3, "Anna", "Sidorova", "Alexandrovna", g1);

    Course* course = faculty.createCourse(1, "Object-Oriented Programming");
    *course += t1;
    *course += t2;
    *course += t3;

    course->addActivity(std::make_unique<LectureActivity>(16, t1, 8, 32));
    course->addActivity(std::make_unique<LabActivity>(16, t2, 8, 4));
    course->addActivity(std::make_unique<PracticeActivity>(16, t3, 4, 12, 6));

    // 3. Run interactive interactive management menu
    runMainMenu(faculty);
    return 0;
}
