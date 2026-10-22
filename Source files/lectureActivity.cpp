#include "../Header files/lectureActivity.h"
#include "../Header files/teacher.h"
#include <iostream>
#include <format>

void LectureActivity::printDetails() const {
    std::string teacherStr = getTeacher() ? getTeacher()->getFullName() : std::format("ID: {}", getTeacherId());
    std::cout << "  [Lecture] Lessons: " << getLessonsCount()
              << ", Topics: " << topicsCount
              << ", Hours: " << hours
              << ", Teacher: " << teacherStr << "\n";
}
