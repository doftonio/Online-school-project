#pragma once
#include "labGrade.h"
#include "practiceGrade.h"
#include <vector>
#include <iostream>

class StudentLabGradesContainer {
private:
    int studentId{ 0 };
    std::vector<LabGrade> grades{};

public:
    explicit StudentLabGradesContainer(int id);

    int getStudentId() const;
    const std::vector<LabGrade>& getGrades() const;

    void addGrade(const LabGrade& grade);
    bool removeGradeByDate(const Date& targetDate);
    double getAverageScore() const;

    friend std::ostream& operator<<(std::ostream& os, const StudentLabGradesContainer& c) {
        os << "ID " << c.studentId << " | ќценки: ";
        if (c.grades.empty()) {
            os << "нет";
        }
        else {
            for (const auto& g : c.grades) os << g << " ";
        }
        os << " | —р. балл: " << c.getAverageScore();
        return os;
    }
};

class StudentPracticeGradesContainer {
private:
    int studentId{ 0 };
    std::vector<PracticeGrade> grades{};

public:
    explicit StudentPracticeGradesContainer(int id);

    int getStudentId() const;
    const std::vector<PracticeGrade>& getGrades() const;

    void addGrade(const PracticeGrade& grade);
    bool removeGradeByDate(const Date& targetDate);
    double getAverageScore() const;

    friend std::ostream& operator<<(std::ostream& os, const StudentPracticeGradesContainer& c) {
        os << "ID " << c.studentId << " | ќценки: ";
        if (c.grades.empty()) {
            os << "нет";
        }
        else {
            for (const auto& g : c.grades) os << g << " ";
        }
        os << " | —р. балл: " << c.getAverageScore();
        return os;
    }
};