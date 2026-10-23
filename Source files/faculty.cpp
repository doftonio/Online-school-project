#include "../Header files/faculty.h"

Faculty::Faculty(std::string_view facultyName) : name(facultyName) {}

Teacher* Faculty::createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept) {
    auto teacher = std::make_unique<Teacher>(id, first, last, middle, dept);
    Teacher* raw = teacher.get();
    allTeachers.push_back(std::move(teacher));
    return raw;
}

Course* Faculty::createCourse(int id, std::string_view title) {
    auto c = std::make_unique<Course>(id, title);
    Course* raw = c.get();
    allCourses.push_back(std::move(c));
    return raw;
}

Teacher* Faculty::findTeacher(int teacherId) const {
    for (const std::unique_ptr<Teacher>& t : allTeachers) {
        if (t && t->getId() == teacherId) return t.get();
    }
    return nullptr;
}

Course* Faculty::findCourse(int courseId) const {
    for (const std::unique_ptr<Course>& c : allCourses) {
        if (c && c->getId() == courseId) return c.get();
    }
    return nullptr;
}
