#include "../Header files/practiceActivity.h"
#include "../Header files/teacher.h"
#include <iostream>

void PracticeActivity::addGradeForStudent(int /*studentId*/, const Grade& /*grade*/) {
}

bool PracticeActivity::removeGradeForStudentByDate(int /*studentId*/, const Date& /*date*/) {
    return true;
}

void PracticeActivity::printJournal() const {
    std::cout << "Practice journal is empty.\n";
}

void PracticeActivity::printDetails() const {
    std::cout << "  [Practice] Lessons: " << getLessonsCount()
              << ", Tests: " << testsCount
              << ", Tasks: " << tasksCount
              << ", Calculations: " << calculationsCount
              << ", Teacher: " << (getTeacher() ? getTeacher()->getFullName() : "ID: " + std::to_string(getTeacherId())) << "\n";
}
