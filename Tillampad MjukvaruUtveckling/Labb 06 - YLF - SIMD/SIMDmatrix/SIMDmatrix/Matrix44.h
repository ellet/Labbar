#pragma once
#include <array>
#include <intrin.h>

template<typename TYPE>
class Matrix44
{
public:     // Constant to avoid using magic numbers
			//
	static const unsigned int   NumRows = 4,
		NumColumns = 4,
		NumElements = NumRows * NumColumns;

	// Initializes the matrix to the identity matrix
	//
	Matrix44()
	{
		for (unsigned int y = 0; y < NumRows; y++)
		{
			for (unsigned int x = 0; x < NumColumns; x++)
			{
				Read(y, x) = static_cast<TYPE>(x == y ? 1 : 0);
			}
		}
	}

	// Initializes the matrix with the data from anOther
	//
	Matrix44(const Matrix44 &anOther)
	{
		myMatrix = anOther.myMatrix;
	}

	// Initializes the matrix with the static_cast'ed data from anOther
	//
	template<typename U>
	Matrix44(const Matrix44<U> &anOther)
	{
		for (unsigned int y = 0; y < NumRows; y++)
		{
			for (unsigned int x = 0; x < NumColumns; x++)
			{
				Read(y, x) = static_cast<U>(anOther.Read(y, x));
			}
		}
	}

	// Initializes the matrix with the data from an array
	//
	Matrix44(const TYPE(&anArray)[NumElements])
	{
		for (int i = 0; i < NumElements; i++)
		{
			myMatrix[i] = anArray[i];
		}
	}

	// Initializes the matrix with plain values
	//
	Matrix44(
		const TYPE a11, const TYPE a12, const TYPE a13, const TYPE a14,
		const TYPE a21, const TYPE a22, const TYPE a23, const TYPE a24,
		const TYPE a31, const TYPE a32, const TYPE a33, const TYPE a34,
		const TYPE a41, const TYPE a42, const TYPE a43, const TYPE a44)
	{
		myMatrix[0] = a11;
		myMatrix[1] = a12;
		myMatrix[2] = a13;
		myMatrix[3] = a14;


		myMatrix[4] = a21;
		myMatrix[5] = a22;
		myMatrix[6] = a23;
		myMatrix[7] = a24;

		myMatrix[8] = a31;
		myMatrix[9] = a32;
		myMatrix[10] = a33;
		myMatrix[11] = a34;

		myMatrix[12] = a41;
		myMatrix[13] = a42;
		myMatrix[14] = a43;
		myMatrix[15] = a44;
	}

	// Adds and assigns the values of aRight to this matrix
	//
	Matrix44 &operator +=(const Matrix44 &aRight)
	{
		for (int i = 0; i < NumElements; i++)
		{
			myMatrix[i] += aRight.myMatrix[i];
		}
		return *this;
	}

	// Subtract and assigns the values of aRight to this matrix
	//
	Matrix44 &operator -=(const Matrix44 &aRight)
	{
		for (int i = 0; i < NumElements; i++)
		{
			myMatrix[i] -= aRight.myMatrix[i];
		}
		return *this;
	}

	// Multiplies this matrix with aRight
	//
	Matrix44 &operator *=(const Matrix44 &aRight)
	{
		*this = *this * aRight;
		return *this;
	}

	// Sets the values of this matrix to those of aRight
	//
	Matrix44 &operator =(const Matrix44 &aRight)
	{
		myMatrix = aRight.myMatrix;
		return *this;
	}

	// Returns a transposed copy of this matrix
	//
	Matrix44 &Transpose()
	{
		Matrix44 copy = *this;
		for (int y = 0; y < NumRows; y++)
		{
			for (int x = 0; x < NumColumns; x++)
			{
				Read(y, x) = copy.Read(x, y);
			}
		}
		return *this;
	}

	Matrix44 GetInverse() const
	{
		Matrix44 inverse = *this;
		inverse.SetPosition(Vector3f::Zero);
		inverse.Transpose();
		Vector4<TYPE> position = Vector4<TYPE>(-GetPosition(), 1.f);
		position = position * inverse;
		inverse.SetPosition(position);
		return inverse;
	}

