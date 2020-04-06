#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) : //konstruktor
		memory_(calloc(size, 1)), //alokacia pamate v operacnej pamati (calloc(pocetPrvkov, vekost)) --- free - na uvolnenie pamate (vzdy ked je malloc tak musi byt free)
		size_(size) //nastavim atribut size (atribut_)
	{
	}

	Vector::Vector(const Vector& other) : //copy konstruktor
		Vector(other.size_) //prebieha tam alokacia pamate zavolanim konstruktora
	{
		memcpy(memory_, other.memory_, size_);
	}

	Vector::~Vector()
	{
		free(memory_); // uvolnenie pamate
		memory_ = nullptr; //zrusenie smernika
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other) //strukturu pretipujeme na vektor a potom vraciame
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other) //operator priradenia ---- & - modifikacia samotnej struktury, bez toho modifikujem kopiu v stacku
	{
		if (this != &other)
		{
			size_ = other.size_;
			memory_ = realloc(memory_, size_); // realokuje pamat
			memcpy(memory_, other.memory_, size_); //nakopiruje pamat na alokovane miesto
		}
		return *this; // this = odkaz(smernik) na seba sameho, na 8 bit *this = dereferencovanie, vrati sa objekt
	}

	bool Vector::operator==(const Vector& other) const
	{
		return size_ == other.size_ && memcmp(memory_, other.memory_, size_);
	}

	byte& Vector::operator[](const int index) //byte& -> vyvolanim vraciam objekt adresou
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index.");//treba zistiti ci sa index nachadza v nasom vektore
		return *(reinterpret_cast<byte*>(memory_) + index); //pristup k bajtu na pozicii index
		// viod nema urcenu velkost o ktoru sa mame posuvat
	}

	byte Vector::operator[](const int index) const //pracuje sa s kopiou objektu
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index.");//treba zistiti ci sa index nachadza v nasom vektore
		return *(reinterpret_cast<byte*>(memory_) + index); //pristup k bajtu na pozicii index
															// viod nema urcenu velkost o ktoru sa mame posuvat
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest) //zoberiem prvok na pozicii index, urcity pocet a skopirujem ich tam kde mi ukazuje dest
	{ //porovnanie indexov so size
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index.");
		DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Invalid index + count.");
		DSRoutines::rangeCheckExcept(count, size_ + 1, "Invalid count.");
		memcpy(&dest, reinterpret_cast<byte*>(memory_) + index, count); //reinterpret_cast<byte*>(memory_) + index -----> presun na index vo vektore 
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{ //podobne ako kopirovanie poli, musime kontrolovat rozsahy
		
		// ak je length nula nech nic nerobi
		//parametre: verktor ktory idem kopirovat, index odkial kopirujem, vektor kam kopirujem, index kam kopirujem, size
		//otestovat ci mozeme pouzit memcpy , memmove je pomaly
		if (length != 0)
		{
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid index");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Invalid index");
			DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid index + length."); //1+, lebo length je normalne cislo
			DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Invalid index + length.");//1+, lebo length je normalne cislo
		
			if (&src != &dest)
			{
				memcpy(reinterpret_cast<byte*>(dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
			}
			else {
				memmove(reinterpret_cast<byte*>(dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
			}
		}
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index.");//treba zistiti ci sa index nachadza v nasom vektore
		return reinterpret_cast<byte*>(memory_) + index; //pristup k bajtu na pozicii index
															// viod nema urcenu velkost o ktoru sa mame posuvat
	}

}