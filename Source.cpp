#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;
template<typename T>
class LinkedList {
public:

	LinkedList();
	~LinkedList();
	

	void pop_front();
	void push_back(T data);
	void clear();
	int GetSize() { return Size; };
	T& operator[](const int index);
	void push_front(T data);
	void insert(T data, int index);

private:


	template<typename T>
	class Node {
	public:
		Node* pNext;
		T data;
		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T> *head;

};


template<typename T>
LinkedList<T>::LinkedList() 
{
	Size = 0;
	head = nullptr;
}


template<typename T>
LinkedList<T>::~LinkedList() 
{
	clear();
}



template<typename T>
void LinkedList<T>::pop_front()
{
	Node<T> *temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

template<typename T>
void LinkedList<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	Size++;
}

template<typename T>
void LinkedList<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
T& LinkedList<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void LinkedList<T>::push_front(T data)
{
	head = new Node<T>(data,head);
	Size++;

}

template<typename T>
void LinkedList<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}

	if ((index > Size)||(index<0))
	{ 
		cout << "index out of range" << endl;
	}

	else
	{
		Node<T>* previous = head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;
		Size++;
	}
}


typedef struct TemperatureData {
	string date;
	int temperature;
};

bool operator<(const TemperatureData& lhs, const TemperatureData& rhs) {
	return (lhs.temperature < rhs.temperature) || (lhs.temperature == rhs.temperature && lhs.date < rhs.date);
}

void insertSorted(LinkedList<TemperatureData>& data, const TemperatureData& newData) {
	int it = 0;
	if (data.GetSize() == 0)
	{
		data.push_front(newData);
		return;
	}
	while (it != data.GetSize()-1 && data[it] < newData) {
		++it;
	}
	data.insert(newData,it);
}

int main() {
	ifstream file("input.txt");
	if (!file) {
		cout << "Error opening file\n";
		return 1;
	}

	LinkedList<TemperatureData> data;
	string line;
	while (std::getline(file, line)) {
		TemperatureData entry;
		entry.date = line.substr(0, 10);
		entry.temperature = stof(line.substr(11));
		insertSorted(data, entry);
	}
	file.close();
	cout << "Days with temperature below 0:" << endl;
	for (int i = 0; i<data.GetSize()-1;i++) {
		if (data[i].temperature < 0) {
			cout << data[i].date << " - " << data[i].temperature << endl;
		}
	}


	cout << "Enter a temperature to search for: ";
	int searchTemperature;
	cin >> searchTemperature;

	bool found = false;
	for (int i = 0; i < data.GetSize() - 1; i++) {
		if (data[i].temperature == searchTemperature) {
			cout << "Day with temperature " << searchTemperature << " found: " << data[i].date << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "Day with temperature " << searchTemperature << " not found." << endl;
	}

	return 0;
}