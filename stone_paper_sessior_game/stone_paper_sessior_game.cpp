// stone_paper_sessior_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <string>

using namespace std;

enum enGameChoice {Stone = 1, Paper = 2, Scissors = 3};
enum enWinner {Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo {
	short roundNumber;
	enGameChoice playerChoice;
	enGameChoice computerChoice;
	enWinner winner;
	string winnerName;
};

struct stGameResults {
	short gameRounds;
	short computerWinTimes;
	short player1WinTimes;
	short drawTimes;
	enWinner gameWinner;
	string winnerName;

};

string Tabs(short NumberOfTabs) {
	string t = "";

	for(int i = 1; i < NumberOfTabs; i++) {
		t += "\t";
		cout<<t;
	}
	return t;
}

int ReadPositiveNumber(string message) {
	int number = 0;
	cout <<message<<endl;
	cin >> number;

	return number;
}

int RandomNumber(int From, int To) {
	int randNumber = rand() % (To - From + 1) + From;
	return randNumber;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
	
	if(RoundInfo.playerChoice == RoundInfo.computerChoice) {
		return enWinner::Draw;
	}

	switch (RoundInfo.playerChoice)
	{
	case enGameChoice::Stone: 
		if(RoundInfo.computerChoice == enGameChoice::Paper) {
		return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper: 
		if(RoundInfo.computerChoice == enGameChoice::Scissors) {
		return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors: 
		if(RoundInfo.computerChoice == enGameChoice::Stone) {
		return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;
}

void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout<<"\a";
		break; 

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

void ShowFinalGameResults(stGameResults GameResults) {
	cout<<Tabs(2)<<"____________________[ Game Results ]____________________\n\n";
	cout<<Tabs(2)<<"Game Rounds		   : "<<GameResults.gameRounds<<endl;
	cout<<Tabs(2)<<"Player1 won times  : "<<GameResults.player1WinTimes<<endl;
	cout<<Tabs(2)<<"Computer won times : "<<GameResults.computerWinTimes<<endl;
	cout<<Tabs(2)<<"Draw times	       : "<<GameResults.drawTimes<<endl;
	cout<<Tabs(2)<<"Final winner	   : "<<GameResults.winnerName<<endl;
	cout<<Tabs(2)<<"___________________________________________________________\n";

	SetWinnerScreenColor(GameResults.gameWinner);
}

void ShowGameOverScreen() {
	cout<<Tabs(2)<<"_________________________________________________________\n\n";
	cout<<Tabs(2)<<"				+++ G a m e O v e r +++\n";
	cout<<Tabs(2)<<"_________________________________________________________\n\n";
}

short ReadHowManyRounds() {
	int GameRounds = 1;
	do {
	GameRounds = ReadPositiveNumber("How many rounds 1 to 10 ?");
	} while(GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

enGameChoice ReadPlayerChoice() {
	short choice = 1;

	do {
		cout<<"Your choice: [1]:Stone, [2]:Paper, [3]:Sicssors ? ";
		cin >> choice;
	} while(choice < 1 || choice > 3);

	return (enGameChoice)choice;
}

enGameChoice GetComputerChoice(){
	return (enGameChoice)RandomNumber(1,3);
}

string ChoiceName(enGameChoice Choice) {
	string arrGameChoices[3] = {"Stone", "Paper", "Sicssors"};
	return arrGameChoices[Choice - 1];
}

void PrintRoundResults(stRoundInfo RoundInfo) {
	cout<<"______________Round [ "<< RoundInfo.roundNumber <<" ] ______________\n\n";
	cout<<"Player1 Choice: "<<ChoiceName(RoundInfo.playerChoice)<<endl;
	cout<<"Computer Choice: "<<ChoiceName(RoundInfo.computerChoice)<<endl;
	cout<<"Round Winner: [ "<<RoundInfo.winnerName<<" ]\n";
	cout<<"______________________________\n"<<endl;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes) {
	if(Player1WinTimes > ComputerWinTimes) 
		return enWinner::Player;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

string WinnerName (enWinner Winner) {
	string arrWinnerName[3] = {"Player1", "Computer", "No Winner"};
	return arrWinnerName[Winner - 1];
}

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {
	stGameResults GameResults;

	GameResults.gameRounds = GameRounds;
	GameResults.player1WinTimes = Player1WinTimes;
	GameResults.computerWinTimes = ComputerWinTimes;
	GameResults.drawTimes = DrawTimes;
	GameResults.gameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.winnerName = WinnerName(GameResults.gameWinner);

	return GameResults;
}

stGameResults PlayGame(short HowManyRounds) {
	stRoundInfo roundInfo;
	short playerWinTimes = 0, computerWinTimes = 0, drawTimes = 0;

	for(short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
		cout<<"\nRound [ "<<GameRound<<" ] begins :\n";
		roundInfo.playerChoice = ReadPlayerChoice();
		roundInfo.computerChoice = GetComputerChoice();
		roundInfo.winner = WhoWonTheRound(roundInfo);
		roundInfo.winnerName = WinnerName(roundInfo.winner);
		roundInfo.roundNumber = GameRound;

		// Increase win/draw counters
		if(roundInfo.winner == enWinner::Player) {
			playerWinTimes++;
		} else if (roundInfo.winner == enWinner::Computer) {
			computerWinTimes++;
		} else {
			drawTimes++;
		}

		PrintRoundResults(roundInfo);
	}

	return FillGameResults(HowManyRounds, playerWinTimes, computerWinTimes, drawTimes);
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}


void StartGame() {
	char playAgain = 'Y';
	do {
	ResetScreen();
	stGameResults gameResults = PlayGame(ReadHowManyRounds());
	ShowGameOverScreen();
	ShowFinalGameResults(gameResults);
	cout<<endl<<Tabs(3)<<"Do you want to play again ? Y/N ?\n";
	cin >> playAgain;
	} while(playAgain == 'Y' || playAgain == 'y');
}


int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));

	StartGame();
	
	system("pause");
	return 0;
}

