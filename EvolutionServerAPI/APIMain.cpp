#include <iostream>
#include <thread>
#include <stdlib.h>
#include <pch.h>

using namespace std::literals::chrono_literals;
//mikro szervizek + dockerek
int main()
{
	Simulation sim;

	int botCount = 100, foodCount = 500;

	int steps = 43;

	int inNodes = 2, outNodes = 4;

	int lives = 200;

	int width = 200, height = 50;

	sim.Innit(botCount, foodCount, steps, inNodes, outNodes, lives, width, height);

	sim.Start();

	srand(time(0));
	/*
	
	input: 4
	output: 4
	hidden: 1
	
	connection:
		1->5 
		2->5
		2->10
		10->5
	*/
	while (true)
	{
		std::cout << "\x1B[3J\x1B[H";
		//std::this_thread::sleep_for(0.1s);
		auto stats = sim.ReadState();

		std::cout << "botSzam: " << stats.botCount << " foodSzam: " << stats.foodCount << " maxInnov: " << stats.maxInnov << " stepCount: " << stats.stepNum << " maxGenNum: " << stats.maxGenCount << " " << std::endl;

		for (int x = 0; x <= width + 2; x++)
			std::cout << "=";
		std::cout << std::endl;

		for (int y = height ; y >= 0; y--)
		{
			std::cout << "|";
			for (int x = 0; x <= width; x++)
			{
				char out = ' ';

				auto it = stats.botsPos.begin();

				for (it; it != stats.botsPos.end(); it++) {
					if ((*it) == Position(x, y))
					{
						out = 'B';
					}
				}

				if (out == ' ')
				{
					it = stats.foodPos.begin();

					for (it; it != stats.foodPos.end(); it++) {
						if ((*it) == Position(x, y))
						{
							out = '.';
						}
					}
				}

				std::cout << out;
			}
			std::cout << "|" << std::endl;
		}
		for (int x = 0; x <= width + 2; x++)
			std::cout << "=";

		if (stats.botCount == 0)
			sim.End();

	}


	return 0;
}