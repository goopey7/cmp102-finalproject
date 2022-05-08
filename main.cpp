#include <iostream>
#include <cmath>

#include "Player.h"
#include "Match.h"
#include "Read.h"

int main()
{
	while(true)
	{
		Read::printFile("art.txt");
		std::cout << "What game do you wanna play?\n";
		std::cout << "1) 301 Darts\n";
		std::cout << "2) 501 Darts\n";
		std::cout << "3) Quit Program\n";
		std::cout << "Enter Choice (1/2/3): > ";
		int choice = 0;
		std::cin >> choice;
		while(choice < 1 || choice > 3)
		{
			std::cout << "It's either 1, 2, or 3 you muppet\n";
			std::cout << "Enter Choice (1/2/3): > ";
			std::cin.clear();
			std::cin >> choice;
		}

		if(choice == 3)
		{
			std::cout << "goodbye!\n";
			return 0;
		}
		
		std::cout << "Would you like to automatically simulate matches? (Y/N): > ";
		std::string yesOrNo;
		std::cin.clear();
		std::cin >> yesOrNo;
		while(yesOrNo != "No" && yesOrNo != "no" && yesOrNo != "N" && yesOrNo != "n"
				&& yesOrNo != "Yes" && yesOrNo != "yes" && yesOrNo != "Y" && yesOrNo != "y")
		{
			std::cout << "Please input 'yes' or 'no' (Y/N) > ";
			std::cin.clear();
			std::cin >> yesOrNo;
		}

		std::cout << "Enter a name for player 1: > ";
		std::string p1Name;
		std::cin.clear();
		std::cin >> p1Name;
		std::cout << "Enter a percent accuracy for " << p1Name << ": > ";
		int p1Accuracy = 0;
		std::cin.clear();
		std::cin >> p1Accuracy;
		Player p1(p1Name,p1Accuracy);

		std::cout << "Enter a name for player 2: > ";
		std::string p2Name;
		std::cin.clear();
		std::cin >> p2Name;
		std::cout << "Enter a percent accuracy for " << p2Name << ": > ";
		int p2Accuracy = 0;
		std::cin >> p2Accuracy;
		Player p2(p2Name,p2Accuracy);

		bool bP1FirstIn301 = true;
		if(choice == 1) // 301
		{
			std::cout << "Who would you like " << p1.getName() << " to go first? (Y/N): > ";

			std::string p1First = "";
			std::cin.clear();
			std::cin >> p1First;
			while(p1First != "No" && p1First != "no" && p1First != "N" && p1First != "n"
				&& p1First != "Yes" && p1First != "yes" && p1First != "Y" && p1First != "y")
			{
				std::cout << "Please input 'yes' or 'no' (Y/N) > ";
				std::cin >> p1First;
			}
			if(p1First.at(0) == 'N' || p1First.at(0) == 'n')
			{
				bP1FirstIn301 = false;
			}
		}

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
				for(int i=0;i<numMatches;i++)
				{
					Game game(&p1,&p2,GameType::ThreeHundredOne,bP1FirstIn301);
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
				double totalResults = 0;
				for(std::pair<std::string,int> result : frequencies)
					totalResults += result.second;
				for(std::pair<std::string,int> result : frequencies)
				{
					double percentRounded = std::round((result.second/totalResults)*100.f);
					// if percentage is below 0.5%, don't round to nearest percent
					if(((int)percentRounded) == 0)
					{
						percentRounded = ((double)result.second/(double)totalResults)*100.f;
					}
					std::cout << result.first << "                 " << percentRounded << "%\n";
					if(result.second > mostFrequency)
					{
						mostFrequentResult = result.first;
						mostFrequency = result.second;
					}
				}
				std::cout << "\n\nMost frequent outcome from " << numMatches << " matches:  " << mostFrequentResult << '\n';
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
				Game game(&p1,&p2,GameType::ThreeHundredOne,bP1FirstIn301);
				game.play();
			}
		}
		std::string returnToMenu = "";
		std::cout << "Return to main menu? (Y/N): > ";
		std::cin.clear();
		std::cin >> returnToMenu;
		while(returnToMenu != "No" && returnToMenu != "no" && returnToMenu != "N" && returnToMenu != "n"
			&& returnToMenu != "Yes" && returnToMenu != "yes" && returnToMenu != "Y" && returnToMenu != "y")
		{
			std::cout << "Please input 'yes' or 'no' (Y/N) > ";
			std::cin >> returnToMenu;
		}
		if(returnToMenu.at(0) == 'n' || returnToMenu.at(0) == 'N')
		{
			std::cout << "Thanks for playing :)\n";
			return 0;
		}
	}
	
	return 0;
}

