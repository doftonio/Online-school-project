#include "../Header files/student.h"
#include <iostream>

void Student::initStudent(int id, std::string_view name)
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

void Student::setStudentName(std::string_view name)
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
    std::cout << "Student: " << studentName
        << ", Student ID: " << studentId
        << ", completed tasks: " << completedTasks << std::endl;
}