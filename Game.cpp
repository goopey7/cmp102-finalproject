//Copyright Sam Collier 2022

#include "Game.h"

Game::Game(Player* p1, Player* p2, GameType type, bool p1First)
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
}

Game::~Game()
{
	delete board;
}

DartBoard* Game::getBoard() const
{
	return board;
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
		srand(msSinceEpoch());
		Player* currentPlayer = (bP1Turn) ? p1 : p2;

		// AI LOGIC
		int desiredTarget;
		Zone desiredZone = Zone::Single;
		int result;

		std::cout << "\n===========================================================================\n";
		if(currentPlayer->getPointsInCurrentGame() == 1)
		{
			int x;
			std::cin >> x;
		}
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
				else if(currentPlayer->getPointsInCurrentGame() < 50 && currentPlayer->getPointsInCurrentGame() > 21)
				{
					desiredZone = Zone::Single;
					desiredTarget = 20;
				}
				else if(currentPlayer->getPointsInCurrentGame() <= 21)
				{
					desiredZone = Zone::Double;
					desiredTarget = board->getClosestTarget(currentPlayer->getPointsInCurrentGame()/2);
					if(desiredTarget*2 == currentPlayer->getPointsInCurrentGame()-1)
						desiredZone = Zone::Single;
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
	winner = board->getWinner();
}

void Game::play()
{
	Player* p1 = (bP1First) ? players.first : players.second;
	Player* p2 = (!bP1First) ? players.first : players.second;

	bool bP1Turn = true;
	while(!board->isGameOver())
	{
		Player* currentPlayer = (bP1Turn) ? p1 : p2;
		std::cout << "\n===================================================\n";
		std::cout << "Current Player: " << currentPlayer->getName() << '\n';
		std::cout << "Ponts: " << currentPlayer->getPointsInCurrentGame() << '\n';
		std::cout << "\n===================================================\n";
		// 301 Manual gameplay
		if(gameType == GameType::ThreeHundredOne)
		{
			Zone desiredZone = Zone::Single;
			
			std::cout << "<Enter desired target> : ";
			int desiredTarget;
			std::cin >> desiredTarget;
			
			// handle bad input
			while(!isATarget(desiredTarget) && desiredTarget != 50 && desiredTarget != 0)
			{
				std::cout << "\nPlease enter a valid target you muppet! > ";
				std::cin >> desiredTarget;
			}
			if(desiredTarget == 50)
				desiredZone = Zone::Bullseye;
			std::cout << currentPlayer->getName() << " hit a " << currentPlayer->throwDart(desiredTarget,desiredZone) << "!\n";
			bP1Turn = !bP1Turn;
		}
		// 501 Manual gameplay
		else if(gameType == GameType::FiveHundredOne)
		{
			std::vector<std::pair<int,Zone>>* pThrows = new std::vector<std::pair<int,Zone>>();

			// TURNS
			for(int turn=0;turn<3;turn++)
			{
				ThrowError* error = new ThrowError();
				
				Zone desiredZone;
				int desiredTarget;

				// select a zone
				int choice = 0;
				int roundScoreSoFar = 0;
				for(std::pair<int,Zone> dart : *pThrows)
				{
					if(dart.second != Zone::Bullseye && dart.second != Zone::OuterBullseye)
						roundScoreSoFar += dart.first * dart.second;
					else
						roundScoreSoFar += dart.first;
				}
				std::cout << "\n\nScore accumulated so far: " << roundScoreSoFar;
				std::cout << "\nPotential score so far: " << currentPlayer->getPointsInCurrentGame() - roundScoreSoFar;
				std::cout << "\n\nPlease select your desired Zone:\n";
				std::cout << "(1) Single\n";
				std::cout << "(2) Double\n";
				std::cout << "(3) Treble\n";
				std::cout << "(4) Outer Bullseye\n";
				std::cout << "(5) Inner Bullseye\n";
				std::cout << "Zone: > ";
				std::cin >> choice;
				while(choice < 1 || choice > 5)
				{
					std::cout << "Please enter a value between 1-5\n";
					std::cin >> choice;
				}

				switch(choice)
				{
					case 1:
						desiredZone = Zone::Single;
						break;
					case 2:
						desiredZone = Zone::Double;
						break;
					case 3:
						desiredZone = Zone::Treble;
						break;
					case 4:
						desiredZone = Zone::OuterBullseye;
						break;
					case 5:
						desiredZone = Zone::Bullseye;
						break;
				}

				// select a target
				if(desiredZone != Zone::Bullseye && desiredZone != Zone::OuterBullseye)
				{
					choice = 0;
					std::cout << "\nPlease input your desired target: > ";
					std::cin >> desiredTarget;
					if(!isATarget(desiredTarget))
					{
						std::cout << "\nPlease enter a valid target you muppet! > ";
						std::cin >> desiredTarget;
					}
				}
				else if(desiredZone == Zone::Bullseye)
				{
					desiredTarget = 50;
				}
				else
				{
					desiredTarget = 25;
				}

				Zone* hitZone = new Zone();
				int result = currentPlayer->throwDart(desiredTarget,desiredZone,hitZone,pThrows,error);
				// resulting output
				if(desiredZone != Zone::Bullseye && desiredZone != Zone::OuterBullseye)
					std::cout << currentPlayer->getName() << " is going for a " << zoneToString(desiredZone) << " " << desiredTarget << '\n';
				else if(desiredZone == Zone::Bullseye)
					std::cout << currentPlayer->getName() << " is going for a bullseye!\n";
				else
					std::cout << currentPlayer->getName() << " is going for the outer bullseye!\n";

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

long msSinceEpoch()
{
	using namespace std::chrono;
	milliseconds ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());
	return ms.count();
}

bool Game::isATarget(int targetIn) const
{
	return board->isTarget(targetIn);
}

