#include "../Header files/courseActivity.h"

std::string activityTypeToString(ActivityType type) {
    using enum ActivityType;
    switch (type) {
    case Lecture:  return "Лекционное занятие";
    case Lab:      return "Лабораторная работа";
    case Practice: return "Практическое занятие";
    }
    return "Неизвестно";
}

CourseActivity::CourseActivity(std::string_view actTitle, int lessons, int assignedTeacher)
    : title(actTitle), lessonsCount(lessons), teacherId(assignedTeacher) {
}

std::string CourseActivity::getTitle() const { return title; }
int CourseActivity::getLessonsCount() const { return lessonsCount; }
int CourseActivity::getTeacherId() const { return teacherId; }

void CourseActivity::setLessonsCount(int lessons) { lessonsCount = lessons; }
void CourseActivity::setTeacherId(int id) { teacherId = id; }

int CourseActivity::calculateHours() const {
    return lessonsCount * 2;
}