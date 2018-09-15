#include <iostream>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurretTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::GetIsGameWon() const{ return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 2;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurretTry = 1;
	bGameIsWon = false;

	return;
}

/*int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}*/

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if the guess isn't an isogram, return an error 
	if (!IsIsogram(Guess) ) 
	{
		return EGuessStatus::Not_Isogram;
	}	
	//if the guess isn't all lowercase, return error 
	else if (false) //TODO Write function
	{
		return EGuessStatus::Not_Lowercase;
	}
	//if the guess length is wrong, return error
	else if (GetHiddenWordLength() != Guess.length() )
	{
		return EGuessStatus::Wrong_Length;
	}
	//otherwise return OK
	else
	{
		return EGuessStatus::OK;
	}
}

//Receives a valid guess, increments turns and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurretTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming both words are same length

	//Loop through all letters in the Hidden Word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//std::cout << "Hidden word length: " << HiddenWordLength << std::endl;
			//std::cout << "Comparing letters: " << MyHiddenWord[MHWChar] << " " << Guess[GChar] << " \n";
			//std::cout << "The letters match: " << (MyHiddenWord[MHWChar] == Guess[GChar]) << std::endl;

			//Iterate through comparing all letters against the same to count cows
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				if (MHWChar == GChar)
				{
					//Increment cows based on matching letters for the word
					//std::cout << "Increasing Bulls: " << MyHiddenWord[MHWChar] << " " << Guess[GChar] << std::endl;
					BullCowCount.Bulls++;
				}
				else //(MyHiddenWord[MHWChar] == Guess[MHWChar])
				{
					if (MHWChar != GChar)
					{
						//std::cout << "Increasing Cows: " << MyHiddenWord[MHWChar] << " " << Guess[GChar] << std::endl;
						BullCowCount.Cows++;
					}
				}
			}
		}
		
		//Increment Bulls if they're in the same place

	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	
	//Cows are counting bulls and cows, subtracting bulls to give accurate amount
	//BullCowCount.Cows = BullCowCount.Cows - BullCowCount.Bulls;

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//Tread 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	//Setup a map
	TMap<char, bool> LetterSeen; 
	int32 MapLoc = 0;

	for (auto Letter : Word) //For all letters of the word
	{
		Letter = tolower(Letter); //Handle mixed case
		
		//Keep count of how many times each letter was seen
		LetterSeen.insert(std::pair<char, bool>(Letter, true));


		std::cout << MapLoc << " " << LetterSeen[MapLoc] << std::endl;

		MapLoc++;

		std::cout << '\n';

		//If same letter was seen twice return false

		//Else return true cause all letters were only seen once

	}

	
	return true;
}
