#pragma once
#include <string>
#include <string_view>
#include <iostream>

enum class ActivityType {
    Lecture,
    Lab,
    Practice
};

std::string activityTypeToString(ActivityType type);

class CourseActivity {
private:
    std::string title{};
    int lessonsCount{ 0 };
    int teacherId{ -1 };

public:
    CourseActivity() = default;
    CourseActivity(std::string_view actTitle, int lessons, int assignedTeacher);
    virtual ~CourseActivity() = default;

    std::string getTitle() const;
    int getLessonsCount() const;
    int getTeacherId() const;

    void setLessonsCount(int lessons);
    void setTeacherId(int id);

    virtual int calculateHours() const;
    virtual ActivityType getType() const = 0;
    virtual void printDetails() const = 0;
};