	static Matrix44 CreateTranslation(const TYPE x, const TYPE y, const TYPE z)
	{
		return Matrix44(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1
		);
	}

	static Matrix44 CreateScale(const TYPE x, const TYPE y, const TYPE z)
	{
		return Matrix44(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		);
	}

	static Matrix44 CreateProjection(float aFovInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane)
	{
		Matrix44 temp;
		TYPE    SinFov;
		TYPE    CosFov;
		TYPE    Height;
		TYPE    Width;

		float aAspectRatio = aProjectionWidth / aProjectionHeight;

		SinFov = sin(0.5f * (aFovInDegrees / 180.f * Pi));
		CosFov = cos(0.5f * (aFovInDegrees / 180.f * Pi));

		Height = CosFov / SinFov;
		Width = Height / aAspectRatio;

		TYPE scaling = aFarPlane / (aFarPlane - aNearPlane);

		temp.myMatrix[0] = Width;
		temp.myMatrix[5] = Height;
		temp.myMatrix[10] = scaling;
		temp.myMatrix[11] = 1.f;
		temp.myMatrix[14] = -scaling * aNearPlane;
		temp.myMatrix[15] = 0;

		return temp;
	}

	// Creates a transformation matrix for rotating anAngle rad around the x-axis
	//
	static Matrix44 CreateRotateAroundX(const TYPE anAngle);

	// Creates a transformation matrix for rotating anAngle rad around the y-axis
	//
	static Matrix44 CreateRotateAroundY(const TYPE anAngle);

	// Creates a transformation matrix for rotating anAngle rad around the z-axis
	//
	static Matrix44 CreateRotateAroundZ(const TYPE anAngle);

	// Returns a transposed copy of aMatrix
	//
	static Matrix44 Transpose(Matrix44 aMatrix)
	{
		return aMatrix.Transpose();
	}

