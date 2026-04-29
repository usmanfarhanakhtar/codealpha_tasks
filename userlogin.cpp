#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Simple hash function (for basic security)
string hashPassword(string password) {
    string hashed = "";
    for (char c : password) {
        hashed += char(c + 3); // simple shift encryption
    }
    return hashed;
}

// Check if username already exists
bool userExists(string username) {
    ifstream file("users.txt");
    string user, pass;

    while (file >> user >> pass) {
        if (user == username) {
            return true;
        }
    }
    return false;
}

// Registration Function
void registerUser() {
    string username, password;

    cout << "\n===== REGISTRATION =====\n";
    cout << "Enter username: ";
    cin >> username;

    // Validation
    if (username.length() < 3) {
        cout << "? Username must be at least 3 characters long!\n";
        return;
    }

    if (userExists(username)) {
        cout << "? Username already exists! Try another.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (password.length() < 5) {
        cout << "? Password must be at least 5 characters long!\n";
        return;
    }

    // Hash password before storing
    string hashedPass = hashPassword(password);

    ofstream file("users.txt", ios::app);
    file << username << " " << hashedPass << endl;

    cout << "? Registration successful!\n";
}

// Login Function
void loginUser() {
    string username, password;
    string user, pass;
    bool found = false;

    cout << "\n===== LOGIN =====\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string hashedPass = hashPassword(password);

    ifstream file("users.txt");

    while (file >> user >> pass) {
        if (user == username && pass == hashedPass) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "? Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "? Invalid username or password!\n";
    }
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "?? Exiting program...\n";
                break;
            default:
                cout << "? Invalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
