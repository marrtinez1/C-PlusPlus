#pragma once
#include <string>
#include "structures\heap_monitor.h"

//using namespace structures;
using namespace std;

class Objednavka
{
public:
	Objednavka(double, int, double, int, double);
	~Objednavka();

	double getHmotnost();
	int getRegVyzdvyhnutia();
	double getVzdialVyzdvyhnutia();
	int getRegDorucenia();
	double getVzdialDorucenia();

	bool getBolaVyzdvyhnuta();
	void setBolaVyzdvyhnuta(bool);
	bool getZrusena();
	void setZrusena(bool);
	time_t getCasZrusenia();
	void setCasZrusenia(time_t);

private:
	double hmotnost;
	int regionVyzdvyhnutia;
	double vzdialenostVyzdvyhnutia;
	int regionDorucenia;
	double vzdialenostDorucenia;

	bool bolaVyzdvyhnuta = 0;
	bool zrusena = 0;
	time_t casZrusenia;
};

