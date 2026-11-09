#ifndef PRACTICE_ACTIVITY_H
#define PRACTICE_ACTIVITY_H

#include "courseActivity.h"

class PracticeActivity : public CourseActivity {
private:
    int testsCount{0};
    int tasksCount{0};
    int calculationsCount{0};

public:
    PracticeActivity() = default;
    PracticeActivity(int lessons, Teacher* assignedTeacher, int tests, int practicals, int calculations);

    ActivityType getType() const noexcept override { return ActivityType::Practice; }
    int calculateHours() const override { return getLessonsCount() * 2; }

    void printDetails() const override;
};

#endif