	inline void MulSIMD(const Matrix44 &aLeft, const Matrix44&aRight)
	{
		Matrix44 newMatrix;

		__m128 firstRowLeft = _mm_set_ps(aLeft.m14, aLeft.m13, aLeft.m12, aLeft.m11);
		__m128 secondRowLeft = _mm_set_ps(aLeft.m24, aLeft.m23, aLeft.m22, aLeft.m21);
		__m128 thirdRowLeft = _mm_set_ps(aLeft.m34, aLeft.m33, aLeft.m32, aLeft.m31);
		__m128 fourthRowLeft = _mm_set_ps(aLeft.m44, aLeft.m43, aLeft.m42, aLeft.m41);

		__m128 firstColumnLeft = _mm_set_ps(aRight.m41, aRight.m31, aRight.m21, aRight.m11);
		__m128 secondColumnLeft = _mm_set_ps(aRight.m42, aRight.m32, aRight.m22, aRight.m12);
		__m128 thirdColumnLeft = _mm_set_ps(aRight.m43, aRight.m33, aRight.m23, aRight.m13);
		__m128 fourthColumnLeft = _mm_set_ps(aRight.m44, aRight.m34, aRight.m24, aRight.m14);

		__m128 multResultm11 = _mm_mul_ps(firstRowLeft, firstColumnLeft);
		__m128 multResultm12 = _mm_mul_ps(firstRowLeft, secondColumnLeft);
		__m128 multResultm13 = _mm_mul_ps(firstRowLeft, thirdColumnLeft);
		__m128 multResultm14 = _mm_mul_ps(firstRowLeft, fourthColumnLeft);
		
		__m128 multResultm21 = _mm_mul_ps(secondRowLeft, firstColumnLeft);
		__m128 multResultm22 = _mm_mul_ps(secondRowLeft, secondColumnLeft);
		__m128 multResultm23 = _mm_mul_ps(secondRowLeft, thirdColumnLeft);
		__m128 multResultm24 = _mm_mul_ps(secondRowLeft, fourthColumnLeft);
		
		__m128 multResultm31 = _mm_mul_ps(thirdRowLeft, firstColumnLeft);
		__m128 multResultm32 = _mm_mul_ps(thirdRowLeft, secondColumnLeft);
		__m128 multResultm33 = _mm_mul_ps(thirdRowLeft, thirdColumnLeft);
		__m128 multResultm34 = _mm_mul_ps(thirdRowLeft, fourthColumnLeft);
		
		__m128 multResultm41 = _mm_mul_ps(fourthRowLeft, firstColumnLeft);
		__m128 multResultm42 = _mm_mul_ps(fourthRowLeft, secondColumnLeft);
		__m128 multResultm43 = _mm_mul_ps(fourthRowLeft, thirdColumnLeft);
		__m128 multResultm44 = _mm_mul_ps(fourthRowLeft, fourthColumnLeft);

		float placementResultm11[4];
		_mm_storeu_ps(placementResultm11, multResultm11);
		newMatrix.m11 = placementResultm11[0] + placementResultm11[1] + placementResultm11[2] + placementResultm11[3];

		float placementResultm12[4];
		_mm_storeu_ps(placementResultm12, multResultm12);
		newMatrix.m12 = placementResultm12[0] + placementResultm12[1] + placementResultm12[2] + placementResultm12[3];

		float placementResultm13[4];
		_mm_storeu_ps(placementResultm13, multResultm13);
		newMatrix.m13 = placementResultm13[0] + placementResultm13[1] + placementResultm13[2] + placementResultm13[3];

		float placementResultm14[4];
		_mm_storeu_ps(placementResultm14, multResultm14);
		newMatrix.m14 = placementResultm14[0] + placementResultm14[1] + placementResultm14[2] + placementResultm14[3];

		float placementResultm21[4];
		_mm_storeu_ps(placementResultm21, multResultm21);
		newMatrix.m21 = placementResultm21[0] + placementResultm21[1] + placementResultm21[2] + placementResultm21[3];

		float placementResultm22[4];
		_mm_storeu_ps(placementResultm22, multResultm22);
		newMatrix.m22 = placementResultm22[0] + placementResultm22[1] + placementResultm22[2] + placementResultm22[3];

		float placementResultm23[4];
		_mm_storeu_ps(placementResultm23, multResultm23);
		newMatrix.m23 = placementResultm23[0] + placementResultm23[1] + placementResultm23[2] + placementResultm23[3];

		float placementResultm24[4];
		_mm_storeu_ps(placementResultm24, multResultm24);
		newMatrix.m24 = placementResultm24[0] + placementResultm24[1] + placementResultm24[2] + placementResultm24[3];

		float placementResultm31[4];
		_mm_storeu_ps(placementResultm31, multResultm31);
		newMatrix.m31 = placementResultm31[0] + placementResultm31[1] + placementResultm31[2] + placementResultm31[3];

		float placementResultm32[4];
		_mm_storeu_ps(placementResultm32, multResultm32);
		newMatrix.m32 = placementResultm32[0] + placementResultm32[1] + placementResultm32[2] + placementResultm32[3];

		float placementResultm33[4];
		_mm_storeu_ps(placementResultm33, multResultm33);
		newMatrix.m33 = placementResultm33[0] + placementResultm33[1] + placementResultm33[2] + placementResultm33[3];

		float placementResultm34[4];
		_mm_storeu_ps(placementResultm34, multResultm34);
		newMatrix.m34 = placementResultm34[0] + placementResultm34[1] + placementResultm34[2] + placementResultm34[3];

		float placementResultm41[4];
		_mm_storeu_ps(placementResultm41, multResultm41);
		newMatrix.m41 = placementResultm41[0] + placementResultm41[1] + placementResultm41[2] + placementResultm41[3];

		float placementResultm42[4];
		_mm_storeu_ps(placementResultm42, multResultm42);
		newMatrix.m42 = placementResultm42[0] + placementResultm42[1] + placementResultm42[2] + placementResultm42[3];

		float placementResultm43[4];
		_mm_storeu_ps(placementResultm43, multResultm43);
		newMatrix.m43 = placementResultm43[0] + placementResultm43[1] + placementResultm43[2] + placementResultm43[3];

		float placementResultm44[4];
		_mm_storeu_ps(placementResultm44, multResultm44);
		newMatrix.m44 = placementResultm44[0] + placementResultm44[1] + placementResultm44[2] + placementResultm44[3];

		*this = newMatrix;

	}

	// The data of this matrix
	//
#pragma warning( disable : 4201 ) // NOTE: This works fine in VC2013 and GCC so I'm keeping it. //MAHAM
	union __declspec(align(16))
	{
		struct
		{
			TYPE    m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
		};

