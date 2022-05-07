#include <iostream>
#include <cmath>

#include "Player.h"
#include "Match.h"
#include "Read.h"

int main()
{
	Read::printFile("art.txt");
	std::cout << "What game do you wanna play?\n";
	std::cout << "1) 301 Darts\n";
	std::cout << "2) 501 Darts\n";
	std::cout << "Enter Choice (1/2): > ";
	int choice = 0;
	std::cin >> choice;
	while(choice < 1 && choice > 2)
	{
		std::cout << "It's either 1 or 2 you muppet\n";
		std::cin >> choice;
	}
	std::cout << "Would you like to automatically simulate matches? (Y/N): > ";
	std::string yesOrNo;
	std::cin >> yesOrNo;
	while(yesOrNo != "No" && yesOrNo != "no" && yesOrNo != "N" && yesOrNo != "n"
			&& yesOrNo != "Yes" && yesOrNo != "yes" && yesOrNo != "Y" && yesOrNo != "y")
	{
		std::cout << "Please input 'yes' or 'no' (Y/N) > ";
		std::cin >> yesOrNo;
	}

	std::cout << "Enter a name for player 1: > ";
	std::string p1Name;
	std::cin >> p1Name;
	std::cout << "Enter a percent accuracy for " << p1Name << ": > ";
	int p1Accuracy = 0;
	std::cin >> p1Accuracy;
	Player p1(p1Name,p1Accuracy);

	std::cout << "Enter a name for player 2: > ";
	std::string p2Name;
	std::cin >> p2Name;
	std::cout << "Enter a percent accuracy for " << p2Name << ": > ";
	int p2Accuracy = 0;
	std::cin >> p2Accuracy;
	Player p2(p2Name,p2Accuracy);

	// we are simulating matches
	if(yesOrNo.at(0) == 'Y' || yesOrNo.at(0) == 'y')
	{
		int numMatches = 0;
		std::cout << "How many matches would you like to simulate? > ";
		std::cin >> numMatches;

		// for 501
		std::map<std::string,int> frequencies;

		// for 301
		int p1Wins = 0;
		int p2Wins = 0;
		if(choice == 2)
		{
			for(int i=0;i<numMatches;i++)
			{
				Match match(p1,p2);
				match.simulate();
				frequencies[match.getResult()]++;
			}
		}
		else
		{
			// TODO determine who goes first

			for(int i=0;i<numMatches;i++)
			{
				Game game(&p1,&p2,GameType::ThreeHundredOne,true);
				game.simulate();

				if(game.getWinner() == p1.getName())
					p1Wins++;
				else
					p2Wins++;
			}
		}

		std::cout << "\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n";
		if(choice == 2) // 501 sim results
		{
			std::cout << "Result\n";
			std::cout << p1.getName() << " : " << p2.getName() << "                 ";
			std::cout << "Frequency\n";
			std::string mostFrequentResult = "";
			int mostFrequency = 0;
			float totalResults = 0;
			for(std::pair<std::string,int> result : frequencies)
				totalResults += result.second;
			for(std::pair<std::string,int> result : frequencies)
			{
				std::cout << result.first << "                 " << std::round((result.second/totalResults)*100.f) << "%\n";
				if(result.second > mostFrequency)
				{
					mostFrequentResult = result.first;
					mostFrequency = result.second;
				}
			}
			std::cout << "\n\nMost frequent outcome: " << mostFrequentResult << '\n';
		}
		else // 301 sim results
		{
			std::cout << "Score: " << p1.getName() << " " << p1Wins << " : " << p2Wins << " " << p2.getName();
		}
		std::cout << "\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n";
	}
	else
	{
		if(choice == 2)
		{
			Match match(p1,p2);
			match.play();
		}
		else
		{
			Game game(&p1,&p2,GameType::ThreeHundredOne,true);
			game.play();
		}
	}
	return 0;
}

