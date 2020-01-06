#pragma once
//local
#include "point.h"
#include "klaster.h"

double getDistance(const point & X, const point & Y) {
	int distance = 0;
	for (uint16_t tmp = 0; tmp < X.n; ++tmp) {
		distance += pow(abs(static_cast<int>((X.v[tmp] - Y.v[tmp]))), 2);
	}
	return static_cast<double>(sqrt(distance));
};

class pointsKeeper {

	std::vector<point> points;

public:
	pointsKeeper(uint16_t n, uint32_t pointsCounter) {
		for (uint16_t index = 0; index < pointsCounter; ++index) {
			point tmp = point(n);
			points.push_back(tmp);
		}
	};

	std::list<klaster> getKlasters(const pointsKeeper & p) {

		std::list<klaster> retList;

		for (auto p : points) {
			retList.push_back(klaster(p));
		}

		double minDistance = 0;
		int minIndex = 0;
		for (uint32_t i = 0; i < p.points.size(); ++i) { // для всех пришедших точек
			for (uint32_t j = 0; j < points.size(); ++j) { // определяю к какому из данных центров текущая точка ближе

				if (minDistance == 0 && j == 0) {
					minDistance = getDistance(p.points[i], points[j]); 
					minIndex = j;
					continue;
				}

				if (minDistance > getDistance(p.points[i], points[j])) {
					minDistance = getDistance(p.points[i], points[j]);
					minIndex = j;
				}
			}
	
			//ПРОБЛЕМКА С ИНИЦИАЛИЗАЦИЕЙ РЕТ ЛИСТА
			for (auto & kl : retList) { // в листе который пойдет в ретурн я в кластер с соответствующим центром докидываю теперь принадлежащую ему точку
				if (kl.center == points[minIndex]) {
					kl.k_points.push_back(p.points[i]);
				}
			}

			minIndex = 0;
			minDistance = 0;
		}

		return retList;
	};
};
