#pragma once
#include <string>
#include <time.h>
#include "structures\heap_monitor.h"

//using namespace structures;
using namespace std;

class Zasielka
{
public:
	Zasielka(double, int, double);
	~Zasielka();

	double getHmotnost();
	int getRegDorucenia();
	double getVzdialDorucenia();

	bool getVydzvyhnutaOdDorucovatela();
	void setVydzvyhnutaOdDorucovatela(bool);

	time_t getCasVyzdvyhnutia();
	time_t getCasOdoslania();
	void setCasOdoslania(time_t);

private:
	double hmotnost;
	int regionDorucenia;
	double vzdialenostDorucenia;

	bool vyzdvyhnutaOdDorucovatela = false;

	time_t casVyzdvyhnutia;
	time_t casOdoslania;
};

