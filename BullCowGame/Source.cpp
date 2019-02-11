#include "pch.h"
#include "FBullCowGame.h"
#include <iostream>
#include <string>

using FText = std::string;
using int32 = int;

void PrintIntro ();
FText GetGuess ();
void PlayGame ();
bool AskToPlayAgain ();
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
	constexpr int32 WORD_LENGT = 5;
	std::cout << "Welocome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << WORD_LENGT << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

void PlayGame () {

	BCGame.Reset ();
	int32 MaxTries = BCGame.GetMaxTries ();

	for ( int32 i = 0; i < MaxTries; i++ ) {
		FText Guess = GetGuess ();

		FBullCowCount BullCowCount = BCGame.SubmitGuess (Guess);

		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << ". Cows= " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
}

FText GetGuess () {

	int32 CurrentTry = BCGame.GetCurrentTry ();
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	FText Guess = "";
	getline (std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain () {
	std::cout << "Do you want to play? (y/n) ";
	FText Response = "";
	std::getline (std::cin, Response);

	return (Response [0] == 'y') || (Response [0] == 'Y');

	std::cout << std::endl;
}