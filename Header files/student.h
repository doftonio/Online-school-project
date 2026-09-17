#pragma once
#include <string>

class Student {
private:
    int studentId;
    std::string studentName;
    int completedTasks;

public:
    Student();

    void initStudent(int id, const std::string& name);
    int getStudentId() const;
    std::string getStudentName() const;
    int getCompletedTasks() const;

    void setStudentName(const std::string& name);
    void completeTask();
    void resetTasks();

    void printInfo() const;
};