#include "../Header files/lectureActivity.h"

LectureActivity::LectureActivity(int lessons, int assignedTeacher, int topics, int lectureHrs)
    : CourseActivity("Lectures", lessons, assignedTeacher),
    topicsCount(topics), hours(lectureHrs) {
}

ActivityType LectureActivity::getType() const { return ActivityType::Lecture; }
int LectureActivity::calculateHours() const { return hours; }

void LectureActivity::printDetails() const {
    std::cout << "    [Lectures] Lessons: " << getLessonsCount()
        << " (" << calculateHours() << " h) | Teacher ID: " << getTeacherId() << "\n"
        << "      Syllabus topics: " << topicsCount << "\n";
}