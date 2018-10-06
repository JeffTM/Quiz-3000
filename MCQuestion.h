#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "Question.h"

class MCQuestion : public Question
{
public:
	MCQuestion();
	MCQuestion(const std::string & prompt, int points, std::string correctAns);

	int scoreAnswer(std::string answer, std::ostream & output = std::cout);
private:
	std::string correctAnswer;
};
