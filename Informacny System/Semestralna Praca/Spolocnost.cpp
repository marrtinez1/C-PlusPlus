#include <fstream>
#include "Spolocnost.h"


Spolocnost::Spolocnost()
{
	vozidla = new ArrayList<Vozidlo*>();
	prekladiska = new Array<Prekladisko*>(25);
	objednavky = new LinkedList<Objednavka*>();
	zasielkyNaRozvoz = new ExplicitQueue<Zasielka*>();

	prekladiska->operator[](0) = new Prekladisko("ZA", 0); prekladiska->operator[](5) = new Prekladisko("BA", 5); prekladiska->operator[](10) = new Prekladisko("NR", 10);
	prekladiska->operator[](1) = new Prekladisko("NO", 1); prekladiska->operator[](6) = new Prekladisko("MA", 6); prekladiska->operator[](11) = new Prekladisko("TN", 11);
	prekladiska->operator[](2) = new Prekladisko("LM", 2); prekladiska->operator[](7) = new Prekladisko("TT", 7); prekladiska->operator[](12) = new Prekladisko("PD", 12);
	prekladiska->operator[](3) = new Prekladisko("CA", 3); prekladiska->operator[](8) = new Prekladisko("KN", 8); prekladiska->operator[](13) = new Prekladisko("KA", 13);
	prekladiska->operator[](4) = new Prekladisko("MT", 4); prekladiska->operator[](9) = new Prekladisko("LV", 9); prekladiska->operator[](14) = new Prekladisko("ZV", 14);
	prekladiska->operator[](15) = new Prekladisko("BB", 15); prekladiska->operator[](16) = new Prekladisko("LC", 16); prekladiska->operator[](17) = new Prekladisko("RA", 17);
	prekladiska->operator[](18) = new Prekladisko("PP", 18); prekladiska->operator[](19) = new Prekladisko("SL", 19); prekladiska->operator[](20) = new Prekladisko("PO", 20);
	prekladiska->operator[](21) = new Prekladisko("HE", 21); prekladiska->operator[](22) = new Prekladisko("SN", 22); prekladiska->operator[](23) = new Prekladisko("KE", 23);
	prekladiska->operator[](24) = new Prekladisko("MI", 24);

}


Spolocnost::~Spolocnost()
{
	for (Vozidlo* voz : *vozidla)
	{
		delete voz;
		voz = nullptr;
	}
	delete vozidla;
	vozidla = nullptr;

	for (size_t i = 0; i < prekladiska->size(); i++)
	{
		delete prekladiska->operator[](i);
	}
	/*for (Prekladisko* prekladisko : *prekladiska)
	{
		delete prekladisko;
		prekladisko = nullptr;
	}*/
	delete prekladiska;
	prekladiska = nullptr;

	for (Objednavka* obj : *objednavky)
	{
		delete obj;
		obj = nullptr;
	}
	delete objednavky;
	objednavky = nullptr;

	int zasNaRozvoz = zasielkyNaRozvoz->size();
	for (size_t i = 0; i < zasNaRozvoz; i++)
	{
		delete zasielkyNaRozvoz->pop();
	}
	
	delete zasielkyNaRozvoz;
	zasielkyNaRozvoz = nullptr;
}

time_t Spolocnost::getAktualnyUnixCas() {

	time_t datum = time(0);
	datum += pocetPosunutychHodin;
	return datum;
}

void Spolocnost::posunCasOHodinu() {
	pocetPosunutychHodin = pocetPosunutychHodin + UNIX_HODINA;
}

string Spolocnost::getAktualnyCas() {
	
	time_t datum = getAktualnyUnixCas();

	char cas[20];
	strftime(cas, sizeof(cas), "%H:%M-%d-%B-%Y", localtime(&datum));
	return cas;
}


//------------------------ Vozidlo ---------------------------------
//------------------------------------------------------------------

void Spolocnost::pridajVozidlo()
{
	string spz;
	double nosnost;
	int prevadzkoveNaklady, pocetRegionov, prekladiskoPreAuto;
	bool loopVariable = true;	
	Array<int> *nazvyReg;
	
	system("CLS");
	cout << "Zadajte SPZ: ";
	while (loopVariable)
	{
		cin >> spz;
		loopVariable = false;
		for each (Vozidlo *vozidlo in *vozidla)
		{
			if (vozidlo->operator==(spz)) {
				cout << "SPZ s takym nazvom existuje. Zadajte inu SPZ" << endl;
				loopVariable = true;
			}
		}
	}
	
	cout << "Zadajte nosnost v tonach: ";
	cin >> nosnost;
	cout << "Zadajte prevadzkove naklady: ";
	cin >> prevadzkoveNaklady;
	cout << "Zadajte pocet prekladisk cez ktore bude auto jazdit: ";
	cin >> pocetRegionov;

	nazvyReg = new Array<int>(pocetRegionov);

	vypisPrekladisk();

	for (size_t i = 0; i < nazvyReg->size(); i++)
	{
		cout << "\nZadajte prekladisko: ";
		cin >> prekladiskoPreAuto;

		nazvyReg->operator[](i) = prekladiskoPreAuto;	
	}

	if (vozidla->size() == 0) {
		vozidla->add(new Vozidlo(spz, nosnost, prevadzkoveNaklady, *nazvyReg));
	}
	else if (vozidla->size() == 1) {
		if (nosnost * 1000 > (*vozidla)[0]->getNosnost()) 
		{
			vozidla->insert(new Vozidlo(spz, nosnost, prevadzkoveNaklady, *nazvyReg), 0);
		}
		else 
		{
			vozidla->add(new Vozidlo(spz, nosnost, prevadzkoveNaklady, *nazvyReg));
		}
	}
	else {
		bool vloziloSa = false;
		int index = 0;
		if ((*vozidla)[0]->getNosnost() < nosnost * 1000) 
		{
			vozidla->insert(new Vozidlo(spz, nosnost, prevadzkoveNaklady, *nazvyReg), 0);
			vloziloSa = true;
		}
		if ((*vozidla)[vozidla->size() - 1]->getNosnost() > nosnost * 1000) 
		{
			vozidla->add(new Vozidlo(spz, nosnost, prevadzkoveNaklady, *nazvyReg));			
			vloziloSa = true;
		}
		while (!vloziloSa) 
		{
			if ((*vozidla)[index]->getNosnost() >= nosnost * 1000 & (*vozidla)[index + 1]->getNosnost() <= nosnost * 1000) 
			{
				vozidla->insert(new Vozidlo(spz, nosnost, prevadzkoveNaklady, *nazvyReg), index + 1);
				vloziloSa = true;
			}
			else 
			{
				index++;
			}
		}
	}

	system("CLS");
	cout << "Vozidlo bolo pridane.\n";

	delete nazvyReg;
	nazvyReg = nullptr;
}


