#ifndef LAB_ACTIVITY_H
#define LAB_ACTIVITY_H

#include "courseActivity.h"
#include "grade.h"

class Faculty;
class StudyGroup;
class Student;
class Course;

class LabActivity : public CourseActivity {
private:
    int count{0};
    int minPassingScore{4};

public:
    LabActivity() = default;
    LabActivity(int lessons, Teacher* assignedTeacher, int labsCount, int minScore)
        : CourseActivity("Lab", lessons, assignedTeacher), count(labsCount), minPassingScore(minScore) {}

    LabActivity(int lessons, int assignedTeacherId, int labsCount, int minScore)
        : CourseActivity("Lab", lessons, assignedTeacherId), count(labsCount), minPassingScore(minScore) {}

    ActivityType getType() const noexcept override { return ActivityType::Lab; }
    int calculateHours() const override { return getLessonsCount() * 2; }
    int getCount() const noexcept { return count; }
    int getMinPassingScore() const noexcept { return minPassingScore; }

    void addGradeForStudent(int studentId, const Grade& grade) const;
    bool removeGradeForStudentByDate(int studentId, const Date& date) const;
    void printJournal() const;

    void printDetails() const override;
};

inline void printLabJournal(const auto&... /*args*/) {
    // Compatibility stub for legacy menu calls
}

#endif // LAB_ACTIVITY_H
