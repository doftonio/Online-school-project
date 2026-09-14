#include "../Header files/student.h"
#include <iostream>

Student::Student()
{
    studentId = 0;
    studentName = "";
    completedTasks = 0;
}

void Student::initStudent(int id, std::string name)
{
    studentId = id;
    studentName = name;
    completedTasks = 0;
}

int Student::getStudentId()
{
    return studentId;
}

std::string Student::getStudentName()
{
    return studentName;
}

int Student::getCompletedTasks()
{
    return completedTasks;
}

void Student::setStudentName(std::string name)
{
    studentName = name;
}

void Student::completeTask()
{
    completedTasks++;
}

void Student::resetTasks()
{
    completedTasks = 0;
}

void Student::printInfo()
{
    std::cout << "Student: \033[36m" << studentName << "\033[0m"
        << ", Student ID: " << studentId
        << ", completed tasks: \033[32m" << completedTasks << "\033[0m" << std::endl;
}
