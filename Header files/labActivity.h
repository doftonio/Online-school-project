#ifndef LAB_ACTIVITY_H
#define LAB_ACTIVITY_H

#include "courseActivity.h"

class LabActivity : public CourseActivity {
private:
    int count{0};
    int minPassingScore{4};

public:
    LabActivity() = default;
    LabActivity(int lessons, Teacher* assignedTeacher, int labsCount, int minScore)
        : CourseActivity("Lab", lessons, assignedTeacher), count(labsCount), minPassingScore(minScore) {}

    ActivityType getType() const noexcept override { return ActivityType::Lab; }
    int calculateHours() const override { return getLessonsCount() * 2; }
    int getCount() const noexcept { return count; }
    int getMinPassingScore() const noexcept { return minPassingScore; }

    void printDetails() const override;
};

#endif // LAB_ACTIVITY_H
