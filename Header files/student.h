#pragma once
#include <string>
#include <string_view>

class Student {
private:
    int studentId{ 0 };
    std::string studentName{};
    int completedTasks{ 0 };

public:
    Student() = default;

    void initStudent(int id, std::string_view name);
    int getStudentId() const;
    std::string getStudentName() const;
    int getCompletedTasks() const;

    void setStudentName(std::string_view name);
    void completeTask();
    void resetTasks();

    void printInfo() const;
};