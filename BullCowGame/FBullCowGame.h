#pragma once
#include "pch.h"
#include <iostream>
#include <string>

using Fstring = std::string;
using int32 = int;

struct	FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame ();
	int32 GetMaxTries () const;
	int32 GetCurrentTry () const;
	bool IsGameWon () const;
	bool CheckGuessValidity (Fstring);
	void Reset ();
	//count bulls and cows, and increased try number assumin valid guess
	FBullCowCount SubmitGuess (Fstring);
private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	Fstring MyHiddenWord;

};