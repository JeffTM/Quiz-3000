//Abstract class
#pragma once
#include <iostream>
#include <ostream>
#include <string>

class Question
{
public:
	Question();
	Question(const std::string & prompt, int points);
	virtual ~Question();

	virtual void displayPrompt(std::ostream & output = std::cout);
	virtual int getPoints();
	virtual int scoreAnswer(std::string answer, std::ostream & output = std::cout) = 0;
protected:
	void toLowerCase(std::string & s);
private:
	std::string prompt;
	int points;
};
