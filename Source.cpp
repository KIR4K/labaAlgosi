#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string> 
#include <locale> 
using namespace ::std;


//(���������, ���������� ���� � �����������)
typedef struct Day {
    string date;
    int temperature;
};

//  ������� ���������(����������) ��� ����������� ������������� � ������� sort
bool compareTemperature(const Day& a, const Day& b) {
    if (a.temperature == b.temperature) {
        return a.date < b.date;
    }
    return a.temperature < b.temperature;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Day> days; //������ ������ �������� ���� Day ��� �������� ������
    ifstream file("input.txt"); //��������� ���� "input.txt" ��� ������ ������
    if (!file) {
        cout << "������ ��� �������� �����" << endl;
        return 1;
        //���� ���� �� ������� �������, ������� ��������� �� ������ � ��������� ���������
    }
    string line;
    while (getline(file, line)) {
        Day day;//������ ������ ������ ���� day
        day.date = line.substr(0, 10);//���������� ������ 10 �������� ���������� �� ���� � ������� ����-��-��
        day.temperature = stoi(line.substr(11));//���������� ������� ���������� � �����������
        days.push_back(day);//��������� ������ � ����� �������
    }
    file.close();//��������� ����

    sort(days.begin(), days.end(), compareTemperature);//��������� ������ ��������� � sort ������� ��������� ������� ���������

    cout << "��� � ������������ ���� ����:" << endl;
    for (const Day& day : days) {
        if (day.temperature < 0) {
            cout << day.date << " :  " << day.temperature << endl;
        }
    }

    cout << "������� �������� ����������� ��� ������ ���: ";
    int searchTemperature;//����������� ������� ����� ������
    cin >> searchTemperature;

    bool found = false;//���� ��� ��� ���� for else �����������
    for (const Day& day : days) {
        if (day.temperature == searchTemperature) {
            cout << "���� � ������������  " << searchTemperature << " ������: " << day.date << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "���� � ������������ " << searchTemperature << " �� �������." << endl;
    }

    return 0;
}