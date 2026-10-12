#pragma once
#include "courseActivity.h"
#include "studentContainers.h"
#include <vector>
#include <iostream>

class LabActivity : public CourseActivity {
private:
    int count{ 0 };
    int minPassingScore{ 4 };
    std::vector<StudentLabGradesContainer> journal{};

public:
    LabActivity(int lessons, int assignedTeacher, int labsCount, int minScore);

    [[nodiscard]] ActivityType getType() const override;
    [[nodiscard]] int getCount() const;
    [[nodiscard]] int getMinPassingScore() const;

    void addGradeForStudent(int studentId, const LabGrade& grade);
    bool removeGradeForStudentByDate(int studentId, const Date& date);
    [[nodiscard]] double getGroupAverageScore() const;

    void printDetails() const override;
    friend void printLabJournal(std::ostream& os, const LabActivity& activity);
};