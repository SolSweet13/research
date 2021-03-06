#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//All numbers initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public: 
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 ConvertPlayerHiddenWord(FString);
	bool GetIsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);


private:
	//See constructor for initialization
	int32 MyCurretTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	void SetHiddenWord(int32);
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsValidNumber(FString) const;
};