#include "practiceActivity.h"
#include "teacher.h"
#include <iostream>

void PracticeActivity::printDetails() const {
    std::cout << "  [Практика] Занятий: " << lessonsCount
              << ", Тестов: " << testsCount
              << ", Задач: " << tasksCount
              << ", Расчетов: " << calculationsCount
              << ", Преподаватель: " << (teacher ? teacher->getFullName() : "Не назначен") << "\n";
}
