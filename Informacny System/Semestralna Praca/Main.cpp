#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "structures\heap_monitor.h"
#include "Spolocnost.h"

using namespace std;
using namespace structures;

int main() {

	initHeapMonitor();
	int volba;
	bool koniec = false;

	Spolocnost *Sp = new Spolocnost;

	/*struct tm tm;
	time_t ts = 0;
	memset(&tm, 0, sizeof(tm));

	char *strptime(const char * __restrict, const char * __restrict, struct tm * __restrict);
	strptime("1998-04-11", "%Y-%m-%d", &tm);
	ts = mktime(&tm);

	printf("%d \n", (int)ts); //unix time-stamp
	printf("%s \n", ctime(&ts)); //human readable date*/


	while (!koniec)
	{
		system("CLS");
		cout << "\n";
		cout << "||=====================================================||" << endl;
		cout << "||------------ Spolocnost Age of Express --------------||" << endl;
		cout << "||-----------------------------------------------------||" << endl;
		cout << "||---------------------- MENU -------------------------||" << endl;
		cout << "||              Co si prajete vykonat?                 ||" << endl;
		cout << "||                                                     ||" << endl;
		cout << "||1: Pridanie noveho vozidla.                          ||" << endl;
		cout << "||2: Vypis vozidiel podla datumu zaradenia.            ||" << endl;
		cout << "||3: Pridanie noveho dronu.                            ||" << endl;
		cout << "||4: Vypis dronov v zadanom prekladisku.               ||" << endl;
		cout << "||5: Vytvorenie novej objednakvy.                      ||" << endl;
		cout << "||6: Vyzdvyhnutie zasielky u odosielatela.             ||" << endl;
		cout << "||7: Navrat vozidiel do centralneho skladu.            ||" << endl;
		cout << "||8: Naplnenie vozidel zasielkami.                     ||" << endl;
		cout << "||9: Transport zasielok do prekladisk.                 ||" << endl;
		cout << "||10: Odovzdanie zasielky adresatovi.                  ||" << endl;
		cout << "||11: Vypisy.                                          ||" << endl;
		cout << "||                                                     ||" << endl;
		cout << "||15: Vypis UNIX cas.                                  ||" << endl;
		cout << "||16: Vypis aktualny datum.                            ||" << endl;
		cout << "||17: Posun casu o hodinu.                             ||" << endl;
		cout << "||                                                     ||" << endl;
		cout << "||20: Vypis vsetky prekladiska.                        ||" << endl;
		cout << "||21: Vypis vsetky objednavky.                         ||" << endl;
		cout << "||22: Pridaj zasielku.                                 ||" << endl;
		cout << "||23: Vypis zasielky z prekladiska.                    ||" << endl;
		cout << "||24: Vypis kufor.                                     ||" << endl;
		cout << "||25: Vypis prekladiska vozidla.                       ||" << endl;
		cout << "||26: Vypis zasielky v centralnom sklade.              ||" << endl;
		cout << "||27: Vypis zasielky v pre drony.                      ||" << endl;
		cout << "||                                                     ||" << endl;
		cout << "||40: Naciataj zo suboru.                              ||" << endl;
		cout << "||41: Zapis do suboru.                                 ||" << endl;
		cout << "||0: Koniec.                                           ||" << endl;
		cout << "||=====================================================||" << endl;
				
		cin >> volba;
		switch (volba)
		{
		case 1:
			Sp->pridajVozidlo();
			cin.get(); cin.get();
			break;

		case 2:
			Sp->vypisVozidiel();
			cin.get(); cin.get();
			break;

		case 3:
			Sp->pridanieDronuDoPrekladiska();
			cin.get(); cin.get();
			break;

		case 4:
			Sp->vypisDronovVPrekladisku();
			cin.get(); cin.get();
			break;

		case 5:
			Sp->vytvorenieObjednavky();
			cin.get(); cin.get();
			break;

		case 6:
			Sp->vyzdvyhnutieZasielkyUOdosielatela();
			cin.get(); cin.get();
			break;

		case 7:
			Sp->navratVozidielDoCentralnehoSkladu();
			cin.get(); cin.get();
			break;

		case 8:
			Sp->naplnenieVozidielZasielkami();
			cin.get(); cin.get();
			break;

		case 9:
			Sp->transportZasielokDoPrekladisk();
			cin.get(); cin.get();
			break;
		case 10:

			Sp->odovzdanieZasielkyAdresatovi();
			cin.get(); cin.get();
			break;
		case 11:
			Sp->vypisy();
			cin.get(); cin.get();
			break;
		
			
		case 15:
			system("CLS");
			cout << Sp->getAktualnyUnixCas();
			cin.get(); cin.get();
			break;

		case 16:
			system("CLS");
			cout << Sp->getAktualnyCas() << endl;
			cin.get(); cin.get();
			break;

		case 17:
			Sp->posunCasOHodinu();
			break;

		
		
		
		case 20:
			Sp->vypisPrekladisk();
			cin.get(); cin.get();
			break;

		case 21:
			Sp->vypisObjednavky();
			cin.get(); cin.get();
			break;		
		case 22:
			Sp->pridajZasielku();
			cin.get(); cin.get();
			break;
		case 23:
			Sp->vypisZasielky();
			cin.get(); cin.get();
			break;
		case 24:
			Sp->vypisKuforVozidla();
			cin.get(); cin.get();
			break;
		case 25:
			Sp->vypisPrekladiskaVozidla();
			cin.get(); cin.get();
			break;
		case 26:
			Sp->vypisZasielkyVSklade();
			cin.get(); cin.get();
			break;
		case 27:
			Sp->vypisZasielkyPreDrony();
			cin.get(); cin.get();
			break;

		
		case 40:
			Sp->nacitajZoSuboru();
			cin.get(); cin.get();
			break;
		case 41:
			Sp->zapisDoSuboru();
			cin.get(); cin.get();
			break;
		
		case 0:
			koniec = true;
			break;

		default:
			cout << "Zla volba. Skuste este raz." << endl;
			break;
		}
	}

	delete Sp;
	Sp = nullptr;
	
	return 0;
}