void Spolocnost::vypisVozidiel()
{
	system("CLS");
	if (vozidla->isEmpty())
	{
		cout << "V zozname nie su ziadne vozidla.\n";
	}
	else
	{
		/*bool swapped;
		do
		{
			swapped = false;
			for (size_t j = 1; j < vozidla->size(); j++) {
				if (vozidla->operator[](j - 1)->getDatumZaradeniaDoEvidencie() > vozidla->operator[](j)->getDatumZaradeniaDoEvidencie()) {

					Vozidlo *vozidlo = vozidla->operator[](j - 1);
					vozidla->operator[](j - 1) = vozidla->operator[](j);
					vozidla->operator[](j) = vozidlo;
					swapped = true;
				}
			}
		} while (swapped);*/

		for each (Vozidlo *voz in *vozidla)
		{
			cout << "SPZ: " << voz->getSpz();
			cout << " || NOSNOST: "  <<	voz->getNosnost();
			cout << " || DATUM: " << voz->getDatumZaradeniaDoEvidencie();
			cout << " || PREVADZKOVE NAKLADY: " << voz->getPrevadzkoveNaklady();
			cout << " || CELKOVE PREVADZKOVE NAKLADY: " << voz->getCelkovePrevadzkoveNaklady() << endl;
		}
	}
}

//------------------------ Prekladisko -----------------------------
//------------------------------------------------------------------

void Spolocnost::vypisPrekladisk()
{
	int index = 1;
	for (size_t i = 0; i < prekladiska->size(); i++)	
	{
		cout << index << " -> " << prekladiska->operator[](i)->getNazovPrekladiska() << " \t ";
		index++;
		if (index % 2)
		{
			cout << "\n";
		}
	}
}

void Spolocnost::pridanieDronuDoPrekladiska()
{
	system("CLS");
	int indexPrekladiska;
	int serioveCislo;
	bool typ;

	vypisPrekladisk();

	cout << "\nVyberte si prekladisko podla indexu do ktoreho chcete pridat dron.\n" << endl;
	cin >> indexPrekladiska;
	system("CLS");

	if (indexPrekladiska >= 1 && indexPrekladiska <= this->prekladiska->size()) {
		cout << "Zadajte seriove cislo dronu: " << endl;
		cin >> serioveCislo;
		system("CLS");
		cout << "Zadajte typ dronu." << endl;
		cout << "Stlacte 0 pre dron typu I." << endl;
		cout << "Stlacte 1 pre dron typu II." << endl;
		cin >> typ;
		system("CLS");
		
		prekladiska->operator[](indexPrekladiska - 1)->pridajDron(serioveCislo, typ);
	}
	else {
		cout << "Zadajte prosim cislo z rozsahu <1;" << this->prekladiska->size() << ">" << endl;
	}
}

void Spolocnost::vypisDronovVPrekladisku()
{
	system("CLS");
	int indexPrekladiska;
	
	vypisPrekladisk();

	cout << "\nVyberte si prekladisko podla indexu z ktoreho chcete vypisat drony." << endl;
	cin >> indexPrekladiska;

	if (indexPrekladiska >= 1 && indexPrekladiska <= this->prekladiska->size()) {
		prekladiska->operator[](indexPrekladiska - 1)->vypisDronovVjednomPrekladisku();
	}
	else {
		cout << "Zadajte prosim cislo z rozsahu <1;" << this->prekladiska->size() << ">" << endl;
	}
}

//------------------------ Objednavka ------------------------------
//------------------------------------------------------------------

