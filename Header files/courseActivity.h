#ifndef COURSE_ACTIVITY_H
#define COURSE_ACTIVITY_H

#include <string>
#include <string_view>

class Teacher;

enum class ActivityType {
    Lecture,
    Lab,
    Practice
};

class CourseActivity {
private:
    std::string title;
    int lessonsCount{0};
    Teacher* teacher{nullptr};

public:
    CourseActivity() = default;
    CourseActivity(std::string_view actTitle, int lessons, Teacher* assignedTeacher)
        : title(actTitle), lessonsCount(lessons), teacher(assignedTeacher) {}
    virtual ~CourseActivity() = default;

    const std::string& getTitle() const noexcept { return title; }
    int getLessonsCount() const noexcept { return lessonsCount; }
    Teacher* getTeacher() const noexcept { return teacher; }
    void setTeacher(Teacher* t) noexcept { teacher = t; }

    virtual int calculateHours() const = 0;
    virtual ActivityType getType() const noexcept = 0;
    virtual void printDetails() const = 0;
};

#endif // COURSE_ACTIVITY_H
