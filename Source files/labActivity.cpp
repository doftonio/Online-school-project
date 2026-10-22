#include "labActivity.h"
#include "teacher.h"
#include <iostream>

void LabActivity::printDetails() const {
    std::cout << "  [Лабораторная] Занятий: " << lessonsCount
              << ", Всего работ: " << count
              << ", Мин. проходной балл: " << minPassingScore
              << ", Преподаватель: " << (teacher ? teacher->getFullName() : "Не назначен") << "\n";
}
