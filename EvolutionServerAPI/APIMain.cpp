#include <iostream>
#include <thread>

#include "pch.h"


using namespace std::literals::chrono_literals;


int main()
{
	Simulation ss;
	ss.Innit(4, 4, 43, 6, 1, 100, 40, 40);

	ss.Start();

	std::this_thread::sleep_for(5s);

	std::cout << ss.read() << "\n";

	std::this_thread::sleep_for(2s);

	ss.End();

	std::cout << ss.read() << std::endl;

	std::this_thread::sleep_for(2s);

	std::cout << ss.read();

	return 0;
}