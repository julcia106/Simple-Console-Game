#pragma once
#include "pch.h"
#include "FBullCowGame.h"
#include <iostream>
#include <string>

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro ();
void PrintGameSummary ();
void PlayGame ();
bool AskToPlayAgain ();
FText GetValidGuess ();
FBullCowGame BCGame;

int main () {

	bool bPlayAgain = false;
	do {
		PrintIntro ();
		PlayGame ();
		bPlayAgain = AskToPlayAgain ();
	}
	while ( bPlayAgain );

	return 0;
}

void PrintIntro () {

	std::cout << "\n\nWelocome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength ();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

//plays a single game to completion
void PlayGame () {

	BCGame.Reset ();
	int32 MaxTries = BCGame.GetMaxTries ();

	while ( !BCGame.IsGameWon () && BCGame.GetCurrentTry()<= MaxTries ) {
		FText Guess = GetValidGuess ();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess (Guess);

		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << ". Cows= " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary ();
}

//loop continually until the user gives a valid guess
FText GetValidGuess () {

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry ();
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries() <<". Enter your guess: ";
		getline (std::cin, Guess);

		Status = BCGame.CheckGuessValidity (Guess);
		switch ( Status ) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength () << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please eneter a word without repeating letter.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			//assume the guess is valid 
			break;
		}
	}
	while ( Status != EGuessStatus::OK ); //keep looping until we get no errors
	return Guess;

}

bool AskToPlayAgain () {
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline (std::cin, Response);

	return (Response [0] == 'y') || (Response [0] == 'Y');

	std::cout << std::endl;
}

void PrintGameSummary () {
	if ( BCGame.IsGameWon () )
		std::cout << "YOU WIN!\n\n";
	else
		std::cout << "Better luck next time!\n\n";
}