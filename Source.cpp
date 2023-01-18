#include <iostream>
#include <string>
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

void write_student_info_into_file(string file_name, Student s) {
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
    write_student_info_into_file("all.txt", student);
    write_student_info_into_file(group_name, student);
}

void show_records(string file_name) {
    ifstream file;
    file.open(file_name, ios::in);
    string line;
    while (getline(file, line)) {
        if (!line.empty()){
            cout << line << endl;
        }
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
        if (!line.empty()) {
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
    }        
    temp.close();
    file.close();
    remove(file_name.c_str());
    if (rename("temp.txt", file_name.c_str()) != 0) {
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
         if (!line.empty()) {
             string data[2];
             stringstream stream(line);
             getline(stream, data[0], ' ');
             s.faculty_number = stoi(data[0]);
             if (faculty_num != s.faculty_number) {
                 temp << line << endl;
             }
         }
    }
    temp.close();
    file.close();
    remove(file_name.c_str());
    if (rename("temp.txt", file_name.c_str()) != 0) {
       cout << "Error while deleting";
    }
}

void edit_record(Student& r2, Student& r1) {
    r2.faculty_number = r1.faculty_number;
    r2.group = r1.group;
    r2.first_name = r1.first_name;
    r2.middle_name = r1.middle_name;
    r2.last_name = r1.last_name;
    r2.num_of_courses = r1.num_of_courses;
    r2.average_grade = r1.average_grade;
    for (int course_index = 0; course_index < r1.num_of_courses; course_index++) {
        r2.courses[course_index] = r1.courses[course_index];
        r2.grades[course_index] = r1.grades[course_index];
    }
}

void swap_students(Student &s1, Student &s2) {
    Student temp;
    edit_record(temp, s1);
    edit_record(s1, s2);
    edit_record(s2, temp);
}

void sort_by_faculty_number(Student* s, int size) {
   int i, j;
   for (i = 0; i < size - 1; i++) {
       for (j = 0; j < size - i - 1; j++){
           if (s[j].faculty_number > s[j + 1].faculty_number) {
               swap_students(s[j], s[j+1]);
           }
       }
    }
}

void sort_by_average_grade(Student* s, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (s[j].average_grade < s[j + 1].average_grade) {
                swap_students(s[j], s[j + 1]);
            }
        }
    }
}

void sort_students(string file_name, string option) {
    Student s[25];
    ifstream file;
    file.open(file_name);
    ofstream temp;
    temp.open("temp.txt");
    string line[25];
    int record_count = 0;
    while (getline(file, line[record_count])) {
        if (!line[record_count].empty()) {
            string data[28];
            int i = 0;
            stringstream stream(line[record_count]);
            while (getline(stream, data[i], ' ')) {
                i++;
            }
            int j = 0;
            s[record_count].faculty_number = stoi(data[j]);
            s[record_count].group = stoi(data[++j]);
            s[record_count].first_name = data[++j];
            s[record_count].middle_name = data[++j];
            s[record_count].last_name = data[++j];
            s[record_count].num_of_courses = stoi(data[++j]);
            s[record_count].average_grade = stod(data[++j]);
            for (int course_index = 0; course_index < s[record_count].num_of_courses; course_index++) {
                s[record_count].courses[course_index] = data[++j];
                s[record_count].grades[course_index] = stod(data[++j]);
            }
            record_count++;
        }
    }
    file.close();
    if (option == "faculty_number") {
       sort_by_faculty_number(s, record_count);
    }
    else {
       sort_by_average_grade(s, record_count);
    }
    for (int i = 0; i < record_count; i++) {
       write_student_info_into_file("temp.txt", s[i]);
    }
    temp.close();
    remove(file_name.c_str());
    if (rename("temp.txt", file_name.c_str()) != 0) {
        cout << "Error while renaming the file";
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
            if (group > 0 && group < 9) {
                string group_file = group_file_name(group);
                delete_from_group(group_file, faculty_num);
            }
            else {
                cout << "There isn't a student with this faculty number!" << endl;
            }
            break;
        }
        case 3: {
            int option;
            cout << "To see all students records sorted by average grade enter 0 or enter the group number to see sorted records of the students in the group" << endl;
            cin >> option;
            if (option > 0 && option < 9) {
                string group_file = group_file_name(option);
                sort_students(group_file, "average_grade");
                show_records(group_file);
            }
            else if (option == 0){
                sort_students("all.txt", "average_grade");
                show_records("all.txt");
            }
            else {
                cout << "Invalid choice";
            }
            break;
        }
        case 4: {
            int option;
            cout << "To see all students records sorted by faculty number enter 0 or enter the group number to see sorted records of the students in the group" << endl;
            cin >> option;
            if (option > 0 && option < 9) {
                string group_file = group_file_name(option);
                sort_students(group_file, "faculty_number");
                show_records(group_file);
            }
            else if (option == 0) {
                sort_students("all.txt", "faculty_number");
                show_records("all.txt");
            }
            else {
                cout << "Invalid choice";
            }
            break;
        }
        case 5: {
            int option;
            cout << "To see all students records enter 0 or enter the group number to see records of the students in the group" << endl;
            cin >> option;
            if (option > 0 && option < 9) {
                string group_file = group_file_name(option);
                show_records(group_file);
            }
            else if (option == 0) {
                show_records("all.txt");
            }
            else {
                cout << "Invalid choice";
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

