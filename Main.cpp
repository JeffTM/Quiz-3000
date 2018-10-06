#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include "FileNotFoundException.h"
#include "InvalidQuizException.h"
#include "Question.h"
#include "QuizFileReader.h"
#include "Vector.h"
using namespace std;

int main()
{
	Jeff::Vector<shared_ptr<Question>> quiz;
	QuizFileReader fin;
	string finPath;
	ofstream fout;
	string foutPath;
	
	//Attempt to load and read the file
	cout << "Welcome to quiz 3000!" << endl;
	cout << "Enter the name of the file to read the quiz from: ";
	getline(cin, finPath);
	fin.setPath(finPath);
	while (!fin.checkFile())
	{
		cout << "That file does not exist. Please reenter: ";
		getline(cin, finPath);
		fin.setPath(finPath);
	}
	
	cout << "Enter the name of the file that you want to save your results to: ";
	getline(cin, foutPath);
	fout.open(foutPath);

	cout << "Loading quiz..." << endl;
	try
	{
		fin.read(quiz);
	}
	catch (InvalidQuizException e)
	{
		cout << "Could not read quiz file. Please ensure it is in the correct format." << endl;
		cout << "Error: " << e.what() << endl;
		cout << "Program terminated. Press any key to continue . . . ";
		cin.get();
		return -1;
	}
	cout << endl;

	//Run the quiz
	int points = 0;
	int totalPoints = 0;

	fout << "Quiz results:" << endl << endl;

	for (int i = 0; i < quiz.size(); i++)
	{
		string answer;

		cout << "Question " << i + 1 << endl << endl;
		fout << "Question " << i + 1 << endl;
		fout << "Points: " << quiz[i]->getPoints() << endl;
		quiz[i]->displayPrompt();
		cout << endl;
		cout << "Answer: ";
		getline(cin, answer);
		points += quiz[i]->scoreAnswer(answer, fout);
		totalPoints += quiz[i]->getPoints();
		cout << endl;
		fout << endl;
	}

	double score;
	if (totalPoints == 0)
		score = 100;
	else
		score = static_cast<double>(100) * points / totalPoints;

	cout << "Quiz completed. Final results:" << endl;
	cout << "Points earned: " << points << endl;
	cout << "Points possible: " << totalPoints << endl;
	cout << "Score: " << score << '%' << endl << endl;

	fout << "Final results:" << endl;
	fout << "Points earned: " << points << endl;
	fout << "Points possible: " << totalPoints << endl;
	fout << "Score: " << score << '%';

	fout.close();
	cout << "Program terminated. Press any key to continue . . . ";
	cin.get();
	return 0;
}