#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <sstream>
#include "structures\array\array.h"
#include "structures\list\linked_list.h"
#include "structures\list\array_list.h"
#include "structures\queue\explicit_queue.h"
#include "structures\heap_monitor.h"
#include "SymbolickeKonstanty.h"
#include "Vozidlo.h"
#include "Prekladisko.h"
#include "Objednavka.h"
#include "Zasielka.h"

using namespace structures;

class Spolocnost
{
public:
	Spolocnost();
	~Spolocnost();

	time_t getAktualnyUnixCas();
	string getAktualnyCas();
	void posunCasOHodinu();

	void pridajVozidlo();
	void vypisVozidiel();

	void vypisPrekladisk();
	void pridanieDronuDoPrekladiska();
	void vypisDronovVPrekladisku();

	void vytvorenieObjednavky();
	bool kontrolaPrekoceniaNosnosti(double, int, int);
	bool kontrolaDoOsemnastej(int, double);
	void vypisObjednavky();

	void vyzdvyhnutieZasielkyUOdosielatela();
	Objednavka* najdenieNevyzdvyhnutejObj();

	void navratVozidielDoCentralnehoSkladu();

	void naplnenieVozidielZasielkami();

	void transportZasielokDoPrekladisk();

	void odovzdanieZasielkyAdresatovi();

	void vypisy();
	string regionSNjaviacDorucenymiZasielkami();
	string regionSNjaviacOdoslanymiZasielkami();
	void regionySNajviacZrusenymiZasielkami();
	void vypisCelkovehoPoctuDorucenychZasielok();
	void vypisNajazdenychKilometrov();
	void vypisNalietanychHodin();

	//pomocna
	void pridajZasielku();
	//pomocna
	void vypisZasielky();
	//pomocna
	void vypisZasielkyPreDrony();
	//pomocna
	void vypisPrekladiskaVozidla();
	//pomocna
	void vypisKuforVozidla();
	//pomocna
	void vypisZasielkyVSklade();


	void nacitajZoSuboru();
	void zapisDoSuboru();

	unsigned long premenCasStringNaUTS(string);
	
private:
	ArrayList<Vozidlo*> *vozidla;
	Array<Prekladisko*> *prekladiska;
	LinkedList<Objednavka*> *objednavky;	
	ExplicitQueue<Zasielka*> *zasielkyNaRozvoz;
	
	time_t pocetPosunutychHodin = 0;
	
};

