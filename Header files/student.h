#pragma once
#include <string>

class Student {
private:
    int studentId{ 0 };
    std::string studentName{};
    int completedTasks{ 0 };

public:
    Student() = default;

    void initStudent(int id, const std::string& name);
    int getStudentId() const;
    std::string getStudentName() const;
    int getCompletedTasks() const;

    void setStudentName(const std::string& name);
    void completeTask();
    void resetTasks();

    void printInfo() const;
};