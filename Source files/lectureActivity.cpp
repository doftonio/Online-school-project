#include "lectureActivity.h"
#include "teacher.h"
#include <iostream>

void LectureActivity::printDetails() const {
    std::cout << "  [Лекция] Занятий: " << lessonsCount
              << ", Темы: " << topicsCount
              << ", Часы: " << hours
              << ", Преподаватель: " << (teacher ? teacher->getFullName() : "Не назначен") << "\n";
}
