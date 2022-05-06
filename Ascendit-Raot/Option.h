#pragma once
#include <variant>

class Window;

class Option
{
public:
	Option() = default;
	Option(bool boolSetting);
	Option(int intMin, int intMax);
	void write(std::string otherText, Window* window);
	std::variant<int, bool> getCurrentValue();
	void setCurrentValue(int i);
	void setCurrentValue(bool b);
	void toggleBool();
	void toggleInt();
	void increaseValue();
	void decreaseValue();
private:
	bool boolSetting;
	int intMin, intMax, intCurrent;
	std::string settingMode;
};