void Spolocnost::vytvorenieObjednavky()
{
	system("CLS");
	double hmotnost, vzdialVyz, vzdialDor;
	int regVyz, regDor;
	bool loopVar = true;
	time_t datum = time(0);

	cout << "Zadajte hmotnost zasielky v kg: ";	
	cin >> hmotnost;
	system("CLS");
	cout << "------------ Informacie o Mieste Vyzdvyhnutia --------------" << endl;
	vypisPrekladisk();
	cout << "\nZadajte index regionu vyzdvyhnutia: ";
	cin >> regVyz;

	if (regVyz >= 1 && regVyz <= this->prekladiska->size()) {
		cout << "Zadajte vzdialenost odosielatela od lokalneho prekladiska: ";
		cin >> vzdialVyz;

		system("CLS");
		cout << "------------ Informacie o Mieste Dorucenia --------------" << endl;
		vypisPrekladisk();
		cout << "\nZadajte index regionu dorucenia: ";
		cin >> regDor;

		if (regDor >= 1 && regDor <= this->prekladiska->size()) {
			cout << "Zadajte vzdialenost adresata od lokalneho prekladiska: ";
			cin >> vzdialDor;

			/*if (hmotnost <= 2)
			{
				if (kontrolaPrekoceniaNosnosti(hmotnost, regVyz, regDor))
				{
					string dovod = "Objednavka zamietnuta. Nalozenie zasielky do vozidla prekroci jeho hmotnost.";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;
				}
				else if (OSEM_HODIN_VECER <= ((datum + 3600) % UNIX_DEN) + (vzdialVyz / DRON_I_KM_ZA_SEKUNDU) )
				{
					string dovod = "Objednavka zamietnuta. Zasielka by musel byt vyzdvyhnuta za po 20:00";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;
				}
				else if (DRON_I_MAX_DOBA_LETU <= ((vzdialVyz / DRON_I_KM_ZA_MINUTU) * 2) || DRON_I_MAX_DOBA_LETU <= ((vzdialDor / DRON_I_KM_ZA_MINUTU) * 2))
				{
					string dovod = "Objednavka zamietnuta. Zasielka je mimo akcny radius dronov.";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;
				}
				else if (!prekladiska->operator[](regVyz - 1)->existujeDron() || !prekladiska->operator[](regDor - 1)->existujeDron())
				{
					string dovod = "Objednavka zamietnuta. V prekladisku nie je dron s pozadovanou nosnostou";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;					
				}
				else
				{*/
					objednavky->add(new Objednavka(hmotnost, regVyz, vzdialVyz, regDor, vzdialDor));					
				/*}
			}
			else if(hmotnost <= 5)
			{
				if (kontrolaPrekoceniaNosnosti(hmotnost, regVyz, regDor))
				{
					string dovod = "Objednavka zamietnuta. Nalozenie zasielky do vozidla prekroci jeho hmotnost.";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;
				}
				else if (OSEM_HODIN_VECER <= ((datum + 3600) % UNIX_DEN) + (vzdialVyz / DRON_II_KM_ZA_SEKUNDU))
				{
					string dovod = "Objednavka zamietnuta. Zasielka by musel byt vyzdvyhnuta za po 20:00";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;
				}
				else if (DRON_II_MAX_DOBA_LETU <= ((vzdialVyz / DRON_II_KM_ZA_MINUTU) * 2) || DRON_II_MAX_DOBA_LETU <= ((vzdialDor / DRON_II_KM_ZA_MINUTU) * 2))
				{
					string dovod = "Objednavka zamietnuta. Zasielka je mimo akcny radius dronov.";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;
				}
				else if (!prekladiska->operator[](regVyz - 1)->existujeDronTypuDva() || !prekladiska->operator[](regDor - 1)->existujeDronTypuDva())
				{
					string dovod = "Objednavka zamietnuta. V prekladisku nie je dron s pozadovanou nosnostou";
					prekladiska->operator[](regVyz - 1)->pridajDovod(dovod);
					cout << dovod;
				}
				else
				{
					objednavky->add(new Objednavka(hmotnost, regVyz, vzdialVyz, regDor, vzdialDor));
				}
			}
			else
			{
				cout << "Objednavka zamietnuta. Hmotnost musi byt do 5 kg.";
			}*/
		}
		else {
			system("CLS");
			cout << "Zadajte prosim cislo z rozsahu <1;" << this->prekladiska->size() << ">" << endl;
		}
	}
	else {
		system("CLS");
		cout << "Zadajte prosim cislo z rozsahu <1;" << this->prekladiska->size() << ">" << endl;
	}
	
}

bool Spolocnost::kontrolaPrekoceniaNosnosti(double pHmotnostObjednavky, int pRegionVyzdvyhnutia, int pRegionDorucenia)
{
	double nosnost = 0;
	double hmotnostVsObjednavokVyzdvyhnutia = 0;
	double hmotnostVsObjednavokDorucenia = 0;
	
	for each (Vozidlo* vozidlo in *vozidla)
	{
		for (size_t i = 0; i < vozidlo->getPocetPrekladiskKtoreNavstivi(); i++)
		{
			if (pRegionVyzdvyhnutia == vozidlo->getPrekladisko(i) + 1)
			{
				nosnost += vozidlo->getNosnost();
				break;
			}		
		}		
	}
	for each (Objednavka* objednavka in *objednavky)
	{
		if (objednavka->getRegVyzdvyhnutia() == pRegionVyzdvyhnutia)
		{
			hmotnostVsObjednavokVyzdvyhnutia += objednavka->getHmotnost();
		}
	}
	for each (Objednavka* objednavka in *objednavky)
	{
		if (objednavka->getRegDorucenia() == pRegionDorucenia)
		{
			hmotnostVsObjednavokDorucenia += objednavka->getHmotnost();
		}
	}
	if (nosnost >= hmotnostVsObjednavokVyzdvyhnutia + pHmotnostObjednavky && nosnost >= hmotnostVsObjednavokDorucenia + pHmotnostObjednavky)
	{
		return 0;
	}
	else
	{
		return 1;
	}	
}

bool Spolocnost::kontrolaDoOsemnastej(int pRegDor, double pVzdialDor)
{
	/*double vzdialenostObj = 0;
	double vzdialenostDronov = 0;

	for each (Objednavka *obj in *objednavky)
	{
		if (obj->getRegDorucenia() == pRegDor && obj->getBolaVyzdvyhnuta() == 1)
		{
			vzdialenostObj += obj->getVzdialDorucenia;
		}
	}
	vzdialenostDronov = prekladiska->operator[](pRegDor - 1)->sucetCasovDronov();
	*/
	return false;
}

