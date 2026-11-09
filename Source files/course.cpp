#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include <iostream>

Course::Course(int courseId, std::string_view courseTitle)
    : id(courseId), title(courseTitle) {
    if (courseId <= 0) {
        throw InvalidInputDataException("Course ID must be positive: provided " + std::to_string(courseId));
    }
    if (courseTitle.empty()) {
        throw InvalidInputDataException("Course title cannot be empty.");
    }
}

Course& Course::operator+=(Teacher* teacher) {
    if (!teacher) {
        throw InvalidInputDataException("Cannot assign null teacher pointer to course \"" + title + "\".");
    }

    if (teachers.size() >= MAX_TEACHERS_PER_COURSE) {
        throw CapacityExceededException("Capacity limit reached: Maximum " +
            std::to_string(MAX_TEACHERS_PER_COURSE) + " teachers allowed for course \"" + title + "\".");
    }

    if (teachers.find(teacher).has_value()) {
        throw DuplicateEntityException("Teacher [ID: " + std::to_string(teacher->getId()) +
            "] is already assigned to course \"" + title + "\".");
    }

    teachers.add(teacher);
    return *this;
}

Course& Course::operator-=(Teacher* teacher) {
    if (!teacher) {
        throw InvalidInputDataException("Cannot remove null teacher pointer from course \"" + title + "\".");
    }
    if (!teachers.remove(teacher)) {
        throw EntityNotFoundException("Teacher [ID: " + std::to_string(teacher->getId()) +
            "] is not assigned to course \"" + title + "\".");
    }
    return *this;
}

Course& Course::operator-=(int teacherId) {
    if (teacherId <= 0) {
        throw InvalidInputDataException("Teacher ID must be positive: provided " + std::to_string(teacherId));
    }
    const auto predicate = [teacherId](const Teacher* t) {
        return t && t->getId() == teacherId;
    };
    if (const auto erasedCount = teachers.removeIf(predicate); erasedCount == 0) {
        throw EntityNotFoundException("Teacher with ID " + std::to_string(teacherId) +
            " is not assigned to course \"" + title + "\".");
    }
    return *this;
}

void Course::addActivity(std::unique_ptr<CourseActivity> activity) {
    if (!activity) {
        throw InvalidInputDataException("Cannot add null activity to course \"" + title + "\".");
    }
    activities.add(std::move(activity));
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
