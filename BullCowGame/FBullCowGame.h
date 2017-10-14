#pragma once
#include <string>

using int32 = int;
using FString = std::string;

//all values initialise to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{

public:

	FBullCowGame(); //constructor

	void Reset(); //TODO make a more rich return value.
	int32 GetMaxTries() const;
	int32 GetCurentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon()const;
	EGuessStatus CheckGuessValidity(FString) const;//TODO make a more rich return value.
	FBullCowCount SubmitValidGuess(FString);


private:
	//see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};