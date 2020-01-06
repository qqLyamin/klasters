//global
#include <iostream>
#include <cstdint>
#include <list>
#include <vector>

//local
#include "pointsKeeper.h"
#include "klaster.h"

#define stop __asm nop

int main()
{
	//n - space
	uint16_t n = 2; 

	std::cout << "input n" << std::endl;
	std::cin >> n;

	//pointsCounter
	uint32_t pointsCounter = 10;
	
	std::cout << "input pointsCounter" << std::endl;
	std::cin >> pointsCounter;

	//container for all random-points
	pointsKeeper points = pointsKeeper(n, pointsCounter);

	//count of clasters by hands
	uint32_t K = 3;

	std::cout << "input Klasters count K <= pointsCounter" << std::endl;
	std::cin >> K;
	if (K > pointsCounter) K = pointsCounter;

	//i got a lot of points
	//and a lot of centers
	//so i wanna make my klasters
	pointsKeeper Kpoints = pointsKeeper(n, K);

	std::list<klaster> kList = Kpoints.getKlasters(points);

	stop
}