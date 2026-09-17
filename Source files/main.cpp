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
    std::cout << "Verifying basic object operations:\n";
    Student singleStudent;
    singleStudent.initStudent(101, "John Doe");
    singleStudent.printInfo();
    singleStudent.setStudentName("John Smith");
    std::cout << "Updated name: " << singleStudent.getStudentName() << "\n\n";
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