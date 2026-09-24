#include "../Header files/header.h"

void populateInitialData(CourseList& courseList)
{
    courseList.addCourse(1, "C++ Programming", "Alex Sidorov", 10, 2);
    courseList.addCourse(2, "Web Development", "Elena Kuznetsova", 8, 5);

    if (CourseNode* cppNode = courseList.getCoursePointerById(1))
    {
        cppNode->data.enrollStudent(5583001, "John Smith");
        cppNode->data.enrollStudent(5583002, "Anna Smirnova");
        cppNode->data.enrollStudent(5583003, "Paul Kovalev");

        cppNode->data.recordTaskCompletion(5583001);
        cppNode->data.recordTaskCompletion(5583001);
        cppNode->data.recordTaskCompletion(5583002);
    }

    if (CourseNode* webNode = courseList.getCoursePointerById(2))
    {
        webNode->data.enrollStudent(5583001, "Anna Smirnova");
        webNode->data.enrollStudent(5583003, "Paul Kovalev");

        webNode->data.recordTaskCompletion(5583003);
    }
}

void verifyBasicOperations()
{
    std::cout << "=========================================================\n";
    std::cout << "DEMONSTRATION OF OVERLOADED OPERATORS & FRIEND FUNCTION\n";
    std::cout << "=========================================================\n\n";

    std::cout << "--- 1. Overloaded Output Operator (<<) & Equality (==, !=) ---\n";
    Student s1(5583001, "John Smith", 6);
    Student s2(5583001, "John Smith (Duplicate ID)", 2);
    Student s3(5583002, "Anna Smirnova", 8);

    std::cout << "Student 1:\n" << s1 << "\n\n";
    std::cout << "Student 2:\n" << s2 << "\n\n";
    std::cout << "Student 3:\n" << s3 << "\n\n";

    std::cout << "Checking s1 == s2 (same ID 5583001): " << (s1 == s2) << "\n";
    std::cout << "Checking s1 == s3 (different IDs):   " << (s1 == s3) << "\n";
    std::cout << "Checking s1 != s3:                   " << (s1 != s3) << "\n\n";

    std::cout << "--- 2. Relational Operators (<, >, <=, >=) based on Completed Tasks ---\n";
    std::cout << "s1 tasks: " << s1.getCompletedTasks() << ", s3 tasks: " << s3.getCompletedTasks() << "\n";
    std::cout << "s1 > s3 : " << (s1 > s3) << "\n";
    std::cout << "s1 < s3 : " << (s1 < s3) << "\n";
    std::cout << "s1 >= s3: " << (s1 >= s3) << "\n";
    std::cout << "s1 <= s3: " << (s1 <= s3) << "\n\n";

    std::cout << "--- 3. Friend Function Demonstration ---\n";
    inspectStudentInternals(s1);
    std::cout << "\n";

    std::cout << "--- 4. Overloaded Operators += and -= for Course with Student & Limit Control ---\n";
    Course testCourse;
    testCourse.initCourse(10, "Software Engineering", "Dr. Miller", 12, 2);

    std::cout << "Enrolling students using operator+= (max capacity = 2):\n";
    testCourse += s1;
    testCourse += s3;

    Student s4(5583004, "David Brown", 3);
    std::cout << "Attempting to enroll 3rd student (exceeding limit):\n";
    testCourse += s4;

    std::cout << "\nCourse status after enrollments:\n";
    testCourse.printFullCourseInfo();

    std::cout << "Removing student using operator-=:\n";
    testCourse -= s1;

    std::cout << "Attempting to enroll s4 after a spot was freed:\n";
    testCourse += s4;

    std::cout << "\nFinal course status:\n";
    testCourse.printFullCourseInfo();
    std::cout << "=========================================================\n\n";
}

int main()
{
    verifyBasicOperations();

    CourseList courseList;

    std::cout << "Initializing default courses and students through CourseList:\n";
    populateInitialData(courseList);

    mainMenu(courseList);

    return 0;
}