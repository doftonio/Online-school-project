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
    int getTestsCount() const noexcept { return testsCount; }
    int getTasksCount() const noexcept { return tasksCount; }
    int getCalculationsCount() const noexcept { return calculationsCount; }

    void printDetails() const override;
    std::string serializeRecord(int courseId) const override;
    std::string formatReportLine() const override;
};

#endif
