#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string> 
#include <locale> 
using namespace ::std;


//(структура, содержащая дату и температуру)
typedef struct Day {
    string date;
    int temperature;
};

//  Функция сравнения(компаратор) для дальнейшего использования в функции sort
bool compareTemperature(const Day& a, const Day& b) {
    if (a.temperature == b.temperature) {
        return a.date < b.date;
    }
    return a.temperature < b.temperature;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Day> days; //пустой вектор объектов типа Day для хранения данных
    ifstream file("input.txt"); //Открывает файл "input.txt" для чтения данных
    if (!file) {
        cout << "Ошибка при открытии файла" << endl;
        return 1;
        //Если файл не удалось открыть, выводит сообщение об ошибке и завершает программу
    }
    string line;
    while (getline(file, line)) {
        Day day;//создаём пустой объект типа day
        day.date = line.substr(0, 10);//записываем первые 10 символов отвечающих за дату в формате ГГГГ-ММ-ДД
        day.temperature = stoi(line.substr(11));//оставшиеся символы записываем в температуру
        days.push_back(day);//добавляем объект в конец вектора
    }
    file.close();//закрываем файл

    sort(days.begin(), days.end(), compareTemperature);//сортируем вектор передавая в sort третьим элементом функцию сравнения

    cout << "Дни с температурой ниже нуля:" << endl;
    for (const Day& day : days) {
        if (day.temperature < 0) {
            cout << day.date << " :  " << day.temperature << endl;
        }
    }

    cout << "Введите значение температуры для поиска дня: ";
    int searchTemperature;//температура которую будем искать
    cin >> searchTemperature;

    bool found = false;//флаг так как нету for else конструкции
    for (const Day& day : days) {
        if (day.temperature == searchTemperature) {
            cout << "День с температурой  " << searchTemperature << " найден: " << day.date << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Дней с температурой " << searchTemperature << " не найдено." << endl;
    }

    return 0;
}