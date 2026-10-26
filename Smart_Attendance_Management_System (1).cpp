f#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;
const int MAX_STUDENTS = 200;
const int MAX_FACULTY = 100;
const int MAX_SUBJECTS = 100;
const int MAX_ATTENDANCE = 5000;
const float MIN_PERCENTAGE = 75.0f;
class Person
{
public:
    string name;
    string contact;
    string email;
    Person()
    {
        name = "";
        contact = "";
        email = "";
    }
    void takePerson()
    {
        cout << "Enter name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Enter contact number: ";
        getline(cin, contact);
        cout << "Enter email: ";
        getline(cin, email);
    }
    void displayPerson()
    {
        cout << "Name: " << name << endl;
        cout << "Contact: " << contact << endl;
        cout << "Email: " << email << endl;
    }
};
class Student : public Person
{
public:
    int roll;
    string prn;
    string className;
    char division;
    Student()
    {
        roll = 0;
        prn = "";
        className = "";
        division = 'A';
    }
    void takeStudent()
    {
        takePerson();
        cout << "Enter roll number: ";
        cin >> roll;
        cout << "Enter PRN: ";
        cin >> ws;
        getline(cin, prn);
        cout << "Enter class name: ";
        getline(cin, className);
        cout << "Enter division: ";
        cin >> division;
    }
    void displayStudent()
    {
        displayPerson();
        cout << "Roll number: " << roll << endl;
        cout << "PRN: " << prn << endl;
        cout << "Class: " << className << endl;
        cout << "Division: " << division << endl;
    }
};
class Faculty : public Person
{
public:
    int facultyId;
    string subjectCode;
    string subjectName;
    int theoryHours;
    int practicalHours;
    Faculty()
    {
        facultyId = 0;
        subjectCode = "";
        subjectName = "";
        theoryHours = 0;
        practicalHours = 0;
    }
    void takeFaculty()
    {
        takePerson();
        cout << "Enter faculty ID: ";
        cin >> facultyId;
        cout << "Enter subject code: ";
        cin >> ws;
        getline(cin, subjectCode);
        cout << "Enter subject name: ";
        getline(cin, subjectName);
        cout << "Enter theory hours: ";
        cin >> theoryHours;
        cout << "Enter practical hours: ";
        cin >> practicalHours;
    }
    void displayFaculty()
    {
        displayPerson();
        cout << "Faculty ID: " << facultyId << endl;
        cout << "Subject code: " << subjectCode << endl;
        cout << "Subject name: " << subjectName << endl;
        cout << "Theory hours: " << theoryHours << endl;
        cout << "Practical hours: " << practicalHours << endl;
    }
};
class Subject
{
public:
    string code;
    string name;
    string className;
    char division;
    int facultyId;
    Subject()
    {
        code = "";
        name = "";
        className = "";
        division = 'A';
        facultyId = 0;
    }
    void takeSubject()
    {
        cout << "Enter subject code: ";
        cin >> ws;
        getline(cin, code);
        cout << "Enter subject name: ";
        getline(cin, name);
        cout << "Enter class name: ";
        getline(cin, className);
        cout << "Enter division: ";
        cin >> division;
        cout << "Enter assigned faculty ID: ";
        cin >> facultyId;
    }
    void displaySubject()
    {
        cout << "Subject code: " << code << endl;
        cout << "Subject name: " << name << endl;
        cout << "Class: " << className << endl;
        cout << "Division: " << division << endl;
        cout << "Faculty ID: " << facultyId << endl;
    }
};
class Attendance
{
public:
    int roll;
    string subjectCode;
    string date;
    char status;
    Attendance()
    {
        roll = 0;
        subjectCode = "";
        date = "";
        status = 'A';
    }
    void takeAttendance()
    {
        cout << "Enter student roll number: ";
        cin >> roll;
        cout << "Enter subject code: ";
        cin >> ws;
        getline(cin, subjectCode);
        cout << "Enter date (DD-MM-YYYY): ";
        getline(cin, date);
        cout << "Enter status (P/A): ";
        cin >> status;
        if (status >= 'a' && status <= 'z')
        {
            status = static_cast<char>(status - 32);
        }
        while (status != 'P' && status != 'A')
        {
            cout << "Invalid status. Enter P or A: ";
            cin >> status;
            if (status >= 'a' && status <= 'z')
            {
                status = static_cast<char>(status - 32);
            }
        }
    }
    void displayAttendance()
    {
        cout << left << setw(12) << roll;
        cout << setw(18) << subjectCode;
        cout << setw(16) << date;
        cout << status << endl;
    }
};
Student students[MAX_STUDENTS];
Faculty faculties[MAX_FACULTY];
Subject subjects[MAX_SUBJECTS];
Attendance records[MAX_ATTENDANCE];
int studentCount = 0;
int facultyCount = 0;
int subjectCount = 0;
int attendanceCount = 0;
int findStudentIndex(int roll)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].roll == roll)
        {
            return i;
        }
    }
    return -1;
}
int findFacultyIndex(int id)
{
    for (int i = 0; i < facultyCount; i++)
    {
        if (faculties[i].facultyId == id)
        {
            return i;
        }
    }
    return -1;
}
int findSubjectIndex(string code)
{
    for (int i = 0; i < subjectCount; i++)
    {
        if (subjects[i].code == code)
        {
            return i;
        }
    }
    return -1;
}
void saveStudents()
{
    ofstream file("students.txt");
    if (!file)
    {
        cout << "Unable to save student file." << endl;
        return;
    }
    file << studentCount << endl;
    for (int i = 0; i < studentCount; i++)
    {
        file << students[i].name << endl;
        file << students[i].contact << endl;
        file << students[i].email << endl;
        file << students[i].roll << endl;
        file << students[i].prn << endl;
        file << students[i].className << endl;
        file << students[i].division << endl;
    }
    file.close();
}
void loadStudents()
{
    ifstream file("students.txt");
    if (!file)
    {
        return;
    }
    file >> studentCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    if (studentCount < 0 || studentCount > MAX_STUDENTS)
    {
        studentCount = 0;
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        getline(file, students[i].name);
        getline(file, students[i].contact);
        getline(file, students[i].email);
        file >> students[i].roll;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, students[i].prn);
        getline(file, students[i].className);
        file >> students[i].division;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();
}
void saveFaculties()
{
    ofstream file("faculties.txt");
    if (!file)
    {
        cout << "Unable to save faculty file." << endl;
        return;
    }
    file << facultyCount << endl;
    for (int i = 0; i < facultyCount; i++)
    {
        file << faculties[i].name << endl;
        file << faculties[i].contact << endl;
        file << faculties[i].email << endl;
        file << faculties[i].facultyId << endl;
        file << faculties[i].subjectCode << endl;
        file << faculties[i].subjectName << endl;
        file << faculties[i].theoryHours << endl;
        file << faculties[i].practicalHours << endl;
    }
    file.close();
}
void loadFaculties()
{
    ifstream file("faculties.txt");
    if (!file)
    {
        return;
    }
    file >> facultyCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    if (facultyCount < 0 || facultyCount > MAX_FACULTY)
    {
        facultyCount = 0;
        return;
    }
    for (int i = 0; i < facultyCount; i++)
    {
        getline(file, faculties[i].name);
        getline(file, faculties[i].contact);
        getline(file, faculties[i].email);
        file >> faculties[i].facultyId;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, faculties[i].subjectCode);
        getline(file, faculties[i].subjectName);
        file >> faculties[i].theoryHours;
        file >> faculties[i].practicalHours;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();
}
void saveSubjects()
{
    ofstream file("subjects.txt");
    if (!file)
    {
        cout << "Unable to save subject file." << endl;
        return;
    }
    file << subjectCount << endl;
    for (int i = 0; i < subjectCount; i++)
    {
        file << subjects[i].code << endl;
        file << subjects[i].name << endl;
        file << subjects[i].className << endl;
        file << subjects[i].division << endl;
        file << subjects[i].facultyId << endl;
    }
    file.close();
}
void loadSubjects()
{
    ifstream file("subjects.txt");
    if (!file)
    {
        return;
    }
    file >> subjectCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    if (subjectCount < 0 || subjectCount > MAX_SUBJECTS)
    {
        subjectCount = 0;
        return;
    }
    for (int i = 0; i < subjectCount; i++)
    {
        getline(file, subjects[i].code);
        getline(file, subjects[i].name);
        getline(file, subjects[i].className);
        file >> subjects[i].division;
        file >> subjects[i].facultyId;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();
}
void saveAttendance()
{
    ofstream file("attendance.txt");
    if (!file)
    {
        cout << "Unable to save attendance file." << endl;
        return;
    }
    file << attendanceCount << endl;
    for (int i = 0; i < attendanceCount; i++)
    {
        file << records[i].roll << endl;
        file << records[i].subjectCode << endl;
        file << records[i].date << endl;
        file << records[i].status << endl;
    }
    file.close();
}
void loadAttendance()
{
    ifstream file("attendance.txt");
    if (!file)
    {
        return;
    }
    file >> attendanceCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    if (attendanceCount < 0 || attendanceCount > MAX_ATTENDANCE)
    {
        attendanceCount = 0;
        return;
    }
    for (int i = 0; i < attendanceCount; i++)
    {
        file >> records[i].roll;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, records[i].subjectCode);
        getline(file, records[i].date);
        file >> records[i].status;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();
}
void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        cout << "Student storage is full." << endl;
        return;
    }
    Student temp;
    temp.takeStudent();
    if (findStudentIndex(temp.roll) != -1)
    {
        cout << "Roll number already exists." << endl;
        return;
    }
    students[studentCount] = temp;
    studentCount++;
    saveStudents();
    cout << "Student added successfully." << endl;
}
void displayStudents()
{
    if (studentCount == 0)
    {
        cout << "No student records found." << endl;
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        cout << endl << "Student " << i + 1 << endl;
        students[i].displayStudent();
    }
}
void searchStudent()
{
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;
    int index = findStudentIndex(roll);
    if (index == -1)
    {
        cout << "Student not found." << endl;
    }
    else
    {
        students[index].displayStudent();
    }
}
void updateStudent()
{
    int roll;
    cout << "Enter roll number to update: ";
    cin >> roll;
    int index = findStudentIndex(roll);
    if (index == -1)
    {
        cout << "Student not found." << endl;
        return;
    }
    cout << "Enter updated details." << endl;
    students[index].takeStudent();
    saveStudents();
    cout << "Student updated successfully." << endl;
}
void deleteStudent()
{
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;
    int index = findStudentIndex(roll);
    if (index == -1)
    {
        cout << "Student not found." << endl;
        return;
    }
    for (int i = index; i < studentCount - 1; i++)
    {
        students[i] = students[i + 1];
    }
    studentCount--;
    saveStudents();
    cout << "Student deleted successfully." << endl;
}
void studentMenu()
{
    int choice;
    do
    {
        cout << endl;
        cout << "========== STUDENT MANAGEMENT ==========" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Display students" << endl;
        cout << "3. Search student" << endl;
        cout << "4. Update student" << endl;
        cout << "5. Delete student" << endl;
        cout << "6. Return to main menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 6);
}
void addFaculty()
{
    if (facultyCount >= MAX_FACULTY)
    {
        cout << "Faculty storage is full." << endl;
        return;
    }
    Faculty temp;
    temp.takeFaculty();
    if (findFacultyIndex(temp.facultyId) != -1)
    {
        cout << "Faculty ID already exists." << endl;
        return;
    }
    faculties[facultyCount] = temp;
    facultyCount++;
    saveFaculties();
    cout << "Faculty added successfully." << endl;
}
void displayFaculties()
{
    if (facultyCount == 0)
    {
        cout << "No faculty records found." << endl;
        return;
    }
    for (int i = 0; i < facultyCount; i++)
    {
        cout << endl << "Faculty " << i + 1 << endl;
        faculties[i].displayFaculty();
    }
}
void searchFaculty()
{
    int id;
    cout << "Enter faculty ID to search: ";
    cin >> id;
    int index = findFacultyIndex(id);
    if (index == -1)
    {
        cout << "Faculty not found." << endl;
    }
    else
    {
        faculties[index].displayFaculty();
    }
}
void updateFaculty()
{
    int id;
    cout << "Enter faculty ID to update: ";
    cin >> id;
    int index = findFacultyIndex(id);
    if (index == -1)
    {
        cout << "Faculty not found." << endl;
        return;
    }
    cout << "Enter updated faculty details." << endl;
    faculties[index].takeFaculty();
    saveFaculties();
    cout << "Faculty updated successfully." << endl;
}
void deleteFaculty()
{
    int id;
    cout << "Enter faculty ID to delete: ";
    cin >> id;
    int index = findFacultyIndex(id);
    if (index == -1)
    {
        cout << "Faculty not found." << endl;
        return;
    }
    for (int i = index; i < facultyCount - 1; i++)
    {
        faculties[i] = faculties[i + 1];
    }
    facultyCount--;
    saveFaculties();
    cout << "Faculty deleted successfully." << endl;
}
void facultyMenu()
{
    int choice;
    do
    {
        cout << endl;
        cout << "========== FACULTY MANAGEMENT ==========" << endl;
        cout << "1. Add faculty" << endl;
        cout << "2. Display faculty" << endl;
        cout << "3. Search faculty" << endl;
        cout << "4. Update faculty" << endl;
        cout << "5. Delete faculty" << endl;
        cout << "6. Return to main menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addFaculty();
            break;
        case 2:
            displayFaculties();
            break;
        case 3:
            searchFaculty();
            break;
        case 4:
            updateFaculty();
            break;
        case 5:
            deleteFaculty();
            break;
        case 6:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 6);
}
void addSubject()
{
    if (subjectCount >= MAX_SUBJECTS)
    {
        cout << "Subject storage is full." << endl;
        return;
    }
    Subject temp;
    temp.takeSubject();
    if (findSubjectIndex(temp.code) != -1)
    {
        cout << "Subject code already exists." << endl;
        return;
    }
    if (findFacultyIndex(temp.facultyId) == -1)
    {
        cout << "Faculty ID does not exist." << endl;
        return;
    }
    subjects[subjectCount] = temp;
    subjectCount++;
    saveSubjects();
    cout << "Subject added successfully." << endl;
}
void displaySubjects()
{
    if (subjectCount == 0)
    {
        cout << "No subject records found." << endl;
        return;
    }
    for (int i = 0; i < subjectCount; i++)
    {
        cout << endl << "Subject " << i + 1 << endl;
        subjects[i].displaySubject();
    }
}
void searchSubject()
{
    string code;
    cout << "Enter subject code to search: ";
    cin >> ws;
    getline(cin, code);
    int index = findSubjectIndex(code);
    if (index == -1)
    {
        cout << "Subject not found." << endl;
    }
    else
    {
        subjects[index].displaySubject();
    }
}
void updateSubject()
{
    string code;
    cout << "Enter subject code to update: ";
    cin >> ws;
    getline(cin, code);
    int index = findSubjectIndex(code);
    if (index == -1)
    {
        cout << "Subject not found." << endl;
        return;
    }
    cout << "Enter updated subject details." << endl;
    subjects[index].takeSubject();
    saveSubjects();
    cout << "Subject updated successfully." << endl;
}
void deleteSubject()
{
    string code;
    cout << "Enter subject code to delete: ";
    cin >> ws;
    getline(cin, code);
    int index = findSubjectIndex(code);
    if (index == -1)
    {
        cout << "Subject not found." << endl;
        return;
    }
    for (int i = index; i < subjectCount - 1; i++)
    {
        subjects[i] = subjects[i + 1];
    }
    subjectCount--;
    saveSubjects();
    cout << "Subject deleted successfully." << endl;
}
void subjectMenu()
{
    int choice;
    do
    {
        cout << endl;
        cout << "========== SUBJECT AND CLASS MANAGEMENT ==========" << endl;
        cout << "1. Add subject and class" << endl;
        cout << "2. Display subjects and classes" << endl;
        cout << "3. Search subject" << endl;
        cout << "4. Update subject" << endl;
        cout << "5. Delete subject" << endl;
        cout << "6. Return to main menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addSubject();
            break;
        case 2:
            displaySubjects();
            break;
        case 3:
            searchSubject();
            break;
        case 4:
            updateSubject();
            break;
        case 5:
            deleteSubject();
            break;
        case 6:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 6);
}
void markAttendance()
{
    if (attendanceCount >= MAX_ATTENDANCE)
    {
        cout << "Attendance storage is full." << endl;
        return;
    }
    Attendance temp;
    temp.takeAttendance();
    if (findStudentIndex(temp.roll) == -1)
    {
        cout << "Student roll number does not exist." << endl;
        return;
    }
    if (findSubjectIndex(temp.subjectCode) == -1)
    {
        cout << "Subject code does not exist." << endl;
        return;
    }
    for (int i = 0; i < attendanceCount; i++)
    {
        if (records[i].roll == temp.roll &&
            records[i].subjectCode == temp.subjectCode &&
            records[i].date == temp.date)
        {
            cout << "Attendance already exists for this student, subject and date." << endl;
            return;
        }
    }
    records[attendanceCount] = temp;
    attendanceCount++;
    saveAttendance();
    cout << "Attendance marked successfully." << endl;
}
void displayAttendance()
{
    if (attendanceCount == 0)
    {
        cout << "No attendance records found." << endl;
        return;
    }
    cout << left << setw(12) << "Roll";
    cout << setw(18) << "Subject";
    cout << setw(16) << "Date";
    cout << "Status" << endl;
    cout << "----------------------------------------------------------" << endl;
    for (int i = 0; i < attendanceCount; i++)
    {
        records[i].displayAttendance();
    }
}
void updateAttendance()
{
    int roll;
    string code;
    string date;
    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter subject code: ";
    cin >> ws;
    getline(cin, code);
    cout << "Enter date: ";
    getline(cin, date);
    for (int i = 0; i < attendanceCount; i++)
    {
        if (records[i].roll == roll &&
            records[i].subjectCode == code &&
            records[i].date == date)
        {
            cout << "Enter new status (P/A): ";
            cin >> records[i].status;
            if (records[i].status >= 'a' && records[i].status <= 'z')
            {
                records[i].status = static_cast<char>(records[i].status - 32);
            }
            while (records[i].status != 'P' && records[i].status != 'A')
            {
                cout << "Invalid status. Enter P or A: ";
                cin >> records[i].status;
                if (records[i].status >= 'a' && records[i].status <= 'z')
                {
                    records[i].status = static_cast<char>(records[i].status - 32);
                }
            }
            saveAttendance();
            cout << "Attendance updated successfully." << endl;
            return;
        }
    }
    cout << "Attendance record not found." << endl;
}
void deleteAttendance()
{
    int roll;
    string code;
    string date;
    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter subject code: ";
    cin >> ws;
    getline(cin, code);
    cout << "Enter date: ";
    getline(cin, date);
    for (int i = 0; i < attendanceCount; i++)
    {
        if (records[i].roll == roll &&
            records[i].subjectCode == code &&
            records[i].date == date)
        {
            for (int j = i; j < attendanceCount - 1; j++)
            {
                records[j] = records[j + 1];
            }
            attendanceCount--;
            saveAttendance();
            cout << "Attendance record deleted." << endl;
            return;
        }
    }
    cout << "Attendance record not found." << endl;
}
void attendanceMenu()
{
    int choice;
    do
    {
        cout << endl;
        cout << "========== ATTENDANCE MARKING ==========" << endl;
        cout << "1. Mark attendance" << endl;
        cout << "2. Display attendance" << endl;
        cout << "3. Update attendance" << endl;
        cout << "4. Delete attendance record" << endl;
        cout << "5. Return to main menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            markAttendance();
            break;
        case 2:
            displayAttendance();
            break;
        case 3:
            updateAttendance();
            break;
        case 4:
            deleteAttendance();
            break;
        case 5:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 5);
}
int countStudentClasses(int roll, string code)
{
    int total = 0;
    for (int i = 0; i < attendanceCount; i++)
    {
        if (records[i].roll == roll && records[i].subjectCode == code)
        {
            total++;
        }
    }
    return total;
}
int countStudentPresent(int roll, string code)
{
    int present = 0;
    for (int i = 0; i < attendanceCount; i++)
    {
        if (records[i].roll == roll &&
            records[i].subjectCode == code &&
            records[i].status == 'P')
        {
            present++;
        }
    }
    return present;
}
float calculatePercentage(int roll, string code)
{
    int total = countStudentClasses(roll, code);
    int present = countStudentPresent(roll, code);
    if (total == 0)
    {
        return 0.0f;
    }
    return (static_cast<float>(present) / total) * 100.0f;
}
void studentAttendanceReport()
{
    int roll;
    cout << "Enter student roll number: ";
    cin >> roll;
    int index = findStudentIndex(roll);
    if (index == -1)
    {
        cout << "Student not found." << endl;
        return;
    }
    cout << endl;
    students[index].displayStudent();
    cout << endl;
    cout << left << setw(18) << "Subject Code";
    cout << setw(12) << "Present";
    cout << setw(12) << "Total";
    cout << setw(14) << "Percentage";
    cout << "Status" << endl;
    for (int s = 0; s < subjectCount; s++)
    {
        int total = countStudentClasses(roll, subjects[s].code);
        if (total > 0)
        {
            int present = countStudentPresent(roll, subjects[s].code);
            float percentage = calculatePercentage(roll, subjects[s].code);
            cout << left << setw(18) << subjects[s].code;
            cout << setw(12) << present;
            cout << setw(12) << total;
            cout << setw(14) << fixed << setprecision(2) << percentage;
            if (percentage < MIN_PERCENTAGE)
            {
                cout << "SHORTAGE";
            }
            else
            {
                cout << "OK";
            }
            cout << endl;
        }
    }
}
void subjectAttendanceReport()
{
    string code;
    cout << "Enter subject code: ";
    cin >> ws;
    getline(cin, code);
    int subjectIndex = findSubjectIndex(code);
    if (subjectIndex == -1)
    {
        cout << "Subject not found." << endl;
        return;
    }
    cout << "Subject: " << subjects[subjectIndex].name << endl;
    cout << left << setw(12) << "Roll";
    cout << setw(25) << "Student Name";
    cout << setw(12) << "Present";
    cout << setw(12) << "Total";
    cout << setw(14) << "Percentage";
    cout << "Status" << endl;
    for (int i = 0; i < studentCount; i++)
    {
        int total = countStudentClasses(students[i].roll, code);
        if (total > 0)
        {
            int present = countStudentPresent(students[i].roll, code);
            float percentage = calculatePercentage(students[i].roll, code);
            cout << left << setw(12) << students[i].roll;
            cout << setw(25) << students[i].name;
            cout << setw(12) << present;
            cout << setw(12) << total;
            cout << setw(14) << fixed << setprecision(2) << percentage;
            cout << (percentage < MIN_PERCENTAGE ? "SHORTAGE" : "OK");
            cout << endl;
        }
    }
}
void classAttendanceReport()
{
    string className;
    char division;
    cout << "Enter class name: ";
    cin >> ws;
    getline(cin, className);
    cout << "Enter division: ";
    cin >> division;
    cout << left << setw(12) << "Roll";
    cout << setw(25) << "Student Name";
    cout << setw(18) << "Class";
    cout << "Division" << endl;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].className == className &&
            students[i].division == division)
        {
            cout << left << setw(12) << students[i].roll;
            cout << setw(25) << students[i].name;
            cout << setw(18) << students[i].className;
            cout << students[i].division << endl;
        }
    }
}
void shortageReport()
{
    bool found = false;
    cout << left << setw(12) << "Roll";
    cout << setw(25) << "Student Name";
    cout << setw(18) << "Subject";
    cout << setw(14) << "Percentage" << endl;
    for (int i = 0; i < studentCount; i++)
    {
        for (int s = 0; s < subjectCount; s++)
        {
            int total = countStudentClasses(students[i].roll, subjects[s].code);
            if (total > 0)
            {
                float percentage = calculatePercentage(students[i].roll, subjects[s].code);
                if (percentage < MIN_PERCENTAGE)
                {
                    found = true;
                    cout << left << setw(12) << students[i].roll;
                    cout << setw(25) << students[i].name;
                    cout << setw(18) << subjects[s].code;
                    cout << setw(14) << fixed << setprecision(2) << percentage << endl;
                }
            }
        }
    }
    if (!found)
    {
        cout << "No attendance shortages found." << endl;
    }
}
void overallAnalytics()
{
    int totalRecords = attendanceCount;
    int presentRecords = 0;
    int absentRecords = 0;
    for (int i = 0; i < attendanceCount; i++)
    {
        if (records[i].status == 'P')
        {
            presentRecords++;
        }
        else
        {
            absentRecords++;
        }
    }
    float percentage = 0.0f;
    if (totalRecords > 0)
    {
        percentage = (static_cast<float>(presentRecords) / totalRecords) * 100.0f;
    }
    cout << "Total students: " << studentCount << endl;
    cout << "Total faculty: " << facultyCount << endl;
    cout << "Total subjects: " << subjectCount << endl;
    cout << "Total attendance entries: " << totalRecords << endl;
    cout << "Present entries: " << presentRecords << endl;
    cout << "Absent entries: " << absentRecords << endl;
    cout << "Overall attendance: " << fixed << setprecision(2) << percentage << "%" << endl;
}
void saveStudentReport()
{
    ofstream file("student_report.txt");
    if (!file)
    {
        cout << "Unable to create report file." << endl;
        return;
    }
    file << "STUDENT ATTENDANCE REPORT" << endl;
    file << "=========================" << endl;
    for (int i = 0; i < studentCount; i++)
    {
        file << "Roll: " << students[i].roll << endl;
        file << "Name: " << students[i].name << endl;
        file << "PRN: " << students[i].prn << endl;
        for (int s = 0; s < subjectCount; s++)
        {
            int total = countStudentClasses(students[i].roll, subjects[s].code);
            if (total > 0)
            {
                int present = countStudentPresent(students[i].roll, subjects[s].code);
                float percentage = calculatePercentage(students[i].roll, subjects[s].code);
                file << subjects[s].code << " ";
                file << present << "/" << total << " ";
                file << fixed << setprecision(2) << percentage << "%" << endl;
            }
        }
        file << "-------------------------" << endl;
    }
    file.close();
    cout << "Report saved to student_report.txt." << endl;
}
void reportsMenu()
{
    int choice;
    do
    {
        cout << endl;
        cout << "========== ATTENDANCE TRACKING AND REPORTS ==========" << endl;
        cout << "1. Student attendance report" << endl;
        cout << "2. Subject attendance report" << endl;
        cout << "3. Class report" << endl;
        cout << "4. Shortage report" << endl;
        cout << "5. Overall analytics" << endl;
        cout << "6. Save student report to file" << endl;
        cout << "7. Return to main menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            studentAttendanceReport();
            break;
        case 2:
            subjectAttendanceReport();
            break;
        case 3:
            classAttendanceReport();
            break;
        case 4:
            shortageReport();
            break;
        case 5:
            overallAnalytics();
            break;
        case 6:
            saveStudentReport();
            break;
        case 7:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 7);
}
void showFileMenu()
{
    int choice;
    do
    {
        cout << endl;
        cout << "========== FILE MANAGEMENT ==========" << endl;
        cout << "1. Save all records" << endl;
        cout << "2. Reload all records" << endl;
        cout << "3. Show saved file names" << endl;
        cout << "4. Return to main menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            saveStudents();
            saveFaculties();
            saveSubjects();
            saveAttendance();
            cout << "All records saved." << endl;
            break;
        case 2:
            loadStudents();
            loadFaculties();
            loadSubjects();
            loadAttendance();
            cout << "Records loaded from files." << endl;
            break;
        case 3:
            cout << "students.txt" << endl;
            cout << "faculties.txt" << endl;
            cout << "subjects.txt" << endl;
            cout << "attendance.txt" << endl;
            cout << "student_report.txt" << endl;
            break;
        case 4:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 4);
}
void displayMainMenu()
{
    cout << endl;
    cout << "==============================================" << endl;
    cout << " SMART ATTENDANCE TRACKING SYSTEM" << endl;
    cout << "==============================================" << endl;
    cout << "1. Student Management" << endl;
    cout << "2. Faculty Management" << endl;
    cout << "3. Subject and Class Management" << endl;
    cout << "4. Attendance Marking" << endl;
    cout << "5. Attendance Tracking and Calculation" << endl;
    cout << "6. Analytics, Reports and File Management" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}
int main()
{
    loadStudents();
    loadFaculties();
    loadSubjects();
    loadAttendance();
    int choice;
    do
    {
        displayMainMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            studentMenu();
            break;
        case 2:
            facultyMenu();
            break;
        case 3:
            subjectMenu();
            break;
        case 4:
            attendanceMenu();
            break;
        case 5:
            reportsMenu();
            break;
        case 6:
            showFileMenu();
            break;
        case 7:
            saveStudents();
            saveFaculties();
            saveSubjects();
            saveAttendance();
            cout << "All records saved. Thank you." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
    return 0;
}
