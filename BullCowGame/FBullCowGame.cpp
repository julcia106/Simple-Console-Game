#pragma once
#include "pch.h"
#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame () { Reset (); }
int32 FBullCowGame::GetMaxTries () const { return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry () const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength () const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset () {

	constexpr int32 MAX_TRIES = 8;
	const Fstring HIDDEN_WORD = "pantera";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//receives a valid guess, incriments turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess (Fstring Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the hidden word
	for ( int32 MHWChar = 0; MHWChar < WordLength; MHWChar++ ) {
		for ( int32 GChar = 0; GChar < WordLength; GChar++ ) {
			if ( Guess [GChar] == MyHiddenWord [MHWChar] ) {
				if ( MHWChar == GChar ) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if ( BullCowCount.Bulls == WordLength ) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity (Fstring Guess) const {

		if (false) {
			return EGuessStatus::Not_Isogram;
		}
		else if (false) {
			return EGuessStatus::Not_Lowercase;
		}
		else if ( Guess.length () != GetHiddenWordLength() ) {
			return EGuessStatus::Wrong_Length;
		}
		else {
			return EGuessStatus::OK;
		}
}
