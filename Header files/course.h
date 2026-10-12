#pragma once
#include "teacher.h"
#include "courseActivity.h"
#include <span>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

struct GroupActivityProfile {
    std::string groupNumber{};
    std::vector<std::unique_ptr<CourseActivity>> activities{};
};

class Course {
private:
    int id{ 0 };
    std::string title{};
    std::vector<Teacher*> teachers{};
    std::vector<GroupActivityProfile> groupProfiles{};

public:
    Course(int courseId, std::string_view courseTitle);

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] std::span<const Teacher* const> getTeachers() const;
    [[nodiscard]] const std::vector<GroupActivityProfile>& getGroupProfiles() const;

    Course& operator+=(Teacher* teacher);
    Course& operator-=(int teacherId);

    [[nodiscard]] Teacher* findTeacher(int teacherId) const;

    void addActivityForGroup(std::string_view groupNumber, std::unique_ptr<CourseActivity> activity);
    [[nodiscard]] CourseActivity* findActivity(std::string_view groupNumber, ActivityType type);

    void printFullCourseInfo() const;
};