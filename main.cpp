#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>

using namespace std;

class Task {
public:
    string title;
    int priority;
    string deadline;

    Task(string t, int p, string dl) : title(t), priority(p), deadline(dl) {}
};


string getFormattedDate(int daysFromNow) {
    time_t now = time(0);
    now += daysFromNow * 86400;
    tm *ltm = localtime(&now);
    stringstream dateStream;
    dateStream << setfill('0') << setw(2) << ltm->tm_mon + 1 << "/"
               << setw(2) << ltm->tm_mday << "/"
               << setw(2) << (ltm->tm_year + 1900) % 100;
    return dateStream.str();
}


class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask() {
        string title;
        int priority, daysFromNow;

        cout << "\nEnter Task Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Priority (any number): ";
        cin >> priority;
        cout << "Enter Deadline (days from now): ";
        cin >> daysFromNow;

        string formattedDeadline = getFormattedDate(daysFromNow);
        tasks.push_back(Task(title, priority, formattedDeadline));
        cout << "Task added successfully!\n";
    }

    void displayTasks() {
        if (tasks.empty()) {
            cout << "\nNo tasks available.\n";
            return;
        }

        sort(tasks.begin(), tasks.end(), [](Task &a, Task &b) {
            return (a.priority < b.priority);
        });

        cout << "\n========================================================\n";
        cout << "| No. |       Title        | Priority | Deadline  |";
        cout << "\n========================================================\n";

        for (size_t i = 0; i < tasks.size(); i++) {
            cout << "| " << setw(3) << i + 1 << " | " << setw(18) << left << tasks[i].title
                 << " | " << setw(8) << tasks[i].priority
                 << " | " << setw(9) << tasks[i].deadline << " |" << endl;
        }

        cout << "========================================================\n";
    }

    void removeTask() {
        displayTasks();
        if (tasks.empty()) return;

        int index;
        cout << "\nEnter task number to remove: ";
        cin >> index;

        if (index > 0 && index <= tasks.size()) {
            tasks.erase(tasks.begin() + index - 1);
            cout << "Task removed successfully!\n";
        } else {
            cout << "Invalid task number!\n";
        }
    }
};

void menu() {
    ToDoList list;
    int choice;

    do {
        cout << "\n----- MSST To-Do List -----\n";
        cout << "1 Add Task\n";
        cout << "2 View Tasks\n";
        cout << "3 Remove Task\n";
        cout << "4 Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: list.addTask(); break;
            case 2: list.displayTasks(); break;
            case 3: list.removeTask(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;
}
