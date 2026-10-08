#include "../Header files/webinarCourse.h"
#include <iostream>

WebinarCourse::WebinarCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
    const WebinarDetails& details)
    : Course(id, title, teacher, lessons, capacity),
    platformUrl(details.platformUrl), scheduleTime(details.scheduleTime), totalWebinars(details.totalWebinars)
{}

std::string WebinarCourse::getPlatformUrl() const
{
    return platformUrl;
}

std::string WebinarCourse::getScheduleTime() const
{
    return scheduleTime;
}

int WebinarCourse::getTotalWebinars() const
{
    return totalWebinars;
}

void WebinarCourse::setPlatformUrl(std::string_view url)
{
    platformUrl = url;
}

void WebinarCourse::setScheduleTime(std::string_view schedule)
{
    scheduleTime = schedule;
}

void WebinarCourse::printFullCourseInfo() const
{
    std::cout << "\nCourse Information (Webinar Course):\n";
    std::cout << "Title: " << getCourseTitle() << "\n";
    std::cout << "Instructor: " << getTeacherName() << "\n";
    std::cout << "Platform URL: " << platformUrl << "\n";
    std::cout << "Schedule: " << scheduleTime << "\n";
    std::cout << "Total webinars: " << totalWebinars << "\n";
    std::cout << "Enrolled students: " << getEnrolledCount() << " / " << getMaxCapacity() << "\n";
    printEnrolledStudentsList("attended sessions");
    std::cout << std::endl;
}