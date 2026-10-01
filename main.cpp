#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Unit {
    string code;
    string name;
};

struct Result {
    string unitCode;
    double cat = 0;
    double assignment = 0;
    double exam = 0;
    double total = 0;
    char grade = 'F';
};

class Person {
protected:
    string id;
    string name;
public:
    Person(string id = "", string name = "") : id(id), name(name) {}
    virtual ~Person() = default;
    virtual void login() = 0;
    string getId() const { return id; }
    string getName() const { return name; }
};

class Student : public Person {
private:
    string registrationNumber;
    vector<Unit> registeredUnits;
    map<string, Result> results;
public:
    Student(string id = "", string name = "", string registrationNumber = "")
        : Person(id, name), registrationNumber(registrationNumber) {}

    void login() override {
        cout << "Student " << name << " logged in successfully.\n";
    }

    void registerUnit(const Unit& unit) {
        for (const auto& current : registeredUnits) {
            if (current.code == unit.code) {
                cout << "Student is already registered for " << unit.code << "\n";
                return;
            }
        }
        registeredUnits.push_back(unit);
        cout << "Unit " << unit.code << " registered successfully.\n";
    }

    void viewRegisteredUnits() const {
        cout << "\nRegistered Units:\n";
        if (registeredUnits.empty()) {
            cout << "No units registered.\n";
            return;
        }
        for (const auto& unit : registeredUnits) {
            cout << "- " << unit.code << " : " << unit.name << "\n";
        }
    }

    void viewGrades() const {
        cout << "\nStudent Results:\n";
        if (results.empty()) {
            cout << "No results available.\n";
            return;
        }

        for (const auto& [unitCode, result] : results) {
            cout << unitCode << " -> CAT: " << result.cat
                 << ", Assignment: " << result.assignment
                 << ", Exam: " << result.exam
                 << ", Total: " << result.total
                 << ", Grade: " << result.grade << "\n";
        }
    }

    void setResult(const Result& result) {
        results[result.unitCode] = result;
    }

    string getRegistrationNumber() const { return registrationNumber; }
    vector<Unit> getRegisteredUnits() const { return registeredUnits; }
    map<string, Result> getResults() const { return results; }
};

class Lecturer : public Person {
private:
    string staffNumber;
    vector<string> teachingUnits;
public:
    Lecturer(string id = "", string name = "", string staffNumber = "")
        : Person(id, name), staffNumber(staffNumber) {}

    void login() override {
        cout << "Lecturer " << name << " logged in successfully.\n";
    }

    void addTeachingUnit(const string& code) {
        teachingUnits.push_back(code);
    }

    void uploadNotes(const string& unitCode) {
        cout << "Lecture notes uploaded for " << unitCode << "\n";
    }

    void uploadAssignment(const string& unitCode) {
        cout << "Assignment uploaded for " << unitCode << "\n";
    }

    void uploadCAT(const string& unitCode) {
        cout << "CAT uploaded for " << unitCode << "\n";
    }

    void enterMarks(Student& student, const string& unitCode, double cat, double assignment, double exam) {
        Result result;
        result.unitCode = unitCode;
        result.cat = cat;
        result.assignment = assignment;
        result.exam = exam;
        result.total = cat + assignment + exam;

        if (result.total >= 75) result.grade = 'A';
        else if (result.total >= 65) result.grade = 'B';
        else if (result.total >= 55) result.grade = 'C';
        else if (result.total >= 45) result.grade = 'D';
        else if (result.total >= 30) result.grade = 'E';
        else result.grade = 'F';

        student.setResult(result);
        cout << "Marks entered and synchronized to the student portal.\n";
    }

    string getStaffNumber() const { return staffNumber; }
};

class Admin : public Person {
public:
    Admin(string id = "", string name = "") : Person(id, name) {}

    void login() override {
        cout << "Administrator " << name << " logged in successfully.\n";
    }

    void addStudent(vector<Student>& students, const Student& student) {
        students.push_back(student);
        cout << "Student added successfully.\n";
    }

    void addLecturer(vector<Lecturer>& lecturers, const Lecturer& lecturer) {
        lecturers.push_back(lecturer);
        cout << "Lecturer added successfully.\n";
    }

