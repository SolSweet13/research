/*This is the console executable, that makes use of the BullCow class.
This act as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int32;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //Instantiate a new game

//The entry poipnt for the application
int main()
{

	
	do 
	{
		PrintIntro(); //Announces the game
		PlayGame();
	} while ( AskToPlayAgain() );

	return 0;
}

//Indroduce the game
void PrintIntro()
{

	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;
	//Loop asking for guesses while the game is NOT won
	// and there are still tries remaining

	while (!BCGame.GetIsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		//std::cout << "DEBUG: Guess Status: " << std::endl;
		//repeat the guess back to them
		
		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		//Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	//std::cout << "DEBUG: Play Game is Over...\n";

	//TODO: Add a game summary
	PrintGameSummary();
	return;
}

//Loop until valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do
	{
		int32 ActiveTry = BCGame.GetCurrentTry();

		std::cout << std::endl;
		std::cout << "Try: " << ActiveTry << ". Enter a guess: ";

		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::OK:
			return Guess;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use all lower case in the guess. \n";
			break;
		default:
			//assuming the guess is valid
			return Guess;
			break;
		}

		std::cout << std::endl;

	} while (Status != EGuessStatus::OK); //Keep loop until we get now errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << std::endl;
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	std::cout << "Is it [y]? " << (Response[0] == 'y') || (Response[0] == 'Y');
	std::cout << std::endl;

	//Return
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.GetIsGameWon())
	{
		std::cout << "YOU WON! Or at least completed the puzzle. \n Congrats!";
	}
	else
	{
		std::cout << "Keep trying, Bulls equals right letter right place. \n Cows equal right letter for the word.";
	}

}
