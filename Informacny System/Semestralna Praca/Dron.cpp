#include "Dron.h"

Dron::Dron(int pSerioveCislo, bool pTyp)
{
	this->serioveCislo = pSerioveCislo;
	this->datumPridaniaUnix = time(NULL);
	this->typ = pTyp;

	if (!pTyp)
	{
		this->nosnost = 2;
		this->priemernaRychlost = 80;
		this->maxDobaLetu = 40;
		this->dobaNabijania = 3;
	}
	else
	{
		this->nosnost = 5;
		this->priemernaRychlost = 40;
		this->maxDobaLetu = 60;
		this->dobaNabijania = 5;
	}
}

Dron::~Dron()
{
}

int Dron::getSerioveCislo()
{
	return this->serioveCislo;
}

bool Dron::getTyp()
{
	return this->typ;
}

int Dron::getNosnost()
{
	return this->nosnost;
}

int Dron::getPriemrnaRychlost()
{
	return this->priemernaRychlost;
}

int Dron::getMaxDobaLetu()
{
	return this->maxDobaLetu;
}

int Dron::getDobaNabijania()
{
	return this->dobaNabijania;
}

string Dron::getDatumPridania()
{
	char cas[20];
	strftime(cas, sizeof(cas), "%H:%M-%d-%B-%Y", localtime(&datumPridaniaUnix));
	return cas;
}

time_t Dron::getDatumPridaniaUnix()
{
	return this->datumPridaniaUnix;
}

double Dron::getPocetNalietanychHod()
{
	return (this->pocetNalietanychHod) / 60;
}

void Dron::setPocetNalietanychHodin(double pPocetHodin)
{
	this->pocetNalietanychHod += pPocetHodin;
}

int Dron::getPocetPrepravenychZasielok()
{
	return this->pocetPrepravenychZasielok;
}

void Dron::setPocetPrepravenychZasielok(int pPocetZasielok)
{
	this->pocetPrepravenychZasielok += pPocetZasielok;
}

bool Dron::isVolny()
{
	return this->volny;
}

void Dron::setIsVolny(bool pVolny)
{
	this->volny = pVolny;
}

double Dron::getStavBaterie()
{
	return this->stavBaterie;
}

void Dron::setStavBaterie(double pStavBaterie)
{
	this->stavBaterie = pStavBaterie;
}

time_t Dron::getCasCesty()
{
	return this->casCesty;
}

void Dron::setCasCesty(time_t pCas)
{
	this->casCesty = pCas;
}

time_t Dron::getCasPrichodu()
{
	return this->casPrichodu;
}

string Dron::getCasPrichoduString()
{
	char cas[20];
	strftime(cas, sizeof(cas), "%H:%M-%d-%B-%Y", localtime(&casPrichodu));
	return cas;
}

void Dron::setCasPrichodu(time_t pCasPrichodu)
{
	this->casPrichodu = pCasPrichodu;
}

time_t Dron::getCasOdchodu()
{
	return this->casOdchodu;
}

string Dron::getCasOdchoduString()
{
	char cas[20];
	strftime(cas, sizeof(cas), "%H:%M-%d-%B-%Y", localtime(&casOdchodu));
	return cas;
}

void Dron::setCasOdchodu(time_t pCasOdchodu)
{
	this->casOdchodu = pCasOdchodu;
}