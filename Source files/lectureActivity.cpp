#include "lectureActivity.h"
#include "teacher.h"
#include <iostream>

void LectureActivity::printDetails() const {
    std::cout << "  [Лекция] Занятий: " << getLessonsCount()
              << ", Темы: " << topicsCount
              << ", Часы: " << hours
              << ", Преподаватель: " << (getTeacher() ? getTeacher()->getFullName() : "Не назначен") << "\n";
}
