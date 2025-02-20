#include <iostream>
#include <string>

using namespace std;

const int MAX_ROOMS = 100;
const int MAX_STUDENTS = MAX_ROOMS * 6;

struct Student {
    string name;
    int id;
};

int main() {
    int totalRooms;
    cout << "Enter the total number of rooms in the dormitory: ";
    cin >> totalRooms;

    if (totalRooms <= 0 || totalRooms > MAX_ROOMS) {
        cout << "Invalid number of rooms. Exiting the program." << endl;
        return 0;
    }

    Student* students[MAX_STUDENTS] = {nullptr};
    int assignedRooms[MAX_ROOMS] = {0};

    while (true) {
        cout << "\nDormitory Services Menu\n";
        cout << "1. Assign room for students\n";
        cout << "2. Check whether a room is assigned or not\n";
        cout << "3. Update student's information\n";
        cout << "4. Search student's information\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int roomNumber;
                cout << "Enter the room number (1-" << totalRooms << "): ";
                cin >> roomNumber;

                if (roomNumber < 1 || roomNumber > totalRooms) {
                    cout << "Invalid room number!" << endl;
                    break;
                }

                if (assignedRooms[roomNumber - 1] == 1) {
                    cout << "Room " << roomNumber << " is already assigned." << endl;
                    break;
                }

                int availableIndex = -1;
                for (int i = (roomNumber - 1) * 6; i < roomNumber * 6; i++) {
                    if (students[i] == nullptr) {
                        availableIndex = i;
                        break;
                    }
                }

                if (availableIndex == -1) {
                    cout << "Room " << roomNumber << " is already full." << endl;
                    break;
                }

                string name;
                int id;
                cout << "Enter the name of the student: ";
                cin >> name;
                cout << "Enter the ID number of the student: ";
                cin >> id;

                students[availableIndex] = new Student{name, id};
                assignedRooms[roomNumber - 1] = 1;
                cout << "Student assigned to room " << roomNumber << " successfully." << endl;
                break;
            }
            case 2: {
                int roomNumber;
                cout << "Enter the room number (1-" << totalRooms << "): ";
                cin >> roomNumber;

                if (roomNumber < 1 || roomNumber > totalRooms) {
                    cout << "Invalid room number!" << endl;
                    break;
                }

                if (assignedRooms[roomNumber - 1] == 1) {
                    cout << "Room " << roomNumber << " is assigned." << endl;
                } else {
                    cout << "Room " << roomNumber << " is not assigned." << endl;
                }
                break;
            }
            case 3: {
                int roomNumber;
                cout << "Enter the room number (1-" << totalRooms << "): ";
                cin >> roomNumber;

                if (roomNumber < 1 || roomNumber > totalRooms) {
                    cout << "Invalid room number!" << endl;
                    break;
                }

                if (assignedRooms[roomNumber - 1] == 0) {
                    cout << "Room " << roomNumber << " is not assigned. Cannot update student information." << endl;
                    break;
                }

                int studentIndex = -1;
                for (int i = (roomNumber - 1) * 6; i < roomNumber * 6; i++) {
                    if (students[i] != nullptr) {
                        studentIndex = i;
                        break;
                    }
                }

                if (studentIndex == -1) {
                    cout << "No student found in room " << roomNumber << "." << endl;
                    break;
                }

                string name;
                int id;
                cout << "Enter the new name of the student: ";
                cin >> name;
                cout << "Enter the new ID number of the student: ";
                cin >> id;

                students[studentIndex]->name = name;
                students[studentIndex]->id = id;
                cout << "Student information updated successfully." << endl;
                break;
            }
            case 4: {
                string name;
                cout << "Enter the name of the student to search: ";
                cin >> name;

                bool found = false;
                for (int i = 0; i < MAX_STUDENTS; i++) {
                    if (students[i] != nullptr && students[i]->name == name) {
                        cout << "Student found in room " << (i / 6) + 1 << endl;
                        cout << "Name: " << students[i]->name << ", ID: " << students[i]->id << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 5:
                cout << "Exiting the program." << endl;
                // Cleanup memory
                for (int i = 0; i < MAX_STUDENTS; i++) {
                    delete students[i];
                }
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    }

    // Cleanup memory in case of unexpected exit from the loop
    for (int i = 0; i < MAX_STUDENTS; i++) {
        delete students[i];
    }
    return 0;
}
