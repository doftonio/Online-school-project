#include "../Header files/practiceActivity.h"
#include "../Header files/teacher.h"
#include <iostream>

void PracticeActivity::printDetails() const {
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : "None";
    std::cout << "  [Practice] Lessons: " << getLessonsCount()
              << ", Tests: " << testsCount
              << ", Tasks: " << tasksCount
              << ", Calculations: " << calculationsCount
              << ", Teacher: " << teacherStr << "\n";
}
