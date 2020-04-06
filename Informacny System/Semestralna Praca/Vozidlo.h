#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include "structures\heap_monitor.h"
#include "structures\queue\explicit_queue.h"
#include "structures\list\array_list.h"
#include "structures\array\array.h"
#include "Zasielka.h"

using namespace structures;
using namespace std;

class Vozidlo {

public:
	Vozidlo(string pSPZ, double pNosnost, int pPrevadzkoveNaklady);
	Vozidlo(string pSPZ, double pNosnost, int pPrevadzkoveNaklady, Array<int>);

	~Vozidlo();

	string getSpz();
	double getNosnost();
	int getPrevadzkoveNaklady();
	int getCelkovePrevadzkoveNaklady();
	void setCelkovePrevadzkoveNaklady(int);
	string getDatumZaradeniaDoEvidencie();

	int getPocetPrekladiskKtoreNavstivi();
	int getPrekladisko(int);

	ExplicitQueue<Zasielka*> *getKufor();
	void vypisKufor();

	//pomocna
	void vypisPrekladiskaVKtorychJazdi();	

	bool operator==(string);

private:
	string spz;
	double nosnost;
	int prevadzkoveNaklady;
	int celkovePrevadzkoveNaklady = 0;
	time_t datumZaradeniaDoEvidencie;

	double hmotnostZasielokVKufri = 0;

	Array<int> *prekladiskaKtoreNavstivi;
	ExplicitQueue<Zasielka*> *kufor;
};