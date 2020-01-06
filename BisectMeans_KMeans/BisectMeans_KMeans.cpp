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
	//n-мерное пространство
	uint16_t n = 2; 

	//std::cout << "input n" << std::endl;
	//std::cin >> n;

	//pointsCounter-число точек
	uint32_t pointsCounter = 10;
	
	//std::cout << "input pointsCounter" << std::endl;
	//std::cin >> pointsCounter;

	//создадим контейнер для всех наших точек, генерируя их рандомно
	pointsKeeper points = pointsKeeper(n, pointsCounter);

	//пока без BisectMeans зададим количество кластеров руками
	uint32_t K = 3;

	/*std::cout << "input Klasters count K <= pointsCounter" << std::endl;
	std::cin >> K;*/
	if (K > pointsCounter) K = pointsCounter;

	//теперь у меня есть множество точек в n-мерном пространстве
	//а также множество точек, которые я называю центрами кластеров
	pointsKeeper Kpoints = pointsKeeper(n, K);

	std::list<klaster> kList = Kpoints.getKlasters(points);

	stop
}