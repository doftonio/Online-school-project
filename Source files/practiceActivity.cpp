#include "practiceActivity.h"
#include "teacher.h"
#include <iostream>

void PracticeActivity::printDetails() const {
    std::cout << "  [Практика] Занятий: " << getLessonsCount()
              << ", Тестов: " << testsCount
              << ", Задач: " << tasksCount
              << ", Расчетов: " << calculationsCount
              << ", Преподаватель: " << (getTeacher() ? getTeacher()->getFullName() : "Не назначен") << "\n";
}
