#include "../Header files/practiceActivity.h"
#include "../Header files/teacher.h"
#include <iostream>
#include <format>

void PracticeActivity::addGradeForStudent(int /*studentId*/, const Grade& /*grade*/) const {
    // Compatibility stub: grade storage is handled by CourseGradeBook
}

bool PracticeActivity::removeGradeForStudentByDate(int /*studentId*/, const Date& /*date*/) const {
    return true;
}

void PracticeActivity::printJournal() const {
    std::cout << "Practice journal is empty.\n";
}

void PracticeActivity::printDetails() const {
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : std::format("ID: {}", getTeacherId());
    std::cout << "  [Practice] Lessons: " << getLessonsCount()
              << ", Tests: " << testsCount
              << ", Tasks: " << tasksCount
              << ", Calculations: " << calculationsCount
              << ", Teacher: " << teacherStr << "\n";
}
