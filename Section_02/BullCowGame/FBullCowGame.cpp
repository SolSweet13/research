#include <iostream>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FText = std::string;

TMap<int32, FString> ChosenWordLength{ {3, "map"}, {4, "live"}, {5, "plane"}, {6, "planet"} };

FBullCowGame::FBullCowGame() { Reset(); } //Default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurretTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::GetIsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::ConvertPlayerHiddenWord(FString PlayerChosenLength)
{
	
	int32 NewHiddenWordLength = 0;
	if (IsValidNumber(PlayerChosenLength))
	{
		//Converts the string to an int, if we've verified the it can be
		NewHiddenWordLength = std::stoi(PlayerChosenLength);
		SetHiddenWord(NewHiddenWordLength);
		return NewHiddenWordLength;
	}
	else
	{
		//This returns zero so the AskForHiddenWordLength() in main.cpp continues to run
		return 0;
	}
	
}

//Size of Hidden Word... Is this needed or will the enum suffice?
void FBullCowGame::SetHiddenWord(int32 NewWordLength)
{
	//std::cout << ChosenWordLength[NewWordLength] << std::endl;
	MyHiddenWord = ChosenWordLength[NewWordLength];
	return;
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 4}, {5,5}, {6,7} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{

	//const FString HIDDEN_WORD = "planet";
	MyHiddenWord = "map";

	MyCurretTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if the guess isn't an isogram, return an error 
	if (!IsIsogram(Guess) ) 
	{
		return EGuessStatus::Not_Isogram;
	}	
	//if the guess isn't all lowercase, return error 
	else if (!IsLowercase(Guess)) 
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

	for (auto Letter : Word) //For all letters of the word
	{
		Letter = tolower(Letter); //Handle mixed capitalization case
		
		//If the letter can be found in the map, this isn't an isogram
		if (LetterSeen.find(Letter) != LetterSeen.end())
		{
			//std::cout << "Has this letter been seen?: " << Letter << (LetterSeen.find(Letter) != LetterSeen.end()) << std::endl;
			return false;
		}
		else //Add the letter to the map to get checked against
		{
			LetterSeen.insert(std::make_pair(Letter, true));
		}
		

	}

	/* LEAVING IN FOR NOW
		This was a different way of arriving at the same answer
		It takes compares the size of the map array after adding
		all the letters to the size of the word. This worked fine
		since the map only adds an entry once and won't duplicate it
		However it's faster to check the above way because as soon as
		a duplicate is found it jumps out of adding the map.
	*/
	//If the container size doesn't equal the word size, it can't be an isogram
	//if (LetterSeen.size() != Word.size())
	//{
	//	std::cout << "This is not an isogram..." << std::endl;
	//	return false;
	//}
	////Else return true cause all letters were only seen once
	//else
	//{
	//	std::cout << "Isogram confirmed!!!";
	//	return true;
	//}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{

	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			//std::cout << "This letter is not lower case: " << Letter << std::endl;
			return false; 
		}
	}

	return true;
}

//Check player entered string for validity when choosing a word length
bool FBullCowGame::IsValidNumber(FString PlayerChosenLength) const
{
	int32 LetterCount =	0;

	for (auto Letter : PlayerChosenLength) //For all letters of the word
	{

		//std::cout << "For Loop: " << Letter;

		//If there are too many characters then it can't be a single integer
		if (LetterCount > 0)
		{
			std::cout << "Please enter a single digit. " << std::endl;
			return false; 
		}


		LetterCount++;
	}

	//std::cout << "What value is this? " << std::stoi(PlayerChosenLength);
	//Ensures this char can be converted to an int
	for (FString::size_type i = 0; i < PlayerChosenLength.length(); i++)
	{
		if (isdigit(PlayerChosenLength[i]) ) //If this is a digit, break the loop and check for valid range
		{
			break;
		}
		else //This is not a digit and return false to continue asking for a valid number
		{
			return false;
		}
	} 
	

	//Check the number to make sure it's between 3 and 6
	if (std::stoi(PlayerChosenLength) == 3)	{ return true; }
	else if (std::stoi(PlayerChosenLength) == 4) { return true; }
	else if (std::stoi(PlayerChosenLength) == 5) { return true; }
	else if (std::stoi(PlayerChosenLength) == 6) { return true; }
	else { std::cout << PlayerChosenLength << " is not between 3 and 6... \n";  return false; }
	
	//return false;
}
