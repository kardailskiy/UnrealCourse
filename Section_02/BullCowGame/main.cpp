// BullCowGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());

    return 0;
}

void PrintIntro()
{
	std::cout << "Welcome" << std::endl;
	std::cout << "Can you guess " << BCGame.GetHiddenWordLength() << " letter?" << std::endl;
	std::cout << std::endl;

	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Ivalid_Status;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";

		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n\n";
				break;
			default:
				break;
		}
	} while (Status != EGuessStatus::Ok);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want a play again (y/n)?";
	FString Response = "";
	getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "Win" << std::endl;
	else
		std::cout << "Lose" << std::endl;
}

