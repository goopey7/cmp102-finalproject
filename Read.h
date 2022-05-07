// CMP102 TEACHERS PLEASE NOTE
// THIS FILE HAS BEEN CREATED AND USED
// IN PREVIOUS PROJECTS OUTSIDE OF CMP102

//Copyright Sam Collier 2022
#pragma once
#include <iostream>
#include <string>
#include <fstream>
class Read
{
public:
	static std::string getInputAsString()
	{
		std::string in;
		std::getline(std::cin, in);
		return in;
	}
	// print contents of ascii art plaintext file
	// https://stackoverflow.com/questions/35201919/how-do-i-print-out-the-contents-of-a-file-c-file-stream
	static void printFile(std::string fileName)
	{
		std::ifstream f(fileName.c_str());
		if (f.is_open())
			std::cout << f.rdbuf();
	}
};
