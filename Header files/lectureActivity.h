#ifndef LECTURE_ACTIVITY_H
#define LECTURE_ACTIVITY_H

#include "courseActivity.h"

class LectureActivity : public CourseActivity {
private:
    int topicsCount{0};
    int hours{0};

public:
    LectureActivity(int lessons, Teacher* assignedTeacher, int topics, int lectureHrs)
        : CourseActivity("Лекция", lessons, assignedTeacher), topicsCount(topics), hours(lectureHrs) {}

    [[nodiscard]] ActivityType getType() const noexcept override { return ActivityType::Lecture; }
    [[nodiscard]] int calculateHours() const override { return hours; }

    [[nodiscard]] int calculateSelfStudyHours(double selfStudyRatio = 1.5) const noexcept {
        return (hours <= 0) ? 0 : static_cast<int>(hours * selfStudyRatio);
    }

    void printDetails() const override;
};

#endif // LECTURE_ACTIVITY_H
