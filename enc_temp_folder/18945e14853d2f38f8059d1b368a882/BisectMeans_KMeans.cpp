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
	const uint16_t n = 2; 

	//pointsCounter
	uint32_t pointsCounter = 100;
	
	//std::cout << "input pointsCounter" << std::endl;
	//std::cin >> pointsCounter;

	//container for all random-points
	pointsKeeper points = pointsKeeper(n, pointsCounter);

	//count of clasters 
	const uint32_t K = 3;

	//i got a lot of points
	//and a lot of centers
	//so i wanna make my klasters
	pointsKeeper Kpoints = pointsKeeper(n, K);
	std::list<klaster> kList = Kpoints.getKlasters(points);

	link:
	//change center
	int i = 0;
	std::vector<point> centers;
	for (auto & kl : kList) { //look at the all klasters
		std::vector<std::vector<uint32_t>> med(K);
		for (auto & v : med) {
			v.resize(n);
		}

		for (auto & point : kl.k_points) { //there at the all points
			for (auto & index : point.v) { //and there at the all coordinates
				med[i].push_back(index);
				++i;
			}
			i = 0;
		}

		point newCenter = point();
		//kl.center.v.clear(); // clear current center coordinates
		for (auto & v : med) { // and fill it by the new middle values
			std::sort(v.begin(), v.end());
			if (v.size() % 2 == 0) {
				newCenter.v.push_back((v[v.size() / 2] + v[v.size() / 2 - 1]) / 2);
				//kl.center.v.push_back((v[v.size() / 2] + v[v.size() / 2 - 1]) / 2);
			} else {
				newCenter.v.push_back(v[v.size() / 2]);
			}
		}
		if (newCenter != kl.center) {
			centers.push_back(newCenter);
		} else {
			centers.push_back(kl.center);
		}
	}

	while (true) {

		bool isChanged = false;

		int i = 0;
		for (auto & x : Kpoints.points) {
			if (x != centers[i]) {
				isChanged = true;
				break;
			}
			++i;
		}

		if (isChanged) {
			Kpoints.points = centers;
			kList = Kpoints.getKlasters(points);
			goto link;
		} else {
			break;
		}
	}


	stop
}