#ifndef ARRAY_2D_H
#define ARRAY_2D_H

#include <stdexcept>
#include <iostream>
#include <string>
#include <type_traits>

template<typename T>
class Array2D
{
	static_assert(std::is_floating_point<T>::value || std::is_same<T, int>::value || std::is_same<T, long>::value, "Can only be of numeric type!");

	T** array2D;
	int rows;
	int columns;

public:
	// inicializuje matici hodnotami 0
	Array2D(int rows, int columns);

	// vytvoří matici jako kopii jiné (vytvoří hlubokou kopii)
	Array2D(const Array2D<T>& array2D);
	~Array2D();
	
	void PutAt(int row, int column, T value);

	// nastaví všechny buňky podle vybraného jednorozměrného pole(předpokládejte,
	// že rozměr pole je správný; hodnoty v poli jsou uloženy postupně po řádcích)
	void PutFrom(T* array);

	// pro přístup k buňkám realizujte metody (přístup na neplatný index vyvolá výjimku):	
	T& GetAt(int row, int column);
	const T& GetAt(int row, int column) const;

	// metoda vytvoří novou matici požadovaného typu o stejných
	// rozměrech jako původní matice a převede všechny hodnoty na cílový typ do nové matice
	template<typename R>
	Array2D<R> Cast() const;

	// Operace vždy vytvářejí novou matici a nemění aktuální objekt
	Array2D<T> Transpose() const;
	Array2D<T> Multiplication(const Array2D& matrix) const;
	Array2D<T> Multiplication(T skalar) const;
	Array2D<T> Addition(const Array2D& matrix) const;
	Array2D<T> Addition(T skalar) const;

	// pro porovnání shody dvou matic vytvořte metodu
	bool IsEqual(const Array2D& m) const;

	void Print() const;
};

#endif // !ARRAY_2D_H

template<typename T>
inline Array2D<T>::Array2D(int rows, int columns)
{
	if (rows <= 0 || columns <= 0)
	{
		throw std::invalid_argument("Number of rows and columns must be bigger than 0!");
	}

	this->rows = rows;
	this->columns = columns;
	array2D = new T * [rows];

	for (int i = 0; i < rows; i++)
	{
		array2D[i] = new T[columns];
		for (int j = 0; j < columns; j++)
		{
			array2D[i][j] = 0;
		}
	}
}

template<typename T>
inline Array2D<T>::Array2D(const Array2D<T>& matrix)
{
	rows = matrix.rows;
	columns = matrix.columns;
	this->array2D = new T * [rows];

	for (int i = 0; i < rows; i++)
	{
		this->array2D[i] = new T[columns];
		for (int j = 0; j < columns; j++)
		{
			this->array2D[i][j] = matrix.array2D[i][j];
		}
	}
}

template<typename T>
inline Array2D<T>::~Array2D()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] array2D[i];
	}

	delete[] array2D;	
}

template<typename T>
inline void Array2D<T>::PutAt(int row, int column, T value)
{
	if (row < 0 || row > rows || column < 0 || column > columns)
	{
		throw std::out_of_range("Given position is out of range of array!");
	}

	array2D[row][column] = value;
}

template<typename T>
inline void Array2D<T>::PutFrom(T* array)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			array2D[i][j] = array[(i * columns) + j];
		}
	}
}

template<typename T>
inline T& Array2D<T>::GetAt(int row, int column)
{
	if (row < 0 || row > rows || column < 0 || column > columns)
	{
		throw std::out_of_range("Given position is out of range of array!");
	}

	return array2D[row][column];
}

template<typename T>
inline const T& Array2D<T>::GetAt(int row, int column) const
{
	if (row < 0 || row > rows || column < 0 || column > columns)
	{
		throw std::out_of_range("Given position is out of range of array!");
	}

	return array2D[row][column];
}

template<typename T>
inline Array2D<T> Array2D<T>::Transpose() const
{
	Array2D<T> newArray2D{ rows, columns };

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			newArray2D.array2D[i][j] = array2D[j][i];
		}
	}

	return newArray2D;
}

template<typename T>
inline Array2D<T> Array2D<T>::Multiplication(const Array2D& matrix) const
{
	if (columns != matrix.rows)
	{
		throw std::invalid_argument("Number of rows and columns must be bigger than 0!");
	}

	Array2D<T> newArray2D{ rows, columns };	

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < matrix.rows; j++)
		{
			T temp = 0;

			for (int k = 0; k < matrix.columns; k++)
			{
				temp += array2D[i][k] * matrix.array2D[k][j];
			}

			newArray2D.array2D[i][j] = temp;
		}
	}

	return newArray2D;
}

template<typename T>
inline Array2D<T> Array2D<T>::Multiplication(T skalar) const
{
	Array2D<T> newArray2D{ rows, columns };

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			newArray2D.array2D[i][j] = array2D[i][j] * skalar;
		}
	}

	return newArray2D;
}

template<typename T>
inline Array2D<T> Array2D<T>::Addition(const Array2D& matrix) const
{
	if (rows != matrix.rows || columns != matrix.columns)
	{
		throw std::invalid_argument("Arrays must be of the same size!");
	}

	Array2D<T> newArray2D{ rows, columns };

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			newArray2D.array2D[i][j] = matrix.array2D[i][j] + array2D[i][j];
		}
	}

	return newArray2D;
}

template<typename T>
inline Array2D<T> Array2D<T>::Addition(T skalar) const
{
	Array2D<T> newArray2D{ rows, columns };

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			newArray2D.array2D[i][j] = array2D[i][j] + skalar;
		}
	}

	return newArray2D;
}

template<typename T>
inline bool Array2D<T>::IsEqual(const Array2D& matrix) const
{
	if (rows != matrix.rows || columns != matrix.columns)
	{
		return false;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (array2D[i][j] != matrix.array2D[i][j])
			{
				return false;
			}
		}
	}

	return true;

}

template<typename T>
inline void Array2D<T>::Print() const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << std::to_string(array2D[i][j]) << "\t";
		}

		std::cout << std::endl;
	}

}

template<typename T>
template<typename R>
inline Array2D<R> Array2D<T>::Cast() const
{
	Array2D<R> newArray2D{ rows, columns };

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			newArray2D.PutAt(i, j, static_cast<R>(GetAt(i, j)));
		}
	}

	return newArray2D;
}
