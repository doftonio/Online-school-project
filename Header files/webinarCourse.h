#pragma once
#include "course.h"
#include <string>
#include <string_view>

struct WebinarDetails
{
    std::string_view platformUrl{};
    std::string_view scheduleTime{};
    int totalWebinars{ 0 };
};

class WebinarCourse : public Course
{
private:
    std::string platformUrl{};
    std::string scheduleTime{};
    int totalWebinars{ 0 };

public:
    WebinarCourse() = default;
    WebinarCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
        const WebinarDetails& details);

    std::string getPlatformUrl() const;
    std::string getScheduleTime() const;
    int getTotalWebinars() const;

    void setPlatformUrl(std::string_view url);
    void setScheduleTime(std::string_view schedule);

    void printFullCourseInfo() const override;
};