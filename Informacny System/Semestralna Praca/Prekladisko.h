#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "structures\heap_monitor.h"
#include "structures\queue\explicit_queue.h"
#include "structures\list\linked_list.h"
#include "structures\list\array_list.h"
#include "SymbolickeKonstanty.h"
#include "Dron.h"
#include "Zasielka.h"

using namespace structures;
using namespace std;

class Prekladisko
{
public:
	Prekladisko(string, int);
	~Prekladisko();

	bool pridajDron(int, bool);
	void vypisDronovVjednomPrekladisku();
	bool existujeDron();
	bool existujeDronTypuDva();
	double sucetCasovDronov();

	bool najdiVhodnyDron(double, double, time_t, int, double);

	double nalozenieZasielokDoAuta(ExplicitQueue<Zasielka*> *kufor, double, double);

	bool getPrazdne();
	void setPrazdne(bool);

	void vylozenieZasielokZAuta(ExplicitQueue<Zasielka*> *kufor);

	Zasielka *getZasielkaPreDron();

	void pridajZasielku(double, int, double);
	void vypisZasielky();
	void vypisZasielkyPreDrony();

	void vyhladanieDorucenychZasielokPodlaCasu(int, int);
	void vyhladanieOdoslanychZasielokPodlaCasu(int, int);
	int getDoruceneZasielky();
	int getOdoslaneZasielky();
	int getIndexPrekladiska();

	double getPocetHodinDronovTypuI();
	double getPocetHodinDronovTypuII();

	void pridajDovod(string);
	void vypisDovody();

	LinkedList<Dron*> *getDrony();

	string getNazovPrekladiska();

private:
	LinkedList<Dron*> *drony;
	ExplicitQueue<Zasielka*> *zasielkyNaVyzdvyhnutie;
	ExplicitQueue<Zasielka*> *zasielkyPreDrony;

	string nazov;

	bool prazdne = true;
	int indexPrekladiska;

	int doruceneZasielky = 0;
	int odoslaneZasielky = 0;

	ArrayList<string> *dovodyZamietnutia;
};

