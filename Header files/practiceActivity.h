#ifndef PRACTICE_ACTIVITY_H
#define PRACTICE_ACTIVITY_H

#include "courseActivity.h"
#include "grade.h"

class Faculty;
class StudyGroup;
class Student;
class Course;

class PracticeActivity : public CourseActivity {
private:
    int testsCount{0};
    int tasksCount{0};
    int calculationsCount{0};

public:
    PracticeActivity() = default;
    PracticeActivity(int lessons, Teacher* assignedTeacher, int tests, int practicals, int calculations)
        : CourseActivity("Practice", lessons, assignedTeacher),
          testsCount(tests), tasksCount(practicals), calculationsCount(calculations) {}

    PracticeActivity(int lessons, int assignedTeacherId, int tests, int practicals, int calculations)
        : CourseActivity("Practice", lessons, assignedTeacherId),
          testsCount(tests), tasksCount(practicals), calculationsCount(calculations) {}

    ActivityType getType() const noexcept override { return ActivityType::Practice; }
    int calculateHours() const override { return getLessonsCount() * 2; }

    void addGradeForStudent(int studentId, const Grade& grade) const;
    bool removeGradeForStudentByDate(int studentId, const Date& date) const;
    void printJournal() const;

    void printDetails() const override;
};

inline void printPracticeJournal(const auto&... /*args*/) {
    // Intentionally left empty: backward compatibility stub for legacy menu calls
}

#endif // PRACTICE_ACTIVITY_H
