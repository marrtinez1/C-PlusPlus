#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../ds_routines.h"

namespace structures 
{
	
	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T> 
	class Array	: public Structure
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(const size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(const Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();
		
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat pola. </summary>
		/// <returns> Ukazovatel na vytvoreny klon pola. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (pole), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je Array. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Pole, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		Array<T>& operator=(const Array<T>& other);

		/// <summary> Operator porovnania. </summary>
		/// <param name = "other"> Pole, s ktorym sa ma porovnat. </param>
		/// <returns> true, ak su polia rovnake, false inak. </returns>
		bool operator==(const Array<T>& other) const;
		
		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>  
		T& operator[](const int index);

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>  
		const T operator[](const int index) const;

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception> 
		static void copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length);

	private:
		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(const int index) const;
	};

	template<typename T> //T akeho typu bude array
	Array<T>::Array(const size_t size) :
		vector_(new Vector(size * sizeof(T))),
		size_(size)
	{
	}

	template<typename T> //copy konstruktor, robime kopiu other
	Array<T>::Array(const Array<T>& other) :
		vector_(new Vector(*(other.vector_))), //potrebujeme vyhradit novy blok pamate pre vektor, aby array nezdielal jednu pamat ale  aby pouzival vlastnu pamat
		size_(other.size_)
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		//TODO 02: Array
		delete vector_; // deletujeme vtedy ked pouzijeme slovisko new (ako to je v konstruktoroch)
		vector_ = nullptr; //nastavim vektor na nullptr aby neukazoval na zruseny vektor
		size_ = 0;
	}

	template<typename T>
	Structure* Array<T>::clone() const
	{
		return new Array<T>(*this);
	}

	template<typename T>
	Structure& Array<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Array<T>&>(other); //struktura ktora tu pride bude pretypovana na array
		}
		return *this;
		//dynamic_cast pretypovava objekty vramci dedicnosti, chcem pretypovat predka na potomka
	}

	template<typename T>
	Array<T>& Array<T>::operator=(const Array<T>& other) //kalsicky operator priradenia
	{
		//TODO 02: Array
		if (this != &other) {
			if (size_ != other.size_)
			{
				throw std::logic_error("Arrays sizes are diferrent.");
			}
			*vector_ = *other.vector_; //dereferencuje - vector_ a other.vector_ nie su smerniky; uz to nie je priradenie adries
		}
		return *this;
	}
	
	template<typename T>
	size_t Array<T>::size() const //kolko prvkov je v poli
	{
		return size_; //size_ obsahuje pocet bajtov, v array pocet prvkov v poli
	}

	template<typename T>
	T& Array<T>::operator[](const int index) //vraciame odkaz -> &
	{
		//TODO 02: Array
		return *(reinterpret_cast<T*>(vector_->getBytePointer(mapFunction(index))));
	}

	template<typename T>
	const T Array<T>::operator[](const int index) const //vraciame jeho kopiu
	{
		//TODO 02: Array
		return *(reinterpret_cast<T*>(vector_->getBytePointer(mapFunction(index))));
	}

	template<typename T>
	inline bool Array<T>::operator==(const Array<T>& other) const
	{
		//TODO 02: Array
		return *vector_ == *other.vector_ && size_ == other.size_;
		//porovnat size
	}

	template<typename T>
	void Array<T>::copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length)
	{
		//TODO 02: Array
		if (length != 0)
		{
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid Index.");
			DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid Index.");
			DSRoutines::rangeCheckExcept(destStartIndex, src.size_, "Invalid Index.");
			DSRoutines::rangeCheckExcept(destStartIndex + length, src.size_ + 1, "Invalid Index.");

			Vector::copy(*src.vector_, src.mapFunction(srcStartIndex), *dest.vector_, dest.mapFunction(destStartIndex), length * sizeof(T));
		}
	}

	template<typename T>
	inline int Array<T>::mapFunction(const int index) const
	{
		//TODO 02: Array 
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index of Array.");
		return index * sizeof(T);
	}
}

