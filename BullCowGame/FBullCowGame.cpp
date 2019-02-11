#include "pch.h"
#include "FBullCowGame.h"
#include <string>

using int32 = int;

void FBullCowGame::Reset () {

	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const Fstring HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;// kom
	return;
}

//receives a valid guess, incriments turn, and return count
FBullCowCount FBullCowGame::SubmitGuess (Fstring Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.size ();
	Fstring MyGuess = Guess;

	for ( int32 i = 0; i < HiddenWordLength; i++ ) {
		for ( int32 j = 0; j < HiddenWordLength; j++ ) {
			if ( Guess [i] == MyHiddenWord [i] )
				if ( i == j )
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
		}
	}


	return BullCowCount;
}

FBullCowGame::FBullCowGame () {

	Reset ();
}

int32 FBullCowGame::GetMaxTries () const {

	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry () const {
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon () const {
	return false;
}

bool FBullCowGame::CheckGuessValidity (Fstring) {
	return false;
}
