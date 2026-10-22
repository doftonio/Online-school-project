#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <span>
#include "courseActivity.h"
#include "courseGradeBook.h"

class Teacher;

class Course {
private:
    int id{0};
    std::string title;
    std::vector<Teacher*> teachers;
    std::vector<std::unique_ptr<CourseActivity>> activities;
    CourseGradeBook gradeBook;

public:
    Course(int courseId, std::string_view courseTitle);

    [[nodiscard]] int getId() const noexcept { return id; }
    [[nodiscard]] const std::string& getTitle() const noexcept { return title; }
    [[nodiscard]] std::span<Teacher* const> getTeachers() const noexcept { return teachers; }
    [[nodiscard]] CourseGradeBook& getGradeBook() noexcept { return gradeBook; }
    [[nodiscard]] const CourseGradeBook& getGradeBook() const noexcept { return gradeBook; }

    Course& operator+=(Teacher* teacher);
    Course& operator-=(Teacher* teacher);

    void addActivity(std::unique_ptr<CourseActivity> activity);
    [[nodiscard]] CourseActivity* findActivity(ActivityType type) const;
    void printFullCourseInfo() const;
};

#endif // COURSE_H
