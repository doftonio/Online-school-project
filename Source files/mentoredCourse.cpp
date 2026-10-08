#include "../Header files/mentoredCourse.h"
#include <iostream>

MentoredCourse::MentoredCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
    std::string_view mentor, int reviewsLimit)
    : Course(id, title, teacher, lessons, capacity),
    mentorName(mentor), maxReviewsPerStudent(reviewsLimit)
{}

std::string MentoredCourse::getMentorName() const
{
    return mentorName;
}

int MentoredCourse::getMaxReviews() const
{
    return maxReviewsPerStudent;
}

int MentoredCourse::getTotalReviewsConducted() const
{
    return totalReviewsConducted;
}

void MentoredCourse::setMentorName(std::string_view mentor)
{
    mentorName = mentor;
}

void MentoredCourse::conductReview(int studentId)
{
    if (calculateStudentProgress(studentId) == -1)
    {
        std::cout << "Student with ID " << studentId << " not found for review.\n";
        return;
    }

    totalReviewsConducted++;
    recordTaskCompletion(studentId);
    std::cout << "Mentor " << mentorName << " approved project for student ID "
        << studentId << ".\n";
}

bool MentoredCourse::enrollStudent(const Student& student)
{
    if (constexpr int maxMentorLoad = 5; getEnrolledCount() >= maxMentorLoad)
    {
        std::cout << "Cannot enroll in Mentored Course: mentor workload limit ("
            << maxMentorLoad << " students) reached for " << mentorName << ".\n";
        return false;
    }
    return Course::enrollStudent(student);
}

bool MentoredCourse::enrollStudent(int id, std::string_view name)
{
    Student newStudent;
    newStudent.initStudent(id, name);
    return enrollStudent(newStudent);
}

void MentoredCourse::printFullCourseInfo() const
{
    std::cout << "\nCourse Information (Mentored Course):\n";
    std::cout << "Title: " << getCourseTitle() << "\n";
    std::cout << "Instructor: " << getTeacherName() << "\n";
    std::cout << "Mentor: " << mentorName << "\n";
    std::cout << "Reviews quota: " << maxReviewsPerStudent << "\n";
    std::cout << "Reviews conducted: " << totalReviewsConducted << "\n";
    std::cout << "Enrolled students: " << getEnrolledCount() << " / " << getMaxCapacity() << "\n";
    printEnrolledStudentsList("reviews passed");
    std::cout << std::endl;
}