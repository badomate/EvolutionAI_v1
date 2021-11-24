#include <iostream>
#include "Simulation.h"

//https://www.cse.unr.edu/~sushil/class/gas/papers/NEAT.pdf

int main()
{
    
   while (true)
    {
        srand(time(0));
        Simulation sim;
        sim.Start(2000, 300, 300, 12, 4, 1000, 128, 128);
    }

    return 0;
}



