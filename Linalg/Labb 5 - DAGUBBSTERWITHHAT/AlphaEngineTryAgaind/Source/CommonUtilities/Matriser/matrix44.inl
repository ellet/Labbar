
template<typename T>
Matrix44<T>::Matrix44(void)
{
	m11 = static_cast<T>(1);
	m12 = static_cast<T>(0);
	m13 = static_cast<T>(0);
	m14 = static_cast<T>(0);
	
	m21 = static_cast<T>(0);
	m22 = static_cast<T>(1);
	m23 = static_cast<T>(0);
	m24 = static_cast<T>(0);

	m31 = static_cast<T>(0);
	m32 = static_cast<T>(0);
	m33 = static_cast<T>(1);
	m34 = static_cast<T>(0);

	m41 = static_cast<T>(0);
	m42 = static_cast<T>(0);
	m43 = static_cast<T>(0);
	m44 = static_cast<T>(1);

}

template<typename T>
template<typename U>
Matrix44<T>::Matrix44(const Matrix44<U> &anOther)
{
	m11 = static_cast<T>(anOther.m11);
	m12 = static_cast<T>(anOther.m12);
	m13 = static_cast<T>(anOther.m13);
	m14 = static_cast<T>(anOther.m14);

	m21 = static_cast<T>(anOther.m21);
	m22 = static_cast<T>(anOther.m22);
	m23 = static_cast<T>(anOther.m23);
	m24 = static_cast<T>(anOther.m24);

	m31 = static_cast<T>(anOther.m31);
	m32 = static_cast<T>(anOther.m32);
	m33 = static_cast<T>(anOther.m33);
	m34 = static_cast<T>(anOther.m34);

	m41 = static_cast<T>(anOther.m41);
	m42 = static_cast<T>(anOther.m42);
	m43 = static_cast<T>(anOther.m43);
	m44 = static_cast<T>(anOther.m44);
}

template<typename T>
Matrix44<T>::Matrix44(const T(&anArray)[NumElements])
{
	for (size_t iArraySlot = 0; iArraySlot < NumElements; ++iArraySlot)
	{
		myMatrix[iArraySlot] = anArray[iArraySlot];
	}
}

template<typename T>
Matrix44<T>::Matrix44(
	const T a11, const T a12, const T a13, const T a14,
	const T a21, const T a22, const T a23, const T a24,
	const T a31, const T a32, const T a33, const T a34,
	const T a41, const T a42, const T a43, const T a44)
{
	m11 = a11;
	m12 = a12;
	m13 = a13;
	m14 = a14;

	m21 = a21;
	m22 = a22;
	m23 = a23;
	m24 = a24;

	m31 = a31;
	m32 = a32;
	m33 = a33;
	m34 = a34;

	m41 = a41;
	m42 = a42;
	m43 = a43;
	m44 = a44;
}


template<typename T>
Matrix44<T> & Matrix44<T>::operator +=(const Matrix44 &aRight)
{
	for (size_t iArraySlot = 0; iArraySlot < NumElements; ++iArraySlot)
	{
		myMatrix[iArraySlot] += aRight.myMatrix[iArraySlot];
	}

	return (*this);
}

template<typename T>
Matrix44<T> & Matrix44<T>::operator -=(const Matrix44 &aRight)
{
	for (size_t iArraySlot = 0; iArraySlot < NumElements; ++iArraySlot)
	{
		myMatrix[iArraySlot] -= aRight.myMatrix[iArraySlot];
	}

	return (*this);
}


template<typename T>
Matrix44<T> & Matrix44<T>::operator *=(const Matrix44 &aRight)
{
	
	std::array<T, NumElements> tempMatrix;

	for (size_t iRowPos = 0; iRowPos < NumRows; ++iRowPos)
	{
		for (size_t iColumnPos = 0; iColumnPos < NumColumns; ++iColumnPos)
		{
			T result = 0;

			for (size_t iPos = 0; iPos < NumRows; ++iPos)
			{
				result += (*this)(iPos + 1, iColumnPos + 1) * (*this)((iRowPos + 1), iPos + 1);
			}

			tempMatrix[((iColumnPos * NumColumns) + iRowPos)] = result;
		}
	}

	myMatrix = tempMatrix;

	return (*this);
}

template<typename T>
T& Matrix44<T>::operator()(const size_t aRow, const size_t aColumn)
{
	return myMatrix[(((aColumn -1) * NumColumns) + (aRow -1))];
}

template<typename T>
Matrix44<T> & Matrix44<T>::Transpose(void)
{
	std::array<T, NumElements> tempMatrix;

	for (size_t iColumnPos = 0; iColumnPos < NumColumns; ++iColumnPos)
	{
		for (size_t iRowPos = 0; iRowPos < NumRows; ++iRowPos)
		{

			tempMatrix[((iColumnPos * NumColumns) + iRowPos)] = (*this)(iColumnPos + 1, iRowPos + 1);
		}
	}

	myMatrix = tempMatrix;

	return (*this);
}


template<typename T>
Matrix44<T> Matrix44<T>::CreateRotateAroundX(const T anAngle)
{
	return Matrix44(
		static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(cos(anAngle)), static_cast<T>(sin(anAngle)), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(-sin(anAngle)), static_cast<T>(cos(anAngle)), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}

template<typename T>
Matrix44<T> Matrix44<T>::CreateRotateAroundY(const T anAngle)
{
	return Matrix44(
		static_cast<T>(cos(anAngle)), static_cast<T>(0), static_cast<T>(-sin(anAngle)), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(sin(anAngle)), static_cast<T>(0), static_cast<T>(cos(anAngle)), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}

template<typename T>
Matrix44<T> Matrix44<T>::CreateRotateAroundZ(const T anAngle)
{
	return Matrix44(
		static_cast<T>(cos(anAngle)), static_cast<T>(sin(anAngle)), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(-sin(anAngle)), static_cast<T>(cos(anAngle)), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) );
}

template<typename T>
Matrix44<T> Matrix44<T>::Transpose(Matrix44 aMatrix)
{
	Matrix44 copy(aMatrix);

	return copy.Transpose();
}

template<typename T>
Matrix44<T>::Matrix44(const Matrix33<T> &anOther)
{
	m11 = static_cast<T>(1);
	m12 = static_cast<T>(0);
	m13 = static_cast<T>(0);
	m14 = static_cast<T>(0);

	m21 = static_cast<T>(0);
	m22 = static_cast<T>(1);
	m23 = static_cast<T>(0);
	m24 = static_cast<T>(0);

	m31 = static_cast<T>(0);
	m32 = static_cast<T>(0);
	m33 = static_cast<T>(1);
	m34 = static_cast<T>(0);

	m41 = static_cast<T>(0);
	m42 = static_cast<T>(0);
	m43 = static_cast<T>(0);
	m44 = static_cast<T>(1);

	m11 = anOther.m11;
	m12 = anOther.m12;
	m13 = anOther.m13;

	m21 = anOther.m21;
	m22 = anOther.m22;
	m23 = anOther.m23;

	m31 = anOther.m31;
	m32 = anOther.m32;
	m33 = anOther.m33;
}