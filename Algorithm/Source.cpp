#include"Algorithm_Encryption.h"
#include"Algorithm_Decryption.h"
#include <conio.h>


void Restart() {

}
int main() {

Algorithm_start:
	std::cout << "1)Encryption\n2)Decryption\n\n";
	int Algorithm_choice;
	std::cout << "Enter your choice:";
	std::cin >> Algorithm_choice;
	
	if (!std::cin) {
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	}

	if (Algorithm_choice == 1) {

		Algorithm_Encryption EOBJ;

		EOBJ.setData();
		EOBJ.ReadFile();

		char restart;
		std::cout << "Do you wanna Restart (Y/n):";
		restart = _getch();

		if (restart == 'Y' || restart == 'y') {
			system("cls");
			goto Algorithm_start;
		}
	}
	else if (Algorithm_choice == 2) {

		Algorithm_Decryption DOBJ;

		DOBJ.setData();
		DOBJ.ReadFile();
		char restart;
		std::cout << "Do you wanna Restart (Y/n):";
		restart = _getch();

		if (restart == 'Y' || restart == 'y') {
			system("cls");
			goto Algorithm_start;
		}
	}
	else {
		std::cout << "Invalid Choice!!" << std::endl;
		std::cout << "Press Enter to Restart" << std::endl;
		system("pause");
		system("cls");
		goto Algorithm_start;
	}

	std::cout << std::endl;
	system("pause");
}