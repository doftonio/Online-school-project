#include "../Header files/labActivity.h"
#include "../Header files/teacher.h"
#include <iostream>
#include <format>

void LabActivity::addGradeForStudent(int /*studentId*/, const Grade& /*grade*/) const {
    // Compatibility stub: grade storage is handled by CourseGradeBook
}

bool LabActivity::removeGradeForStudentByDate(int /*studentId*/, const Date& /*date*/) const {
    return true;
}

void LabActivity::printJournal() const {
    std::cout << "Lab journal is empty.\n";
}

void LabActivity::printDetails() const {
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : std::format("ID: {}", getTeacherId());
    std::cout << "  [Lab] Lessons: " << getLessonsCount()
              << ", Total labs: " << count
              << ", Min passing score: " << minPassingScore
              << ", Teacher: " << teacherStr << "\n";
}