void Spolocnost::vypisObjednavky()
{
	for each (Objednavka *obj in *objednavky)
	{
		cout << "Hmotnost: " << obj->getHmotnost();
		cout << " || Bola Vyzdvyhnuta: " << obj->getBolaVyzdvyhnuta();
		cout << " || Bola Zrusena: " << obj->getZrusena();
		cout << " || Region Vyzdvyhnutia: " << obj->getRegVyzdvyhnutia();
		cout << " || Vzdialenost od Odoberatela: " << obj->getVzdialVyzdvyhnutia();
		cout << " || Region Dorucenia: " << obj->getRegDorucenia();
		cout << " || Vzdialenost od Adresata: " << obj->getVzdialDorucenia() << endl;
	}
}

//----------------- Vyzdvyhnutie u odosielatela --------------------
//------------------------------------------------------------------

void Spolocnost::vyzdvyhnutieZasielkyUOdosielatela()
{
	Objednavka* nevyzdvyhnutaObj = najdenieNevyzdvyhnutejObj();
	
	if (nevyzdvyhnutaObj != nullptr)
	{
		int regionVyzdvyhnutia = nevyzdvyhnutaObj->getRegVyzdvyhnutia();
		double hmotnostVybavovanejZasielky = nevyzdvyhnutaObj->getHmotnost();
		double vzdialenostVyzdvyhnutia = nevyzdvyhnutaObj->getVzdialVyzdvyhnutia();
		int regionDorucenia = nevyzdvyhnutaObj->getRegDorucenia();
		double vzdialenostDorucenia = nevyzdvyhnutaObj->getVzdialDorucenia();

		if (prekladiska->operator[](regionVyzdvyhnutia - 1)->najdiVhodnyDron(hmotnostVybavovanejZasielky, vzdialenostVyzdvyhnutia, getAktualnyUnixCas(), regionDorucenia, vzdialenostDorucenia))
		{
			nevyzdvyhnutaObj->setZrusena(1);
			nevyzdvyhnutaObj->setCasZrusenia(getAktualnyUnixCas());
		}
		else
		{
			nevyzdvyhnutaObj->setBolaVyzdvyhnuta(1);
		}						
	}
	else
	{
		cout << "Vsetky objednavky boli vyzdvyhnute." << endl;
	}
}

Objednavka* Spolocnost::najdenieNevyzdvyhnutejObj()
{
	Objednavka *smernikNaObjednavku = nullptr;

	for each (Objednavka *obj in *objednavky)
	{
		if (!obj->getBolaVyzdvyhnuta() && !obj->getZrusena()) {
			smernikNaObjednavku = obj;
			break;
		}
	}

	return smernikNaObjednavku;
}


//------------ Navrat vozidiel do centralneho skladu ---------------
//------------------------------------------------------------------

void Spolocnost::navratVozidielDoCentralnehoSkladu()
{
	if (vozidla->isEmpty())
	{
		cout << "V spolocnosti sa nenachadzaju vozidla.";
	}
	else
	{
		for each (Vozidlo *voz in *vozidla)
		{
			int pocetNavstivenychPrekladisk = 0;
			double hmotnostZasielokVKufri = 0;

			for (size_t i = 0; i < voz->getPocetPrekladiskKtoreNavstivi(); i++)
			{
				if (prekladiska->operator[](voz->getPrekladisko(i))->getPrazdne() == false)
				{
					double pom = prekladiska->operator[](voz->getPrekladisko(i))->nalozenieZasielokDoAuta(voz->getKufor(), voz->getNosnost(), hmotnostZasielokVKufri);

					if (pom != hmotnostZasielokVKufri)
					{
						pocetNavstivenychPrekladisk++;
					}

					hmotnostZasielokVKufri = pom;
				}
				if (voz->getNosnost() == hmotnostZasielokVKufri)
				{
					break;
				}
			}

			int vzorec = 2 * voz->getPrevadzkoveNaklady() * pocetNavstivenychPrekladisk;
			voz->setCelkovePrevadzkoveNaklady(vzorec);

			if (!pocetNavstivenychPrekladisk)
			{
				cout << "Vozidlo s SPZ " << voz->getSpz() << " nenavstivilo ziadne prekladisko. Zasielky v nom uz boli vyzdvyhnute alebo tam ziadne neboli." << endl;
			}
			else
			{
				while (voz->getKufor()->size() > 0)
				{
					zasielkyNaRozvoz->push(voz->getKufor()->pop());					
				}		
				cout << "Vozidlo s SPZ " << voz->getSpz() << " navstivilo " << pocetNavstivenychPrekladisk << " prekladisk a vyzdvyhlo zasielky s hmotnostou dokopy " << hmotnostZasielokVKufri << " kg." << endl;
			}
		}
	}

	//----------------------------Druhy sposob----------------------------
	//--------------------------------------------------------------------
	/*if (vozidla->isEmpty())
	{
		cout << "V spolocnosti sa nenachadzaju vozidla.";
	}
	else
	{
		for each (Vozidlo *voz in *vozidla)
		{
			int pocetNavstivenychPrekladisk = 0;
			double hmotnostZasielokVKufri = 0;

			for each (Prekladisko *prekladisko in *prekladiska)
			{
				if (prekladisko->getPrazdne() == false)
				{
					double pom = prekladisko->nalozenieZasielokDoAuta(voz->getKufor(), voz->getNosnost(), hmotnostZasielokVKufri);

					if (pom != hmotnostZasielokVKufri)
					{
						pocetNavstivenychPrekladisk++;
					}

					hmotnostZasielokVKufri = pom;
									
				}
				if (voz->getNosnost() == hmotnostZasielokVKufri)
				{
					break;
				}
			}

			int vzorec = 2 * voz->getPrevadzkoveNaklady() * pocetNavstivenychPrekladisk;
			voz->setCelkovePrevadzkoveNaklady(vzorec);

			if (!pocetNavstivenychPrekladisk)
			{
				cout << "Vozidlo s SPZ " << voz->getSpz() << " nenavstivilo ziadne prekladisko. Zasielky v nom uz boli vyzdvyhnute alebo tam ziadne neboli." << endl;
			}
			else
			{
				while (voz->getKufor()->size() > 0)
				{
					zasielkyNaRozvoz->push(voz->getKufor()->peek());
					voz->getKufor()->pop();
				}
				//for each (Zasielka *zasielka in *voz->getKufor())
				//{
					//zasielkyNaRozvoz->push(new Zasielka(*zasielka));
				//}

				voz->getKufor()->clear();				

				cout << "Vozidlo s SPZ " << voz->getSpz() << " navstivilo " << pocetNavstivenychPrekladisk << " prekladisk." << endl;
			}
		}	
	}*/
}

