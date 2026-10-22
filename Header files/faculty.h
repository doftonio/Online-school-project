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

    const std::string& getName() const noexcept { return name; }

    const std::vector<std::unique_ptr<Student>>& getStudents() const noexcept { return allStudents; }
    const std::vector<std::unique_ptr<Teacher>>& getTeachers() const noexcept { return allTeachers; }
    const std::vector<std::unique_ptr<StudyGroup>>& getGroups() const noexcept { return allGroups; }
    const std::vector<std::unique_ptr<Course>>& getCourses() const noexcept { return allCourses; }

    Teacher* createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept);
    StudyGroup* createGroup(std::string_view number, int year, int capacity);
    Course* createCourse(int id, std::string_view title);

    StudyGroup* findGroup(std::string_view groupNum) const;
    Teacher* findTeacher(int teacherId) const;
    Course* findCourse(int courseId) const;
    Student* findStudent(int studentId) const;

    Student* enrollStudentInGroup(int id, std::string_view first, std::string_view last, std::string_view middle, StudyGroup* group);
    Student* enrollStudentInGroup(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view groupNum);

    void expelStudent(Student* student);
    void expelStudent(int studentId);
};

#endif // FACULTY_H
