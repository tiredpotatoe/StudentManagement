#include <iostream>
    #include <vector>
    #include <algorithm>
    #include <limits>

    using namespace std;

    /*************************************************************************** */

    struct Course {
        string name;
        int credits;
        float grade;
    };

    struct Student {
        string firstName, lastName;
        string studentID;
        string major;
        vector<Course> courses;
        float gpa;
    };

    /*************************************************************************** */

    vector<Student> students;

    /*************************************************************************** */
    
    void registerStudent();
    void addCourse();
    void listStudents(string majorFilter );
    void printTranscript();
    void deleteStudent();
    void searchStudent();

    /*************************************************************************** */

    int main() {
        int choice;
        //for some reason the thingies dont pop up so ima add a cin and check if the probram even starts or not
        cout << "Starting program...\n";

        do {
            cout << "\n1. Register Student\n2. Add Course\n3. List Students\n4. Print Transcript(results paper)\n5. Delete Student\n6. Search Student\n7. Exit\nOption: ";
            // cin >> choice;
            
            //update
            //when uh the user puts anything beside 1-6 it makes a weird loop so i wanted to add an if statement but i used .clear()
            if (!(cin >> choice)) { 
            cin.clear();  // Clears error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discards invalid input
            cout << "\nInvalid input! Please select an option.\n";
            continue;
            } 
            //update this somehow fucks up the program ima see why //nvm im stupid i put cin>>choice twice

            switch (choice) {
                case 1: registerStudent(); break;
                case 2: addCourse(); break;
                case 3: {
                    string major;
                    cout << "\nEnter major to filter (or press enter to list all): ";

                    // cin.ignore();
                    // getline(cin, major);
                    //update cin.ignore has a problem it like only removes one char and doesnt fully clear the uh buffer or whatever
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, major);

                    listStudents(major);
                    break;
                }
                case 4: printTranscript(); break;
                case 5: deleteStudent(); break;
                case 6: searchStudent(); break;
                case 7: cout << "\nExiting...\n"; break;
                default: cout << "\nInvalid choice!\n";
            }
        } while (choice != 7);
        return 0;
    }

    //--------------------------------------------------------------------------------------
    
    void registerStudent() {
        Student s;

        // cout << "Enter first name: \n"; cin >> s.firstName;
        // cout << "Enter last name: \n"; cin >> s.lastName;
        //update this has a space thingi problem
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Enter first name: "; getline(cin, s.firstName);
        cout << "Enter last name: "; getline(cin, s.lastName);
        cout << "Enter student ID: \n"; cin >> s.studentID;
        //update had to add cin.ignore cuz the uh new line in studentID fucks up the function
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter major: \n"; getline(cin, s.major); //cin >> s.major;

        s.gpa = 0;

        students.push_back(s); //this uh adds to the vector
        cout << "Student registered successfully!\n";
    }

    //------------------------------------------------------------------------------------------

    // void addCourse() {
    //     string id;
    //     cout << "Enter student ID: "; cin >> id;
    //     for (auto &s : students) {
    //         if (s.studentID == id) {
    //             Course c;
    //             // cout << "Enter course name: \n"; cin >> c.name;
    //             //again space problem
    //             cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //             cout << "Enter course name: "; getline(cin, c.name);

    //             cout << "Enter credits(vahed dars): \n"; cin >> c.credits;
    //             cout << "Enter grade: \n"; cin >> c.grade;
    //             s.courses.push_back(c);
    //             float totalGrade = 0, totalCredits = 0;
    //             for (auto &course : s.courses) {
    //                 totalGrade += course.grade * course.credits;
    //                 totalCredits += course.credits;
    //             }
    //             // s.gpa = totalGrade / totalCredits;
    //             //this had a uh division by zero problem
    //             s.gpa = (totalCredits > 0) ? (totalGrade / totalCredits) : 0;

    //             cout << "Course added successfully!\n";
    //             return;
    //         }
    //     }
    //     cout << "Student not found!\n";
    // }
    //update
    void addCourse() {
        string id;
        cout << "Enter student ID: "; cin >> id;

        for (auto &s : students) {
            if (s.studentID == id) {
                int numCourses;
                cout << "How many courses do you want to add? ";  
                
                while (!(cin >> numCourses) || numCourses <= 0) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Invalid number! Please enter a positive integer: ";
                }

                for (int i = 0; i < numCourses; i++) {
                    Course c;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    cout << "\nEnter course #" << (i + 1) << " name: "; 
                    getline(cin, c.name);
                    
                    cout << "Enter credits (vahed dars): ";
                    while (!(cin >> c.credits) || c.credits <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid credits! Please enter a positive integer: ";
                    }

                    cout << "Enter grade: ";
                    while (!(cin >> c.grade) || c.grade < 0 || c.grade > 20) { 
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid grade! Please enter a value between 0 and 20: ";
                    }

                    s.courses.push_back(c);
                }

                float totalGrade = 0, totalCredits = 0;
                for (auto &course : s.courses) {
                    totalGrade += course.grade * course.credits;
                    totalCredits += course.credits;
                }
                s.gpa = (totalCredits > 0) ? (totalGrade / totalCredits) : 0;

                cout << "\nCourses added successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }


    /*************************************************************************** */

    void listStudents(string majorFilter = "") {

        //update this will still search if  student is empty so i had to change/check
        if (students.empty()) {
        cout << "No students available!\n";
        return;
        }   

        vector<Student> filteredStudents;
        for (const auto &s : students) {
            if (majorFilter.empty() || s.major == majorFilter) {
                filteredStudents.push_back(s);
            }
        }

        sort(filteredStudents.begin(), filteredStudents.end(), [](const Student &a, const Student &b) {
            return a.gpa > b.gpa;
        });

        for (const auto &s : filteredStudents) {
            cout << s.firstName << " " << s.lastName << " | " << s.studentID << " | " << s.major << " | GPA: " << s.gpa << endl;
        }
    }

    /*************************************************************************** */

    void printTranscript() {

        string id;
        cout << "Enter student ID: \n"; cin >> id;

        for (const auto &s : students) {

            if (s.studentID == id) {
                cout << "****~Transcript~****\n";
                cout << "Name: " << s.firstName << " " << s.lastName << "\n";
                cout << "Student ID: " << s.studentID << "\n";
                cout << "Major: " << s.major << "\n";
                cout << "GPA: " << s.gpa << "\n\n";
                cout << "Courses: \n";

                for (const auto &c : s.courses) {
                    cout << "- " << c.name << " (" << c.credits << " credits) | Grade: " << c.grade << "\n";
                }
                return;
            }
        }
        cout << "Student not found!\n";
    }

    /*************************************************************************** */

    void deleteStudent() {
        string id;
        cout << "Enter student ID to delete: "; cin >> id;

        auto it = remove_if(students.begin(), students.end(), [&](const Student &s) {
            return s.studentID == id;
        });

        if (it != students.end()) {
            students.erase(it, students.end());
            cout << "Student deleted successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

    /***************************************************************************************************** */

    void searchStudent() {
    string query;
    cout << "\nEnter student name or ID to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, query);

    bool found = false;
    for (const auto &s : students) {
        if (s.firstName == query || s.lastName == query || s.studentID == query) {
            cout << "\nStudent Found:\n";
            cout << "Name: " << s.firstName << " " << s.lastName << "\n";
            cout << "Student ID: " << s.studentID << "\n";
            cout << "Major: " << s.major << "\n";
            cout << "GPA: " << s.gpa << "\n";
            cout << "Courses: \n";
            for (const auto &c : s.courses) {
                cout << "- " << c.name << " (" << c.credits << " credits) | Grade: " << c.grade << "\n";
            }
            found = true;
        }
    }

    if (!found) {
        cout << "No matching student found!\n";
    }
}

