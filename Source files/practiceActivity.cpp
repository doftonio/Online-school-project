#include "../Header files/practiceActivity.h"
#include "../Header files/teacher.h"
#include <iostream>
#include <format>

PracticeActivity::PracticeActivity(int lessons, Teacher* assignedTeacher, int tests, int practicals, int calculations)
    : CourseActivity("Practice", lessons, assignedTeacher),
      testsCount(tests), tasksCount(practicals), calculationsCount(calculations) {
    if (tests < 0 || practicals < 0 || calculations < 0) {
        throw InvalidInputDataException("Practice tasks counts cannot be negative.");
    }
    if (tests + practicals + calculations == 0) {
        throw InvalidInputDataException("Practice activity must have at least one test, task or calculation.");
    }
}

void PracticeActivity::printDetails() const {
    const std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : "None";
    std::cout << "  [Practice] Lessons: " << getLessonsCount()
              << ", Tests: " << testsCount
              << ", Tasks: " << tasksCount
              << ", Calculations: " << calculationsCount
              << ", Teacher: " << teacherStr << "\n";
}

std::string PracticeActivity::serializeRecord(int courseId) const {
    const int teacherId = getTeacher() ? getTeacher()->getId() : 0;
    return std::format("ACTIVITY|{}|PRACTICE|{}|{}|{}|{}|{}",
                       courseId, getLessonsCount(), teacherId,
                       testsCount, tasksCount, calculationsCount);
}

std::string PracticeActivity::formatReportLine() const {
    const std::string teacherName = getTeacher() ? getTeacher()->getFullName() : "Unassigned";
    return std::format("    - [Practice] Lessons: {}, Tests: {}, Tasks: {}, Calcs: {}, Hours: {}, Teacher: {}",
                       getLessonsCount(), testsCount, tasksCount, calculationsCount, calculateHours(), teacherName);
}
