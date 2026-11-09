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
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : "None";
    std::cout << "  [Lab] Lessons: " << getLessonsCount()
              << ", Total labs: " << count
              << ", Min passing score: " << minPassingScore
              << ", Teacher: " << teacherStr << "\n";
}
