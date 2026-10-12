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

    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] int getLessonsCount() const;
    [[nodiscard]] int getTeacherId() const;

    void setLessonsCount(int lessons);
    void setTeacherId(int id);

    [[nodiscard]] virtual int calculateHours() const;
    [[nodiscard]] virtual ActivityType getType() const = 0;
    virtual void printDetails() const = 0;
};