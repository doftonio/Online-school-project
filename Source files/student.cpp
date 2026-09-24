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

bool Student::operator==(const Student& other) const
{
    return studentId == other.studentId;
}

bool Student::operator!=(const Student& other) const
{
    return studentId != other.studentId;
}

bool Student::operator<(const Student& other) const
{
    return completedTasks < other.completedTasks;
}

bool Student::operator>(const Student& other) const
{
    return completedTasks > other.completedTasks;
}

bool Student::operator<=(const Student& other) const
{
    return completedTasks <= other.completedTasks;
}

bool Student::operator>=(const Student& other) const
{
    return completedTasks >= other.completedTasks;
}

std::ostream& operator<<(std::ostream& os, const Student& student)
{
    os << "Student Name: " << student.studentName << "\n"
        << "Student ID: " << student.studentId << "\n"
        << "Completed tasks: " << student.completedTasks;
    return os;
}

std::istream& operator>>(std::istream& is, Student& student)
{
    std::cout << "Enter student ID: ";
    is >> student.studentId;
    is.ignore();
    std::cout << "Enter student name: ";
    std::getline(is, student.studentName);
    std::cout << "Enter completed tasks count: ";
    is >> student.completedTasks;
    return is;
}

void inspectStudentInternals(const Student& student)
{
    std::cout << "[Friend Function inspectStudentInternals] Direct access to private members:\n"
        << "  studentId: " << student.studentId
        << ", studentName: " << student.studentName
        << ", completedTasks: " << student.completedTasks << std::endl;
}