//------------ Naplnenie vozidiel v centralnom skalde zasielkami ---------------
//------------------------------------------------------------------------------

void Spolocnost::naplnenieVozidielZasielkami()
{
	for each (Vozidlo *vozidlo in *vozidla)
	{
		double hmotnostZasielok = 0;
		int pocetZasielok = 0;

		for (size_t i = 0; i < vozidlo->getPocetPrekladiskKtoreNavstivi(); i++)
		{
			int pocetZasielokNaKontrolu = zasielkyNaRozvoz->size();

			for (size_t j = 0; j < pocetZasielokNaKontrolu; j++) 
			{			
				if (vozidlo->getPrekladisko(i) == (zasielkyNaRozvoz->peek()->getRegDorucenia() - 1) && hmotnostZasielok + zasielkyNaRozvoz->peek()->getHmotnost() <= vozidlo->getNosnost()) 
				{
					hmotnostZasielok += zasielkyNaRozvoz->peek()->getHmotnost();
					vozidlo->getKufor()->push(zasielkyNaRozvoz->pop());		
					pocetZasielok++;
				}
				else {
					zasielkyNaRozvoz->push(zasielkyNaRozvoz->pop());					
				}
			}
		}
		cout << "Vozidlo s SPZ " << vozidlo->getSpz() << " sa naplnilo " << pocetZasielok << " zasielkami." << endl;
	}	
}

// Transport zasielok z centralneho skladu do lokalnych prekladisk
//------------------------------------------------------------------

void Spolocnost::transportZasielokDoPrekladisk()
{
	for each (Vozidlo *voz in *vozidla)
	{
		int pocetZasielok = voz->getKufor()->size();
		for (size_t i = 0; i < voz->getPocetPrekladiskKtoreNavstivi(); i++)
		{
			prekladiska->operator[](voz->getPrekladisko(i))->vylozenieZasielokZAuta(voz->getKufor());
		}

		cout << "Vozidlo s SPZ " << voz->getSpz() << " rozviezlo " << pocetZasielok << " zasielok do lokalnych prekladisk." << endl;
	}
}

//---------------------- Odovzdanie zasielky adresatovi ------------------------
//------------------------------------------------------------------------------

void Spolocnost::odovzdanieZasielkyAdresatovi()
{
	int prekladisko;

	cout << "Zadajte prekladisko: ";
	cin >> prekladisko;

	double hmotnost = prekladiska->operator[](prekladisko - 1)->getZasielkaPreDron()->getHmotnost();
	double vzdialDorucenia = prekladiska->operator[](prekladisko - 1)->getZasielkaPreDron()->getVzdialDorucenia();

	prekladiska->operator[](prekladisko - 1)->najdiVhodnyDron(hmotnost, vzdialDorucenia, getAktualnyUnixCas(), -1, -1);
}

//------------------------ Vypisy sumarnych statistik --------------------------
//------------------------------------------------------------------------------

void Spolocnost::vypisy()
{
	system("cls");
	int volba, regionC;
	cout << "1) Region do ktoreho bolo v danom casovom obdobi dorucenych najviac zasielok." << endl;
	cout << "2) Region z ktoreho bolo v danom casovom obdobi odoslanych najviac zasielok." << endl;
	cout << "3) Vypis zasielok v danom regione ktore boli v danom casovom obdobi zamietnute spolu s dovodom ich zamietnutia." << endl;
	cout << "4) Vypis poctu zrusenych objednavok za dane casove obdobie v jednotlivych regionoch." << endl;
	cout << "5) Vypis celkoveho poctu dorucenych zasielok." << endl;
	cout << "6) Vypis celkoveho poctu najazdenych kilometrov vsetkych vozidiel." << endl;
	cout << "7) Vypis celkoveho poctu nalietanych hodin podla typu drona v jednotlivych prekladiskach." << endl;

	cin >> volba;
	switch (volba)
	{
	case 1:
		cout << "---" << regionSNjaviacDorucenymiZasielkami() << "---" << endl;
		break;
	case 2:
		cout << "---" << regionSNjaviacOdoslanymiZasielkami() << "---" << endl;
		break;
	case 3:
		cin >> regionC;
		prekladiska->operator[](regionC)->vypisDovody();
		break;
	case 4:
		regionySNajviacZrusenymiZasielkami();
		break;
	case 5:
		vypisCelkovehoPoctuDorucenychZasielok();
		break;
	case 6:
		vypisNajazdenychKilometrov();
		break;
	case 7:
		vypisNalietanychHodin();
		break;

	default:
		cout << "Zla volba. Skuste este raz." << endl;
		break;
	}
}

