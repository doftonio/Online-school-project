#pragma once
#include "courseActivity.h"

class LectureActivity : public CourseActivity {
private:
    int topicsCount{ 0 };
    int hours{ 0 };

public:
    LectureActivity(int lessons, int assignedTeacher, int topics, int lectureHrs);

    [[nodiscard]] ActivityType getType() const override;
    [[nodiscard]] int calculateHours() const override;
    void printDetails() const override;
};