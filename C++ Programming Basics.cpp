#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Constants for the number of classes and students per class
const int NUM_BIO_CLASSES = 3;
const int NUM_MATH_CLASSES = 5;
const int STUDENTS_PER_CLASS = 40;

// Structure to store student information
struct Student {
    string name;
    int marks[3];  // Marks for Biology, Physics, and Chemistry
    int totalMarks;
    int classRank;
    int schoolRank;
};

// Function to calculate the total marks for a student
int calculateTotalMarks(const int marks[], int numSubjects) {
    int total = 0;
    for (int i = 0; i < numSubjects; i++) {
        total += marks[i];
    }
    return total;
}

// Function to read student marks from a file
void readStudentMarks(const string& filename, vector<Student>& students) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    Student student;
    while (inputFile >> student.name) {
        for (int i = 0; i < 3; i++) {
            inputFile >> student.marks[i];
        }
        student.totalMarks = calculateTotalMarks(student.marks, 3);
        students.push_back(student);
    }

    inputFile.close();
}

// Function to compare students based on total marks
bool compareStudents(const Student& a, const Student& b) {
    return a.totalMarks > b.totalMarks;
}

// Function to calculate class rank for students in a specific stream and class
void calculateClassRank(vector<Student>& students, int numClasses) {
    for (int c = 0; c < numClasses; c++) {
        // Get the range of students in the current class
        int startIdx = c * STUDENTS_PER_CLASS;
        int endIdx = startIdx + STUDENTS_PER_CLASS;

        // Sort the students in the current class based on total marks
        sort(students.begin() + startIdx, students.begin() + endIdx, compareStudents);

        // Assign class ranks to students in the current class
        for (int i = startIdx; i < endIdx; i++) {
            students[i].classRank = i - startIdx + 1;
        }
    }
}

// Function to calculate school rank for all students
void calculateSchoolRank(vector<Student>& students) {
    sort(students.begin(), students.end(), compareStudents);

    for (int i = 0; i < students.size(); i++) {
        students[i].schoolRank = i + 1;
    }
}

// Function to display student ranks
void displayRanks(const vector<Student>& students) {
    cout << "-------------------------------------" << endl;
    cout << "Name\t\tClass Rank\tSchool Rank" << endl;
    cout << "-------------------------------------" << endl;

    for (const auto& student : students) {
        cout << setw(10) << left << student.name << "\t";
        cout << setw(10) << student.classRank << "\t";
        cout << setw(10) << student.schoolRank << endl;
    }

    cout << "-------------------------------------" << endl;
}

// Function to write student ranks to a file
void writeRanksToFile(const string& filename, const vector<Student>& students) {
    ofstream outputFile(filename);
