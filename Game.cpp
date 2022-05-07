//Copyright Sam Collier 2022

#include "Game.h"

Game::Game(Player* p1, Player* p2, GameType type, int id, bool p1First)
	: bP1First(p1First), gameType(type)
{
	players.first = p1;
	players.second = p2;

	switch(type)
	{
		case ThreeHundredOne:
			board = new ThreeHundredOneBoard(p1->getName(),p2->getName());
			break;
		case FiveHundredOne:
			board = new FiveHundredOneBoard(p1->getName(), p2->getName());
			break;
	}

	p1->newGame(board);
	p2->newGame(board);

	this->id = id;
}

Game::~Game()
{
	delete board;
}

DartBoard* Game::getBoard() const
{
	return board;
}

int Game::getID() const
{
	return id;
}

const std::string& Game::getWinner() const
{
	return winner;
}

void Game::simulate()
{
	Player* p1 = (bP1First) ? players.first : players.second;
	Player* p2 = (!bP1First) ? players.first : players.second;

	bool bP1Turn = true;
	while(!board->isGameOver())
	{
		Player* currentPlayer = (bP1Turn) ? p1 : p2;

		// AI LOGIC
		int desiredTarget;
		Zone desiredZone = Zone::Single;
		int result;

		std::cout << "\n===========================================================================\n";
		std::cout << currentPlayer->getName() << " has " << currentPlayer->getPointsInCurrentGame() << '\n';

		// 301 AI
		if(gameType == GameType::ThreeHundredOne)
		{

			if(currentPlayer->getPointsInCurrentGame() > 100)
			{
				// sometimes it'll go for 20s, sometimes bullseyes. Most effective way to knock pts down imo
				bool bCoinFlip = rand() % 2;
				if(bCoinFlip)
				{
					desiredTarget = 50;
					desiredZone = Zone::Bullseye;
				}
				else desiredTarget = 20;
			}
			else if(currentPlayer->getPointsInCurrentGame() > 70)
			{
				desiredTarget = 20;
			}
			else if(currentPlayer->getPointsInCurrentGame() > 50 && currentPlayer->getPointsInCurrentGame() <= 70)
			{
				desiredTarget = board->getClosestTarget(currentPlayer->getPointsInCurrentGame()-50);
			}
			else if(currentPlayer->getPointsInCurrentGame() == 50)
			{
				desiredTarget = 50;
				desiredZone = Zone::Bullseye;
			}
			result = currentPlayer->throwDart(desiredTarget,desiredZone);
			std::cout << currentPlayer->getName() << " is going for a " << desiredTarget << '\n';
			std::cout << currentPlayer->getName() << " hit a " << result << "!\n";
		}
		// 501 AI
		else if(gameType == GameType::FiveHundredOne)
		{
			std::vector<std::pair<int,Zone>>* pThrows = new std::vector<std::pair<int,Zone>>();

			// TURNS
			for(int turn=0;turn<3;turn++)
			{
				ThrowError* error = new ThrowError();
				if(currentPlayer->getPointsInCurrentGame() > 100)
				{
					desiredZone = Zone::Single;
					desiredTarget = 0;
					bool bGoForSpecialZone = rand() % 2;
					if(bGoForSpecialZone)
					{
						bool bGoForDouble = rand() % 2;
						if(bGoForDouble)
							desiredZone = Zone::Double;
						else desiredZone = Zone::Treble;
					}

					// sometimes scratch that idea and go for bullseye instead
					bool bGoForBullseyeInstead = rand() % 4 == 0;
					if(bGoForBullseyeInstead)
						desiredZone = Zone::Bullseye;
					desiredTarget = 20;
				}
				else if(currentPlayer->getPointsInCurrentGame() > 52)
				{
					// aim for the bullseye and hope for the best
					desiredZone = Zone::Bullseye;

					bool bMaybeTryDouble = rand() % 6 == 0;
					if(bMaybeTryDouble)
					{
						desiredZone = Zone::Double;
						while(desiredTarget == 0)
							desiredTarget = (*board->getNeighbors())[0][rand() % (*board->getNeighbors())[0].size()];
					}
				}
				// we're in the endgame and we want to hit zero with a double or bullseye
				else if(currentPlayer->getPointsInCurrentGame() == 50 || currentPlayer->getPointsInCurrentGame() == 52) 
				{
					desiredZone = Zone::Bullseye;
					desiredTarget = 50;
				}
				else if(currentPlayer->getPointsInCurrentGame() < 50 && currentPlayer->getPointsInCurrentGame() > 20)
				{
					desiredZone = Zone::Single;
					desiredTarget = 20;
				}
				else if(currentPlayer->getPointsInCurrentGame() <= 20 && currentPlayer->getPointsInCurrentGame() > 10)
				{
					desiredZone = Zone::Double;
					desiredTarget = board->getClosestTarget(currentPlayer->getPointsInCurrentGame());
				}
				else if(currentPlayer->getPointsInCurrentGame() <= 10)
				{
					desiredZone = Zone::Double;
					desiredTarget = board->getClosestTarget(currentPlayer->getPointsInCurrentGame()/2);
				}

				Zone* hitZone = new Zone();
				result = currentPlayer->throwDart(desiredTarget,desiredZone,hitZone,pThrows,error);
				// resulting output
				if(desiredZone != Zone::Bullseye)
					std::cout << currentPlayer->getName() << " is going for a " << zoneToString(desiredZone) << " " << desiredTarget << '\n';
				else
					std::cout << currentPlayer->getName() << " is going for a bullseye!\n";
				if(result != 0)
				{
					if(*hitZone != Zone::Bullseye && *hitZone != Zone::OuterBullseye)
						std::cout << currentPlayer->getName() << " hit a " << zoneToString(*hitZone) << " " << result << "!\n";
					else if(*hitZone == Zone::Bullseye)
						std::cout << currentPlayer->getName() << " hit a bullseye!!\n";
					else if(*hitZone == Zone::OuterBullseye)
						std::cout << currentPlayer->getName() << " hit the outer bullseye!!\n";
				}
				else
					std::cout << currentPlayer->getName() << " has managed to miss the board entirely\n";
				if(*error == ThrowError::SurpassedZero)
					std::cout << currentPlayer->getName() << " has surpassed 0 points. Bust!\n";
				else if(*error == ThrowError::ImpossibleToFinish)
					std::cout << currentPlayer->getName() << " can't score a double at the end!\n";
				else if(*error == ThrowError::NotEndOnDouble)
					std::cout << currentPlayer->getName() << " did not finish with a double or bullseye!\n";
				bool bBreakLoop = *error != ThrowError::None || currentPlayer->getPointsInCurrentGame() == 0;
				delete hitZone;
				if(*error != ThrowError::None)
				{
					board->undoLastThreeThrows(currentPlayer->getName(),pThrows);
				}

				delete error;

				if(bBreakLoop)
					break;
			}
			int totalScored = 0;
			for(std::pair<int,Zone> score : *pThrows)
			{
				if(score.second != Zone::Bullseye && score.second != Zone::OuterBullseye)
					totalScored+=score.first*score.second;
				else
					totalScored+=score.first;
			}
			std::cout << currentPlayer->getName() << " scored " << totalScored << '\n';
			pThrows->clear();
			delete pThrows;
		}
		std::cout << currentPlayer->getName() << " now has " << currentPlayer->getPointsInCurrentGame() << '\n';
		std::cout << "\n===========================================================================\n";
		bP1Turn = !bP1Turn;
		if(currentPlayer->getPointsInCurrentGame() == 0)
			break;
	}
	std::cout << "\n***************************************************\n";
	std::cout << "WINNER: " << board->getWinner();
	std::cout << "\n***************************************************\n";
}

