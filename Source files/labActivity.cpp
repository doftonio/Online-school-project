#include "../Header files/labActivity.h"
#include "../Header files/teacher.h"
#include <iostream>

void LabActivity::addGradeForStudent(int /*studentId*/, const Grade& /*grade*/) {
}

bool LabActivity::removeGradeForStudentByDate(int /*studentId*/, const Date& /*date*/) {
    return true;
}

void LabActivity::printJournal() const {
    std::cout << "Lab journal is empty.\n";
}

void LabActivity::printDetails() const {
    std::cout << "  [Lab] Lessons: " << getLessonsCount()
              << ", Total labs: " << count
              << ", Min passing score: " << minPassingScore
              << ", Teacher: " << (getTeacher() ? getTeacher()->getFullName() : "ID: " + std::to_string(getTeacherId())) << "\n";
}
