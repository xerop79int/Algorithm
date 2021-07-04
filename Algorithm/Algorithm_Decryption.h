#ifndef __DECRYPTION_H_
#define __DECRYPTION_H_

#include<iostream>
#include<string>
#include<fstream>

class Algorithm_Decryption {
	std::string file_name;
	std::string text;
	std::string plain_text;
	std::string cipher_text;
	int key = 0;

public:
	Algorithm_Decryption(std::string file_name = "",
		       std::string text = "",
		       std::string plain_text = "",
		       std::string cipher_text = "",
		       int key = 0)
												:	file_name(file_name),
													text(text),
													plain_text(plain_text),
													cipher_text(cipher_text),
													key(key) {}
	void setData() {
		std::cout << "Enter Encrypted File Name:";
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

				// Decryption & Write in File
				cipher_text = line;
				Algorithm_Decrypt();
				WriteFile();
			}
		}

		else std::cout << "Unable to open file" << std::endl;

	}

	void WriteFile() {
		std::ofstream my_file;
		my_file.open("Decrypted.txt", std::ios::out | std::ios::app | std::ios::binary);
		my_file << plain_text << std::endl;
		my_file.close();
		plain_text = "";
	}

	void Algorithm_Decrypt() {
		
		//if to check the key from 1 to 100
		if (key > 0 && key <= 100) {

			// using for loop to rev the string and to increment the key in each single character
			for (int i = cipher_text.size() - 1  ; i >= 0; i--) {
				char result = static_cast<int>(cipher_text[i]) - key;
				text = text + result;
			}

			RF_Decrypt(12);
		}
		else
			std::cout << "\nInvalid Key";
	}


	void RF_Decrypt(int RF_key)
	{
		// create the matrix to cipher plain text 
		// key = rows , length(text) = columns 
		char rail[100][1000];

		// filling the rail matrix to distinguish filled 
		// spaces from blank ones 
		for (int i = 0; i < RF_key; i++)
			for (int j = 0; j < text.length(); j++)
				rail[i][j] = '\n';

		// to find the direction 
		bool dir_down;

		int row = 0, col = 0;

		// mark the places with '*' 
		for (int i = 0; i < text.length(); i++)
		{
			// check the direction of flow 
			if (row == 0)
				dir_down = true;
			if (row == RF_key - 1)
				dir_down = false;

			// place the marker 
			rail[row][col++] = '*';

			// find the next row using direction flag 
			dir_down ? row++ : row--;
		}

		// now we can construct the fill the rail matrix 
		int index = 0;
		for (int i = 0; i< RF_key; i++)
			for (int j = 0; j<text.length(); j++)
				if (rail[i][j] == '*' && index < text.length())
					rail[i][j] = text[index++];


		// now read the matrix in zig-zag manner to construct 
		// the resultant text 
		row = 0, col = 0;
		for (int i = 0; i< text.size(); i++)
		{
			// check the direction of flow 
			if (row == 0)
				dir_down = true;
			if (row == RF_key - 1)
				dir_down = false;

			// place the marker 
			if (rail[row][col] != '*')
				plain_text.push_back(rail[row][col++]);

			// find the next row using direction flag 
			dir_down ? row++ : row--;
		}
	}
};

#endif // !__DECRYPTION_H_
	