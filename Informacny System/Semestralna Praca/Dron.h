#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "structures\heap_monitor.h"

using namespace std;

class Dron
{
public:
	Dron(int, bool);
	~Dron();

	int getSerioveCislo();
	bool getTyp();
	int getNosnost();
	int getPriemrnaRychlost();
	int getMaxDobaLetu();
	int getDobaNabijania();
	string getDatumPridania();
	time_t getDatumPridaniaUnix();
	double getPocetNalietanychHod();
	void setPocetNalietanychHodin(double);
	int getPocetPrepravenychZasielok();
	void setPocetPrepravenychZasielok(int);

	bool isVolny();
	void setIsVolny(bool);
	double getStavBaterie();
	void setStavBaterie(double);

	time_t getCasCesty();
	void setCasCesty(time_t);
	time_t getCasPrichodu();
	string getCasPrichoduString();
	void setCasPrichodu(time_t);
	time_t getCasOdchodu();
	string getCasOdchoduString();
	void setCasOdchodu(time_t);


private:
	int serioveCislo;
	bool typ;
	int nosnost;
	int priemernaRychlost;
	int maxDobaLetu;
	int dobaNabijania;
	time_t datumPridaniaUnix;
	double pocetNalietanychHod = 0.0;
	int pocetPrepravenychZasielok = 0;

	bool volny = 1;
	double stavBaterie = 100;
	time_t casCesty;
	time_t casPrichodu = 0;
	time_t casOdchodu = 0;

};

