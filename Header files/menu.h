#ifndef MENU_H
#define MENU_H

class Faculty;
class Course;

void runMainMenu(Faculty& faculty);

void showTeachersSubmenu(Faculty& faculty);
void showCoursesSubmenu(Faculty& faculty);
void showCourseDetailsSubmenu(const Faculty& faculty, Course* course);

void handleAddTeacher(Faculty& faculty);
void handleCreateCourse(Faculty& faculty);
void handleAssignTeacherToCourse(const Faculty& faculty, Course* course);
void handleRemoveTeacherFromCourse(Course* course);
void handleAddActivityToCourse(const Faculty& faculty, Course* course);

#endif // MENU_H
