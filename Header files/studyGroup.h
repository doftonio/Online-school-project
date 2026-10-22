#ifndef STUDY_GROUP_H
#define STUDY_GROUP_H

#include <string>
#include <string_view>
#include <vector>
#include <span>

class Student;

class StudyGroup {
private:
    std::string number;
    int courseYear{1};
    int maxCapacity{30};
    std::vector<Student*> students;

public:
    StudyGroup(std::string_view groupNum, int year, int capacity);

    const std::string& getNumber() const noexcept { return number; }
    int getCourseYear() const noexcept { return courseYear; }
    int getMaxCapacity() const noexcept { return maxCapacity; }
    std::span<const Student* const> getStudents() const noexcept { return students; }

    StudyGroup& operator+=(Student* student);
    StudyGroup& operator-=(Student* student);

    Student* findStudent(int studentId) const;
    void printInfo() const;
};

#endif // STUDY_GROUP_H
