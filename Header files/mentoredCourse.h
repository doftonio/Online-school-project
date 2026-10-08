#pragma once
#include "course.h"
#include <string>
#include <string_view>

class MentoredCourse : public Course
{
private:
    std::string mentorName{};
    int maxReviewsPerStudent{ 3 };
    int totalReviewsConducted{ 0 };

public:
    MentoredCourse() = default;
    MentoredCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
        std::string_view mentor, int reviewsLimit);

    std::string getMentorName() const;
    int getMaxReviews() const;
    int getTotalReviewsConducted() const;

    void setMentorName(std::string_view mentor);

    void conductReview(int studentId);

    bool enrollStudent(const Student& student) override;
    bool enrollStudent(int id, std::string_view name) override;

    void printFullCourseInfo() const override;
};