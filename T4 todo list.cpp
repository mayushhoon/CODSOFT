#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool completed;
};

vector<Task> tasks;

// Add a new task
void addTask() {
    string desc;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, desc);
    tasks.push_back({desc, false});
    cout << "Task added!\n";
}

// View all tasks
void viewTasks() {
    if(tasks.empty()) {
        cout << "No tasks in the list.\n";
        return;
    }
    cout << "\nTo-Do List:\n";
    for(size_t i = 0; i < tasks.size(); ++i) {
        cout << i+1 << ". [" << (tasks[i].completed ? "X" : " ") << "] "
             << tasks[i].description << "\n";
    }
}

// Mark a task as completed
void markCompleted() {
    int num;
    viewTasks();
    if(tasks.empty()) return;
    cout << "Enter task number to mark as completed: ";
    cin >> num;
    if(num < 1 || num > (int)tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }
    tasks[num-1].completed = true;
    cout << "Task marked as completed!\n";
}

// Remove a task
void removeTask() {
    int num;
    viewTasks();
    if(tasks.empty()) return;
    cout << "Enter task number to remove: ";
    cin >> num;
    if(num < 1 || num > (int)tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }
    tasks.erase(tasks.begin() + num - 1);
    cout << "Task removed!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- To-Do List Manager ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch(choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(); break;
            case 4: removeTask(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while(choice != 5);

    return 0;
}
