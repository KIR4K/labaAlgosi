#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace :: std;

typedef struct Day {
    string date;
    int temperature;
};

bool operator < (const Day& lhs, const Day& rhs) {
    return (lhs.temperature < rhs.temperature) || (lhs.temperature == rhs.temperature && lhs.date < rhs.date);
}

void insertSorted(list<Day>& data, const Day& newData) {
    auto it = data.begin();
    while (it != data.end() && *it < newData) {
        ++it;
    }
    data.insert(it, newData);
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cout << "Error opening file\n";
        return 1;
    }

    list<Day> days;
    string line;
    while (getline(file, line)) {
        Day entry;
        size_t pos = line.find(' ');
        entry.date = line.substr(0, pos);
        entry.temperature = stof(line.substr(pos + 1));
        insertSorted(days, entry);
    }

    cout << "Days with temperature below zero:\n";
    for (const auto& entry : days) {
        if (entry.temperature < 0) {
            cout << "Date: " << entry.date << ", Temperature: " << entry.temperature << "\n";
        }
    }


    cout << "Enter temperature to search: ";
    int searchTemperature;
    cin >> searchTemperature;


    bool found = false;
    for (const Day& day : days) {
        if (day.temperature == searchTemperature) {
            cout << "Day with temperature  " << searchTemperature << " found: " << day.date << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Day with temperature " << searchTemperature << " is not in list." << endl;
    }

    return 0;
}
