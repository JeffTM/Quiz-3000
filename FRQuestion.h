#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "Question.h"

class FRQuestion : public Question
{
public:
	FRQuestion();
	FRQuestion(const std::string & prompt, int points);

	int scoreAnswer(std::string answer, std::ostream & output = std::cout);
};
