#include "../Header files/labActivity.h"
#include "../Header files/teacher.h"
#include <iostream>

void LabActivity::printDetails() const {
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : "None";
    std::cout << "  [Lab] Lessons: " << getLessonsCount()
              << ", Total labs: " << count
              << ", Min passing score: " << minPassingScore
              << ", Teacher: " << teacherStr << "\n";
}
