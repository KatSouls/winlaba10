// lab.10.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

SYSTEM_INFO si;

using namespace std;
int main() {

	setlocale(LC_ALL, "Russian");


	GetSystemInfo(&si);


	cout << "\nУровень процессора:                \t" << si.wProcessorLevel;
	cout << "\nАрхитектура процессора:            \t" << si.wProcessorArchitecture;
	cout << "\nРазмер страницы:                   \t" << si.dwPageSize;
	cout << "\nКол. ядер процессора:              \t" << si.dwNumberOfProcessors;
	cout << "\nМинимальный адрес памяти:          \t" << si.lpMinimumApplicationAddress;
	cout << "\nМаксимальный адрес памяти:         \t" << si.lpMaximumApplicationAddress;
	cout << "\nДетализации начального адреса:     \t" << si.dwAllocationGranularity;
	cout << "\n";

}









































	// Страничная память — способ организации виртуальной памяти, при котором виртуальные адреса отображаются на физические постранично. 
// 4 кб
// от 0 до 4 гб
//  2^64 байта (16 exabytes)
//от 128 гб до 6 тб

