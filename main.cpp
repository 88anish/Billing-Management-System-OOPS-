#include <iostream>
#include <vector>
#include <set>

class Student {
private:
    std::string firstName;
    std::string lastName;
    int rollNumber;
    float cgpa;
    std::vector<int> courseIDs;

public:
    // Constructor
    Student(const std::string& fName, const std::string& lName, int roll, float gpa, const std::vector<int>& cIDs)
        : firstName(fName), lastName(lName), rollNumber(roll), cgpa(gpa), courseIDs(cIDs) {}

    // Getter functions
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    int getRollNumber() const { return rollNumber; }
    float getCGPA() const { return cgpa; }
    std::vector<int> getCourseIDs() const { return courseIDs; }
};

class StudentManagementSystem {
private:
    std::vector<Student> students;
    std::set<int> rollNumbers;

public:
    // Function to add a student
    bool addStudent(const Student& student) {
        if (rollNumbers.count(student.getRollNumber()) == 0) {
            students.push_back(student);
            rollNumbers.insert(student.getRollNumber());
            return true;
        } else {
            return false; // Roll number already exists
        }
    }

    // Function to find a student by roll number
    Student findStudentByRollNumber(int roll) const {
        for (const Student& student : students) {
            if (student.getRollNumber() == roll) {
                return student;
            }
        }
        // Return an empty student object if not found
        return Student("", "", -1, -1.0, {});
    }

    // ... Implement other functions for finding, deleting, updating students ...

    // Function to print the total number of students
    void printTotalStudents() const {
        std::cout << "Total number of students: " << students.size() << std::endl;
    }
};

int main() {
    StudentManagementSystem sms;

    int numStudents;
    std::cout << "Enter the number of students to add: ";
    std::cin >> numStudents;

    for (int i = 0; i < numStudents; i++) {
        std::cout << "Student " << i + 1 << ":\n";
        
        std::string firstName, lastName;
        int rollNumber;
        float cgpa;
        std::vector<int> courseIDs;

        std::cout << "Enter First Name: ";
        std::cin >> firstName;
        std::cout << "Enter Last Name: ";
        std::cin >> lastName;
        
        bool isUniqueRoll = false;
        while (!isUniqueRoll) {
            std::cout << "Enter Roll Number: ";
            std::cin >> rollNumber;
            
            if (rollNumber < 0 || sms.findStudentByRollNumber(rollNumber).getRollNumber() != -1) {
                std::cout << "Invalid or duplicate Roll Number. Please enter a unique positive integer." << std::endl;
            } else {
                isUniqueRoll = true;
            }
        }
        
        std::cout << "Enter CGPA: ";
        std::cin >> cgpa;

        int numCourses;
        std::cout << "Enter the number of courses: ";
        std::cin >> numCourses;
        std::cout << "Enter the Course IDs:\n";
        for (int j = 0; j < numCourses; j++) {
            int courseID;
            std::cin >> courseID;
            courseIDs.push_back(courseID);
        }

        Student student(firstName, lastName, rollNumber, cgpa, courseIDs);
        bool added = sms.addStudent(student);
        if (added) {
            std::cout << "Student added successfully.\n";
        } else {
            std::cout << "Failed to add student. Roll Number already exists.\n";
            i--; // Retry entering details for the same student
        }
    }

    int rollNumber;
    std::cout << "Enter the Roll Number to find a student: ";
    std::cin >> rollNumber;

    Student foundStudent = sms.findStudentByRollNumber(rollNumber);
    if (foundStudent.getRollNumber() == -1) {
        std::cout << "Student with roll number " << rollNumber << " not found." << std::endl;
    } else {
        std::cout << "Found student:\n";
        std::cout << "First Name: " << foundStudent.getFirstName() << std::endl;
        std::cout << "Last Name: " << foundStudent.getLastName() << std::endl;
        std::cout << "Roll Number: " << foundStudent.getRollNumber() << std::endl;
        std::cout << "CGPA: " << foundStudent.getCGPA() << std::endl;
        std::cout << "Course IDs:";
        for (int courseID : foundStudent.getCourseIDs()) {
            std::cout << " " << courseID;
        }
        std::cout << std::endl;
    }

    sms.printTotalStudents();

    return 0;
}
