#ifndef __ENCRYPTION_H_
#define __ENCRYPTION_H_

#include<iostream>
#include<string>
#include<fstream>

class Algorithm_Encryption {
	std::string file_name;
	std::string text;
	std::string plain_text;
	std::string cipher_text;
	int key;

public:
	Algorithm_Encryption(std::string file_name = "",
			   std::string text = "", 
			   std::string plain_text = "",
			   std::string cipher_text = "",
			   int key = 0)
										: file_name(file_name), 
										  text(text),
										  plain_text(plain_text), 
										  cipher_text(cipher_text), 
										  key(key){}
	void setData() {
		std::cout << "Enter File Name:";
		std::cin.ignore();
		std::cin.clear();
		getline(std::cin, file_name);
		std::cout << "Enter Key:";
		std::cin >> key;
	}

	void ReadFile() {

		std::string line;
		std::ifstream myfile(file_name.c_str());
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				// Empty all the variables
				plain_text = "";
				cipher_text = "";
				text = "";

				// Encrypt & Write in File
				plain_text = line;
				Algorithm_Encrypt();
				WriteFile();
			}
			myfile.close();
		}

		else std::cout << "Unable to open file" << std::endl;
	}
	
	void WriteFile() {
		std::ofstream my_file;
		my_file.open("Encrypted.txt", std::ios::out | std::ios::app | std::ios::binary);
		my_file << cipher_text << std::endl;
		my_file.close();
	}
	void Algorithm_Encrypt() {

		//if to check the key from 1 to 100
		if (key > 0 && key <= 100) {

			RF_Encrypt(12);

			// text.length()
			// using for loop to rev the string and to increment the key in each single character
			for (int i = text.length() - 1; i >= 0; i--) {
				char result = static_cast<int>(text[i]) + key;
				cipher_text = cipher_text + result;
			}
		}
		else
			std::cout << "\nInvalid Key";
	}

	void RF_Encrypt(int RF_key)
	{
		// create the matrix to cipher plain text 
		// key = rows , length(text) = columns 
		char rail[100][1000];

		// filling the rail matrix to distinguish filled 
		// spaces from blank ones 
		for (int i = 0; i < RF_key; i++)
			for (int j = 0; j < plain_text.length(); j++)
				rail[i][j] = '\n';

		// to find the direction 
		bool dir_down = false;
		int row = 0, col = 0;

		for (int i = 0; i < plain_text.length(); i++)
		{
			// check the direction of flow 
			// reverse the direction if we've just 
			// filled the top or bottom rail 
			if (row == 0 || row == RF_key - 1)
				dir_down = !dir_down;

			// fill the corresponding alphabet 
			rail[row][col++] = plain_text[i];

			// find the next row using direction flag 
			dir_down ? row++ : row--;
		}

		//now we can construct the cipher using the rail matrix 
		for (int i = 0; i < RF_key; i++)
			for (int j = 0; j < plain_text.length(); j++)
				if (rail[i][j] != '\n')
					text.push_back(rail[i][j]);
	}
};
#endif // !__ENCRYPTION_H_

