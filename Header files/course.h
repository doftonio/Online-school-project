#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <string_view>
#include <memory>
#include <cstddef>
#include <iostream>
#include "courseActivity.h"
#include "collection.h"

class Teacher;

class Course {
public:
    static constexpr std::size_t MAX_TEACHERS_PER_COURSE = 5;

private:
    int id{0};
    std::string title;
    Collection<Teacher*> teachers;
    Collection<std::unique_ptr<CourseActivity>> activities;

public:
    Course() = default;
    Course(int courseId, std::string_view courseTitle);
    Course(Course&&) noexcept = default;
    Course& operator=(Course&&) noexcept = default;
    Course(const Course&) = delete;
    Course& operator=(const Course&) = delete;

    int getId() const noexcept { return id; }
    const std::string& getTitle() const noexcept { return title; }
    const Collection<Teacher*>& getTeachers() const noexcept { return teachers; }
    const Collection<std::unique_ptr<CourseActivity>>& getActivities() const noexcept { return activities; }

    bool operator==(const Course& other) const noexcept {
        return id == other.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Course& course) {
        os << "Course [ID: " << course.id << "] " << course.title;
        return os;
    }

    Course& operator+=(Teacher* teacher);
    Course& operator-=(Teacher* teacher);
    Course& operator-=(int teacherId);

    void addActivity(std::unique_ptr<CourseActivity> activity);
    CourseActivity* findActivity(ActivityType type) const;

    void printFullCourseInfo() const;
};

#endif // COURSE_H