    void manageUnit(vector<Unit>& units, const Unit& unit) {
        units.push_back(unit);
        cout << "Unit added to the system: " << unit.code << "\n";
    }
};

class StudentPortal {
private:
    vector<Student>& students;
public:
    StudentPortal(vector<Student>& allStudents) : students(allStudents) {}

    void showStudentMenu() {
        int choice = 0;
        while (choice != 3) {
            cout << "\n============================\n";
            cout << "STUDENT PORTAL\n";
            cout << "============================\n";
            cout << "1. View registered units\n";
            cout << "2. View grades\n";
            cout << "3. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                if (!students.empty()) {
                    students[0].viewRegisteredUnits();
                }
            } else if (choice == 2) {
                if (!students.empty()) {
                    students[0].viewGrades();
                }
            } else if (choice == 3) {
                cout << "Logging out from Student Portal...\n";
            } else {
                cout << "Invalid option.\n";
            }
        }
    }
};

class LMS {
private:
    vector<Lecturer>& lecturers;
    vector<Unit>& units;
public:
    LMS(vector<Lecturer>& allLecturers, vector<Unit>& allUnits) : lecturers(allLecturers), units(allUnits) {}

    void showLecturerMenu() {
        int choice = 0;
        while (choice != 5) {
            cout << "\n============================\n";
            cout << "LECTURER LMS\n";
            cout << "============================\n";
            cout << "1. Upload notes\n";
            cout << "2. Upload assignment\n";
            cout << "3. Upload CAT\n";
            cout << "4. Enter marks\n";
            cout << "5. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                if (!lecturers.empty()) {
                    lecturers[0].uploadNotes("SCO101");
                }
            } else if (choice == 2) {
                if (!lecturers.empty()) {
                    lecturers[0].uploadAssignment("SCO101");
                }
            } else if (choice == 3) {
                if (!lecturers.empty()) {
                    lecturers[0].uploadCAT("SCO101");
                }
            } else if (choice == 4) {
                if (!lecturers.empty() && !units.empty()) {
                    Student demoStudent("S001", "Jane Student", "SCT121-1234/2025");
                    demoStudent.registerUnit(units[0]);
                    lecturers[0].enterMarks(demoStudent, units[0].code, 20, 18, 40);
                    demoStudent.viewGrades();
                }
            } else if (choice == 5) {
                cout << "Logging out from LMS...\n";
            } else {
                cout << "Invalid option.\n";
            }
        }
    }
};

int main() {
    vector<Unit> units = {
        {"SCO101", "Object Oriented Programming"},
        {"SAD201", "System Analysis and Design"},
        {"DTP101", "Desktop Publishing"}
    };

    vector<Student> students = {
        Student("S001", "Jane Student", "SCT121-1234/2025")
    };

    vector<Lecturer> lecturers = {
        Lecturer("L001", "John Lecturer", "LEC001")
    };

    StudentPortal portal(students);
    LMS lms(lecturers, units);

    students[0].registerUnit(units[0]);
    students[0].registerUnit(units[1]);
    lecturers[0].addTeachingUnit("SCO101");
    lecturers[0].addTeachingUnit("SAD201");

    int menuChoice = 0;

    cout << "JKUAT UNIVERSITY INFORMATION SYSTEM\n";
    while (menuChoice != 4) {
        cout << "\n========================================\n";
        cout << "MAIN MENU\n";
        cout << "========================================\n";
        cout << "1. Student Portal\n";
        cout << "2. Lecturer LMS\n";
        cout << "3. Admin Panel\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> menuChoice;

        if (menuChoice == 1) {
            portal.showStudentMenu();
        } else if (menuChoice == 2) {
            lms.showLecturerMenu();
        } else if (menuChoice == 3) {
            Admin admin("A001", "System Admin");
            admin.login();
            admin.manageUnit(units, {"COM102", "Computer Networks"});
            admin.addStudent(students, Student("S002", "Mary Student", "SCT121-5678/2025"));
            admin.addLecturer(lecturers, Lecturer("L002", "Grace Lecturer", "LEC002"));
        } else if (menuChoice == 4) {
            cout << "Thank you for using JKUAT Information System.\n";
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
