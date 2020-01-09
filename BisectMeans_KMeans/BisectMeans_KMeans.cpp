//global
#include <iostream>
#include <cstdint>
#include <list>
#include <vector>
#include <thread>

//local
#include "pointsKeeper.h"
#include "klaster.h"

#define stop __asm nop

int main()
{
	//n - space
	const uint16_t n = 22;
	uint32_t pointsCounter = 20000;

	//container for all random-points
	pointsKeeper points = pointsKeeper(n, pointsCounter);

	//count of clasters 
	const uint32_t K = 15;
	pointsKeeper Kpoints = pointsKeeper(n, K);

	//i got a lot of points
	//and a lot of centers
	//so i wanna make my klasters	
	std::list<klaster> kList = Kpoints.getKlasters(points);

	uint16_t iterCounter = 0;
	bool isChanged = true;
	while (isChanged)
	{	
		int i = 0, j = 0;
		isChanged = false;
		for (auto & kl : kList) { //look at the all klasters
			std::vector<std::vector<uint32_t>> med(n);
			for (auto & v : med) {
				v.reserve(kl.k_points.size());
			
			for (auto & point : kl.k_points) { //at the all points
				for (auto & index : point.v) { //and at the all coordinates
					med[i].push_back(index);
					++i;
				}
				i = 0;
			}

			//medians coz I'm worried about type overflow when summing coordinates
			bool isZero = false;
			point newCenter = point();
			newCenter.n = n;
			for (auto & v : med) { // fill it by the new middle values
				std::sort(v.begin(), v.end());
				if (v.size() % 2 == 0) {
					if (v.size() == 0) {
						isZero = true;
					} else {
						newCenter.v.push_back((v[v.size() / 2] + v[v.size() / 2 - 1]) / 2);
					}
				} else {
					newCenter.v.push_back(v[v.size() / 2]);
				}
			}
			if (newCenter != kl.center && !isZero) {
				isChanged = true;
				Kpoints.points[j] = newCenter;
			}
			++j;
		}

		if (isChanged) {
			kList = Kpoints.getKlasters(points);
		}

		++iterCounter;
	}

	std::cout << iterCounter << std::endl;
	int asdasd = 9302;
}