#ifndef MENU_H
#define MENU_H

class Faculty;
class Course;

void runMainMenu(Faculty& faculty);

void showTeachersSubmenu(Faculty& faculty);
void showGroupsSubmenu(Faculty& faculty);
void showCoursesSubmenu(Faculty& faculty);
void showCourseDetailsSubmenu(Faculty& faculty, Course* course);

void handleAddTeacher(Faculty& faculty);
void handleCreateGroup(Faculty& faculty);
void handleEnrollStudent(Faculty& faculty);
void handleExpelStudent(Faculty& faculty);
void handleCreateCourse(Faculty& faculty);
void handleAssignTeacherToCourse(Faculty& faculty, Course* course);
void handleRemoveTeacherFromCourse(Course* course);
void handleAddActivityToCourse(Faculty& faculty, Course* course);
void handleAddGradeToCourse(Faculty& faculty, Course* course);
void handleRemoveGradeFromCourse(Faculty& faculty, Course* course);

#endif // MENU_H
