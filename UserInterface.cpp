#include "UserInterface.h"
#include <iostream>

bool relatie(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

SortedMap map(relatie);
SMIterator iter = map.iterator();

void startApp()
{
	showMenu();
	int command;
	while (true) {
		cout << " >>> ";
		cin >> command;
		if (command == 1)
			add();
		else if (command == 2)
			remove();
		else if (command == 3)
			search();
		else if (command == 4)
			getNumberOfCities();
		else if (command == 5)
			listAllCities();
		else if (command == 6)
			getCurrentCity();
		else if (command == 7)
			getNextCity();
		else if (command == 8)
			getFirstCity();
		else if (command == 9)
			showMenu();
		else if (command == 0)
			break;
		else
			cout << "Invalid command! Enter 8 for menu...\n";
	}
}

void showMenu()
{
	cout << "Menu: \n";
	cout << "\t1. Add a new city ( zip code + name ).\n";
	cout << "\t2. Remove a city ( by zip code ).\n";
	cout << "\t3. Find a city ( by zip code ).\n";
	cout << "\t4. Show number of cities.\n";
	cout << "\t5. List all cities.\n";
	cout << "\t6. Display current city.\n";
	cout << "\t7. Display next city.\n";
	cout << "\t8. Display first city.\n";
	cout << "\t9. Show menu.\n";
	cout << "\t0. Exit.\n";
}

void add()
{
	int zip;
	string name;
	cout << "Zip code: ";
	cin >> zip;
	cout << "Name: ";
	cin >> name;
	string oldName = map.add(zip, name);
	iter.first();
	if (oldName == "")
		cout << "New city added!\n";
	else
		cout << "City name updated from " << oldName << " to " << name << ".\n";
}

void remove()
{
	int zip;
	cout << "Zip code: ";
	cin >> zip;
	string name = map.remove(zip);
	iter.first();
	if (name == "")
		cout << "Inexistent zip code!\n";
	else
		cout << "City " << name << " removed!\n";
}

void search()
{
	int zip;
	cout << "Zip code: ";
	cin >> zip;
	string name = map.search(zip);
	if (name == "")
		cout << "City with zip code " << zip << " not found!\n";
	else
		cout << "City with zip code " << zip << " is: " << name << ".\n";
}

void getNumberOfCities()
{
	cout << map.size() << " cities.\n";
}

void listAllCities()
{
	if (map.size() == 0) {
		cout << "No cities!\n";
		return;
	}
	SMIterator auxIter = map.iterator();
	auxIter.first();
	while (auxIter.valid()) {
		try {
			cout << "Zip code: " << auxIter.getCurrent().first << ", city name: " << auxIter.getCurrent().second << endl;
			auxIter.next();
		}
		catch (exception& ex) {
			cout << ex.what();
		}
	}
}

void getCurrentCity()
{
	try {
		cout << "Zip code: " << iter.getCurrent().first << ", city name: " << iter.getCurrent().second << endl;
	}
	catch (exception& ex) {
		cout << "Invalid current city.\n";
	}
}

void getNextCity()
{
	try {
		iter.next();
		cout << "Zip code: " << iter.getCurrent().first << ", city name: " << iter.getCurrent().second << endl;
	}
	catch (exception& ex) {
		cout << "Invalid next city.\n";
	}
}

void getFirstCity()
{
	try {
		iter.first();
		cout << "Zip code: " << iter.getCurrent().first << ", city name: " << iter.getCurrent().second << endl;
	}
	catch (exception& ex) {
		cout << "No cities.\n";
	}
}
