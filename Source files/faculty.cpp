#include "../Header files/faculty.h"
#include <iostream>
#include <format>

Faculty::Faculty(std::string_view facultyName) : name(facultyName) {
    if (facultyName.empty()) {
        throw InvalidInputDataException("Faculty name cannot be empty.");
    }
}

Teacher* Faculty::createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept) {
    if (id <= 0) {
        throw InvalidInputDataException(std::format("Teacher ID must be positive: provided {}", id));
    }
    if (findTeacher(id) != nullptr) {
        throw DuplicateEntityException(std::format("Teacher with ID {} already exists in faculty \"{}\".", id, name));
    }
    auto teacher = std::make_unique<Teacher>(id, first, last, middle, dept);
    Teacher* raw = teacher.get();
    allTeachers.add(std::move(teacher));
    return raw;
}

Course* Faculty::createCourse(int id, std::string_view title) {
    if (id <= 0) {
        throw InvalidInputDataException(std::format("Course ID must be positive: provided {}", id));
    }
    if (findCourse(id) != nullptr) {
        throw DuplicateEntityException(std::format("Course with ID {} already exists in faculty \"{}\".", id, name));
    }
    auto c = std::make_unique<Course>(id, title);
    Course* raw = c.get();
    allCourses.add(std::move(c));
    return raw;
}

Teacher* Faculty::findTeacher(int teacherId) const {
    if (teacherId <= 0) {
        return nullptr;
    }
    for (const auto& t : allTeachers) {
        if (t && t->getId() == teacherId) return t.get();
    }
    return nullptr;
}

Course* Faculty::findCourse(int courseId) const {
    if (courseId <= 0) {
        return nullptr;
    }
    for (const auto& c : allCourses) {
        if (c && c->getId() == courseId) return c.get();
    }
    return nullptr;
}

Teacher* Faculty::getTeacher(int teacherId) const {
    Teacher* t = findTeacher(teacherId);
    if (!t) {
        throw EntityNotFoundException(std::format("Teacher with ID {} was not found in faculty \"{}\".", teacherId, name));
    }
    return t;
}

Course* Faculty::getCourse(int courseId) const {
    Course* c = findCourse(courseId);
    if (!c) {
        throw EntityNotFoundException(std::format("Course with ID {} was not found in faculty \"{}\".", courseId, name));
    }
    return c;
}
