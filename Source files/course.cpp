#include "../Header files/course.h"
#include "../Header files/exceptions.h"
#include <format>
#include <iostream>

Course::Course(int courseId, std::string_view courseTitle)
    : id(courseId), title(courseTitle) {
}

int Course::getId() const { return id; }
std::string Course::getTitle() const { return title; }
std::span<const Teacher* const> Course::getTeachers() const { return teachers; }
const std::vector<GroupActivityProfile>& Course::getGroupProfiles() const { return groupProfiles; }

Course& Course::operator+=(Teacher* teacher) {
    if (!teacher) {
        throw InvalidOperationException("Teacher is nullptr.");
    }
    if (findTeacher(teacher->getId())) {
        throw DuplicateEntityException(std::format("Teacher ID {} is already on the course.", teacher->getId()));
    }
    teachers.push_back(teacher);
    return *this;
}

Course& Course::operator-=(int teacherId) {
    for (size_t i = 0; i < teachers.size(); ++i) {
        if (teachers[i] && teachers[i]->getId() == teacherId) {
            teachers.erase(teachers.begin() + i);
            return *this;
        }
    }
    throw EntityNotFoundException(std::format("Teacher ID {} not found on the course.", teacherId));
}

Teacher* Course::findTeacher(int teacherId) const {
    for (auto* t : teachers) {
        if (t && t->getId() == teacherId) return t;
    }
    return nullptr;
}

void Course::addActivityForGroup(std::string_view groupNumber, std::unique_ptr<CourseActivity> activity) {
    if (!activity) {
        throw InvalidOperationException("Passed empty activity.");
    }

    if (int tId = activity->getTeacherId(); !findTeacher(tId)) {
        throw EntityNotFoundException(std::format("Teacher ID {} is not in the course pool \"{}\"!", tId, title));
    }

    size_t profileIndex = groupProfiles.size();
    for (size_t i = 0; i < groupProfiles.size(); ++i) {
        if (groupProfiles[i].groupNumber == groupNumber) {
            profileIndex = i;
            break;
        }
    }

    if (profileIndex == groupProfiles.size()) {
        groupProfiles.push_back(GroupActivityProfile{ std::string(groupNumber), {} });
        profileIndex = groupProfiles.size() - 1;
    }

    ActivityType incomingType = activity->getType();
    for (const auto& existing : groupProfiles[profileIndex].activities) {
        if (existing->getType() == incomingType) {
            throw DuplicateEntityException(std::format("Activity \"{}\" already exists for group {}!",
                activityTypeToString(incomingType), groupNumber));
        }
    }

    groupProfiles[profileIndex].activities.push_back(std::move(activity));
}

CourseActivity* Course::findActivity(std::string_view groupNumber, ActivityType type) {
    for (const auto& prof : groupProfiles) {
        if (prof.groupNumber != groupNumber) {
            continue;
        }
        for (const auto& act : prof.activities) {
            if (act->getType() == type) {
                return act.get();
            }
        }
    }
    return nullptr;
}

void Course::printFullCourseInfo() const {
    std::cout << "\n=======================================================\n";
    std::cout << "COURSE: " << title << " (ID: " << id << ")\n";
    std::cout << "Course Teachers (" << teachers.size() << "):\n";
    for (const Teacher* const t : teachers) {
        std::cout << "  * " << t->getFullName() << " [ID: " << t->getId()
            << ", Dept: " << t->getDepartment() << "]\n";
    }

    std::cout << "\nGroup Activities:\n";
    for (const auto& prof : groupProfiles) {
        std::cout << ">>> Group: " << prof.groupNumber
            << " (Assigned types: " << prof.activities.size() << "/3)\n";
        for (const auto& act : prof.activities) {
            const Teacher* t = findTeacher(act->getTeacherId());
            std::cout << "  Instructor: " << (t ? t->getFullName() : "N/A") << "\n";
            act->printDetails();
        }
    }
    std::cout << "=======================================================\n";
}