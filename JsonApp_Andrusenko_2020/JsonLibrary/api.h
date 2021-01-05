#ifndef API_H
#define API_H

#include "platform.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

// - �ablona s parametrem datov�ho typu ulo�en�ch hodnot
// - nen� povoleno u�it� STL kontejner� ani jin�ch knihoven pro ukl�d�n� dat
// - realizace mus� vyu��vat dynamicky alokovan� pole, spojov� seznam nebo jinou vhodnou V�mi implementovanou ADS
template<typename T>
class DLL_EXPORT DynamicArray {
	int DefaultCapacity = 5;
	int ExpansionRatio = 2;
	T* array;
	int arraySize;
	int numberOfElements;
	bool HasEmptySpace() const
	{
		return numberOfElements < arraySize;
	}
	void Expand()
	{
		arraySize = arraySize * ExpansionRatio;
		T* tempField = new T[arraySize];

		for (int i = 0; i < numberOfElements; i++)
		{
			tempField[i] = array[i];
		}

		delete[] array;
		array = tempField;
	}
public:
	DynamicArray()
	{
		array = new T[DefaultCapacity];
		arraySize = DefaultCapacity;
		numberOfElements = 0;
	}

	~DynamicArray()
	{
		delete[] array;
	}

	// - p�id� element na konec pole
	void append(const T& element)
	{
		if (!HasEmptySpace())
		{
			Expand();
		}
		array[numberOfElements++] = element;
	}

	// - v�jimky p�i neplatn�m nebo nekorektn�m indexu
	const T& getElementAt(int index) const
	{
		if (index < 0 || index >= numberOfElements)
		{
			throw out_of_range("Index is out of range!");
		}

		return array[index];
	}

	// - vrac� velikost (po�et prvk�) v poli
	int getSize() const
	{
		return numberOfElements;
	}

	T& operator[](int index) const
	{
		if (index < 0 || index >= numberOfElements)
		{
			throw out_of_range("Index is out of range!");
		}

		return array[index];
	}

	T operator[](int index)
	{
		if (index < 0 || index >= numberOfElements)
		{
			throw out_of_range("Index is out of range!");
		}

		return array[index];
	}

	void deleteAtIndex(int index)
	{
		if (index < 0 || index >= numberOfElements)
		{
			throw out_of_range("Index is out of range!");
		}

		for (int i = index; i < numberOfElements; i++)
		{
			array[i] = array[i + 1];
		}

		numberOfElements--;
	}
};

///////////////////////////////////////////////////////////////////////////////

// JSON hodnota - reprezentuje abstraktn�ho p�edka pro z�kladn� datov� typy v JSON (string, number, object, array, bool, null)
class DLL_SPEC Value
{
public:
	Value() = default;
	virtual ~Value() = default;

	// serializuje hodnotu do podoby JSON reprezentace
	virtual std::string serialize() const = 0;
};

///////////////////////////////////////////////////////////////////////////////

// - definuje p�r kl�� (�et�zec) a hodnota (JSON hodnota) pro reprezentaci hodnot JSON objektu
class DLL_SPEC KeyValuePair {
	std::string key;
	Value* value;
public:
	KeyValuePair();
	KeyValuePair(std::string key, Value* value);
	~KeyValuePair();

