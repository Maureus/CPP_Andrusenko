#ifndef API_H
#define API_H

#include "platform.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

// - šablona s parametrem datového typu uložených hodnot
// - není povoleno užití STL kontejnerù ani jiných knihoven pro ukládání dat
// - realizace musí využívat dynamicky alokované pole, spojový seznam nebo jinou vhodnou Vámi implementovanou ADS
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

	// - pøidá element na konec pole
	void append(const T& element)
	{
		if (!HasEmptySpace())
		{
			Expand();
		}
		array[numberOfElements++] = element;
	}

	// - výjimky pøi neplatném nebo nekorektním indexu
	const T& getElementAt(int index) const
	{
		if (index < 0 || index >= numberOfElements)
		{
			throw out_of_range("Index is out of range!");
		}

		return array[index];
	}

	// - vrací velikost (poèet prvkù) v poli
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

// JSON hodnota - reprezentuje abstraktního pøedka pro základní datové typy v JSON (string, number, object, array, bool, null)
class DLL_SPEC Value
{
public:
	Value() = default;
	virtual ~Value() = default;

	// serializuje hodnotu do podoby JSON reprezentace
	virtual std::string serialize() const = 0;
};

///////////////////////////////////////////////////////////////////////////////

// - definuje pár klíè (øetìzec) a hodnota (JSON hodnota) pro reprezentaci hodnot JSON objektu
class DLL_SPEC KeyValuePair {
	std::string key;
	Value* value;
public:
	KeyValuePair();
	KeyValuePair(std::string key, Value* value);
	~KeyValuePair();

	// - vrátí klíè
	std::string getKey() const;
	// - vrátí hodnotu
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

	// - vrací bool hodnotu
	bool get() const;
	std::string serialize() const;

	static BoolValue deserialize(const std::string& value);
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON èíslo
class DLL_SPEC NumberValue :
	public Value
{
	double value;
public:
	NumberValue(double value);
	~NumberValue() = default;

	// - vrací èíselnou hodnotu
	double get() const;
	std::string serialize() const;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON øetìzec (string)
class DLL_SPEC StringValue :
	public Value
{
	std::string value;
public:
	StringValue(std::string value);
	~StringValue() = default;

	// - vrací øetìzcovou hodnotu
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

	// - pøidá element na konec pole
	void append(Value* element);
	std::string serialize() const;
	DynamicArray<Value*>* getValues() const;

private:
	// - atribut DynamicArray<Value*> pro uchování jednotlivých elementù v poli
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

	// - pøidá klíè-element do objektu
	void append(const KeyValuePair& pair);
	std::string serialize() const;
	DynamicArray<KeyValuePair>* getValues() const;

private:
	// - atribut DynamicArray<KeyValuePair> pro uchování jednotlivých hodnot a klíèù v objektu
	DynamicArray<KeyValuePair>* objectValue{};
};

///////////////////////////////////////////////////////////////////////////////

// - tøída pro práci s JSON
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
	// - provede deserializaci øetìzce na vytvoøené objekty
	// - pøeètu znak a rozhodnu se
	// -- '{' - zaèínám èíst objekt
	// -------- ètu znaky, pak musí být dvojteèka, potom volám rekurzivnì deserialize(); následuje èárka nebo '}', podle situace se ètení opakuje
	// -- '[' - zaèínám èíst pole
	// -------- volám rekurzivnì deserialize(); následuje èárka nebo ']', podle situace se ètení opakuje
	// -- '"' - zaèínám èíst øetìzec - pozor na escapované uvozovky
	// -- [-0123456789] - zaèínám èíst èíslo - naètu všechny èíslice (pozor na možnou desetinnou teèku)
	// -- 'n' - 'null'
	// -- 't' - 'true'
	// -- 'f' - 'false'
	// -- cokoliv jiného - vyvolávám výjimku
	// - není pøípustné vracet nullptr
	// - deserializace musí být rozumnì implementována - není pøípustné zde napsat jednu extrémnì dlouhou metodu
	static Value* deserialize(const std::string& string);

	// - provede serializaci do JSON øetìzce
	static std::string serialize(const Value* value);
	static void escape(const std::string input, std::ostringstream& output);
	static Value* getValueByKey(string key, Value* value);
};

///////////////////////////////////////////////////////////////////////////////

#endif // !API_H