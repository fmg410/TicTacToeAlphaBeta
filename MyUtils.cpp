#include "MyUtils.hpp"

void readEnter()
{
	if (std::cin.get() != '\n')
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void readInt(int& num, int lowerBound, int upperBound)
{
	while (true)
	{
		while (true) {
			std::cin >> num;
			if (std::cin.fail() == true) {
				std::cout << "wykryto blad" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else break;
		}
		if (num >= lowerBound && num <= upperBound)
		{
			break;
		}
		else
		{
			std::cout << "Wprowadzono liczbe z poza dostepnego zakresu" << std::endl;
		}
	}
	readEnter();
}