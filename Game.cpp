//Copyright Sam Collier 2022

#include "Game.h"

Game::Game(Player* p1, Player* p2, GameType type, int id, bool p1First)
	: bP1First(p1First)
{
	players.first = p1;
	players.second = p2;

	switch(type)
	{
		case ThreeHundredOne:
			board = new ThreeHundredOneBoard(p1->getName(),p2->getName());
			break;
		case FiveHundredOne:
			// TODO INITIALIZE 501 BOARD
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
			desiredTarget = currentPlayer->getPointsInCurrentGame() - 50;
		}
		else if(currentPlayer->getPointsInCurrentGame() == 50)
		{
			desiredTarget = 50;
			desiredZone = Zone::Bullseye;
		}

		std::cout << "\n===========================================================================\n";
		std::cout << currentPlayer->getName() << " has " << currentPlayer->getPointsInCurrentGame() << '\n';
		std::cout << currentPlayer->getName() << " is going for a " << desiredTarget << '\n';
		int result = currentPlayer->throwDart(desiredTarget,desiredZone);
		std::cout << currentPlayer->getName() << " hit a " << result << "!\n";
		std::cout << currentPlayer->getName() << " now has " << currentPlayer->getPointsInCurrentGame() << '\n';
		std::cout << "\n===========================================================================\n";
		bP1Turn = !bP1Turn;
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

