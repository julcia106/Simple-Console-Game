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

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame ();
		
	int32 GetMaxTries () const;
	int32 GetCurrentTry () const;
	int32 GetHiddenWordLength ()const;
	bool IsGameWon () const;
	EGuessStatus CheckGuessValidity (Fstring) const;

	void Reset ();
	FBullCowCount SubmitValidGuess (Fstring);
private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	Fstring MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram (Fstring) const;

};