#include "../Header files/course.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

Course::Course(int courseId, std::string_view courseTitle)
    : id(courseId), title(courseTitle) {
}

int Course::getId() const { return id; }
std::string Course::getTitle() const { return title; }
const std::vector<Teacher*>& Course::getTeachers() const { return teachers; }

Course& Course::operator+=(Teacher* teacher) {
    if (!teacher) {
        throw std::invalid_argument("Преподаватель nullptr.");
    }
    if (findTeacher(teacher->getId())) {
        throw std::invalid_argument("Преподаватель ID " + std::to_string(teacher->getId()) + " уже на курсе.");
    }
    teachers.push_back(teacher);
    return *this;
}

Course& Course::operator-=(int teacherId) {
    auto it = std::find_if(teachers.begin(), teachers.end(),
        [teacherId](const Teacher* t) { return t && t->getId() == teacherId; });

    if (it == teachers.end()) {
        throw std::runtime_error("Преподаватель ID " + std::to_string(teacherId) + " не найден на курсе.");
    }
    teachers.erase(it);
    return *this;
}

Teacher* Course::findTeacher(int teacherId) const {
    for (auto* t : teachers) {
        if (t && t->getId() == teacherId) return t;
    }
    return nullptr;
}

void Course::addActivityForGroup(std::string_view groupNumber, std::unique_ptr<CourseActivity> activity) {
    if (!activity) {
        throw std::invalid_argument("Передана пустая активность.");
    }

    int tId = activity->getTeacherId();
    if (!findTeacher(tId)) {
        throw std::runtime_error("Преподаватель ID " + std::to_string(tId) + " отсутствует в пуле курса \"" + title + "\"!");
    }

    auto profileIt = std::find_if(groupProfiles.begin(), groupProfiles.end(),
        [groupNumber](const GroupActivityProfile& p) { return p.groupNumber == groupNumber; });

    if (profileIt == groupProfiles.end()) {
        groupProfiles.push_back(GroupActivityProfile{ std::string(groupNumber), {} });
        profileIt = groupProfiles.end() - 1;
    }

    ActivityType incomingType = activity->getType();
    for (const auto& existing : profileIt->activities) {
        if (existing->getType() == incomingType) {
            throw std::logic_error("Для группы " + std::string(groupNumber) +
                " активность \"" + activityTypeToString(incomingType) + "\" уже существует!");
        }
    }

    profileIt->activities.push_back(std::move(activity));
}

CourseActivity* Course::findActivity(std::string_view groupNumber, ActivityType type) {
    for (auto& prof : groupProfiles) {
        if (prof.groupNumber == groupNumber) {
            for (auto& act : prof.activities) {
                if (act->getType() == type) return act.get();
            }
        }
    }
    return nullptr;
}

void Course::printFullCourseInfo() const {
    std::cout << "\n=======================================================\n";
    std::cout << "КУРС: " << title << " (ID: " << id << ")\n";
    std::cout << "Преподаватели курса (" << teachers.size() << "):\n";
    for (const auto* t : teachers) {
        std::cout << "  * " << t->getFullName() << " [ID: " << t->getId()
            << ", Кафедра: " << t->getDepartment() << "]\n";
    }

    std::cout << "\nАктивности по учебным группам:\n";
    for (const auto& prof : groupProfiles) {
        std::cout << ">>> Группа: " << prof.groupNumber
            << " (Назначено типов: " << prof.activities.size() << "/3)\n";
        for (const auto& act : prof.activities) {
            Teacher* t = findTeacher(act->getTeacherId());
            std::cout << "  Ведущий: " << (t ? t->getFullName() : "N/A") << "\n";
            act->printDetails();
        }
    }
    std::cout << "=======================================================\n";
}