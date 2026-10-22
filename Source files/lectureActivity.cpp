#include "../Header files/lectureActivity.h"
#include "../Header files/teacher.h"
#include <iostream>

void LectureActivity::printDetails() const {
    std::cout << "  [Lecture] Lessons: " << getLessonsCount()
              << ", Topics: " << topicsCount
              << ", Hours: " << hours
              << ", Teacher: " << (getTeacher() ? getTeacher()->getFullName() : "ID: " + std::to_string(getTeacherId())) << "\n";
}
