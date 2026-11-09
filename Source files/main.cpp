#include "../Header files/faculty.h"
#include "../Header files/teacher.h"
#include "../Header files/course.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/menu.h"
#include "../Header files/collection.h"
#include "../Header files/exceptions.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void demonstrateTemplates() {
    std::cout << "\n=======================================================\n"
              << "  DEMONSTRATION OF TEMPLATE CLASS AND FUNCTIONS (LAB 5)\n"
              << "=======================================================\n";

    std::cout << "\n--- 1. Primitive Type Collection (Collection<int>) ---\n";
    Collection<int> intColl;
    intColl.add(10);
    intColl.add(25);
    intColl.add(50);
    intColl.add(75);
    std::cout << "Count of elements: " << intColl.size() << "\n";
    intColl.print();

    intColl.remove(25);
    std::cout << "After removing value 25 (size: " << intColl.size() << "):\n";
    intColl.print();

    const auto intIndices = intColl.findIndex([](int val) { return val > 40; });
    std::cout << "[Member method findIndex] Found " << intIndices.size() << " index(es) for elements > 40:\n";
    for (std::size_t idx : intIndices) {
        std::cout << "  Index: " << idx << " (Value: " << intColl[idx] << ")\n";
    }

    const auto intMatches = findByCriterion(intColl, [](int value) { return value > 40; });
    std::cout << "[Free function findByCriterion] Found " << intMatches.size() << " element(s) > 40:\n";
    for (const int* valPtr : intMatches) {
        std::cout << "  Value: " << *valPtr << "\n";
    }

    intColl.clear();
    std::cout << "After clear (empty: " << (intColl.empty() ? "true" : "false") << "):\n";
    intColl.print();

    std::cout << "\n--- 2. Custom Type Collection 1 (Collection<Teacher>) ---\n";
    Collection<Teacher> teacherColl;
    teacherColl.add(Teacher(201, "Anna", "Belaeva", "Sergeevna", "SEIT"));
    teacherColl.add(Teacher(202, "Dmitry", "Kozlov", "Alexandrovich", "IIT"));
    teacherColl.add(Teacher(203, "Olga", "Morozova", "Viktorovna", "IIT"));
    std::cout << "Count of teachers: " << teacherColl.size() << "\n";
    teacherColl.print();

    std::cout << "Accessing element at index 1: " << teacherColl.get(1) << "\n";

    Teacher searchTeacher(202, "Temp", "Temp", "Temp", "Temp");
    if (const auto teacherIndex = teacherColl.find(searchTeacher); teacherIndex.has_value()) {
        std::cout << "[Member method find] Exact teacher with ID 202 found at index: " << *teacherIndex << "\n";
    }

    const auto iitIndices = teacherColl.findIndex([](const Teacher& t) { return t.getDepartment() == "IIT"; });
    std::cout << "[Member method findIndex] Found " << iitIndices.size() << " teacher(s) in IIT department:\n";
    for (std::size_t idx : iitIndices) {
        std::cout << "  Index: " << idx << " -> " << teacherColl[idx] << "\n";
    }

    const auto iitTeachers = findByCriterion(teacherColl, [](const Teacher& t) { return t.getDepartment() == "IIT"; });
    std::cout << "[Free function findByCriterion] Found " << iitTeachers.size() << " teacher(s) in IIT department:\n";
    for (const Teacher* t : iitTeachers) {
        std::cout << "  " << *t << "\n";
    }

    teacherColl.removeAt(0);
    std::cout << "After removing teacher at index 0:\n";
    teacherColl.print();

    std::cout << "\n--- 3. Custom Type Collection 2 (Collection<Course>) ---\n";
    Collection<Course> courseColl;
    courseColl.add(Course(10, "Computer Networks"));
    courseColl.add(Course(20, "Operating Systems"));
    courseColl.add(Course(30, "Database Systems"));
    std::cout << "Count of courses: " << courseColl.size() << "\n";
    courseColl.print();

    const auto systemsIndices = courseColl.findIndex([](const Course& c) {
        return c.getTitle().ends_with("Systems");
    });
    std::cout << "[Member method findIndex] Found " << systemsIndices.size() << " course(s) ending with \"Systems\":\n";
    for (std::size_t idx : systemsIndices) {
        std::cout << "  Index: " << idx << " -> " << courseColl[idx] << "\n";
    }

    const auto systemsCourses = findByCriterion(courseColl, [](const Course& c) {
        return c.getTitle().ends_with("Systems");
    });
    std::cout << "[Free function findByCriterion] Found " << systemsCourses.size() << " course(s) ending with \"Systems\":\n";
    for (const Course* c : systemsCourses) {
        std::cout << "  " << *c << "\n";
    }

    courseColl.remove(Course(20, "Temporary Title"));
    std::cout << "After removing course with ID 20:\n";
    courseColl.print();
}

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
        std::cout << "\n[Test 2] Attempting to create duplicate teacher with ID 101...\n";
        testFaculty.createTeacher(101, "Ivan", "Ivanov", "Ivanovich", "SEIT");
        testFaculty.createTeacher(101, "Petr", "Petrov", "Petrovich", "IIT");
    } catch (const DuplicateEntityException& ex) {
        std::cout << "  -> Caught DuplicateEntityException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 3] Attempting to fetch non-existent course with ID 999...\n";
        [[maybe_unused]] Course* nonExistent = testFaculty.getCourse(999);
    } catch (const EntityNotFoundException& ex) {
        std::cout << "  -> Caught EntityNotFoundException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 4] Attempting to assign 6th teacher to course exceeding limit 5...\n";
        Course* capacityCourse = testFaculty.createCourse(1, "Distributed Cloud Computing");
        for (int i = 1; i <= 6; ++i) {
            Teacher* t = testFaculty.createTeacher(500 + i, "Teacher" + std::to_string(i), "Test", "T", "SEIT");
            *capacityCourse += t;
        }
    } catch (const CapacityExceededException& ex) {
        std::cout << "  -> Caught CapacityExceededException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 5] Attempting to assign already assigned teacher to same course...\n";
        Course* duplicateCourse = testFaculty.createCourse(2, "Advanced C++");
        Teacher* assignedTeacher = testFaculty.createTeacher(601, "Sergey", "Smirnov", "Alexeevich", "SEIT");
        *duplicateCourse += assignedTeacher;
        *duplicateCourse += assignedTeacher;
    } catch (const DuplicateEntityException& ex) {
        std::cout << "  -> Caught DuplicateEntityException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 6] Attempting to remove teacher from course where they are not assigned...\n";
        Course* mathCourse = testFaculty.createCourse(3, "Calculus");
        *mathCourse -= 888;
    } catch (const EntityNotFoundException& ex) {
        std::cout << "  -> Caught EntityNotFoundException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 7] Attempting out-of-bounds access on Collection at index 99...\n";
        Collection<int> testColl;
        testColl.add(100);
        [[maybe_unused]] int val = testColl.get(99);
    } catch (const IndexOutOfBoundsException& ex) {
        std::cout << "  -> Caught IndexOutOfBoundsException: " << ex.what() << "\n";
    }

    try {
        std::cout << "\n[Test 8] Attempting to create LabActivity with invalid minimum passing score (15 > 10)...\n";
        Teacher* labTeacher = testFaculty.findTeacher(601);
        LabActivity invalidLab(16, labTeacher, 10, 15);
    } catch (const InvalidInputDataException& ex) {
        std::cout << "  -> Caught InvalidInputDataException: " << ex.what() << "\n";
    }

    std::cout << "\nAll exception scenarios caught and processed safely without system crash.\n";
}

int main() {
    demonstrateTemplates();
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
