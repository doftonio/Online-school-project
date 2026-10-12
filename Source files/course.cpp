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
        throw InvalidOperationException("Преподаватель nullptr.");
    }
    if (findTeacher(teacher->getId())) {
        throw DuplicateEntityException(std::format("Преподаватель ID {} уже на курсе.", teacher->getId()));
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
    throw EntityNotFoundException(std::format("Преподаватель ID {} не найден на курсе.", teacherId));
}

Teacher* Course::findTeacher(int teacherId) const {
    for (auto* t : teachers) {
        if (t && t->getId() == teacherId) return t;
    }
    return nullptr;
}

void Course::addActivityForGroup(std::string_view groupNumber, std::unique_ptr<CourseActivity> activity) {
    if (!activity) {
        throw InvalidOperationException("Передана пустая активность.");
    }

    if (int tId = activity->getTeacherId(); !findTeacher(tId)) {
        throw EntityNotFoundException(std::format("Преподаватель ID {} отсутствует в пуле курса \"{}\"!", tId, title));
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
            throw DuplicateEntityException(std::format("Для группы {} активность \"{}\" уже существует!",
                groupNumber, activityTypeToString(incomingType)));
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
    std::cout << "КУРС: " << title << " (ID: " << id << ")\n";
    std::cout << "Преподаватели курса (" << teachers.size() << "):\n";
    for (const Teacher* const t : teachers) {
        std::cout << "  * " << t->getFullName() << " [ID: " << t->getId()
            << ", Кафедра: " << t->getDepartment() << "]\n";
    }

    std::cout << "\nАктивности по учебным группам:\n";
    for (const auto& prof : groupProfiles) {
        std::cout << ">>> Группа: " << prof.groupNumber
            << " (Назначено типов: " << prof.activities.size() << "/3)\n";
        for (const auto& act : prof.activities) {
            const Teacher* t = findTeacher(act->getTeacherId());
            std::cout << "  Ведущий: " << (t ? t->getFullName() : "N/A") << "\n";
            act->printDetails();
        }
    }
    std::cout << "=======================================================\n";
}