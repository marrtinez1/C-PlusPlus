#include "Prekladisko.h"


Prekladisko::Prekladisko(string pNazov, int pIndexPrekladiska)
{
	this->nazov = pNazov;
	this->indexPrekladiska = pIndexPrekladiska;
	drony = new LinkedList<Dron*>();
	zasielkyNaVyzdvyhnutie = new ExplicitQueue<Zasielka*>();
	zasielkyPreDrony = new ExplicitQueue<Zasielka*>();
	dovodyZamietnutia = new ArrayList<string>();
}


Prekladisko::~Prekladisko()
{
	for (Dron* dron : *drony)
	{
		delete dron;
		dron = nullptr;
	}
	delete drony;
	drony = nullptr;

	int zasNaVyz = zasielkyNaVyzdvyhnutie->size();
	for (size_t i = 0; i < zasNaVyz; i++)
	{
		delete zasielkyNaVyzdvyhnutie->pop();
	}
	delete zasielkyNaVyzdvyhnutie;
	zasielkyNaVyzdvyhnutie = nullptr;

	int zasPreDrony = zasielkyPreDrony->size();
	for (size_t i = 0; i < zasPreDrony; i++)
	{
		delete zasielkyPreDrony->pop();
	}
	delete zasielkyPreDrony;
	zasielkyPreDrony = nullptr;

	for (size_t i = 0; i < dovodyZamietnutia->size(); i++)
	{
		dovodyZamietnutia->removeAt(i);
	}
	delete dovodyZamietnutia;
	dovodyZamietnutia = nullptr;
}

bool Prekladisko::pridajDron(int pSerioveCislo, bool pTyp)
{	
	for each (Dron *dron in *drony)
	{
		if (dron->getSerioveCislo() == pSerioveCislo) {
			system("CLS");
			cout << "Dron s takym seriovym cislom existuje." << endl;
			return 0;
		}
	}
	Dron *dron = new Dron(pSerioveCislo, pTyp);

	drony->add(dron);
	system("CLS");
	cout << "Dron bol pridany.";
}


void Prekladisko::vypisDronovVjednomPrekladisku()
{
	system("CLS");
	if (drony->isEmpty())
	{
		cout << "V prekladisku nie su ziadne drony.\n";
	}
	else
	{
		for each (Dron* dron in *drony)
		{
			cout << "Seriove Cislo: " << dron->getSerioveCislo();
			cout << " || Datum Zaradenia Do Evidenice: " << dron->getDatumPridania();
			cout << " || Datum Zaradenia V Unixe: " << dron->getDatumPridaniaUnix();
			cout << " || Typ: " << dron->getTyp();
			cout << " || Je volny: " << dron->isVolny();
			cout << " || Stav Baterie: " << dron->getStavBaterie();
			cout << " || Cas Odchodu: " << dron->getCasOdchoduString();
			cout << " || Cas Prichodu: " << dron->getCasPrichoduString();
			cout << " || Celkovy Pocet Nalietanych Hodin: " << dron->getPocetNalietanychHod();			
			cout << " || Celkovy Pocet Prepravenych Zasielok: " << dron->getPocetPrepravenychZasielok() << endl;
		}
	}	
}

