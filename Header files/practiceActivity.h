#pragma once
#include "courseActivity.h"
#include "studentContainers.h"
#include <vector>
#include <iostream>

class PracticeActivity : public CourseActivity {
private:
    int testsCount{ 0 };
    int tasksCount{ 0 };
    int calculationsCount{ 0 };
    std::vector<StudentPracticeGradesContainer> journal{};

public:
    PracticeActivity(int lessons, int assignedTeacher, int tests, int practicals, int calculations);

    [[nodiscard]] ActivityType getType() const override;
    [[nodiscard]] int calculateHours() const override;
    void printDetails() const override;

    void addGradeForStudent(int studentId, const PracticeGrade& grade);
    bool removeGradeForStudentByDate(int studentId, const Date& date);
    [[nodiscard]] double getGroupAverageScore() const;

    friend void printPracticeJournal(std::ostream& os, const PracticeActivity& activity);
};