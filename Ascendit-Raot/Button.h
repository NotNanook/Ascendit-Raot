#pragma once
#include <string>
#include "Option.h"

class Window;

class Button 
{
public:
	Button(std::string text, Option option, std::string key);
	void write(Window* window);
	Option option;
	
private:
	std::string text;
	std::string key;
};