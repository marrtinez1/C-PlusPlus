#include "Objednavka.h"

Objednavka::Objednavka(double pHmotnost, int pRegionVyzdvyhnutia, double pVzdialVyzdvyhnutia, int pRegionDorucenia, double pVzdialDorucenia)
{
	this->hmotnost = pHmotnost;
	this->regionVyzdvyhnutia = pRegionVyzdvyhnutia;
	this->vzdialenostVyzdvyhnutia = pVzdialVyzdvyhnutia;
	this->regionDorucenia = pRegionDorucenia;
	this->vzdialenostDorucenia = pVzdialDorucenia;
}

Objednavka::~Objednavka()
{
}

double Objednavka::getHmotnost()
{
	return this->hmotnost;
}

int Objednavka::getRegVyzdvyhnutia()
{
	return this->regionVyzdvyhnutia;
}

double Objednavka::getVzdialVyzdvyhnutia()
{
	return this->vzdialenostVyzdvyhnutia;
}

int Objednavka::getRegDorucenia()
{
	return this->regionDorucenia;
}

double Objednavka::getVzdialDorucenia()
{
	return this->vzdialenostDorucenia;
}

bool Objednavka::getBolaVyzdvyhnuta()
{
	return this->bolaVyzdvyhnuta;
}

void Objednavka::setBolaVyzdvyhnuta(bool pVyzdvyhnuta)
{
	this->bolaVyzdvyhnuta = pVyzdvyhnuta;
}

bool Objednavka::getZrusena()
{
	return this->zrusena;
}

void Objednavka::setZrusena(bool pZrusena)
{
	this->zrusena = pZrusena;
}

time_t Objednavka::getCasZrusenia()
{
	return this->casZrusenia;
}

void Objednavka::setCasZrusenia(time_t pCasZrusenia)
{
	this->casZrusenia = pCasZrusenia;
}
