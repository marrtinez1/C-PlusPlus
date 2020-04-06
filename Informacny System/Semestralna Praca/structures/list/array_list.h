#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../array/array.h"

namespace structures
{

	/// <summary> Zoznam implementovany polom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ArrayList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> ArrayList, z ktoreho sa prevezmu vlastnosti. </param>
		ArrayList(const ArrayList<T>& other);

		/// <summary> Destruktor. </summary>
		~ArrayList();
		
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		ArrayList<T>& operator=(const ArrayList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pole s datami. </summary>
		Array<T>* array_;
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
	private:
		/// <summary> Rozsiri kapacitu zoznamu. </summary>
		void enlarge();
		void shrink();

		/// <summary> Iterator pre ArrayList. </summary>
		class ArrayListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "arrayList"> Zoznam, cez ktory iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			ArrayListIterator(const ArrayList<T>* arrayList, int position);

			/// <summary> Destruktor. </summary>
			~ArrayListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;


		private:
			/// <summary> Zoznam, cez ktory iteruje. </summary>
			const ArrayList<T>* arrayList_;
			/// <summary> Aktualna pozicia v zozname. </summary>
			int position_;
		};
	};

	template<typename T>
	inline ArrayList<T>::ArrayList():
		List<T>(), // vyvolaj tento konstruktor listu
		array_(new Array<T>(4)),
		size_(0) //prazdny array list
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(const ArrayList<T>& other):
		List<T>(), // volam kontruktor listu
		array_(new Array<T>(*other.array_)), // vytvorim nove pole
		size_(other.size_) // nastavim atribut size
	{
	}

	template<typename T>
	inline ArrayList<T>::~ArrayList()
	{
		//TODO 03: ArrayList
		delete array_;
		array_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Structure * ArrayList<T>::clone() const //kopirovaci konstruktor array listu
	{
		return new ArrayList<T>(*this);
	}

	template<typename T>
	inline size_t ArrayList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& ArrayList<T>::operator=(const List<T>& other) // operator priradenia
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ArrayList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
	{
		//TODO 03: ArrayList
		if (this != &other)
		{
			delete array_; // inak by sme mali memory leak
			array_ = new Array<T>(*other.array_); //dereferencia, lebo konstruktor vyzaduje objekt, nie smernik 
			size_ = other.size_;
		}
		return *this;
	}

	template<typename T>
	inline T & ArrayList<T>::operator[](const int index) // spristupnim prvok na danom indexe
	{
		//TODO 03: ArrayList
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index.");
		return (*array_)[index];
	}

	template<typename T>
	inline const T ArrayList<T>::operator[](const int index) const
	{
		//TODO 03: ArrayList
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index.");
		return (*array_)[index];
	}

	template<typename T>
	inline void ArrayList<T>::add(const T & data)
	{
		//TODO 03: ArrayList
		if (size_ >= array_->size())
		{
			enlarge();
		}
		(*array_)[static_cast<int>(size_)] = data;
		size_++;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T & data, const int index) //obdoba removeAt
	{
		//TODO 03: ArrayList
		DSRoutines::rangeCheckExcept(index, size_ + 1, "Array out of bounds!");
		if (size_ >= array_->size()) enlarge();
		if (index == size_) {
			add(data);
			return;
		}
		Array<T>::copy(*array_, index, *array_, index + 1, size_ - index);
		(*array_)[index] = data;
		size_++;
	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T & data)
	{
		//TODO 03: ArrayList
		int index = getIndexOf(data);
		if (index > -1)
		{
			removeAt(index);
			return true;
		}
		return false;
	}

	template<typename T>
	inline T ArrayList<T>::removeAt(const int index)
	{
		//TODO 03: ArrayList
		T ret = (*this)[index];
		if (index == size_ - 1) {
			size_--;
			return ret;
		}
		Array<T>::copy(*array_, index + 1, *array_, index, size_ - index - 1);
		size_--;
		shrink();
		return ret;
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T & data) //nevkadat do array objekty iba ak smerniky na objekty alebo primitivne typy
	{
		//TODO 03: ArrayList
		for (int i = 0; i < size_; i++) // mozno potom doplnit --> static_cast<int>(size_)
		{
			if ((*array_)[i] == data)
			{
				return i;
			}
		}
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear() // ak je v array objekt tak to musim najskor deletnut a potom zvolat clear
	{
		//TODO 03: ArrayList
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator() const // ukzauje na prvy prvok v array liste na index 0
	{
		//TODO 03: ArrayList
		return new ArrayList<T>::ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator() const // ukzauje za posledny prvok respektyve prvy neplatny prvok v poli
	{
		//TODO 03: ArrayList
		return new ArrayList<T>::ArrayListIterator(this, static_cast<int>(size_));
	}

	template<typename T>
	inline void ArrayList<T>::enlarge()
	{
		//TODO 03: ArrayList
		 Array<T> *pom = new Array<T>(size_ > 0 ? 2 * size_ : 4);
		 Array<T>::copy(*array_, 0, *pom, 0, static_cast<int>(size_));
		 delete array_;
		 array_ = pom;
	}

	template<typename T>
	inline void ArrayList<T>::shrink()
	{
		if (size_ < array_->size() / 4 && array_->size() >= 8) {
			Array<T> * newArr = new Array<T>(array_->size() / 2);
			Array<T>::copy(*array_, 0, *newArr, 0, size_);
			delete array_;
			array_ = newArr;
		}
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(const ArrayList<T>* arrayList, int position) :
		arrayList_(arrayList),
		position_(position)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator() //nikdy nemaze arrayList lebo on mi este moze ukazovat na vela inych veci 
	{
		//TODO 03: ArrayList<T>::ArrayListIterator
		arrayList_ = nullptr;
		position_ = -1; //nieco co v Array liste urcite neexistuje
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator=(const Iterator<T>& other) //priradenia
	{
		//TODO 03: ArrayList
		position_ = dynamic_cast<const ArrayListIterator &>(other).position_;
		arrayList_ = dynamic_cast<const ArrayListIterator &>(other).arrayList_;
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(const Iterator<T>& other) //porovnanie
	{ //pretypujem to n arrayListIterator lebo vkladam vseobecny operator
		//TODO 03: ArrayList
		return !(
			arrayList_ == dynamic_cast<const ArrayListIterator &>(other).arrayList_ &&
			position_ == dynamic_cast<const ArrayListIterator &>(other).position_
		);

		//return position_ != dynamic_cast<const ArrayListIterator&>(other).position_ || 
		//arrayList_ != dynamic_cast<const ArrayListIterator&>(other).arrayList_;
	}

	template<typename T>
	inline const T ArrayList<T>::ArrayListIterator::operator*() //vytiahnutie prvku na danej pozicii
	{
		//TODO 03: ArrayList
		return (*arrayList_)[position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++() //operator posunutia
	{
		//TODO 03: ArrayList
		this->position_++;
		return *this;
	}

}