#pragma once
#include "pch.h"
#include "FBullCowGame.h"
#include <map>
//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame () { Reset (); } //default constructor
int32 FBullCowGame::GetCurrentTry () const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength () const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries () const { 

	TMap <int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries [MyHiddenWord.length ()];

}

void FBullCowGame::Reset () {

	const Fstring HIDDEN_WORD = "horse"; // this MUST be an isogram
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
		//compare letters against the guess
		for ( int32 GChar = 0; GChar < WordLength; GChar++ ) {
			//if they match then
			if ( Guess [GChar] == MyHiddenWord [MHWChar] ) {
				if ( MHWChar == GChar ) { // if they are in the same place
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

bool FBullCowGame::IsIsogram (Fstring word) const {

	// treat 0 and 1 letter words as isograms
	if ( word.length () <= 1 ) { return true; }
	TMap <char, bool> LetterSeen; //setup map
	for ( auto Letter : word ) //for all letter of the word
	{
		Letter = tolower (Letter); //handle mix case
		if ( LetterSeen [Letter] ) { // if the letter is in the map
			return false; // we do not have an isogram 
		}
		else {
			LetterSeen [Letter] = true; //add the letter to the map as seen
		}
	}
	return true; // for ex. in cases where /0 is entered
}

bool FBullCowGame::IsLowercase (Fstring word) const {

	for ( auto Letter : word ) {

		if ( !islower(Letter) )
			return false;
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity (Fstring Guess) const {

		if (!IsIsogram(Guess)) {
			return EGuessStatus::Not_Isogram;
		}
		else if (!IsLowercase(Guess)) {
			return EGuessStatus::Not_Lowercase;
		}
		else if ( Guess.length () != GetHiddenWordLength() ) {
			return EGuessStatus::Wrong_Length;
		}
		else {
			return EGuessStatus::OK;
		}
}
