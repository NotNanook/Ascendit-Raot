#include <iostream>
#include "pch.h"

Option::Option(bool boolSetting)
{
	this->boolSetting = boolSetting;
	this->settingMode = "boolean";
}

Option::Option(int intMin, int intMax)
{
	this->intMin = intMin;
	this->intMax = intMax;
	this->intCurrent = intMin;
	this->settingMode = "integer";
}

void Option::write(std::string otherText, Window* window)
{
	int headerLength = window->getHeaderLength();
	int textLength = otherText.length();
	int spaceCount = 0;
	if (settingMode == "boolean")
	{
		// [true/false] -> 6 letters
		spaceCount = std::abs(headerLength - textLength - 7);
		std::string s(spaceCount, ' ');
		std::cout << s;
		std::cout << '[';
		std::cout << std::boolalpha << boolSetting;
		std::cout << ']';
	}
	else if (settingMode == "integer")
	{
		// [Some numeber(1 or 2 or 3 digit...)] -> 3,4,5.. letters
		spaceCount = (intCurrent > 0) ? std::abs(headerLength - textLength - (int(log10(intCurrent) + 1) + 2)) : headerLength - textLength - 3; // last part gets number of digits and adds the 2 []
		std::string s(spaceCount, ' ');
		std::cout << s;
		std::cout << '[';
		std::cout << intCurrent;
		std::cout << ']';
	}
}

std::variant<int, bool> Option::getCurrentValue()
{
	if (settingMode == "boolean")
	{
		return boolSetting;
	}
	else if (settingMode == "integer")
	{
		return intCurrent;
	}
}

void Option::setCurrentValue(int i)
{
	if (i >= intMin && i <= intMax)
	{
		intCurrent = i;
	}
	else
	{
		std::cout << "[Warning] Cant set int below/above limited range" << std::endl;
	}
}

void Option::setCurrentValue(bool b)
{
	boolSetting = b;
}

void Option::toggleBool()
{
	boolSetting = !boolSetting;
}

void Option::increaseValue()
{
	if (intCurrent < intMax)
	{
		intCurrent++;
	}
}

void Option::decreaseValue()
{
	if (intCurrent > intMin)
	{
		intCurrent--;
	}
}

void Option::toggleInt()
{
	if (intCurrent < intMax)
	{
		intCurrent++;
	}
	else
	{
		intCurrent = intMin;
	}
}
