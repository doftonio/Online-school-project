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

    int getId() const;
    std::string getTitle() const;
    std::span<const Teacher* const> getTeachers() const;
    const std::vector<GroupActivityProfile>& getGroupProfiles() const;

    Course& operator+=(Teacher* teacher);
    Course& operator-=(int teacherId);

    Teacher* findTeacher(int teacherId) const;

    void addActivityForGroup(std::string_view groupNumber, std::unique_ptr<CourseActivity> activity);
    CourseActivity* findActivity(std::string_view groupNumber, ActivityType type);

    void printFullCourseInfo() const;
};