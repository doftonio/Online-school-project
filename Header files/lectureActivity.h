#ifndef LECTURE_ACTIVITY_H
#define LECTURE_ACTIVITY_H

#include "courseActivity.h"

class LectureActivity : public CourseActivity {
private:
    int topicsCount{0};
    int hours{0};

public:
    LectureActivity(int lessons, Teacher* assignedTeacher, int topics, int lectureHrs);

    ActivityType getType() const noexcept override { return ActivityType::Lecture; }
    int calculateHours() const override { return hours; }
    int calculateSelfStudyHours() const override;
    int getTopicsCount() const noexcept { return topicsCount; }

    int calculateSelfStudyHoursWithRatio(double selfStudyRatio) const;

    void printDetails() const override;
    std::string serializeRecord(int courseId) const override;
    std::string formatReportLine() const override;
};

#endif
