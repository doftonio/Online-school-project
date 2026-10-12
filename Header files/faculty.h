#pragma once
#include "student.h"
#include "teacher.h"
#include "studyGroup.h"
#include "course.h"
#include <string>
#include <string_view>
#include <vector>
#include <memory>

class Faculty {
private:
    std::string name{};
    std::vector<std::unique_ptr<Student>> allStudents{};
    std::vector<std::unique_ptr<Teacher>> allTeachers{};
    std::vector<std::unique_ptr<StudyGroup>> allGroups{};
    std::vector<std::unique_ptr<Course>> allCourses{};

public:
    explicit Faculty(std::string_view facultyName);

    [[nodiscard]] std::string getName() const;

    Teacher* createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept);
    StudyGroup* createGroup(std::string_view number, int year, int capacity = 30);
    Course* createCourse(int id, std::string_view title);

    [[nodiscard]] StudyGroup* findGroup(std::string_view groupNum) const;
    [[nodiscard]] Teacher* findTeacher(int teacherId) const;
    [[nodiscard]] Course* findCourse(int courseId) const;

    [[nodiscard]] const std::vector<std::unique_ptr<Teacher>>& getTeachers() const;
    [[nodiscard]] const std::vector<std::unique_ptr<StudyGroup>>& getGroups() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Course>>& getCourses() const;

    Student* enrollStudentInGroup(int id, std::string_view first, std::string_view last,
        std::string_view middle, std::string_view groupNum);

    void expelStudent(int studentId);
};