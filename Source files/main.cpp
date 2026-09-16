#include "../Header files/header.h"

void populateInitialData(CourseList& courseList)

    // Добавляем курсы через метод списка
    courseList.addCourse(1, "C++ Programming", "Alex Sidorov", 10, 2);
    courseList.addCourse(2, "Web Development", "Elena Kuznetsova", 8, 5);

   
    CourseNode* cppNode = courseList.getCoursePointerById(1);
    if (cppNode != nullpt)
    {
        cppNode->data.enrollSpletion(5583001);
        cppNode->data.recordTaskCompletion(5583001);
        cppNode->data.recordTaskCompletion(5583002);
    }

    CourseNode* webNode = courseList.getCoursePointerById(2);
    if (webNode != nullptr)
    {
        webNode->data.enrollStudent(55

void verifyBasicOperations()singleStudent;
    singleStudent.initStudent(101, "John Doe");
    singleStudent.printInfo();
    singleStudent.setStudentName("John Smith");
    std::cout << "Updated name: \033[36m" << singleStudent.getStudentName() << "\033[0m\n\n";
}

int main()
{
    verifyBasicOperations();

    CourseList courseList;

    std::cout << "\033[34mInitializing default courses and students through CourseList:\033[0m\n";
    populateInitialData(courseList);

    mainMenu(courseList);

    return 0;
