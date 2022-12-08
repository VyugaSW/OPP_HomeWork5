
#include <Windows.h>
#include <iostream>
#include <malloc.h>
#include <conio.h>

#include "Reservoir.h"

//Увеличение массива
Reservoir* AddReservoirInArr(Reservoir* arr, int& size) {
	size++; //Увеличиваем размер, новый массив и удаления старого
	Reservoir* newArr = new Reservoir[size];
	for (int i = 0; i < size - 1; i++) {
		newArr[i].copyReservoir(arr[i]);
	}
	delete[]arr;
	return newArr;
}
//Добавлене резервуара
void AddReservoir(Reservoir* arr,int index) {
	//Буферы для ввода
	char* buffN = new char[125];
	char* buffT = new char[125];
	int lenght, width, depth;
	std::cout << "Enter the name of reservoir:\n";
	gets_s(buffN,126);
	std::cout << "Enter the type of reservoir:\n";
	gets_s(buffT, 126);
	std::cout << "Enter the lenght of reservoir\n";
	std::cin >> lenght;
	std::cin.ignore();
	std::cout << "Enter the width of reservoir\n";
	std::cin >> width;
	std::cin.ignore();
	std::cout << "Enter the depth of reservoir\n";
	std::cin >> depth;
	std::cin.ignore();
	Reservoir p(buffN, buffT, width, lenght, depth); //Объект для быстрой инициализации и заполнения объекта в массиве
	arr[index - 1].copyReservoir(p);
}
//Вывод всех резервуаров
void PrintReservoirs(Reservoir* arr, int size) {
	//Лишь выводим список водоёмов, если таковы есть
	if (size == 0) 
		std::cout << "\t|There is not any reservoirs|\n\n\n";
	else {
		for (int i = 0; i < size; i++) {
			std::cout << "Number of reservoir - " << i + 1 << std::endl;
			arr[i].printData();
			std::cout << "---------------------\n";
		}
	}
}
//Уменьшение массива
Reservoir* DeleteReservoirInArr(Reservoir* arr, int& size, int index) {
	size--; //Уменьшаем размер и создаём новый массив, удаляя старый
	Reservoir* newArr = new Reservoir[size];
	for (int i = 0, k = 0; i < size + 1; i++) {
		if (index != i) {
			newArr[k].copyReservoir(arr[i]);
			k++;
		}
	}
	delete[]arr;
	return newArr;
}
//Удаление объекта
int DeleteReservoir(Reservoir* arr, int size) {
	PrintReservoirs(arr, size);
	int index; //Номер удаляемого водоёма
	std::cout << "\nEnter the number of reservoir to delete\n";
	std::cin >> index;
	std::cin.ignore();
	return index-1; //Так как пользователь вводит номер, а необходимо вернуть индекс, то отнимаем единицу
}
//Изменение параметров объекта
void ChangeParameters(Reservoir* arr, int size) {	
	PrintReservoirs(arr, size); //Выводим все водоёмы
	std::cout << "\nEnter the number of reservoir to change\n";
	int index; //Индекс изменяемого водоёма
	std::cin >> index;
	std::cin.ignore();

	if (index > size) { //Если такого нет
		std::cout << "There is not reservoir which has this number\n";
		Sleep(1000);
		ChangeParameters(arr, size);
	}

	bool flag = true;
	while (flag) {  //Меню опций изменения
		system("cls");
		int user;
		std::cout << "For reservoir " << index << " :\n";
		std::cout << "1 - Change name and type\n";
		std::cout << "2 - Change lenght, width and depth\n";
		std::cout << "3 - Change all data of reservoir\n";
		user = _getch();
		system("cls");
		switch (user) {
		case 49: //1
			arr[index - 1].changeNameType();
			flag = false;
			break;
		case 50: //2
			arr[index - 1].changeSizes();
			flag = false;
			break;
		case 51: //3
			AddReservoir(arr, index);
			flag = false;
			break;
		default:
			std::cout << "\t\nWrong!\n";
			break;
		}
	}
}
//Сравнение объектов
void CompareReservoirs(Reservoir* arr, int size) {
	//Надо же было использовать методы из задания
	int index1, index2;
	std::cout << "Enter a number first reservoir:";
	std::cin >> index1;
	std::cout << "Etner a number second reservoir:";
	std::cin >> index2;
	index1--;
	index2--;
	std::cin.ignore();

	std::cout << "Compare reservoirs by:\n";
	std::cout << "1 - Type\n";
	std::cout << "2 - Surface area\n";
	int user;
	user = _getch();
	switch (user) {
	case 49:
		if (arr[index1].compareType(arr[index2].getType()))
			std::cout << "Types are the same\n";
		else
			std::cout << "Types aren't the same\n";
		Sleep(1500);
		break;
	case 50:
		if (arr[index1].compareSurface(arr[index2].getLenght(), arr[index2].getWidth()))
			std::cout << "Surface area are the same\n";
		else
			std::cout << "Surface area aren't the same\n";
		Sleep(1500);
		break;
	default:
		std::cout << "Wrong!\n";
		CompareReservoirs(arr, size);
	}
}
//Сохранение в файл (текстовый)
void SaveInTextFile(Reservoir* arr, int size) {
	char* path = new char[125];
	FILE* in;
	std::cout << "Enter a path to the file (Example - C:\\Test\\test.txt)\n";
	gets_s(path, 126);
	if (!fopen_s(&in, path, "w")) {
		for (int i = 0; i < size; i++) {
			//Просто записываем по порядку в файл
			fprintf_s(in, "%s", arr[i].getName());
			putc('\n',in); //Новая строка для красоты и корректного считывания после
			fprintf_s(in, "%s", arr[i].getType());
			putc('\n', in);
			fprintf_s(in, "%d", arr[i].getLenght());
			putc('\n', in);
			fprintf_s(in, "%d", arr[i].getWidth());
			putc('\n', in);
			fprintf_s(in, "%d", arr[i].getDepth());
			putc('\n\n', in);
		}
		fclose(in);
		system("cls");
		std::cout << "\t\nSuccesfully!\n";
		Sleep(1500);
	}
	else {
		std::cout << "Wrong!\n";
		system("cls");
		SaveInTextFile(arr, size);
	}
}
//Сохранение в файл (бинарный)
void SaveInBinaryFile(Reservoir* arr, int size) {
	char* path = new char[125];
	FILE* in;
	std::cout << "Enter a path to the file (Example - C:\\Test\\data.dat)\n";
	gets_s(path, 126);
	if (!fopen_s(&in, path, "wb")) {
		int len, wid, dep;
		for (int i = 0; i < size; i++) {
			len = arr[i].getLenght(); //Без буферов fwrite не принимает
			wid = arr[i].getWidth();
			dep = arr[i].getDepth();
			fwrite(arr[i].getName(), sizeof(char) * strlen(arr[i].getName()), 1, in);
			fwrite("\n", sizeof(char), 1, in);
			fwrite(arr[i].getType(), sizeof(char) * strlen(arr[i].getName()), 1, in);
			fwrite("\n", sizeof(char), 1, in);
			fwrite(&len, sizeof(int), 1, in);
			fwrite("\n", sizeof(char), 1, in);
			fwrite(&wid, sizeof(int), 1, in);
			fwrite("\n", sizeof(char), 1, in);
			fwrite(&dep, sizeof(int), 1, in);
			fwrite("\n", sizeof(char), 1, in);
		}
		fclose(in);
		system("cls");
		std::cout << "\t\nSuccesfully!\n";
		Sleep(1500);
	}
	else {
		std::cout << "Wrong!\n";
		system("cls");
		SaveInTextFile(arr, size);
	}
}
//Удаление пробелов в конце строки (Специально для функции LoadFromTextFile)
void DeleteNewLen(Reservoir* arr, int index) {
	//А ВОТ ЕСЛИ БЫ FSCANF_S РАБОТАЛА КОРРЕКТНО СО СТРОКАМИ, ТО ЭТОЙ ПОРОЖНЕЙ ФУНКЦИИ
	//МОЖНО БЫЛО БЫ ИЗБЕЖАТЬ!!!!!!!!!!!!! НО ЭТО ТВАРЬ НЕ МОЖЕТ СЧИТЫВАТЬ СИМВОЛЫ ИЗ ФАЙЛА
	//А FWSCANF_S ТОЖЕ АБСОЛЮТНАЯ ПУСТЫШКА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	index--;
	char* buff = new char[125];
	//ИЗМЕНЯЕМ ИМЯ ВОДОЁМА (УБИРАЕМ '\n' С КОНЦА)
	strncpy_s(buff, 125, arr[index].getName(), strlen(arr[index].getName())-1);
	arr[index].setName(buff);

	strncpy_s(buff, 125, arr[index].getType(), strlen(arr[index].getType())-1);
	arr[index].setType(buff);
}
//Загрузка из файла (текстового
Reservoir* LoadFromTextFile(Reservoir* arr, int& size) {
	char* path = new char[125];
	FILE* in;
	std::cout << "Enter a path to the file (Example - C:\\Test\\test.txt)\n";
	gets_s(path, 126);
	int i = 0;
	if (!fopen_s(&in, path, "r")) {
		char* buff = new char[125];
		int intBuff;
		while (!feof(in)) {
			fgets(buff, 135, in); //fscanf_s(in, "%s", &buff, 135) - не может считать символы строки
			if (buff != "\n" || buff != "\0") {
				arr = AddReservoirInArr(arr, size);
				arr[i].setName(buff);
				//Считываем в строку и копируем в объект класса индекса i
				fgets(buff, 135, in);
				arr[i].setType(buff);

				fscanf_s(in, "%d", &intBuff, sizeof(int)+1);
				arr[i].setLenght(intBuff);

				fscanf_s(in, "%d", &intBuff, sizeof(int)+1);
				arr[i].setWidth(intBuff);

				fscanf_s(in, "%d", &intBuff, sizeof(int)+1);
				arr[i].setDepth(intBuff);
				i++;
				DeleteNewLen(arr, i); //Удаляем '\n' в конце массивов name и type (см. Reservoir.h)
			}
		}
		fclose(in);
		system("cls");
		std::cout << "\t\nSuccesfully!\n";
		Sleep(1500);
	}
	else {
		std::cout << "Wrong!\n";
		system("cls");
		LoadFromTextFile(arr, size);
	}
	return arr;
}

