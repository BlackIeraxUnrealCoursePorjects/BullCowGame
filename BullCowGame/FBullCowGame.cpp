#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } //default constructor


int32 FBullCowGame::GetCurentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {2,4}, {3,6}, {4,8}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}




//recives a VALID guess, incriments turn and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length();//asuming the same as guess

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//compare letters against the hidden guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) {//if they are in the same place
					BullCowCount.Bulls++;// incriment bulls
				}
				else 
				{
					BullCowCount.Cows++;// must be a cow
				}
			}
			
			
		}
	}

	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (char Letter : Word) //loop through all the letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])
		{
			return false;//we do not have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;//add the letter to the map as seen
		}
	}
			
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercase letter
		{
			return false;
		}
		
	}
	return true;
}
