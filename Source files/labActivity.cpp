#include "../Header files/labActivity.h"

LabActivity::LabActivity(int lessons, int assignedTeacher, int labsCount, int minScore)
    : CourseActivity("Лабораторные", lessons, assignedTeacher),
    count(labsCount), minPassingScore(minScore) {
}

ActivityType LabActivity::getType() const { return ActivityType::Lab; }
int LabActivity::getCount() const { return count; }
int LabActivity::getMinPassingScore() const { return minPassingScore; }

void LabActivity::addGradeForStudent(int studentId, const LabGrade& grade) {
    for (auto& record : journal) {
        if (record.getStudentId() == studentId) {
            record.addGrade(grade);
            return;
        }
    }
    StudentLabGradesContainer newRecord(studentId);
    newRecord.addGrade(grade);
    journal.push_back(newRecord);
}

bool LabActivity::removeGradeForStudentByDate(int studentId, const Date& date) {
    for (auto& record : journal) {
        if (record.getStudentId() == studentId) {
            return record.removeGradeByDate(date);
        }
    }
    return false;
}

double LabActivity::getGroupAverageScore() const {
    if (journal.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& record : journal) sum += record.getAverageScore();
    return sum / journal.size();
}

void LabActivity::printDetails() const {
    std::cout << "    [Лабораторные] Занятий: " << getLessonsCount()
        << " (" << calculateHours() << " ч.) | Преподаватель ID: " << getTeacherId() << "\n"
        << "      Сдать работ: " << count
        << " | Проходной балл: " << minPassingScore << "\n";
}

void printLabJournal(std::ostream& os, const LabActivity& activity) {
    os << "--- Журнал лабораторных работ (План: " << activity.count
        << ", Мин. балл: " << activity.minPassingScore << ") ---\n";
    for (const auto& record : activity.journal) {
        os << "  * " << record << "\n";
    }
    os << "  -> Средний балл группы за лабы: " << activity.getGroupAverageScore() << "\n";
}