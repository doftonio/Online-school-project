#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include <compare>

class Student {
private:
    int studentId{ 0 };
    std::string studentName{};
    int completedTasks{ 0 };

public:
    Student() = default;
    Student(int id, std::string_view name, int tasks = 0)
        : studentId(id), studentName(name), completedTasks(tasks) {
    }

    void initStudent(int id, std::string_view name);
    int getStudentId() const;
    std::string getStudentName() const;
    int getCompletedTasks() const;

    void setStudentName(std::string_view name);
    void completeTask();
    void resetTasks();

    void printInfo() const;

    bool operator==(const Student& other) const;

    auto operator<=>(const Student& other) const
    {
        return completedTasks <=> other.completedTasks;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student)
    {
        os << "Student Name: " << student.studentName << "\n"
            << "Student ID: " << student.studentId << "\n"
            << "Completed tasks: " << student.completedTasks;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Student& student)
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

    friend void inspectStudentInternals(const Student& student);
};