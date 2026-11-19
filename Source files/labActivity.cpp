#include "../Header files/labActivity.h"
#include "../Header files/teacher.h"
#include <iostream>
#include <format>

LabActivity::LabActivity(int lessons, Teacher* assignedTeacher, int labsCount, int minScore)
    : CourseActivity("Lab", lessons, assignedTeacher), count(labsCount), minPassingScore(minScore) {
    if (labsCount <= 0) {
        throw InvalidInputDataException(std::format("Labs count must be positive: provided {}", labsCount));
    }
    if (minScore < 0 || minScore > 10) {
        throw InvalidInputDataException(std::format("Minimum passing score must be between 0 and 10: provided {}", minScore));
    }
}

void LabActivity::printDetails() const {
    const std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : "None";
    std::cout << "  [Lab] Lessons: " << getLessonsCount()
              << ", Total labs: " << count
              << ", Min passing score: " << minPassingScore
              << ", Teacher: " << teacherStr << "\n";
}

std::string LabActivity::serializeRecord(int courseId) const {
    const int teacherId = getTeacher() ? getTeacher()->getId() : 0;
    return std::format("ACTIVITY|{}|LAB|{}|{}|{}|{}",
                       courseId, getLessonsCount(), teacherId, count, minPassingScore);
}

std::string LabActivity::formatReportLine() const {
    const std::string teacherName = getTeacher() ? getTeacher()->getFullName() : "Unassigned";
    return std::format("    - [Lab] Lessons: {}, Labs: {}, Min Score: {}, Hours: {}, Teacher: {}",
                       getLessonsCount(), count, minPassingScore, calculateHours(), teacherName);
}
