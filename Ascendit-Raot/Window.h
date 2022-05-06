#pragma once
#include <variant>
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

class Button;
class Option;

class Window 
{
public:
	std::vector<Button> buttons;
	Window(std::string header);
	void write();
	void addButton(Button button);
	int getHeaderLength();
	Option* getOptionByIndex(int index);

private:
	std::string header;
	void showConsoleCursor(bool showFlag);
};