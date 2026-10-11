#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 50;
string regNo[MAX];   // student registration numbers
int marks[MAX];      // marks for a unit
int cnt = 0;         // number of students stored

// Linear search: returns index or -1
int findStudent(const string &reg) {
    for (int i = 0; i < cnt; i++)
        if (regNo[i] == reg) return i;
    return -1;
}

void menu() {
    cout << "\n--------------------------------------------\n"
         << "          NIBS TECHNICAL COLLEGE\n"
         << "       STUDENT RECORDS MGT SYSTEM\n"
         << "--------------------------------------------\n"
         << "1. Insert Student\n"
         << "2. Display Students\n"
         << "3. Search Student\n"
         << "4. Update Student\n"
         << "5. Delete Student\n"
         << "6. Sort Students\n"
         << "7. Find Highest Mark\n"
         << "8. Find Lowest Mark\n"
         << "9. Calculate Average\n"
         << "10. Exit\n"
         << "--------------------------------------------\n"
         << "Enter your choice: ";
}

int readInt(const string &prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a number: ";
    }
    return x;
}

void insertStudent() {
    if (cnt == MAX) { cout << "Array full.\n"; return; }
    string reg;
    cout << "Registration number: ";
    cin >> reg;
    if (findStudent(reg) != -1) { cout << "Already exists.\n"; return; }
    int m = readInt("Mark (0-100): ");
    if (m < 0 || m > 100) { cout << "Invalid mark.\n"; return; }
    regNo[cnt] = reg;
    marks[cnt] = m;
    cnt++;
    cout << "Student added.\n";
}

void display() {
    if (cnt == 0) { cout << "No records.\n"; return; }
    cout << left << setw(6) << "No." << setw(20) << "Reg No" << "Mark\n";
    for (int i = 0; i < cnt; i++)
        cout << left << setw(6) << i + 1 << setw(20) << regNo[i] << marks[i] << "\n";
    cout << "Total students: " << cnt << "\n";
}

void searchStudent() {
    string reg;
    cout << "Registration number to search: ";
    cin >> reg;
    int i = findStudent(reg);
    if (i == -1) cout << "Not found.\n";
    else cout << "Found at position " << i + 1 << " | Mark: " << marks[i] << "\n";
}

void updateStudent() {
    string reg;
    cout << "Registration number to update: ";
    cin >> reg;
    int i = findStudent(reg);
    if (i == -1) { cout << "Not found.\n"; return; }
    int m = readInt("New mark (0-100): ");
    if (m < 0 || m > 100) { cout << "Invalid mark.\n"; return; }
    marks[i] = m;
    cout << "Updated.\n";
}

// Delete: shift elements left to fill the gap
void deleteStudent() {
    string reg;
    cout << "Registration number to delete: ";
    cin >> reg;
    int i = findStudent(reg);
    if (i == -1) { cout << "Not found.\n"; return; }
    for (int j = i; j < cnt - 1; j++) {
        regNo[j] = regNo[j + 1];
        marks[j] = marks[j + 1];
    }
    cnt--;
    cout << "Deleted.\n";
}

// Bubble sort by mark, highest first
void sortStudents() {
    for (int i = 0; i < cnt - 1; i++) {
        for (int j = 0; j < cnt - i - 1; j++) {
            if (marks[j] < marks[j + 1]) {
                swap(marks[j], marks[j + 1]);
                swap(regNo[j], regNo[j + 1]);
            }
        }
    }
    cout << "Sorted by mark (highest first).\n";
    display();
}

void highest() {
    if (cnt == 0) { cout << "No records.\n"; return; }
    int max = 0;
    for (int i = 1; i < cnt; i++) if (marks[i] > marks[max]) max = i;
    cout << "Highest: " << marks[max] << " (" << regNo[max] << ")\n";
}

void lowest() {
    if (cnt == 0) { cout << "No records.\n"; return; }
    int min = 0;
    for (int i = 1; i < cnt; i++) if (marks[i] < marks[min]) min = i;
    cout << "Lowest: " << marks[min] << " (" << regNo[min] << ")\n";
}

void average() {
    if (cnt == 0) { cout << "No records.\n"; return; }
    int sum = 0;
    for (int i = 0; i < cnt; i++) sum += marks[i];
    cout << "Count: " << cnt << " | Sum: " << sum
         << " | Average: " << (double)sum / cnt << "\n";
}

int main() {
    int choice;
    do {
        menu();
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter a number: ";
        }
        switch (choice) {
            case 1: insertStudent(); break;
            case 2: display(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortStudents(); break;
            case 7: highest(); break;
            case 8: lowest(); break;
            case 9: average(); break;
            case 10: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 10);
    return 0;
}