#include "Zasielka.h"

Zasielka::Zasielka(double pHmotnost, int pRegionDorucenia, double pVzdialDorucenia)
{
	this->hmotnost = pHmotnost;
	this->regionDorucenia = pRegionDorucenia;
	this->vzdialenostDorucenia = pVzdialDorucenia;
	this->casVyzdvyhnutia = time(0);
}

Zasielka::~Zasielka()
{
}

double Zasielka::getHmotnost()
{
	return this->hmotnost;
}

int Zasielka::getRegDorucenia()
{
	return this->regionDorucenia;
}

double Zasielka::getVzdialDorucenia()
{
	return this->vzdialenostDorucenia;
}

bool Zasielka::getVydzvyhnutaOdDorucovatela()
{
	return this->vyzdvyhnutaOdDorucovatela;
}

void Zasielka::setVydzvyhnutaOdDorucovatela(bool pVyzdvyhnuta)
{
	this->vyzdvyhnutaOdDorucovatela = pVyzdvyhnuta;
}

time_t Zasielka::getCasVyzdvyhnutia()
{
	return this->casVyzdvyhnutia;
}

time_t Zasielka::getCasOdoslania()
{
	return this->casOdoslania;
}

void Zasielka::setCasOdoslania(time_t pCas)
{
	this->casOdoslania = pCas;
}

