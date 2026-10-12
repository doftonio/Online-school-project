#pragma once
#include "courseActivity.h"

class LectureActivity : public CourseActivity {
private:
    int topicsCount{ 0 };
    int hours{ 0 };

public:
    LectureActivity(int lessons, int assignedTeacher, int topics, int lectureHrs);

    ActivityType getType() const override;
    int calculateHours() const override;
    void printDetails() const override;
};