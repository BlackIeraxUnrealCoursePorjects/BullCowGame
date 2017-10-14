/*This is the console executable that makes use of the bull cow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame;
void PrintGameSummary();

//the entry point for the application
int main()
{	
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}



void PrintIntro()
{
	//introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{	
	BCGame.Reset();
	//making instance of bc game
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;

	//loop asking the guesses while the loop is not won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		//submit valid guess to the game and recive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	

	//TODO summarise game
	PrintGameSummary();
	return;
}

FText GetValidGuess() //TODO to GetValidGuess

{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do 
	{
		int32 CurrentTry = BCGame.GetCurentTry();
		//ask the user for a guess
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout <<". Enter your guess: ";

		//get a guess from the player
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n\n";
			break;
		default:
			//asume the guess is valid
			break;
		}
		
	} while (Status != EGuessStatus::OK); //Keep looping untill we get no errors
	return Guess;

	
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done you Win!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}