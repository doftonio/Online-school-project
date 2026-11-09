#include "../Header files/practiceActivity.h"
#include "../Header files/teacher.h"
#include <iostream>

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
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : "None";
    std::cout << "  [Practice] Lessons: " << getLessonsCount()
              << ", Tests: " << testsCount
              << ", Tasks: " << tasksCount
              << ", Calculations: " << calculationsCount
              << ", Teacher: " << teacherStr << "\n";
}
