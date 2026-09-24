#pragma once
#include <string>
#include <string_view>
#include <iostream>

class Student {
private:
    int studentId{ 0 };
    std::string studentName{};
    int completedTasks{ 0 };

public:
    Student() = default;
    Student(int id, std::string_view name, int tasks = 0)
        : studentId(id), studentName(name), completedTasks(tasks) {}

    void initStudent(int id, std::string_view name);
    int getStudentId() const;
    std::string getStudentName() const;
    int getCompletedTasks() const;

    void setStudentName(std::string_view name);
    void completeTask();
    void resetTasks();

    void printInfo() const;

    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<(const Student& other) const;
    bool operator>=(const Student& other) const;
    bool operator<=(const Student& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    friend std::istream& operator>>(std::istream& is, Student& student);

    friend void inspectStudentInternals(const Student& student);
};