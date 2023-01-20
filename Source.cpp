#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
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

int add_student(int group, string group_name) {
    Student student;
    double sum = 0;
    student.group = group;
    cout << "Enter the first name: " << endl;
    cin >> student.first_name;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        return 1;
    }
    cout << "Enter the middle name: " << endl;
    cin >> student.middle_name;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        return 1;
    }
    cout << "Enter the last name: " << endl;
    cin >> student.last_name;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        return 1;
    }
    cout << "Enter the faculty number: " << endl;
    cin >> student.faculty_number;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        return 1;
    }
    do {
        cout << "Number of courses (between 1 and 10): " << endl;
        cin >> student.num_of_courses;
        if (cin.fail()) {
            cout << "Invalid input" << endl;
            return 1;
        }
    } while (student.num_of_courses < 1 || student.num_of_courses > 10);
    for (int course_index = 0; course_index < student.num_of_courses; course_index++) {
        cout << "Name of course: " << endl;
        cin >> student.courses[course_index];
        if (cin.fail()) {
            cout << "Invalid input" << endl;
            return 1;
        }
        do {
            cout << "Grade: " << endl;
            cin >> student.grades[course_index];
            if (cin.fail()) {
                cout << "Invalid input" << endl;
                return 1;
            }
        } while (student.grades[course_index] < 2 || student.grades[course_index] > 6);
        sum = sum + student.grades[course_index];
    }
    student.average_grade = sum / student.num_of_courses;
    write_student_info_into_file("all.txt", student);
    write_student_info_into_file(group_name, student);
    return 0;
}

const int set_fn = 6, set_group = 6, set_name = 20, set_avg = 8, set_course_grade = 16, set_between = 10;
    ifstream file;
    file.open(file_name, ios::in);
    string line;
    cout << left;
    cout << setw(set_fn) << "Fn" << setw(set_group) << "Group" << setw(set_name) << "First name"
        << setw(set_name) << "Middle name" << setw(set_name) << "Last name"
        << setw(set_avg) << "Avg" << setw(set_course_grade) << "Course - grade" << endl;
    while (getline(file, line)) {
        if (!line.empty()) {
            const int max_num_of_info = 27;
            string data[max_num_of_info];
            int word_counter = 0;
            stringstream stream(line);
            while (getline(stream, data[word_counter], ' ')) {
                word_counter++;
            }
            int word_index = 0;
            cout << setw(set_fn) << stoi(data[word_index]);
            cout << setw(set_group) << stoi(data[++word_index]);
            cout << setw(set_name) << data[++word_index];
            cout << setw(set_name) << data[++word_index];
            cout << setw(set_name) << data[++word_index];
            int num_of_courses = stoi(data[++word_index]);
            double average_grade = stod(data[++word_index]);
            cout << setw(set_avg) << setprecision(3) << average_grade;
            for (int course_index = 0; course_index < num_of_courses; course_index++) {
                string course = data[++word_index];
                string grade = data[++word_index];
                course = course + " - " + grade;
                cout << setw(set_course_grade) << course << setw(set_between);
            }
            cout << endl;
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
            string data[2];//we need only the faculty number and the group of the student
            stringstream stream(line);
            getline(stream, data[0], ' ');//data[0] - the faculty name
            s.faculty_number = stoi(data[0]);
            getline(stream, data[1], ' ');//data[1] - the group number
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
        cout << "Error while renaming the file";
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
             string data[1];//we need only the faculty number
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
       cout << "Error while renaming the file";
    }
}

void edit_record(Student& record2, Student& record1) {
    record2.faculty_number = record1.faculty_number;
    record2.group = record1.group;
    record2.first_name = record1.first_name;
    record2.middle_name = record1.middle_name;
    record2.last_name = record1.last_name;
    record2.num_of_courses = record1.num_of_courses;
    record2.average_grade = record1.average_grade;
    for (int course_index = 0; course_index < record1.num_of_courses; course_index++) {
        record2.courses[course_index] = record1.courses[course_index];
        record2.grades[course_index] = record1.grades[course_index];
    }
}

