#include "../Header files/interactiveCourse.h"
#include <iostream>

InteractiveCourse::InteractiveCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
    int exercises, int passingScore)
    : Course(id, title, teacher, lessons, capacity),
    totalExercises(exercises), autoCheckPassingScore(passingScore)
{}

void InteractiveCourse::setTotalExercises(int exercises)
{
    if (exercises >= 0) {
        totalExercises = exercises;
    }
}

int InteractiveCourse::getTotalExercises() const
{
    return totalExercises;
}

int InteractiveCourse::getPassingScore() const
{
    return autoCheckPassingScore;
}

void InteractiveCourse::submitExercise(int studentId, bool passed)
{
    if (passed)
    {
        std::cout << "Exercise submitted and passed for student ID " << studentId << ".\n";
        recordTaskCompletion(studentId);
    }
    else
    {
        std::cout << "Exercise failed for student ID " << studentId << ".\n";
    }
}

int InteractiveCourse::calculateStudentProgress(int studentId) const
{
    int baseProgress = Course::calculateStudentProgress(studentId);
    if (baseProgress < 0) {
        return -1;
    }
    return baseProgress;
}

void InteractiveCourse::printFullCourseInfo() const
{
    std::cout << "\nCourse Information (Interactive Course):\n";
    std::cout << "Title: " << getCourseTitle() << "\n";
    std::cout << "Instructor: " << getTeacherName() << "\n";
    std::cout << "Theory lessons: " << getTotalLessons() << "\n";
    std::cout << "Practice exercises: " << totalExercises << "\n";
    std::cout << "Passing score threshold: " << autoCheckPassingScore << "%\n";
    std::cout << "Enrolled students: " << getEnrolledCount() << " / " << getMaxCapacity() << "\n";
    printEnrolledStudentsList("auto-tests passed");
    std::cout << std::endl;
}