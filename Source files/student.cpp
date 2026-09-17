#include "../Header files/student.h"
#include "../Header files/color.h"
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
    std::cout << "Student: " << Color::cyan << studentName << Color::reset
        << ", Student ID: " << studentId
        << ", completed tasks: " << Color::green << completedTasks << Color::reset << std::endl;
}