#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "pch.h"

Window::Window(std::string header)
{
	this->header = header;
	showConsoleCursor(false);
}

void Window::write()
{
	system("CLS");
	std::string s(getHeaderLength(), '-'); // call a string constructor

	std::cout << header << std::endl;
	std::cout << s << std::endl;

	for (Button button : buttons)
	{
		button.write(this);
	}
}

void Window::addButton(Button button)
{
	buttons.push_back(button);
}

int Window::getHeaderLength()
{
	return header.length();
}

Option* Window::getOptionByIndex(int index)
{
	return &buttons[index].option;
}

void Window::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