string Spolocnost::regionSNjaviacDorucenymiZasielkami()
{
	system("cls");

	int datumOd;
	string pozadovanyDatumOd;
	bool koniecWhile1 = true;

	while (koniecWhile1) {

		cout << "Zadajte datum OD v tvare (YYYY-MM-DD-HH:MN)" << endl;
		cout << "PRIKLAD:   2019-03-30-15:30" << endl;
		cin >> pozadovanyDatumOd;

		if ((pozadovanyDatumOd.size() != 16) | (pozadovanyDatumOd[4] != '-') | (pozadovanyDatumOd[7] != '-' | pozadovanyDatumOd[10] != '-' | pozadovanyDatumOd[13] != ':')) 
		{
			system("cls");
			cout << "Zle zadany datum. Skuste este raz" << endl;
			continue;
		}

		koniecWhile1 = false;
	}
	datumOd = premenCasStringNaUTS(pozadovanyDatumOd);

	system("cls");

	int datumDo;
	string pozadovanyDatumDo;
	bool koniecWhile2 = true;

	while (koniecWhile2) {

		cout << "Zadajte datum DO v tvare (YYYY-MM-DD-HH:MN)" << endl;
		cout << "PRIKLAD:   2019-03-30-15:30" << endl;
		cin >> pozadovanyDatumDo;

		if ((pozadovanyDatumDo.size() != 16) | (pozadovanyDatumDo[4] != '-') | (pozadovanyDatumDo[7] != '-' | pozadovanyDatumDo[10] != '-' | pozadovanyDatumDo[13] != ':'))
		{
			system("cls");
			cout << "Zle zadany datum. Skuste este raz" << endl;
			continue;
		}

		koniecWhile2 = false;
	}
	datumDo = premenCasStringNaUTS(pozadovanyDatumDo);

	for (size_t i = 0; i < prekladiska->size(); i++)
	{
		prekladiska->operator[](i)->vyhladanieDorucenychZasielokPodlaCasu(datumOd, datumDo);
	}

	int prekladisko = prekladiska->operator[](0)->getDoruceneZasielky();
	string nazovPrekl = prekladiska->operator[](0)->getNazovPrekladiska();

	for (size_t j = 1; j < prekladiska->size(); j++)
	{
		if (prekladisko < prekladiska->operator[](j)->getDoruceneZasielky()) {

			prekladisko = prekladiska->operator[](j)->getDoruceneZasielky();
			nazovPrekl = prekladiska->operator[](j)->getNazovPrekladiska();
		}	
	}
	return nazovPrekl;
}

string Spolocnost::regionSNjaviacOdoslanymiZasielkami()
{
	system("cls");

	int datumOd;
	string pozadovanyDatumOd;
	bool koniecWhile1 = true;

	while (koniecWhile1) {

		cout << "Zadajte datum OD v tvare (YYYY-MM-DD-HH:MN)" << endl;
		cout << "PRIKLAD:   2019-03-30-15:30" << endl;
		cin >> pozadovanyDatumOd;

		if ((pozadovanyDatumOd.size() != 16) | (pozadovanyDatumOd[4] != '-') | (pozadovanyDatumOd[7] != '-' | pozadovanyDatumOd[10] != '-' | pozadovanyDatumOd[13] != ':'))
		{
			system("cls");
			cout << "Zle zadany datum. Skuste este raz" << endl;
			continue;
		}

		koniecWhile1 = false;
	}
	datumOd = premenCasStringNaUTS(pozadovanyDatumOd);

	system("cls");

	int datumDo;
	string pozadovanyDatumDo;
	bool koniecWhile2 = true;

	while (koniecWhile2) {

		cout << "Zadajte datum DO v tvare (YYYY-MM-DD-HH:MN)" << endl;
		cout << "PRIKLAD:   2019-03-30-15:30" << endl;
		cin >> pozadovanyDatumDo;

		if ((pozadovanyDatumDo.size() != 16) | (pozadovanyDatumDo[4] != '-') | (pozadovanyDatumDo[7] != '-' | pozadovanyDatumDo[10] != '-' | pozadovanyDatumDo[13] != ':'))
		{
			system("cls");
			cout << "Zle zadany datum. Skuste este raz" << endl;
			continue;
		}

		koniecWhile2 = false;
	}
	datumDo = premenCasStringNaUTS(pozadovanyDatumDo);

	for (size_t i = 0; i < prekladiska->size(); i++)
	{
		prekladiska->operator[](i)->vyhladanieOdoslanychZasielokPodlaCasu(datumOd, datumDo);
	}

	int prekladisko = prekladiska->operator[](0)->getOdoslaneZasielky();
	string nazovPrekl = prekladiska->operator[](0)->getNazovPrekladiska();

	for (size_t j = 1; j < prekladiska->size(); j++)
	{
		if (prekladisko < prekladiska->operator[](j)->getOdoslaneZasielky()) {

			prekladisko = prekladiska->operator[](j)->getOdoslaneZasielky();
			nazovPrekl = prekladiska->operator[](j)->getNazovPrekladiska();
		}
	}
	return nazovPrekl;
}

