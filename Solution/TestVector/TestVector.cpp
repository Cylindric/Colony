// TestVector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iterator>
#include <iostream>

using std::vector;

int _tmain(int argc, _TCHAR* argv[])
{

	vector<int> sourceVector;
	vector<int> destVector;

	sourceVector.push_back(10);
	sourceVector.push_back(20);
	sourceVector.push_back(30);
	sourceVector.push_back(40);
	sourceVector.push_back(50);
	sourceVector.push_back(60);

	for(auto it = sourceVector.begin(); it != sourceVector.end(); ++it)
	{
		std::cout << (*it) << " ";
	}
	std::cout << std::endl;

	auto s = sourceVector.begin()+2;
	auto e = sourceVector.end()-2;

	std::copy(s, e, std::back_inserter(destVector));
	for(auto it = destVector.begin(); it != destVector.end(); ++it)
	{
		std::cout << (*it) << " ";
	}
	std::cout << std::endl;

	return 0;
}

