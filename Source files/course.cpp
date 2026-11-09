#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include <iostream>
#include <format>

Course::Course(int courseId, std::string_view courseTitle)
    : id(courseId), title(courseTitle) {
    if (courseId <= 0) {
        throw InvalidInputDataException(std::format("Course ID must be positive: provided {}", courseId));
    }
    if (courseTitle.empty()) {
        throw InvalidInputDataException("Course title cannot be empty.");
    }
}

Course& Course::operator+=(Teacher* teacher) {
    if (!teacher) {
        throw InvalidInputDataException(std::format("Cannot assign null teacher pointer to course \"{}\".", title));
    }

    if (teachers.size() >= MAX_TEACHERS_PER_COURSE) {
        throw CapacityExceededException(std::format(
            "Capacity limit reached: Maximum {} teachers allowed for course \"{}\".",
            MAX_TEACHERS_PER_COURSE, title));
    }

    if (teachers.find(teacher).has_value()) {
        throw DuplicateEntityException(std::format(
            "Teacher [ID: {}] is already assigned to course \"{}\".",
            teacher->getId(), title));
    }

    teachers.add(teacher);
    return *this;
}

Course& Course::operator-=(Teacher* teacher) {
    if (!teacher) {
        throw InvalidInputDataException(std::format("Cannot remove null teacher pointer from course \"{}\".", title));
    }
    if (!teachers.remove(teacher)) {
        throw EntityNotFoundException(std::format(
            "Teacher [ID: {}] is not assigned to course \"{}\".",
            teacher->getId(), title));
    }
    return *this;
}

Course& Course::operator-=(int teacherId) {
    if (teacherId <= 0) {
        throw InvalidInputDataException(std::format("Teacher ID must be positive: provided {}", teacherId));
    }
    const auto predicate = [teacherId](const Teacher* t) {
        return t && t->getId() == teacherId;
    };
    if (const auto erasedCount = teachers.removeIf(predicate); erasedCount == 0) {
        throw EntityNotFoundException(std::format(
            "Teacher with ID {} is not assigned to course \"{}\".",
            teacherId, title));
    }
    return *this;
}

void Course::addActivity(std::unique_ptr<CourseActivity> activity) {
    if (!activity) {
        throw InvalidInputDataException(std::format("Cannot add null activity to course \"{}\".", title));
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
