#pragma once
#include "course.h"
#include <string_view>

class InteractiveCourse : public Course
{
private:
    int totalExercises{ 0 };
    int autoCheckPassingScore{ 70 };

public:
    InteractiveCourse() = default;
    InteractiveCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
        int exercises, int passingScore);

    void setTotalExercises(int exercises);
    int getTotalExercises() const;
    int getPassingScore() const;

    void submitExercise(int studentId, int mark);

    int calculateStudentProgress(int studentId) const override;
    void printFullCourseInfo() const override;
};