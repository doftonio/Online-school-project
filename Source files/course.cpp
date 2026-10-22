#include "course.h"
#include "teacher.h"
#include <iostream>
#include <algorithm>

Course::Course(int courseId, std::string_view courseTitle)
    : id(courseId), title(courseTitle) {}

Course& Course::operator+=(Teacher* teacher) {
    if (teacher && std::ranges::find(teachers, teacher) == teachers.end()) {
        teachers.push_back(teacher);
    }
    return *this;
}

Course& Course::operator-=(Teacher* teacher) {
    std::erase(teachers, teacher);
    return *this;
}

void Course::addActivity(std::unique_ptr<CourseActivity> activity) {
    if (activity) {
        activities.push_back(std::move(activity));
    }
}

CourseActivity* Course::findActivity(ActivityType type) const {
    for (const auto& act : activities) {
        if (act && act->getType() == type) {
            return act.get();
        }
    }
    return nullptr;
}

void Course::printFullCourseInfo() const {
    std::cout << "\nКурс: " << title << " (ID: " << id << ")\nПреподаватели:\n";
    for (const auto* t : teachers) {
        if (t) std::cout << "  - " << t->getFullName() << " (" << t->getDepartment() << ")\n";
    }
    std::cout << "Активности курса:\n";
    for (const auto& act : activities) {
        if (act) act->printDetails();
    }
}