	// - vr�t� kl��
	std::string getKey() const;
	// - vr�t� hodnotu
	Value* getValue() const;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON null
class DLL_SPEC NullValue :
	public Value
{
public:
	NullValue() = default;
	~NullValue() = default;
	NullValue(const NullValue&) = delete;
	NullValue(NullValue&&) noexcept = delete;
	NullValue& operator=(const NullValue&) = delete;
	NullValue& operator=(NullValue&&) = delete;

	bool operator==(const NullValue& other) const;

	std::string serialize() const;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON bool
class DLL_SPEC BoolValue :
	public Value
{
	bool value;
public:
	BoolValue(bool value);
	~BoolValue() = default;

	// - vrac� bool hodnotu
	bool get() const;
	std::string serialize() const;

	static BoolValue deserialize(const std::string& value);
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON ��slo
class DLL_SPEC NumberValue :
	public Value
{
	double value;
public:
	NumberValue(double value);
	~NumberValue() = default;

	// - vrac� ��selnou hodnotu
	double get() const;
	std::string serialize() const;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON �et�zec (string)
class DLL_SPEC StringValue :
	public Value
{
	std::string value;
public:
	StringValue(std::string value);
	~StringValue() = default;

	// - vrac� �et�zcovou hodnotu
	std::string get() const;
	std::string serialize() const;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON pole
class DLL_SPEC ArrayValue :
	public Value
{
public:
	ArrayValue();
	~ArrayValue();

	// - p�id� element na konec pole
	void append(Value* element);
	std::string serialize() const;
	DynamicArray<Value*>* getValues() const;

private:
	// - atribut DynamicArray<Value*> pro uchov�n� jednotliv�ch element� v poli
	DynamicArray<Value*>* arrayValue{};
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON objekt
class DLL_SPEC ObjectValue :
	public Value
{
public:

	ObjectValue();
	~ObjectValue();

	// - p�id� kl��-element do objektu
	void append(const KeyValuePair& pair);
	std::string serialize() const;
	DynamicArray<KeyValuePair>* getValues() const;

private:
	// - atribut DynamicArray<KeyValuePair> pro uchov�n� jednotliv�ch hodnot a kl��� v objektu
	DynamicArray<KeyValuePair>* objectValue{};
};

///////////////////////////////////////////////////////////////////////////////

// - t��da pro pr�ci s JSON
class DLL_SPEC JSON
{
	static bool validate(const std::string& input);
	static bool matchingChar(std::string& input, char c, int pos);
	static bool isNumber(char c);
	static bool isReplaced(char c);
	static void trim(std::string& input);
	static int parseNullOrBool(std::string& input, char valueType, int pos, DynamicArray<string>& keys, DynamicArray<KeyValuePair>& values, DynamicArray<Value*>& arrayValues);
	static int parseNumber(std::string& input, char valueType, int pos, DynamicArray<string>& keys, DynamicArray<KeyValuePair>& values, DynamicArray<Value*>& arrayValues);
	static int parseValues(std::string& input, int pos, Value* value);
public:
	JSON() = default;
	~JSON() = default;
	// - provede deserializaci �et�zce na vytvo�en� objekty
	// - p�e�tu znak a rozhodnu se
	// -- '{' - za��n�m ��st objekt
	// -------- �tu znaky, pak mus� b�t dvojte�ka, potom vol�m rekurzivn� deserialize(); n�sleduje ��rka nebo '}', podle situace se �ten� opakuje
	// -- '[' - za��n�m ��st pole
	// -------- vol�m rekurzivn� deserialize(); n�sleduje ��rka nebo ']', podle situace se �ten� opakuje
	// -- '"' - za��n�m ��st �et�zec - pozor na escapovan� uvozovky
	// -- [-0123456789] - za��n�m ��st ��slo - na�tu v�echny ��slice (pozor na mo�nou desetinnou te�ku)
	// -- 'n' - 'null'
	// -- 't' - 'true'
	// -- 'f' - 'false'
	// -- cokoliv jin�ho - vyvol�v�m v�jimku
	// - nen� p��pustn� vracet nullptr
	// - deserializace mus� b�t rozumn� implementov�na - nen� p��pustn� zde napsat jednu extr�mn� dlouhou metodu
	static Value* deserialize(const std::string& string);

	// - provede serializaci do JSON �et�zce
	static std::string serialize(const Value* value);
	static void escape(const std::string input, std::ostringstream& output);
	static Value* getValueByKey(string key, Value* value);
};

///////////////////////////////////////////////////////////////////////////////

#endif // !API_H