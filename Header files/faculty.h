#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "teacher.h"
#include "course.h"

class Faculty {
private:
    std::string name;
    std::vector<std::unique_ptr<Teacher>> allTeachers;
    std::vector<std::unique_ptr<Course>> allCourses;

public:
    explicit Faculty(std::string_view facultyName);

    const std::string& getName() const noexcept { return name; }
    const std::vector<std::unique_ptr<Teacher>>& getTeachers() const noexcept { return allTeachers; }
    const std::vector<std::unique_ptr<Course>>& getCourses() const noexcept { return allCourses; }

    Teacher* createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept);
    Course* createCourse(int id, std::string_view title);

    Teacher* findTeacher(int teacherId) const;
    Course* findCourse(int courseId) const;
};

#endif // FACULTY_H
