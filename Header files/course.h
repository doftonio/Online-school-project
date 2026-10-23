#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <span>
#include "courseActivity.h"

class Teacher;

class Course {
private:
    int id{0};
    std::string title;
    std::vector<Teacher*> teachers;
    std::vector<std::unique_ptr<CourseActivity>> activities;

public:
    Course(int courseId, std::string_view courseTitle);

    int getId() const noexcept { return id; }
    const std::string& getTitle() const noexcept { return title; }
    std::span<Teacher* const> getTeachers() const noexcept { return teachers; }

    Course& operator+=(Teacher* teacher);
    Course& operator-=(Teacher* teacher);
    Course& operator-=(int teacherId);

    void addActivity(std::unique_ptr<CourseActivity> activity);
    CourseActivity* findActivity(ActivityType type) const;

    void printFullCourseInfo() const;
};

#endif // COURSE_H