void Spolocnost::regionySNajviacZrusenymiZasielkami()
{
	system("cls");

	int datumOd;
	string pozadovanyDatumOd;
	bool koniecWhile1 = true;

	while (koniecWhile1) {

		cout << "Zadajte datum OD v tvare (YYYY-MM-DD-HH:MN)" << endl;
		cout << "PRIKLAD:   2019-03-30-15:30" << endl;
		cin >> pozadovanyDatumOd;

		if ((pozadovanyDatumOd.size() != 16) | (pozadovanyDatumOd[4] != '-') | (pozadovanyDatumOd[7] != '-' | pozadovanyDatumOd[10] != '-' | pozadovanyDatumOd[13] != ':'))
		{
			system("cls");
			cout << "Zle zadany datum. Skuste este raz" << endl;
			continue;
		}

		koniecWhile1 = false;
	}
	datumOd = premenCasStringNaUTS(pozadovanyDatumOd);

	system("cls");

	int datumDo;
	string pozadovanyDatumDo;
	bool koniecWhile2 = true;

	while (koniecWhile2) {

		cout << "Zadajte datum DO v tvare (YYYY-MM-DD-HH:MN)" << endl;
		cout << "PRIKLAD:   2019-03-30-15:30" << endl;
		cin >> pozadovanyDatumDo;

		if ((pozadovanyDatumDo.size() != 16) | (pozadovanyDatumDo[4] != '-') | (pozadovanyDatumDo[7] != '-' | pozadovanyDatumDo[10] != '-' | pozadovanyDatumDo[13] != ':'))
		{
			system("cls");
			cout << "Zle zadany datum. Skuste este raz" << endl;
			continue;
		}

		koniecWhile2 = false;
	}
	datumDo = premenCasStringNaUTS(pozadovanyDatumDo);

	for (size_t i = 0; i < prekladiska->size(); i++)
	{
		int pocet = 0;
		for each (Objednavka *obj in *objednavky)
		{
			if (obj->getZrusena() & (obj->getRegVyzdvyhnutia() -1) == prekladiska->operator[](i)->getIndexPrekladiska() & obj->getCasZrusenia() >= datumOd & obj->getCasZrusenia() <= datumDo)
			{
				pocet++;
			}
		}
		cout << "Pocet zrusenych objednavok v prekladisku " << prekladiska->operator[](i)->getNazovPrekladiska() << " : " << pocet << endl;
	}
}

void Spolocnost::vypisCelkovehoPoctuDorucenychZasielok()
{
	int celkovyPocetDorucenych = 0;

	for each (Objednavka *obj in *objednavky)
	{
		if (obj->getBolaVyzdvyhnuta())
		{
			celkovyPocetDorucenych++;
		}
	}
	cout << celkovyPocetDorucenych;
}

void Spolocnost::vypisNajazdenychKilometrov()
{
	double kilometreVsetkychVozidiel = 0;

	for each (Vozidlo *voz in *vozidla)
	{
		kilometreVsetkychVozidiel += voz->getCelkovePrevadzkoveNaklady();
	}

	cout << kilometreVsetkychVozidiel;
}

void Spolocnost::vypisNalietanychHodin()
{
	for (size_t i = 0; i < prekladiska->size(); i++)
	{
		cout << "Prekladisko " << prekladiska->operator[](i)->getNazovPrekladiska() << " : dron typu I: " << prekladiska->operator[](i)->getPocetHodinDronovTypuI() << " hodin || dron typu II: " << prekladiska->operator[](i)->getPocetHodinDronovTypuII() << " hodin." << endl;
	}
}

//----------------- Pomocne -----------------
//-------------------------------------------

void Spolocnost::pridajZasielku()
{
	int reg, prekl;
	double hmot, vzdial;
	cout << "Zadaj do ktoreho prekladiska pridat zasielku: ";
	cin >> prekl;
	cout << "Zadaj hmotnost: ";
	cin >> hmot;
	cout << "Zadaj region: ";
	cin >> reg;
	cout << "Zadaj vzdialensot:";
	cin >> vzdial;

	prekladiska->operator[](prekl - 1)->pridajZasielku(hmot, reg, vzdial);
}

void Spolocnost::vypisZasielky()
{
	int prekl;
	cout << "Z ktoreho prekladiska vypisat zasielky?";
	cin >> prekl;
	prekladiska->operator[](prekl - 1)->vypisZasielky();
}

void Spolocnost::vypisZasielkyPreDrony()
{
	int prekl;
	cout << "Z ktoreho prekladiska vypisat zasielky?";
	cin >> prekl;
	prekladiska->operator[](prekl - 1)->vypisZasielkyPreDrony();
}

void Spolocnost::vypisPrekladiskaVozidla()
{
	int vozidlo;
	cout << "Z ktoreho vozidla vypisat prekladiska?";
	cin >> vozidlo;
	vozidla->operator[](vozidlo - 1)->vypisPrekladiskaVKtorychJazdi();
}

void Spolocnost::vypisKuforVozidla()
{
	int vozidlo;
	cout << "Z ktoreho vozidla vypisat zasielky?";
	cin >> vozidlo;
	vozidla->operator[](vozidlo - 1)->vypisKufor();
}

void Spolocnost::vypisZasielkyVSklade()
{
	int pom = zasielkyNaRozvoz->size();
	for (size_t i = 0; i < pom; i++)
	{
		cout << "Hmotnost:" << zasielkyNaRozvoz->peek()->getHmotnost() << endl;
		cout << "Reg dorucenia:" << zasielkyNaRozvoz->peek()->getRegDorucenia() << endl;
		cout << "Vzdialenost dorucenia:" << zasielkyNaRozvoz->peek()->getVzdialDorucenia() << endl;
		cout << "-----------------------------------" << endl;
		zasielkyNaRozvoz->push(zasielkyNaRozvoz->pop());
	}	
}

//------------------------- Subory ---------------------------
//------------------------------------------------------------


