#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "Question.h"

class TFQuestion : public Question
{
public:
	TFQuestion();
	TFQuestion(const std::string & prompt, int points, bool correctAnswer);

	void displayPrompt(std::ostream & output = std::cout);
	int scoreAnswer(std::string answer, std::ostream & output = std::cout);
private:
	bool correctAnswer;
};
