#include "../Header files/student.h"
#include <iostream>

Student::Student()
    : studentId(0),
    studentName(""),
    completedTasks(0)
{
}

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
    std::cout << "Student: \o{33}[36m" << studentName << "\o{33}[0m"
        << ", Student ID: " << studentId
        << ", completed tasks: \o{33}[32m" << completedTasks << "\o{33}[0m" << std::endl;
}