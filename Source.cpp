#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Student {
    int group = 0;
    int faculty_number = 0;
    int num_of_courses = 0;
    string first_name;
    string middle_name;
    string last_name;
    string courses[10];
    double grades[10] = { 0 };
    double average_grade = 0;
};

string group_file_name(int group) {
    string group_name;
    switch (group) {
    case 1:
        group_name = "1.txt";
        break;
    case 2:
        group_name = "2.txt";
        break;
    case 3:
        group_name = "3.txt";
        break;
    case 4:
        group_name = "4.txt";
        break;
    case 5:
        group_name = "5.txt";
        break;
    case 6:
        group_name = "6.txt";
        break;
    case 7:
        group_name = "7.txt";
        break;
    case 8:
        group_name = "8.txt";
        break;
    default:
        group_name = "none";
    }
    return group_name;
}

void get_student_info(string file_name, Student s) {
    fstream file;
    file.open(file_name, ios::app);
    file << "\n";
    file << s.faculty_number << " ";
    file << s.group << " ";
    file << s.first_name << " ";
    file << s.middle_name << " ";
    file << s.last_name << " ";
    file << s.num_of_courses << " ";
    file << s.average_grade << " ";
    for (int course_index = 0; course_index < s.num_of_courses; course_index++) {
        file << s.courses[course_index] << " ";
        file << s.grades[course_index] << " ";
    }
    file.close();
}

void add_student(int group, string group_name) {
    Student student;
    double sum = 0;
    student.group = group;
    cout << "Enter the first name: " << endl;
    cin >> student.first_name;
    cout << "Enter the middle name: " << endl;
    cin >> student.middle_name;
    cout << "Enter the last name: " << endl;
    cin >> student.last_name;
    cout << "Enter the faculty number: " << endl;
    cin >> student.faculty_number;
    do {
        cout << "Number of courses (between 1 and 10): " << endl;
        cin >> student.num_of_courses;
    } while (student.num_of_courses < 1 || student.num_of_courses > 10);
    for (int course_index = 0; course_index < student.num_of_courses; course_index++) {
        cout << "Name of course: " << endl;
        cin >> student.courses[course_index];
        cout << "Grade: " << endl;
        cin >> student.grades[course_index];
        sum = sum + student.grades[course_index];
    }
    student.average_grade = sum / student.num_of_courses;
    get_student_info("all.txt", student);
    get_student_info(group_name, student);
}

void show_records(string file_name) {
    ifstream file;
    file.open(file_name, ios::in);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int delete_from_all(int faculty_num, string file_name) {
    Student s;
    int group = 0;
    ifstream file;
    file.open(file_name);
    ofstream temp;
    temp.open("temp.txt");
    string line;
    while (getline(file, line)) {
        string data[2];
        stringstream stream(line);
        getline(stream, data[0], ' ');
        s.faculty_number = stoi(data[0]);
        getline(stream, data[1], ' ');
        s.group = stoi(data[1]);
        if (faculty_num != s.faculty_number) {
            temp << line << endl;
        }
        else {
            group = s.group;
        }
    }        
    temp.close();
    file.close();
    remove(file_name.c_str());
    if (rename("temp.txt", file_name.c_str()) == 0) {
        cout << "Succes";
    }
    else {
        cout << "Error while deleting";
    }
    return group;
}
void delete_from_group(string file_name, int faculty_num) {
    Student s;
    int group = 0;
    ifstream file;
    file.open(file_name);
    ofstream temp;
    temp.open("temp.txt");
    string line;
    while (getline(file, line)) {
        string data[2];
        stringstream stream(line);
        getline(stream, data[0], ' ');
        s.faculty_number = stoi(data[0]);
        if (faculty_num != s.faculty_number) {
            temp << line << endl;
        }
    }
    temp.close();
    file.close();
    remove(file_name.c_str());
    if (rename("temp.txt", file_name.c_str()) == 0) {
        cout << "Succes";
    }
    else {
        cout << "Error while deleting";
    }
}

int main() {
    int choice;
    do {
        cout << endl;
        cout << "Choose your choice:" << endl;
        cout << "1.Add new student" << endl;
        cout << "2.Delete student" << endl;
        cout << "3.Sort by average grade" << endl;
        cout << "4.Sort by faculty number" << endl;
        cout << "5.Dispaly records" << endl;
        cout << "6.Exit" << endl;
        cout << "Enter your choice:" << endl;
        cin >> choice;
        switch (choice) {
        case 1: {
            int group;
            cout << "Group: " << endl;
            cin >> group;
            string group_file = group_file_name(group);
            add_student(group, group_file);
            break;
        }
        case 2: {
            int faculty_num;
            cout << "Enter the faculty number: ";
            cin >> faculty_num;
            int group = delete_from_all(faculty_num, "all.txt");
            string group_file = group_file_name(group);
            delete_from_group(group_file, faculty_num);
            break;
        }
        case 3: {
            //sort_by_average_grade;
            break;
        }
        case 4: {
            //sort_by_faculty_number;
            break;
        }
        case 5: {
            int option;
            cout << "To see all students records enter 0 OR enter the group to see records of the students of that group" << endl;
            cin >> option;
            if (option) {
                string group_file = group_file_name(option);
                show_records(group_file);
            }
            else {
                show_records("all.txt");
            }
            break;
        }
        case 6: {
            exit(0);
        }
        default:
            cout << "Invalid Choice";
        }
    } while (choice != 6);
    return 0;
}

