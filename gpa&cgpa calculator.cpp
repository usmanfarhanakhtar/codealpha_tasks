#include <iostream>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;

// Convert grade to uppercase
string toUpper(string g) {
    for (char &c : g) {
        c = toupper(c);
    }
    return g;
}

// Convert grade to points
double getGradePoint(string grade) {
    grade = toUpper(grade);

    if (grade == "A+" || grade == "A") return 4.0;
    else if (grade == "A-") return 3.7;
    else if (grade == "B+") return 3.3;
    else if (grade == "B") return 3.0;
    else if (grade == "B-") return 2.7;
    else if (grade == "C+") return 2.3;
    else if (grade == "C") return 2.0;
    else if (grade == "C-") return 1.7;
    else if (grade == "D") return 1.0;
    else if (grade == "F") return 0.0;
    else return -1; // invalid
}

// Input data with validation
void inputData(int n, vector<string> &grades, vector<int> &credits) {
    for (int i = 0; i < n; i++) {
        cout << "\nCourse " << i + 1 << endl;

        // Grade validation
        while (true) {
            cout << "Enter grade: ";
            cin >> grades[i];

            if (getGradePoint(grades[i]) != -1)
                break;
            else
                cout << "Invalid grade! Try again.\n";
        }

        // Credit validation
        do {
            cout << "Enter credit hours: ";
            cin >> credits[i];

            if (credits[i] <= 0)
                cout << "Credit must be positive!\n";

        } while (credits[i] <= 0);
    }
}

// Total credits
int totalCredits(const vector<int>& credits) {
    int sum = 0;
    for (int c : credits) sum += c;
    return sum;
}

// Total points
double totalPoints(const vector<string>& grades, const vector<int>& credits) {
    double sum = 0;
    for (int i = 0; i < grades.size(); i++) {
        sum += getGradePoint(grades[i]) * credits[i];
    }
    return sum;
}

// GPA
double calculateGPA(double points, int credits) {
    if (credits == 0) return 0;
    return points / credits;
}

// Display semester
void displaySemester(int sem, const vector<string>& grades, const vector<int>& credits, double gpa, int creds, double points) {
    cout << "\n===== Semester " << sem << " =====\n";

    for (int i = 0; i < grades.size(); i++) {
        cout << "Course " << i + 1
             << " | Grade: " << toUpper(grades[i])
             << " | Credit: " << credits[i] << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nTotal Credits: " << creds << endl;
    cout << "Total Grade Points: " << points << endl;
    cout << "Semester GPA: " << gpa << endl;
}

int main() {
    int semesters;
    cout << "Enter number of semesters: ";
    cin >> semesters;

    double overallPoints = 0;
    int overallCredits = 0;

    vector<vector<string>> allGrades(semesters);
    vector<vector<int>> allCredits(semesters);
    vector<double> allGPA(semesters);
    vector<int> allSemCredits(semesters);
    vector<double> allSemPoints(semesters);

    for (int s = 1; s <= semesters; s++) {
        int n;
        cout << "\nEnter number of courses in semester " << s << ": ";
        cin >> n;

        vector<string> grades(n);
        vector<int> credits(n);

        inputData(n, grades, credits);

        int creds = totalCredits(credits);
        double points = totalPoints(grades, credits);
        double gpa = calculateGPA(points, creds);

        displaySemester(s, grades, credits, gpa, creds, points);

        // Store data
        allGrades[s - 1] = grades;
        allCredits[s - 1] = credits;
        allGPA[s - 1] = gpa;
        allSemCredits[s - 1] = creds;
        allSemPoints[s - 1] = points;

        overallPoints += points;
        overallCredits += creds;
    }

    double cgpa = calculateGPA(overallPoints, overallCredits);

    // Final display
    cout << "\n========== FINAL RESULT ==========\n";

    for (int s = 0; s < semesters; s++) {
        displaySemester(
            s + 1,
            allGrades[s],
            allCredits[s],
            allGPA[s],
            allSemCredits[s],
            allSemPoints[s]
        );
    }

    cout << "\n============================\n";
    cout << fixed << setprecision(2);
    cout << "Overall Total Credits: " << overallCredits << endl;
    cout << "Overall Total Grade Points: " << overallPoints << endl;
    cout << "Final CGPA: " << cgpa << endl;

    return 0;
}
