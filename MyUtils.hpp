#ifndef MYUTILS_HPP
#define MYUTILS_HPP
#include <iostream>
#include <limits>

#ifdef _WIN32
#define clearConsole system("cls")
#elif __linux__
#define clearConsole system("clear")
#elif __APPLE__
#define clearConsole system("clear")
#else
#define clearConsole printf("\n\n\n");
#endif

void readEnter();

void readInt(int& liczba, int dolnaGranica, int gornaGranica);

#endif