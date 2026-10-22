#include "labActivity.h"
#include "teacher.h"
#include <iostream>

void LabActivity::printDetails() const {
    std::cout << "  [Лабораторная] Занятий: " << getLessonsCount()
              << ", Всего работ: " << count
              << ", Мин. проходной балл: " << minPassingScore
              << ", Преподаватель: " << (getTeacher() ? getTeacher()->getFullName() : "Не назначен") << "\n";
}
