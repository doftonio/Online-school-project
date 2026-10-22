#ifndef MENU_H
#define MENU_H

class Faculty;
class Course;

void runMainMenu(const Faculty& faculty);

void showTeachersSubmenu(const Faculty& faculty);
void showGroupsSubmenu(const Faculty& faculty);
void showCoursesSubmenu(const Faculty& faculty);
void showCourseDetailsSubmenu(const Faculty& faculty, const Course* course);

void handleCourseActivities(const Course* course);
void handleAddGrade(const Course* course);
void handleRemoveGrade(const Course* course);
void handlePrintGrades(const Course* course);

#endif // MENU_H
