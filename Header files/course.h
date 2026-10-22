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

    int getId() const noexcept { return id; }
    const std::string& getTitle() const noexcept { return title; }
    std::span<Teacher* const> getTeachers() const noexcept { return teachers; }
    CourseGradeBook& getGradeBook() noexcept { return gradeBook; }
    const CourseGradeBook& getGradeBook() const noexcept { return gradeBook; }

    Course& operator+=(Teacher* teacher);
    Course& operator-=(Teacher* teacher);
    Course& operator-=(int teacherId);

    void addActivity(std::unique_ptr<CourseActivity> activity);
    void addActivityForGroup(std::string_view groupNumber, std::unique_ptr<CourseActivity> activity);

    CourseActivity* findActivity(ActivityType type) const;
    CourseActivity* findActivity(std::string_view groupNumber, ActivityType type) const;

    void printFullCourseInfo() const;
};

#endif // COURSE_H
