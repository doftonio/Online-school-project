#include "../Header files/lectureActivity.h"
#include "../Header files/teacher.h"
#include <iostream>
#include <format>

LectureActivity::LectureActivity(int lessons, Teacher* assignedTeacher, int topics, int lectureHrs)
    : CourseActivity("Lecture", lessons, assignedTeacher), topicsCount(topics), hours(lectureHrs) {
    if (topics <= 0) {
        throw InvalidInputDataException(std::format("Topics count must be positive: provided {}", topics));
    }
    if (lectureHrs <= 0) {
        throw InvalidInputDataException(std::format("Lecture hours must be positive: provided {}", lectureHrs));
    }
}

int LectureActivity::calculateSelfStudyHours(double selfStudyRatio) const {
    if (selfStudyRatio <= 0.0) {
        throw InvalidInputDataException("Self-study ratio must be positive.");
    }
    return static_cast<int>(hours * selfStudyRatio);
}

void LectureActivity::printDetails() const {
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : "None";
    std::cout << "  [Lecture] Lessons: " << getLessonsCount()
              << ", Topics: " << topicsCount
              << ", Hours: " << hours
              << ", Teacher: " << teacherStr << "\n";
}