void Spolocnost::nacitajZoSuboru()
{
	fstream suborVozidla;
	suborVozidla.open("Subory/Vozidla.txt", ios::in);
	if (suborVozidla.fail()) {
		cout << "Nepodarilo sa otvorit subor na nacitanie vozidiel" << endl;
	}
	else {

		while (!suborVozidla.eof()) {
			string spz;
			double nosnost;
			int naklady;
			int pocetRegionov;
			int region;
			Array<int> *nazvyReg;

			suborVozidla >> spz;
			suborVozidla >> nosnost;
			suborVozidla >> naklady;
			suborVozidla >> pocetRegionov;

			nazvyReg = new Array<int>(pocetRegionov);

			for (size_t i = 0; i < pocetRegionov; i++)
			{				
				suborVozidla >> region;
				nazvyReg->operator[](i) = region;
			}
		
			vozidla->add(new Vozidlo(spz, nosnost, naklady, *nazvyReg));

			delete nazvyReg;

			if (suborVozidla.eof()) {
				break;
			}		
		}

		suborVozidla.close();	
	}

	fstream suborDrony;
	suborDrony.open("Subory/Drony.txt", ios::in);
	if (suborDrony.fail()) {
		cout << "Nepodarilo sa otvorit subor na nacitanie dronov" << endl;
	}
	else {

		while (!suborDrony.eof()) {
			int serioveCislo;
			bool typ;
			int prekladisko;

			suborDrony >> serioveCislo;
			suborDrony >> typ;
			suborDrony >> prekladisko;

			prekladiska->operator[](prekladisko - 1)->pridajDron(serioveCislo, typ);

			if (suborDrony.eof()) {
				break;
			}		
		}

		suborDrony.close();
	}

	fstream suborObjednavky;
	suborObjednavky.open("Subory/Objednavky.txt", ios::in);
	if (suborObjednavky.fail()) {
		cout << "Nepodarilo sa otvorit subor na nacitanie objednavok" << endl;
	}
	else {

		while (!suborObjednavky.eof()) {

			double hmotnost;
			int preladiskoVyz;
			double vzdialVyz;
			int preladiskoDor;
			double vzdialDor;

			suborObjednavky >> hmotnost;
			suborObjednavky >> preladiskoVyz;
			suborObjednavky >> vzdialVyz;
			suborObjednavky >> preladiskoDor;
			suborObjednavky >> vzdialDor;

			objednavky->add(new Objednavka(hmotnost, preladiskoVyz, vzdialVyz, preladiskoDor, vzdialDor));

			if (suborObjednavky.eof()) {
				break;
			}				
		}

		suborObjednavky.close();
	}
}

void Spolocnost::zapisDoSuboru()
{
	fstream suborVozidlaZapis;
	suborVozidlaZapis.open("Subory/VozdilaZapis.txt", ios::out);
	if (suborVozidlaZapis.fail()) {
		cout << "Nepodarilo sa otvorit subor na ulozenie vozidiel" << endl;
	}
	for each (Vozidlo *voz in *vozidla)
	{
		suborVozidlaZapis << voz->getSpz() << endl;
		suborVozidlaZapis << voz->getNosnost() << endl;
		suborVozidlaZapis << voz->getDatumZaradeniaDoEvidencie() << endl;
		suborVozidlaZapis << voz->getPrevadzkoveNaklady() << endl;
		suborVozidlaZapis << voz->getCelkovePrevadzkoveNaklady() << endl;
	}
	suborVozidlaZapis.close();


	fstream suborDronyZapis;
	suborDronyZapis.open("Subory/DronyZapis.txt", ios::out);
	if (suborDronyZapis.fail()) {
		cout << "Nepodarilo sa otvorit subor na ulozenie dronov" << endl;
	}

	for (size_t j = 0; j < prekladiska->size(); j++)
	{
		for (size_t i = 0; i < prekladiska->operator[](j)->getDrony()->size(); i++)
		{
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getSerioveCislo() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getDatumPridania() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getTyp() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->isVolny() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getStavBaterie() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getCasOdchoduString() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getCasPrichoduString() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getPocetNalietanychHod() << endl;
			suborDronyZapis << prekladiska->operator[](j)->getDrony()->operator[](i)->getPocetPrepravenychZasielok() << endl;
		}
	}
	suborDronyZapis.close();


	fstream suborObjednavkyZapis;
	suborObjednavkyZapis.open("Subory/ObjednavkyZapis.txt", ios::out);
	if (suborObjednavkyZapis.fail()) {
		cout << "Nepodarilo sa otvorit subor na ulozenie objednavok" << endl;
	}
	for each (Objednavka *obj in *objednavky)
	{
		suborObjednavkyZapis << obj->getHmotnost() << endl;
		suborObjednavkyZapis << obj->getBolaVyzdvyhnuta() << endl;
		suborObjednavkyZapis << obj->getZrusena() << endl;
		suborObjednavkyZapis << obj->getRegVyzdvyhnutia() << endl;
		suborObjednavkyZapis << obj->getVzdialVyzdvyhnutia() << endl;
		suborObjednavkyZapis << obj->getRegDorucenia() << endl;
		suborObjednavkyZapis << obj->getVzdialDorucenia() << endl;
	}

	suborObjednavkyZapis.close();
}

unsigned long Spolocnost::premenCasStringNaUTS(string fdatetime)
{
	if (fdatetime.length() < 16) {
		std::cout << "zle zadany cas";
	}

	string datetime = fdatetime;
	datetime += " 00:00:00";

	struct tm tm;
	tm.tm_year = atoi(datetime.substr(0, 4).c_str()) - 1900;
	tm.tm_mon = atoi(datetime.substr(5, 2).c_str()) - 1;
	tm.tm_mday = atoi(datetime.substr(8, 2).c_str());
	tm.tm_hour = atoi(datetime.substr(11, 2).c_str()) + 2;
	tm.tm_min = atoi(datetime.substr(14, 2).c_str());
	tm.tm_sec = atoi(datetime.substr(17, 2).c_str());

	char buff[80];
	strftime(buff, 80, "%Y.%m.%d %H:%M:%S", &tm);


	return (mktime(&tm) - (UNIX_HODINA * 2));
}
