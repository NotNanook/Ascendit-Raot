#include <vector>
#include <string>
#include <iostream>
#include "pch.h"

Button::Button(std::string text, Option option, std::string key)
{
	this->text = text;
	this->option = option;
	this->key = key;
};

void Button::write(Window* window)
{
	std::cout << text;
	option.write(text, window);
	std::cout << " [" << key << "]" << std::endl;
};