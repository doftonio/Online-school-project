#include "../Header files/student.h"
#include <iostream>

void Student::initStudent(int id, const std::string& name)
{
    studentId = id;
    studentName = name;
    completedTasks = 0;
}

int Student::getStudentId() const
{
    return studentId;
}

std::string Student::getStudentName() const
{
    return studentName;
}

int Student::getCompletedTasks() const
{
    return completedTasks;
}

void Student::setStudentName(const std::string& name)
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

void Student::printInfo() const
{
    std::cout << "Student: \x1b[36m" << studentName << "\x1b[0m"
        << ", Student ID: " << studentId
        << ", completed tasks: \x1b[32m" << completedTasks << "\x1b[0m" << std::endl;
}