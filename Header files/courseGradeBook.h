#ifndef COURSE_GRADE_BOOK_H
#define COURSE_GRADE_BOOK_H

#include <vector>
#include <algorithm>
#include "grade.h"

class Student;
class CourseActivity;

struct GradeEntry {
    Student* student{nullptr};
    CourseActivity* activity{nullptr};
    Grade grade;
};

class CourseGradeBook {
private:
    std::vector<GradeEntry> entries;

public:
    CourseGradeBook() = default;

    void addGrade(Student* student, CourseActivity* activity, const Grade& grade) {
        if (student && activity) {
            entries.emplace_back(student, activity, grade);
        }
    }

    bool removeGradeByDate(const Student* student, const CourseActivity* activity, const Date& targetDate) {
        auto countBefore = entries.size();
        std::erase_if(entries, [&targetDate, student, activity](const GradeEntry& entry) {
            return entry.student == student &&
                   entry.activity == activity &&
                   entry.grade.getDate() == targetDate;
        });
        return entries.size() < countBefore;
    }

    void removeAllGradesForStudent(const Student* student) noexcept {
        std::erase_if(entries, [student](const GradeEntry& entry) {
            return entry.student == student;
        });
    }

    std::vector<Grade> getGrades(const Student* student, const CourseActivity* activity) const {
        std::vector<Grade> result;
        for (const auto& entry : entries) {
            if (entry.student == student && entry.activity == activity) {
                result.push_back(entry.grade);
            }
        }
        return result;
    }

    double getStudentAverage(const Student* student) const noexcept {
        double sum = 0.0;
        int count = 0;
        for (const auto& entry : entries) {
            if (entry.student == student) {
                sum += entry.grade.getValue();
                ++count;
            }
        }
        return count == 0 ? 0.0 : (sum / count);
    }

    double getActivityAverage(const CourseActivity* activity) const noexcept {
        double sum = 0.0;
        int count = 0;
        for (const auto& entry : entries) {
            if (entry.activity == activity) {
                sum += entry.grade.getValue();
                ++count;
            }
        }
        return count == 0 ? 0.0 : (sum / count);
    }
};

#endif // COURSE_GRADE_BOOK_H
