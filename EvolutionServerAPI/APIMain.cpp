#include <iostream>
#include <thread>

#include "pch.h"

using namespace std::literals::chrono_literals;

int main()
{
	Simulation sim;

	int botCount = 1000, foodCount = 1500;

	int steps = 43;

	int inNodes = 6, outNodes = 1;

	int lives = 350;

	int width = 2000, height = 500;

	sim.Innit(botCount, foodCount, steps, inNodes, outNodes, lives, width, height);

	sim.Start();

	while (true)
	{
		std::cout << "\x1B[3J\x1B[H";
		std::this_thread::sleep_for(0.2s);
		auto bots = sim.ReadState();
		auto food = sim.ReadFood();

		std::cout << "botSzam: " << bots.size() << " " << std::endl;

		/*for (int x = 0; x <= width + 2; x++)
			std::cout << "=";
		std::cout << std::endl;

		for (int y = height ; y >= 0; y--)
		{
			std::cout << "|";
			for (int x = 0; x <= width; x++)
			{
				char out = ' ';

				auto it = bots.begin();

				for (it; it != bots.end(); it++) {
					if ((*it) == Position(x, y))
					{
						out = 'B';
					}
				}

				if (out == ' ')
				{
					it = food.begin();

					for (it; it != food.end(); it++) {
						if ((*it) == Position(x, y))
						{
							out = 'F';
						}
					}
				}

				std::cout << out;
			}
			std::cout << "|" << std::endl;
		}
		for (int x = 0; x <= width + 2; x++)
			std::cout << "=";*/


	}


	return 0;
}