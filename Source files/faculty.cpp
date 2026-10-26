#include "../Header files/faculty.h"
#include <iostream>

Faculty::Faculty(std::string_view facultyName) : name(facultyName) {}

Teacher* Faculty::createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept) {
    if (findTeacher(id) != nullptr) {
        std::cerr << "[Error] Teacher with ID " << id << " already exists in faculty \"" << name << "\".\n";
        return nullptr;
    }
    auto teacher = std::make_unique<Teacher>(id, first, last, middle, dept);
    Teacher* raw = teacher.get();
    allTeachers.add(std::move(teacher));
    return raw;
}

Course* Faculty::createCourse(int id, std::string_view title) {
    if (findCourse(id) != nullptr) {
        std::cerr << "[Error] Course with ID " << id << " already exists in faculty \"" << name << "\".\n";
        return nullptr;
    }
    auto c = std::make_unique<Course>(id, title);
    Course* raw = c.get();
    allCourses.add(std::move(c));
    return raw;
}

Teacher* Faculty::findTeacher(int teacherId) const {
    for (const auto& t : allTeachers) {
        if (t && t->getId() == teacherId) return t.get();
    }
    return nullptr;
}

Course* Faculty::findCourse(int courseId) const {
    for (const auto& c : allCourses) {
        if (c && c->getId() == courseId) return c.get();
    }
    return nullptr;
}
