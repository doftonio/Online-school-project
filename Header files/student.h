#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <compare>
#include <string_view>
#include <iostream>

class Student : public Person {
private:
    int id{0};
    int completedTasks{0};

public:
    Student() = default;
    Student(int studentId, std::string_view first, std::string_view last, std::string_view middle, int tasks = 0);

    int getId() const noexcept { return id; }
    int getCompletedTasks() const noexcept { return completedTasks; }
    void completeTask() noexcept { ++completedTasks; }
    void setCompletedTasks(int tasks) noexcept { completedTasks = tasks; }

    bool checkExamEligibility(int requiredTasksThreshold) const noexcept {
        return completedTasks >= requiredTasksThreshold;
    }

    void printInfo() const override;

    void inspectStudentInternals(const Student& other) const;

    bool operator==(const Student& other) const noexcept { return id == other.id; }
    auto operator<=>(const Student& other) const noexcept { return id <=> other.id; }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Student [ID: " << student.getId() << "] " << student.getFullName()
           << " | Completed tasks: " << student.getCompletedTasks();
        return os;
    }
};

void inspectStudentInternals(const Student& s);
void inspectStudentInternals(const Student& s1, const Student& s2);

#endif // STUDENT_H