bool Prekladisko::existujeDron()
{
	if (drony->isEmpty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Prekladisko::existujeDronTypuDva()
{
	for each (Dron* dron in *drony)
	{
		if (dron->getTyp())
		{
			return true;
		}
	}
	return false;
}

double Prekladisko::sucetCasovDronov()
{
	double vzidalenost = 0;
	for each(Dron* dron in *drony)
	{
		vzidalenost += dron->getMaxDobaLetu();
	}
	return vzidalenost;
}


bool Prekladisko::najdiVhodnyDron(double pHmotnostZasielky, double pVzdialenostVyzdvyhnutia, time_t datum, int pRegionDorucenia, double pVzdialenostDorucenia)
{
	Dron *smernikNaDron = nullptr;
	Dron *najskorsiDron = nullptr;
	//Zasielka *zasielka = new Zasielka(pHmotnostZasielky, pRegionDorucenia, pVzdialenostDorucenia);
	time_t casNajskorsiehoDrona = 0;
	bool pom = false;
	bool pom2 = false;
	bool odpoved = false;

	for each (Dron *dron in *drony) {

		if (dron->isVolny() == 0 && datum > dron->getCasPrichodu()) {
			dron->setIsVolny(true);

			double dobitieBaterie = dron->getTyp() ? (datum - dron->getCasPrichodu()) * DRON_II_DOBITIE_BATERKY_ZA_SEKUNDU :
				(datum - dron->getCasPrichodu()) * DRON_I_DOBITIE_BATERKY_ZA_SEKUNDU;

			if (dron->getStavBaterie() + dobitieBaterie >= 100)
			{
				dron->setStavBaterie(100);
			}
			else
			{
				dron->setStavBaterie(dobitieBaterie);
			}
		}

		double potrebnaBateria = dron->getTyp() ? ((pVzdialenostVyzdvyhnutia * 2) / DRON_II_KM_ZA_SEKUNDU) * DRON_II_PERCENT_BATERKY_ZA_SEKUNDU :
			((pVzdialenostVyzdvyhnutia * 2) / DRON_I_KM_ZA_SEKUNDU) * DRON_I_PERCENT_BATERKY_ZA_SEKUNDU;


		if (dron->getNosnost() >= pHmotnostZasielky) 
		{
			if (!pom) 
			{
				if (dron->isVolny() && dron->getStavBaterie() >= (potrebnaBateria))
				{
					smernikNaDron = dron;
					pom = true;
				}
			}
			else 
			{
				if (dron->isVolny() && dron->getStavBaterie() >= (potrebnaBateria))
				{
					if (dron->getStavBaterie() > smernikNaDron->getStavBaterie()) {
						smernikNaDron = dron;
					}
					if (dron->getNosnost() < smernikNaDron->getNosnost()) {
						smernikNaDron = dron;
					}
				}
			}

			if (!pom2) {
				if (!dron->isVolny() && dron->getStavBaterie() < (potrebnaBateria))
				{
					najskorsiDron = dron;
					//                                              celkovy cas cesty         - kolko uz presiel = kolko este musi byt na ceste + cas na nabitie
					casNajskorsiehoDrona = (((dron->getCasPrichodu() - dron->getCasOdchodu()) - (datum - dron->getCasOdchodu())) + (dron->getTyp() ? ((potrebnaBateria - dron->getStavBaterie()) / DRON_II_DOBITIE_BATERKY_ZA_SEKUNDU) : ((potrebnaBateria - dron->getStavBaterie()) / DRON_I_DOBITIE_BATERKY_ZA_SEKUNDU)));
				}
				else if (!dron->isVolny()) 
				{
					najskorsiDron = dron;
					casNajskorsiehoDrona = ((dron->getCasPrichodu() - dron->getCasOdchodu()) - (datum - dron->getCasOdchodu()));
				}
				else if (dron->getStavBaterie() < (potrebnaBateria)) 
				{
					najskorsiDron = dron;
					casNajskorsiehoDrona = dron->getTyp() ? ((potrebnaBateria - dron->getStavBaterie()) / DRON_II_DOBITIE_BATERKY_ZA_SEKUNDU) : ((potrebnaBateria - dron->getStavBaterie()) / DRON_I_DOBITIE_BATERKY_ZA_SEKUNDU);
				}
				pom2 = true;
			}
			else 
			{
				if (!dron->isVolny() && dron->getStavBaterie() < (potrebnaBateria)) 
				{
					if ((((dron->getCasPrichodu() - dron->getCasOdchodu()) - (datum - dron->getCasOdchodu())) + (dron->getTyp() ? ((potrebnaBateria - dron->getStavBaterie()) / DRON_II_DOBITIE_BATERKY_ZA_SEKUNDU) : ((potrebnaBateria - dron->getStavBaterie()) / DRON_I_DOBITIE_BATERKY_ZA_SEKUNDU)) < (casNajskorsiehoDrona))) 
					{
						najskorsiDron = dron;
						casNajskorsiehoDrona = (((dron->getCasPrichodu() - dron->getCasOdchodu()) - (datum - dron->getCasOdchodu())) + (dron->getTyp() ? ((potrebnaBateria - dron->getStavBaterie()) / DRON_II_DOBITIE_BATERKY_ZA_SEKUNDU) : ((potrebnaBateria - dron->getStavBaterie()) / DRON_I_DOBITIE_BATERKY_ZA_SEKUNDU)));
					}
				}
				else if (!dron->isVolny()) 
				{
					if (((dron->getCasPrichodu() - dron->getCasOdchodu()) - (datum - dron->getCasOdchodu()) < casNajskorsiehoDrona))
					{
						najskorsiDron = dron;
						casNajskorsiehoDrona = ((dron->getCasPrichodu() - dron->getCasOdchodu()) - (datum - dron->getCasOdchodu()));
					}
				}
				else if (dron->getStavBaterie() < (potrebnaBateria)) 
				{
					if (dron->getTyp() ? ((potrebnaBateria - dron->getStavBaterie()) / DRON_II_DOBITIE_BATERKY_ZA_SEKUNDU) : ((potrebnaBateria - dron->getStavBaterie()) / DRON_I_DOBITIE_BATERKY_ZA_SEKUNDU) < casNajskorsiehoDrona) 
					{
						najskorsiDron = dron;
						casNajskorsiehoDrona = dron->getTyp() ? ((potrebnaBateria - dron->getStavBaterie()) / DRON_II_DOBITIE_BATERKY_ZA_SEKUNDU) : ((potrebnaBateria - dron->getStavBaterie()) / DRON_I_DOBITIE_BATERKY_ZA_SEKUNDU);
					}
				}
			}
		}
	}
	if (smernikNaDron) {

		smernikNaDron->setCasOdchodu(datum);

		smernikNaDron->setCasPrichodu(datum + (smernikNaDron->getTyp() ? ((pVzdialenostVyzdvyhnutia * 2) / DRON_II_KM_ZA_SEKUNDU) :
			((pVzdialenostVyzdvyhnutia * 2) / DRON_I_KM_ZA_SEKUNDU)));

		smernikNaDron->setStavBaterie(smernikNaDron->getStavBaterie() - (smernikNaDron->getTyp() ? ((pVzdialenostVyzdvyhnutia * 2) / DRON_II_KM_ZA_SEKUNDU) * DRON_II_PERCENT_BATERKY_ZA_SEKUNDU :
			((pVzdialenostVyzdvyhnutia * 2) / DRON_I_KM_ZA_SEKUNDU) * DRON_I_PERCENT_BATERKY_ZA_SEKUNDU));

		smernikNaDron->setIsVolny(0);

		smernikNaDron->setPocetPrepravenychZasielok(1);

		smernikNaDron->setPocetNalietanychHodin(((double)smernikNaDron->getCasPrichodu() - (double)smernikNaDron->getCasOdchodu()) / 60);

		double casPreZakaznia = (((double)smernikNaDron->getCasPrichodu() - (double)datum) / 60) / 2;

		if (pVzdialenostDorucenia >= 0)
		{
			zasielkyNaVyzdvyhnutie->push(new Zasielka(pHmotnostZasielky, pRegionDorucenia, pVzdialenostDorucenia));
			cout << "Dron so seriovym cislom " << smernikNaDron->getSerioveCislo() << " pride vyzdvyhnut zaiselku za " << casPreZakaznia << " minut.";
			this->prazdne = false;
		}
		else
		{
			zasielkyPreDrony->peek()->setCasOdoslania(datum);
			cout << "Dron so seriovym cislom " << smernikNaDron->getSerioveCislo() << " pride vyzdvyhnut zaiselku s hmotnostou " << zasielkyPreDrony->pop()->getHmotnost() << " kg za " << casPreZakaznia << " minut.";
		}	
	}
	else
	{
		time_t casObjednavky = (najskorsiDron->getTyp() ? ((pVzdialenostVyzdvyhnutia * 2) / DRON_II_KM_ZA_SEKUNDU) : ((pVzdialenostVyzdvyhnutia * 2) / DRON_I_KM_ZA_SEKUNDU));

		if ((casNajskorsiehoDrona + (casObjednavky / 2)) > UNIX_HODINA && pVzdialenostDorucenia >= 0) {

			cout << "Cas za ktory moze prist dron po zasielku je vacsi ako 1 hodina. Chcete zrusit objednavku?" << endl;
			cout << "Stlacte 0 pre nie." << endl;
			cout << "Stlacte 1 pre ano." << endl;
			cin >> odpoved;

			if (!odpoved)
			{
				najskorsiDron->setCasPrichodu(datum + casNajskorsiehoDrona + casObjednavky);

				najskorsiDron->setStavBaterie(najskorsiDron->getStavBaterie() - (najskorsiDron->getTyp() ? ((pVzdialenostVyzdvyhnutia * 2) / DRON_II_KM_ZA_SEKUNDU) * DRON_II_PERCENT_BATERKY_ZA_SEKUNDU :
					((pVzdialenostVyzdvyhnutia * 2) / DRON_I_KM_ZA_SEKUNDU) * DRON_I_PERCENT_BATERKY_ZA_SEKUNDU));

				najskorsiDron->setPocetPrepravenychZasielok(1);

				najskorsiDron->setPocetNalietanychHodin(((double)najskorsiDron->getCasPrichodu() - (double)najskorsiDron->getCasOdchodu()) / 60);

				if (najskorsiDron->getStavBaterie() < 0) 
				{
					najskorsiDron->setStavBaterie(0);
				}
				
				zasielkyNaVyzdvyhnutie->push(new Zasielka(pHmotnostZasielky, pRegionDorucenia, pVzdialenostDorucenia));

				double casPreZakaznia = (((double)najskorsiDron->getCasPrichodu() - (double)datum - (casObjednavky / 2)) / 60);
				cout << "Dron so seriovym cislom " << najskorsiDron->getSerioveCislo() << " pride vyzdyhnut zaiselku za " << casPreZakaznia << " minut.";
				this->prazdne = false;
			}
			else
			{
				cout << "Objednavka zrusena." << endl;
			}
		}
		else
		{
			najskorsiDron->setCasPrichodu(datum + casNajskorsiehoDrona + casObjednavky);

			najskorsiDron->setStavBaterie(najskorsiDron->getStavBaterie() - (najskorsiDron->getTyp() ? ((pVzdialenostVyzdvyhnutia * 2) / DRON_II_KM_ZA_SEKUNDU) * DRON_II_PERCENT_BATERKY_ZA_SEKUNDU :
				((pVzdialenostVyzdvyhnutia * 2) / DRON_I_KM_ZA_SEKUNDU) * DRON_I_PERCENT_BATERKY_ZA_SEKUNDU));

			najskorsiDron->setPocetPrepravenychZasielok(1);

			najskorsiDron->setPocetNalietanychHodin(((double)najskorsiDron->getCasPrichodu() - (double)najskorsiDron->getCasOdchodu()) / 60);

			if (najskorsiDron->getStavBaterie() < 0)
			{
				najskorsiDron->setStavBaterie(0);
			}

			double casPreZakaznia = (((double)najskorsiDron->getCasPrichodu() - (double)datum - (casObjednavky / 2)) / 60);
			if (pVzdialenostDorucenia >= 0)
			{
				zasielkyNaVyzdvyhnutie->push(new Zasielka(pHmotnostZasielky, pRegionDorucenia, pVzdialenostDorucenia));
				cout << "Dron so seriovym cislom " << najskorsiDron->getSerioveCislo() << " pride vyzdvyhnut zaiselku za " << casPreZakaznia << " minut.";
				this->prazdne = false;
			}
			else
			{
				zasielkyPreDrony->peek()->setCasOdoslania(datum);
				cout << "Dron so seriovym cislom " << najskorsiDron->getSerioveCislo() << " pride vyzdvyhnut zaiselku s hmotnostou " << zasielkyPreDrony->pop()->getHmotnost() << " kg za " << casPreZakaznia << " minut.";
			}					
		}
	}
	return odpoved;
}

//------------ Navrat vozidiel do centralneho skladu ---------------
//------------------------------------------------------------------

double Prekladisko::nalozenieZasielokDoAuta(ExplicitQueue<Zasielka*> *kufor, double pNosnost, double pHmotnostzasielokVKufri)
{ 
	int pom = zasielkyNaVyzdvyhnutie->size();

	for (size_t i = 0; i < pom; i++)
	{
		if ((pHmotnostzasielokVKufri + zasielkyNaVyzdvyhnutie->peek()->getHmotnost()) > pNosnost)
		{
			continue;
		}
		else
		{
			pHmotnostzasielokVKufri += zasielkyNaVyzdvyhnutie->peek()->getHmotnost();
			kufor->push(zasielkyNaVyzdvyhnutie->pop());		
		}
	}

	if (zasielkyNaVyzdvyhnutie->size() == 0)
	{
		this->setPrazdne(true);
	}

	return pHmotnostzasielokVKufri;
}

bool Prekladisko::getPrazdne()
{
	return this->prazdne;
}

void Prekladisko::setPrazdne(bool pPrazdne)
{
	this->prazdne = pPrazdne;
}

void Prekladisko::vylozenieZasielokZAuta(ExplicitQueue<Zasielka*>* kufor)
{
	int pocetZasilokVKufri = kufor->size();

	for (size_t i = 0; i < pocetZasilokVKufri; i++)
	{
		if ((this->indexPrekladiska + 1) == kufor->peek()->getRegDorucenia())
		{
			zasielkyPreDrony->push(kufor->pop());
		}
		else
		{
			kufor->push(kufor->pop());
		}		
	}						
}

Zasielka * Prekladisko::getZasielkaPreDron()
{
	return zasielkyPreDrony->peek();
}

//pomocna
void Prekladisko::pridajZasielku(double pHmot, int pRegDor, double pVzdialDor)
{
	zasielkyNaVyzdvyhnutie->push(new Zasielka(pHmot, pRegDor, pVzdialDor));
	setPrazdne(false);
}

//pomocna
void Prekladisko::vypisZasielky()
{
	int pom = zasielkyNaVyzdvyhnutie->size();
	for (size_t i = 0; i < pom; i++)
	{
		cout << "Hmotnost:" << zasielkyNaVyzdvyhnutie->peek()->getHmotnost() << endl;
		cout << "Reg dorucenia:" << zasielkyNaVyzdvyhnutie->peek()->getRegDorucenia() << endl;
		cout << "Vzdialenost dorucenia:" << zasielkyNaVyzdvyhnutie->peek()->getVzdialDorucenia() << endl;
		cout << "-----------------------------------" << endl;
		zasielkyNaVyzdvyhnutie->push(zasielkyNaVyzdvyhnutie->pop());
	}
}

void Prekladisko::vypisZasielkyPreDrony()
{
	int pom = zasielkyPreDrony->size();
	for (size_t i = 0; i < pom; i++)
	{
		cout << "Hmotnost:" << zasielkyPreDrony->peek()->getHmotnost() << endl;
		cout << "Reg dorucenia:" << zasielkyPreDrony->peek()->getRegDorucenia() << endl;
		cout << "Vzdialenost dorucenia:" << zasielkyPreDrony->peek()->getVzdialDorucenia() << endl;
		cout << "-----------------------------------" << endl;
		zasielkyPreDrony->push(zasielkyPreDrony->pop());
	}
}

void Prekladisko::vyhladanieDorucenychZasielokPodlaCasu(int pCasOd, int pCasDo)
{
	int pocetZasielok = zasielkyNaVyzdvyhnutie->size();

	for (size_t i = 0; i < pocetZasielok; i++)
	{
		if (zasielkyNaVyzdvyhnutie->peek()->getCasVyzdvyhnutia() >= pCasOd & zasielkyNaVyzdvyhnutie->peek()->getCasVyzdvyhnutia() <= pCasDo)
		{
			this->doruceneZasielky++;
		}
		zasielkyNaVyzdvyhnutie->push(zasielkyNaVyzdvyhnutie->pop());
	}
}

void Prekladisko::vyhladanieOdoslanychZasielokPodlaCasu(int pCasOd, int pCasDo)
{
	int pocetZasielok = zasielkyPreDrony->size();

	for (size_t i = 0; i < pocetZasielok; i++)
	{
		if (zasielkyPreDrony->peek()->getCasOdoslania() >= pCasOd & zasielkyPreDrony->peek()->getCasOdoslania() <= pCasDo)
		{
			this->odoslaneZasielky++;
		}
		zasielkyPreDrony->push(zasielkyPreDrony->pop());
	}
}

int Prekladisko::getDoruceneZasielky()
{
	return this->doruceneZasielky;
}

int Prekladisko::getOdoslaneZasielky()
{
	return this->odoslaneZasielky;
}

int Prekladisko::getIndexPrekladiska()
{
	return this->indexPrekladiska;
}

double Prekladisko::getPocetHodinDronovTypuI()
{
	double pocetHodin = 0;

	for each (Dron* dron in *drony)
	{
		if (dron->getTyp() == 0)
		{
			pocetHodin += dron->getPocetNalietanychHod();
		}
	}
	return pocetHodin;
}

double Prekladisko::getPocetHodinDronovTypuII()
{
	double pocetHodin = 0;

	for each (Dron* dron in *drony)
	{
		if (dron->getTyp())
		{
			pocetHodin += dron->getPocetNalietanychHod();
		}
	}
	return pocetHodin;
}

void Prekladisko::pridajDovod(string pDovod)
{
	dovodyZamietnutia->add(pDovod);
}

void Prekladisko::vypisDovody()
{
	for (size_t i = 0; i < dovodyZamietnutia->size(); i++)
	{
		cout << dovodyZamietnutia->operator[](i) << endl;
	}
}

LinkedList<Dron*> *Prekladisko::getDrony()
{
	return drony;
}

string Prekladisko::getNazovPrekladiska()
{
	return this->nazov;
}