void Game::play()
{
	Player* p1 = (bP1First) ? players.first : players.second;
	Player* p2 = (!bP1First) ? players.first : players.second;

	bool bP1Turn = true;
	while(!board->isGameOver())
	{
		Zone desiredZone = Zone::Single;
		Player* currentPlayer = (bP1Turn) ? p1 : p2;
		std::cout << "\n===================================================\n";
		std::cout << "Current Player: " << currentPlayer->getName() << '\n';
		std::cout << "Ponts: " << currentPlayer->getPointsInCurrentGame() << '\n';
		std::cout << "\n===================================================\n";
		std::cout << "<Enter desired target> : ";
		int desiredTarget;
		std::cin >> desiredTarget;
		if(desiredTarget == 50)
			desiredZone = Zone::Bullseye;
		std::cout << currentPlayer->getName() << " hit a " << currentPlayer->throwDart(desiredTarget,desiredZone) << "!\n";
		bP1Turn = !bP1Turn;
	}
	std::cout << "\n***************************************************\n";
	std::cout << "WINNER: " << board->getWinner();
	std::cout << "\n***************************************************\n";
}

std::string Game::zoneToString(Zone zoneIn)
{
	switch(zoneIn)
	{
		case Zone::Bullseye:
			return "bullseye";
			break;
		case Zone::Double:
			return "double";
			break;
		case Zone::Single:
			return "single";
			break;
		case Zone::Treble:
			return "treble";
			break;
		case Zone::OuterBullseye:
			return "outer bullseye";
			break;
	}
	return "";
}

std::string Game::getWinner()
{
	return winner;
}

