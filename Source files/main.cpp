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
    std::cout << "\x1b[34mVerifying basic object operations:\x1b[0m\n";
    Student singleStudent;
    singleStudent.initStudent(101, "John Doe");
    singleStudent.printInfo();
    singleStudent.setStudentName("John Smith");
    std::cout << "Updated name: \x1b[36m" << singleStudent.getStudentName() << "\x1b[0m\n\n";
}

int main()
{
    verifyBasicOperations();

    CourseList courseList;

    std::cout << "\x1b[34mInitializing default courses and students through CourseList:\x1b[0m\n";
    populateInitialData(courseList);

    mainMenu(courseList);

    return 0;
}