int main()
{

	int size = 0;
	int user;
	bool flag = true;
	Reservoir* arr = new Reservoir[size];
	//Главное меню
	while (flag) {
		system("cls");
		std::cout << "\t|Reservoir| main menu\n";
		std::cout << "1 - add new reservoir\n";
		std::cout << "2 - print all reservoirs\n";
		std::cout << "3 - delete reservoir\n";
		std::cout << "4 - change parameters of reservoir\n";
		std::cout << "5 - compare reservoirs\n";
		std::cout << "6 - delete all reservoirs\n";
		std::cout << "7 - save in text file\n";
		std::cout << "8 - save in binary file\n";
		std::cout << "9 - load from a file\n";
		std::cout << "10 - Exit\n";
		user = _getch();
		switch (user) {
		case 49: // 1
			system("cls");
			arr = AddReservoirInArr(arr, size);
			AddReservoir(arr, size);
			break;
		case 50: // 2
			system("cls");
			PrintReservoirs(arr, size);
			std::cout << "Press any key to return\n";
			_getch();
			break;
		case 51: // 3
			system("cls");
			DeleteReservoirInArr(arr, size,DeleteReservoir(arr,size));
			system("cls");
			std::cout << "\nReservoir was deleted\n";
			Sleep(1000);
			break;
		case 52: // 4
			system("cls");
			if (size == 0) {
				std::cout << "\t|There is not any reservoirs|\n\n\n";
				Sleep(1500);
				break;
			}
			ChangeParameters(arr, size);
			break;
		case 53: // 5
			system("cls");
			if (size < 2) {
				std::cout << "There is only one reservoir or there is not any reservoirs";
				Sleep(1500);
				break;
			}
			CompareReservoirs(arr, size);
			break;
		case 54: // 6
			system("cls");
			delete[]arr;
			size = 0;
			arr = new Reservoir[0];
			std::cout << "\nAll reservoirs were deleted\n";
			Sleep(1000);
			break;
		case 55: // 7
			system("cls");
			SaveInTextFile(arr,size);
			break;
		case 56: // 8
			system("cls");
			SaveInBinaryFile(arr, size);
			break;
		case 57: // 9
			system("cls");
			arr = LoadFromTextFile(arr, size);
			break;
		case 58: // 10
			system("cls");
			std::cout << "Good bye!\n";
			Sleep(1500);
			flag = false;
			break;
		default:
			std::cout << "\t\tWrong!\n";
			break;
		}





	}




}


