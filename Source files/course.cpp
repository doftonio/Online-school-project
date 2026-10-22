#include "../Header files/course.h"
#include "../Header files/teacher.h"
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

Course& Course::operator-=(int teacherId) {
    std::erase_if(teachers, [teacherId](const Teacher* t) {
        return t && t->getId() == teacherId;
    });
    return *this;
}

void Course::addActivity(std::unique_ptr<CourseActivity> activity) {
    if (activity) {
        activities.push_back(std::move(activity));
    }
}

void Course::addActivityForGroup(std::string_view /*groupNumber*/, std::unique_ptr<CourseActivity> activity) {
    addActivity(std::move(activity));
}

CourseActivity* Course::findActivity(ActivityType type) const {
    for (const std::unique_ptr<CourseActivity>& act : activities) {
        if (act && act->getType() == type) {
            return act.get();
        }
    }
    return nullptr;
}

CourseActivity* Course::findActivity(std::string_view /*groupNumber*/, ActivityType type) const {
    return findActivity(type);
}

void Course::printFullCourseInfo() const {
    std::cout << "\nCourse: " << title << " (ID: " << id << ")\nTeachers:\n";
    for (const Teacher* t : teachers) {
        if (t) std::cout << "  - " << t->getFullName() << " (" << t->getDepartment() << ")\n";
    }
    std::cout << "Course Activities:\n";
    for (const std::unique_ptr<CourseActivity>& act : activities) {
        if (act) act->printDetails();
    }
}
