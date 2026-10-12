#include "../Header files/practiceActivity.h"

PracticeActivity::PracticeActivity(int lessons, int assignedTeacher, int tests, int practicals, int calculations)
    : CourseActivity("Practice", lessons, assignedTeacher),
    testsCount(tests), tasksCount(practicals), calculationsCount(calculations) {
}

ActivityType PracticeActivity::getType() const { return ActivityType::Practice; }

int PracticeActivity::calculateHours() const {
    return CourseActivity::calculateHours() + (testsCount * 2);
}

void PracticeActivity::printDetails() const {
    std::cout << "    [Practice] Lessons: " << getLessonsCount()
        << " (" << calculateHours() << " h) | Teacher ID: " << getTeacherId() << "\n"
        << "      Tests: " << testsCount
        << " | Tasks: " << tasksCount
        << " | Calculations: " << calculationsCount << "\n";
}

void PracticeActivity::addGradeForStudent(int studentId, const PracticeGrade& grade) {
    for (auto& record : journal) {
        if (record.getStudentId() == studentId) {
            record.addGrade(grade);
            return;
        }
    }
    StudentPracticeGradesContainer newRecord(studentId);
    newRecord.addGrade(grade);
    journal.push_back(newRecord);
}

bool PracticeActivity::removeGradeForStudentByDate(int studentId, const Date& date) {
    for (auto& record : journal) {
        if (record.getStudentId() == studentId) {
            return record.removeGradeByDate(date);
        }
    }
    return false;
}

double PracticeActivity::getGroupAverageScore() const {
    if (journal.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& record : journal) sum += record.getAverageScore();
    return sum / journal.size();
}

void printPracticeJournal(std::ostream& os, const PracticeActivity& activity) {
    os << "--- Practice Journal ---\n";
    for (const auto& record : activity.journal) {
        os << "  * " << record << "\n";
    }
    os << "  -> Group average score for practice: " << activity.getGroupAverageScore() << "\n";
}