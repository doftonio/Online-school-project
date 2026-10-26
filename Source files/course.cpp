#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include <iostream>

Course::Course(int courseId, std::string_view courseTitle)
    : id(courseId), title(courseTitle) {}

Course& Course::operator+=(Teacher* teacher) {
    if (!teacher) {
        std::cerr << "[Error] Cannot assign a null teacher to course \"" << title << "\".\n";
        return *this;
    }

    if (teachers.size() >= MAX_TEACHERS_PER_COURSE) {
        std::cerr << "[Constraint Violation] Capacity limit reached: Maximum "
                  << MAX_TEACHERS_PER_COURSE << " teachers allowed per course.\n";
        return *this;
    }

    if (teachers.find(teacher).has_value()) {
        std::cerr << "[Warning] Teacher [ID: " << teacher->getId()
                  << "] is already assigned to this course.\n";
        return *this;
    }

    teachers.add(teacher);
    return *this;
}

Course& Course::operator-=(Teacher* teacher) {
    if (!teacher) return *this;
    if (!teachers.remove(teacher)) {
        std::cerr << "[Warning] Teacher [ID: " << teacher->getId()
                  << "] was not found in course \"" << title << "\".\n";
    }
    return *this;
}

Course& Course::operator-=(int teacherId) {
    const auto predicate = [teacherId](const Teacher* t) {
        return t && t->getId() == teacherId;
    };
    if (const auto erasedCount = teachers.removeIf(predicate); erasedCount == 0) {
        std::cerr << "[Warning] Teacher with ID " << teacherId
                  << " was not found in course \"" << title << "\".\n";
    }
    return *this;
}

void Course::addActivity(std::unique_ptr<CourseActivity> activity) {
    if (activity) {
        activities.add(std::move(activity));
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
    std::cout << "\nCourse: " << title << " (ID: " << id << ")\nTeachers:\n";
    for (const auto* t : teachers) {
        if (t) std::cout << "  - " << t->getFullName() << " (" << t->getDepartment() << ")\n";
    }
    std::cout << "Course Activities:\n";
    for (const auto& act : activities) {
        if (act) act->printDetails();
    }
}