		std::array<TYPE, NumElements> myMatrix;
	};

	// Pre-created identity matrix
	//
	static const Matrix44   Identity,
		Zero;

	__forceinline TYPE &Read(const int aRow, const int aColumn)
	{
		return myMatrix[aRow * NumColumns + aColumn];
	}
	__forceinline TYPE Read(const int aRow, const int aColumn) const
	{
		return myMatrix[aRow * NumColumns + aColumn];
	}

	bool Inverse()
	{
		// From http://stackoverflow.com/a/1148405

		float * m = &myMatrix[0];

		float inv[16], det;
		float invOut[16];
		int i;

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0.f)
			return false;

		det = 1.f / det;

		for (i = 0; i < 16; i++)
			invOut[i] = inv[i] * det;

		memcpy(&myMatrix[0], invOut, sizeof(invOut));

		return true;
	}
};

template <typename TYPE>
const Matrix44<TYPE> Matrix44<TYPE>::Zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
template <typename TYPE>
const Matrix44<TYPE> Matrix44<TYPE>::Identity;

template <typename TYPE>
Matrix44<TYPE> Matrix44<TYPE>::CreateRotateAroundX(const TYPE anAngle)
{
	TYPE sin = static_cast<TYPE>(std::sin(anAngle));
	TYPE cos = static_cast<TYPE>(std::cos(anAngle));
	return Matrix44(1, 0, 0, 0,
		0, cos, sin, 0,
		0, -sin, cos, 0,
		0, 0, 0, 1);
}

template <typename TYPE>
Matrix44<TYPE> Matrix44<TYPE>::CreateRotateAroundY(const TYPE anAngle)
{
	TYPE sin = static_cast<TYPE>(std::sin(anAngle));
	TYPE cos = static_cast<TYPE>(std::cos(anAngle));
	return Matrix44(cos, 0, -sin, 0,
		0, 1, 0, 0,
		sin, 0, cos, 0,
		0, 0, 0, 1);
}

template <typename TYPE>
Matrix44<TYPE> Matrix44<TYPE>::CreateRotateAroundZ(const TYPE anAngle)
{
	TYPE sin = static_cast<TYPE>(std::sin(anAngle));
	TYPE cos = static_cast<TYPE>(std::cos(anAngle));
	return Matrix44(cos, sin, 0, 0,
		-sin, cos, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

using Matrix44f = Matrix44 < float >;

// Returns a new matrix which is the sum of aLeft and aRight
//
template<typename TYPE>
Matrix44<TYPE> operator +(Matrix44<TYPE> aLeft, const Matrix44<TYPE> &aRight)
{
	return aLeft += aRight;
}

// Returns a new matrix wich is the difference of aLeft and aRight
//
template<typename TYPE>
Matrix44<TYPE> operator -(Matrix44<TYPE> aLeft, const Matrix44<TYPE> &aRight)
{
	return aLeft -= aRight;
}

// Returns a new matrix which is the product of aLeft and aRight
//
template<typename TYPE>
Matrix44<TYPE> operator *(const Matrix44<TYPE> &aLeft, const Matrix44<TYPE> &aRight)
{
	Matrix44<TYPE> newMatrix;
	const unsigned int numRows = 4;
	const unsigned int numColumns = 4;
	for (unsigned int i = 0; i < numRows; i++)
	{
		for (unsigned int j = 0; j < numColumns; j++)
		{
			newMatrix.Read(i, j) = static_cast<TYPE>(0);
			for (unsigned int k = 0; k < 4; k++)
			{
				newMatrix.Read(i, j) += aLeft.Read(i, k) * aRight.Read(k, j);
			}
		}
	}
	return newMatrix;
}

// Compares aLeft and aRight componentwise
//
template<typename TYPE>
bool operator ==(const Matrix44<TYPE> &aLeft, const Matrix44<TYPE> &aRight)
{
	return aLeft.myMatrix == aRight.myMatrix;
}

// Returns the negated result of aLeft == aRight
//
template<typename TYPE>
bool operator !=(const Matrix44<TYPE> &aLeft, const Matrix44<TYPE> &aRight)
{
	return (aLeft == aRight) == false;
}
