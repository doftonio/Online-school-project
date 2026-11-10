#include "../Header files/faculty.h"
#include "../Header files/teacher.h"
#include "../Header files/course.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/menu.h"
#include "../Header files/collection.h"
#include "../Exceptions/exceptions.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <format>

void demonstrateExceptions() {
    std::cout << "\n=======================================================\n"
              << "  DEMONSTRATION OF EXCEPTION HANDLING MECHANISM (LAB 6)\n"
              << "=======================================================\n";

    Faculty testFaculty("Faculty of Demonstration");

    try {
        std::cout << "\n[Test 1] Attempting to create teacher with negative ID (-5)...\n";
        Teacher invalidTeacher(-5, "Name", "Surname", "Middle", "SEIT");
    } catch (const InvalidInputDataException& ex) {
        std::cout << "  -> Caught InvalidInputDataException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 2] Attempting to create LabActivity with invalid minimum passing score (15 > 10)...\n";
        Teacher dummyTeacher(901, "Test", "Teacher", "Middle", "SEIT");
        LabActivity invalidLab(16, &dummyTeacher, 10, 15);
    } catch (const InvalidInputDataException& ex) {
        std::cout << "  -> Caught InvalidInputDataException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 3] Attempting to create duplicate teacher with ID 101...\n";
        testFaculty.createTeacher(101, "Ivan", "Ivanov", "Ivanovich", "SEIT");
        testFaculty.createTeacher(101, "Petr", "Petrov", "Petrovich", "IIT");
    } catch (const DuplicateEntityException& ex) {
        std::cout << "  -> Caught DuplicateEntityException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 4] Attempting to assign already assigned teacher to same course...\n";
        Course* duplicateCourse = testFaculty.createCourse(2, "Advanced C++");
        Teacher* assignedTeacher = testFaculty.createTeacher(601, "Sergey", "Smirnov", "Alexeevich", "SEIT");
        *duplicateCourse += assignedTeacher;
        *duplicateCourse += assignedTeacher;
    } catch (const DuplicateEntityException& ex) {
        std::cout << "  -> Caught DuplicateEntityException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 5] Attempting to fetch non-existent course with ID 999...\n";
        [[maybe_unused]] const Course* nonExistent = testFaculty.getCourse(999);
    } catch (const EntityNotFoundException& ex) {
        std::cout << "  -> Caught EntityNotFoundException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 6] Attempting to remove teacher from course where they are not assigned...\n";
        Course* mathCourse = testFaculty.createCourse(3, "Calculus");
        *mathCourse -= 888;
    } catch (const EntityNotFoundException& ex) {
        std::cout << "  -> Caught EntityNotFoundException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 7] Attempting to assign 6th teacher to course exceeding limit 5...\n";
        Course* capacityCourse = testFaculty.createCourse(1, "Distributed Cloud Computing");
        for (int i = 1; i <= 6; ++i) {
            Teacher* t = testFaculty.createTeacher(500 + i, std::format("Teacher{}", i), "Test", "T", "SEIT");
            *capacityCourse += t;
        }
    } catch (const CapacityExceededException& ex) {
        std::cout << "  -> Caught CapacityExceededException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 8] Attempting out-of-bounds access on Collection at index 99...\n";
        Collection<int> testColl;
        testColl.add(100);
        [[maybe_unused]] int val = testColl.get(99);
    } catch (const IndexOutOfBoundsException& ex) {
        std::cout << "  -> Caught IndexOutOfBoundsException: " << ex.what() << "\n";
    }

    std::cout << "\nAll exception scenarios caught and processed safely without system crash.\n";
}

int main() {
    demonstrateExceptions();

    Faculty faculty("Faculty of Computer Systems and Networks");

    Teacher* t1 = faculty.createTeacher(101, "Alexey", "Sidorov", "Ivanovich", "SEIT");
    Teacher* t2 = faculty.createTeacher(102, "Elena", "Kuznetsova", "Vasilyevna", "IIT");
    Teacher* t3 = faculty.createTeacher(103, "Mikhail", "Gromov", "Petrovich", "Higher Math");

    Course* course = faculty.createCourse(1, "Object-Oriented Programming");
    *course += t1;
    *course += t2;
    *course += t3;

    course->addActivity(std::make_unique<LectureActivity>(16, t1, 8, 32));
    course->addActivity(std::make_unique<LabActivity>(16, t2, 8, 4));
    course->addActivity(std::make_unique<PracticeActivity>(16, t3, 4, 12, 6));

    runMainMenu(faculty);
    return 0;
}
