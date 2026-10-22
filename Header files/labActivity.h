#ifndef LAB_ACTIVITY_H
#define LAB_ACTIVITY_H

#include "courseActivity.h"

class LabActivity : public CourseActivity {
private:
    int count{0};
    int minPassingScore{4};

public:
    LabActivity(int lessons, Teacher* assignedTeacher, int labsCount, int minScore)
        : CourseActivity("Лабораторная работа", lessons, assignedTeacher), count(labsCount), minPassingScore(minScore) {}

    [[nodiscard]] ActivityType getType() const noexcept override { return ActivityType::Lab; }
    [[nodiscard]] int calculateHours() const override { return lessonsCount * 2; }
    [[nodiscard]] int getCount() const noexcept { return count; }
    [[nodiscard]] int getMinPassingScore() const noexcept { return minPassingScore; }

    void printDetails() const override;
};

#endif // LAB_ACTIVITY_H