void swap_students(Student &s1, Student &s2) {
    Student temp;
    edit_record(temp, s1);
    edit_record(s1, s2);
    edit_record(s2, temp);
}

void sort_by_faculty_number(Student* s, int size, string order) {
    for (int i = 0; i < size - 1; i++) {
       for (int j = 0; j < size - i - 1; j++){
           if (order == "ascending"){
               if (s[j].faculty_number > s[j + 1].faculty_number) {
                   swap_students(s[j], s[j + 1]);
               }
           }
           else if (order == "descending") {
               if (s[j].faculty_number < s[j + 1].faculty_number) {
                   swap_students(s[j], s[j + 1]);
               }
           }
       }
    }
}

void sort_by_average_grade(Student* s, int size, string order) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (order == "ascending") {
                if (s[j].average_grade > s[j + 1].average_grade) {
                    swap_students(s[j], s[j + 1]);
                }
            }
            else if (order == "descending") {
                if (s[j].average_grade < s[j + 1].average_grade) {
                    swap_students(s[j], s[j + 1]);
                }
            }
        }
    }
}

void sort_students(string file_name, string option, string order) {
    const int max_students = 200;
    Student* s = new Student[max_students];
    ifstream file;
    file.open(file_name);
    ofstream temp;
    temp.open("temp.txt");
    string line[max_students];
    int record_count = 0;
    while (getline(file, line[record_count])) {
        if (!line[record_count].empty()) {
            const int max_num_of_info = 27;
            string data[max_num_of_info];
            int word_count = 0;
            stringstream stream(line[record_count]);
            while (getline(stream, data[word_count], ' ')) {
                word_count++;
            }
            int word_index = 0;
            s[record_count].faculty_number = stoi(data[word_index]);
            s[record_count].group = stoi(data[++word_index]);
            s[record_count].first_name = data[++word_index];
            s[record_count].middle_name = data[++word_index];
            s[record_count].last_name = data[++word_index];
            s[record_count].num_of_courses = stoi(data[++word_index]);
            s[record_count].average_grade = stod(data[++word_index]);
            for (int course_index = 0; course_index < s[record_count].num_of_courses; course_index++) {
                s[record_count].courses[course_index] = data[++word_index];
                s[record_count].grades[course_index] = stod(data[++word_index]);
            }
            record_count++;
        }
    }
    file.close();
    if (option == "faculty_number") {
       sort_by_faculty_number(s, record_count, order);
    }
    else if (option == "average_grade"){
       sort_by_average_grade(s, record_count, order);
    }
    for (int i = 0; i < record_count; i++) {
       write_student_info_into_file("temp.txt", s[i]);
    }
    delete[] s;
    temp.close();
    remove(file_name.c_str());
    if (rename("temp.txt", file_name.c_str()) != 0) {
        cout << "Error while renaming the file";
    }
}

