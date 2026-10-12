#include "../Header files/lectureActivity.h"

LectureActivity::LectureActivity(int lessons, int assignedTeacher, int topics, int lectureHrs)
    : CourseActivity("Лекции", lessons, assignedTeacher),
    topicsCount(topics), hours(lectureHrs) {
}

ActivityType LectureActivity::getType() const { return ActivityType::Lecture; }
int LectureActivity::calculateHours() const { return hours; }

void LectureActivity::printDetails() const {
    std::cout << "    [Лекции] Занятий: " << lessonsCount
        << " (" << calculateHours() << " ч.) | Преподаватель ID: " << teacherId << "\n"
        << "      Тем в плане: " << topicsCount << "\n";
}