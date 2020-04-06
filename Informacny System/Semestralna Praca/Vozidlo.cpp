#include "Vozidlo.h"

/*Vozidlo::Vozidlo(string pSPZ, double pNosnost, int pPrevadzkoveNaklady)
{
	this->spz = pSPZ;
	this->nosnost = (pNosnost) * 1000;
	this->prevadzkoveNaklady = pPrevadzkoveNaklady;
	this->datumZaradeniaDoEvidencie = time(0);

	kufor = new ExplicitQueue<Zasielka*>();
}*/

Vozidlo::Vozidlo(string pSPZ, double pNosnost, int pPrevadzkoveNaklady, Array<int> a)
{
	this->spz = pSPZ;
	this->nosnost = (pNosnost) * 1000;
	this->prevadzkoveNaklady = pPrevadzkoveNaklady;
	this->datumZaradeniaDoEvidencie = time(0);

	prekladiskaKtoreNavstivi = new Array<int>(a);
	kufor = new ExplicitQueue<Zasielka*>();
}

Vozidlo::~Vozidlo()
{
	delete prekladiskaKtoreNavstivi;
	prekladiskaKtoreNavstivi = nullptr;

	int kuf = kufor->size();
	for (size_t i = 0; i < kuf; i++)
	{
		delete kufor->pop();
	}
	delete kufor;
	kufor = nullptr;	
}

string Vozidlo::getSpz()
{
	return this->spz;
}

double Vozidlo::getNosnost()
{
	return this->nosnost;
}

int Vozidlo::getPrevadzkoveNaklady()
{
	return this->prevadzkoveNaklady;
}

int Vozidlo::getCelkovePrevadzkoveNaklady()
{
	return this->celkovePrevadzkoveNaklady;
}

void Vozidlo::setCelkovePrevadzkoveNaklady(int pNaklady)
{
	this->celkovePrevadzkoveNaklady += pNaklady;
}

string Vozidlo::getDatumZaradeniaDoEvidencie()
{
	char cas[20];
	strftime(cas, sizeof(cas), "%H:%M-%d-%B-%Y", localtime(&datumZaradeniaDoEvidencie));
	return cas;
}

int Vozidlo::getPocetPrekladiskKtoreNavstivi()
{
	return prekladiskaKtoreNavstivi->size();
}

void Vozidlo::vypisPrekladiskaVKtorychJazdi()
{
	for (size_t i = 0; i < prekladiskaKtoreNavstivi->size(); i++)
	{
		cout << prekladiskaKtoreNavstivi->operator[](i) << endl;
	}
}

int Vozidlo::getPrekladisko(int pPrekladisko)
{
	return (prekladiskaKtoreNavstivi->operator[](pPrekladisko) - 1);
}

ExplicitQueue<Zasielka*> *Vozidlo::getKufor()
{
	return kufor;
}

void Vozidlo::vypisKufor()
{
	int pom = kufor->size();

	for (size_t i = 0; i < pom; i++)
	{
		cout << "Hmotnost:" << kufor->peek()->getHmotnost() << endl;
		cout << "Reg dorucenia:" << kufor->peek()->getRegDorucenia() << endl;
		cout << "Vzdialenost dorucenia:" << kufor->peek()->getVzdialDorucenia() << endl;
		cout << "-----------------------------------" << endl;
		kufor->push(kufor->pop());
	}
}

bool Vozidlo::operator==(string SPZ)
{
	if (this->getSpz().compare(SPZ) == 0) {
		return true;
	}
	return false;
}