void combine_groups(int groups[], int size) {
    ofstream temp;
    temp.open("combine.txt", ios::ate);
    for (int index = 0; index < size; index++){
        string file_name = group_file_name(groups[index]);
        ifstream file;
        file.open(file_name);
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                temp << line << '\n';
            }
        }
        file.close();
    }
    temp.close();
    cout << endl;
    show_records("combine.txt");
    cout << "Info saved in the file combine.txt " << endl;
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
        cout << "6.Combine groups" << endl;
        cout << "7.Exit" << endl;
        cout << "Enter your choice:" << endl;
        cin >> choice;
        if (cin.fail()) {
            cout << "You didn't enter integer" << endl;
            return 1;
        }
        switch (choice) {
        case 1: {
            int group;
            cout << "Group: " << endl;
            cin >> group;
            if (cin.fail()) {
                cout << "Invalid input" << endl;
                return 1;
            }
            string group_file = group_file_name(group);
            add_student(group, group_file);
            break;
        }
        case 2: {
            int faculty_num;
            cout << "Enter the faculty number: ";
            cin >> faculty_num;
            if (cin.fail()) {
                cout << "Invalid input" << endl;
                return 1;
            }
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
            string order;
            cout << "To see all students records sorted by average grade enter 0. ";
            cout << "To see sorted combined group enter 9. ";
            cout << "Enter the group number to see sorted records of the students in the group" << endl;
            cin >> option;
            if (cin.fail()) {
                cout << "Invalid input" << endl;
                return 1;
            }
            cout << "Enter in which order to sort the records (ascending or descending)" << endl;
            cin >> order;
            if (option > 0 && option < 9) {
                string group_file = group_file_name(option);
                sort_students(group_file, "average_grade", order);
                show_records(group_file);
            }
            else if (option == 0) {
                sort_students("all.txt", "average_grade",order);
                show_records("all.txt");
            }
            else if (option == 9) {
                sort_students("combine.txt", "average_grade", order);
                show_records("combine.txt");
            }
            else {
                cout << "Invalid choice";
            }
            break;
        }
        case 4: {
            int option;
            string order;
            cout << "To see all students records sorted by faculty number enter 0. ";
            cout << "To see sorted combined group enter 9. ";
            cout << "Or enter the group number to see sorted records of the students in the group" << endl;
            cin >> option;
            if (cin.fail()) {
                cout << "Invalid input" << endl;
                return 1;
            }
            cout << "Enter in which order to sort the records (ascending or descending)" << endl;
            cin >> order;
            if (option > 0 && option < 9) {
                string group_file = group_file_name(option);
                sort_students(group_file, "faculty_number", order);
                show_records(group_file);
            }
            else if (option == 0) {
                sort_students("all.txt", "faculty_number", order);
                show_records("all.txt");
            }
            else if (option == 9) {
                sort_students("combine.txt", "faculty_number", order);
                show_records("combine.txt");
            }
            else {
                cout << "Invalid choice";
            }
            break;
        }
        case 5: {
            int option;
            cout << "To see all students records enter 0. ";
            cout << "To see combined records enter 9. ";
            cout << "Or enter the group number to see records of the students in the group" << endl;
            cin >> option;
            if (cin.fail()) {
                cout << "Invalid input" << endl;
                return 1;
            }
            if (option > 0 && option < 9) {
                string group_file = group_file_name(option);
                show_records(group_file);
            }
            else if (option == 0) {
                show_records("all.txt");
            }
            else if (option == 9) {
                show_records("combine.txt");
            }
            else {
                cout << "Invalid choice";
            }
            break;
        }
        case 6: {
            int num_groups;
            cout << "Enter how many groups you want to combine (between 2 and 7).";
            cout << "If you want to see all combined choose \"Show records\" and enter 0" << endl;
            cin >> num_groups;
            if (cin.fail()) {
                cout << "Invalid input" << endl;
                return 1;
            }
            if (num_groups < 2 || num_groups > 7) {
                cout << "Invalid number of groups" << endl;
            }
            else {
                int temp = 0, index = 0;
                bool is_fine = 1;
                int* groups = new int[num_groups];
                while(index < num_groups) {
                    cout << "Group: ";
                    cin >> temp;
                    if (cin.fail()) {
                        cout << "Invalid input" << endl;
                        return 1;
                    }
                    if (temp > 0 && temp < 9) {
                        groups[index] = temp;
                        temp = 0;
                        index++;
                    }
                    else {
                        cout << "Invalid group" << endl;
                        is_fine = 0;
                    }
                }
                if (is_fine) {
                  combine_groups(groups, num_groups);
                }
            }
            break;
        }
        case 7: {
            exit(0);
        }
        default:
            cout << "Invalid choice";
        }
    } while (choice != 7);
    return 0;
}
