#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "student.h"
#include "teacher.h"
#include "studyGroup.h"
#include "course.h"

class Faculty {
private:
    std::string name;
    std::vector<std::unique_ptr<Student>> allStudents;
    std::vector<std::unique_ptr<Teacher>> allTeachers;
    std::vector<std::unique_ptr<StudyGroup>> allGroups;
    std::vector<std::unique_ptr<Course>> allCourses;

public:
    explicit Faculty(std::string_view facultyName);

    [[nodiscard]] const std::string& getName() const noexcept { return name; }

    Teacher* createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept);
    StudyGroup* createGroup(std::string_view number, int year, int capacity);
    Course* createCourse(int id, std::string_view title);

    [[nodiscard]] StudyGroup* findGroup(std::string_view groupNum) const;
    [[nodiscard]] Teacher* findTeacher(int teacherId) const;
    [[nodiscard]] Course* findCourse(int courseId) const;
    [[nodiscard]] Student* findStudent(int studentId) const;

    Student* enrollStudentInGroup(int id, std::string_view first, std::string_view last, std::string_view middle, StudyGroup* group);
    void expelStudent(Student* student);
};

#endif // FACULTY_H
