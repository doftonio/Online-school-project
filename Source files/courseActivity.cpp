#include "../Header files/courseActivity.h"
#include "../Header files/teacher.h"
#include <format>

CourseActivity::CourseActivity(std::string_view actTitle, int lessons, Teacher* assignedTeacher)
    : title(actTitle), lessonsCount(lessons), teacher(assignedTeacher) {
    if (actTitle.empty()) {
        throw InvalidInputDataException("Activity title cannot be empty.");
    }
    if (lessons <= 0) {
        throw InvalidInputDataException(std::format("Lessons count must be positive: provided {}", lessons));
    }
    if (!assignedTeacher) {
        throw InvalidInputDataException("Course activity must have an assigned teacher.");
    }
}

void CourseActivity::setTeacher(Teacher* t) {
    if (!t) {
        throw InvalidInputDataException("Cannot assign null teacher to activity.");
    }
    teacher = t;
}
