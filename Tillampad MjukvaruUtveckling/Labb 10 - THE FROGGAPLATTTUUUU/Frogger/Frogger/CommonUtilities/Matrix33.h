#ifndef MATRIX33_H
#define MATRIX33_H

#include "stdafx.h"
#include "math.h"
#include "Vector3.h"
#include "StaticArray.h"

namespace CommonUtilities
{
	template <typename T>
	class Matrix33
	{
	public:
		Matrix33();
		Matrix33(const Matrix33<T>& aMatrixToCopy);
		Matrix33(
			const T& aXX, const T& aXY, const T& aXZ, 
			const T& aYX, const T& aYY, const T& aYZ, 
			const T& aZX, const T& aZY, const T& aZZ);
		~Matrix33();

		void Set(
			const T& aXX, const T& aXY, const T& aXZ, 
			const T& aYX, const T& aYY, const T& aYZ, 
			const T& aZX, const T& aZY, const T& aZZ);


		void SetToRoationMatrixX(const T& aRotationInRadians);
		void SetToRoationMatrixY(const T& aRotationInRadians);
		void SetToRoationMatrixZ(const T& aRotationInRadians);

		void RotateX(const T& aRotationInRadians);
		void RotateY(const T& aRotationInRadians);
		void RotateZ(const T& aRotationInRadians);

		void SetToIdentityMatrix();


		Matrix33<T>& Transpose();
		Matrix33<T> GetTranspose();

		//////////////////////////////////////////////////////////////////////////
		//																		//
		//						Operator Overloading							//
		//																		//
		//////////////////////////////////////////////////////////////////////////

		Matrix33<T>& operator=(const Matrix33<T>& aRightHandMatrix);
		Matrix33<T>& operator*=(const T& aNumberToScaleWith);
		Matrix33<T>& operator*=(const Matrix33<T>& aRightHandMatrix);
		Matrix33<T>& operator/=(const T& aNumberToDivideBy);
		
		bool operator==(const Matrix33<T>& aRightHandMatrix);
		bool operator!=(const Matrix33<T>& aRightHandMatrix); 


		T myMatrix[3][3];
	private:
	};

	template <typename T>
	Matrix33<T>::Matrix33()
	{
		SetToIdentityMatrix();
	}

	template <typename T>
	Matrix33<T>::Matrix33(const Matrix33<T>& aMatrixToCopy)
	{
		*this = aMatrixToCopy;
	}

	template <typename T>
	Matrix33<T>::Matrix33(
		const T& aXX, const T& aXY, const T& aXZ, 
		const T& aYX, const T& aYY, const T& aYZ, 
		const T& aZX, const T& aZY, const T& aZZ)
	{
		myMatrix[0][0] = aXX;
		myMatrix[0][1] = aXY;
		myMatrix[0][2] = aXZ;

		myMatrix[1][0] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[1][2] = aYZ;

		myMatrix[2][0] = aZX;
		myMatrix[2][1] = aZY;
		myMatrix[2][2] = aZZ;
	}

	template <typename T>
	Matrix33<T>::~Matrix33()
	{

	}

	template <typename T>
	void Matrix33<T>::Set(
		const T& aXX, const T& aXY, const T& aXZ, 
		const T& aYX, const T& aYY, const T& aYZ, 
		const T& aZX, const T& aZY, const T& aZZ)
	{
		myMatrix[0][0] = aXX;
		myMatrix[0][1] = aXY;
		myMatrix[0][2] = aXZ;

		myMatrix[1][0] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[1][2] = aYZ;

		myMatrix[2][0] = aZX;
		myMatrix[2][1] = aZY;
		myMatrix[2][2] = aZZ;
	}

	template <typename T>
	void Matrix33<T>::SetToIdentityMatrix()
	{
		Set(1,0,0,
			0,1,0,
			0,0,1);
	}

	template <typename T>
	Matrix33<T>& Matrix33<T>::Transpose()
	{
		Matrix33<T> aTempMatrix;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				aTempMatrix.myMatrix[j][i] = myMatrix[i][j];
			}
		}
		*this = aTempMatrix;
		return(*this);
	}

	template <typename T>
	Matrix33<T> Matrix33<T>::GetTranspose()
	{
		Matrix33<T> aTempMatrix = *this;
		aTempMatrix.Transpose();
		return aTempMatrix;
	}

	template <typename T>
	void Matrix33<T>::SetToRoationMatrixX(const T &aRotationInRadians)
	{
		myMatrix[1][1] = cos(aRotationInRadians);
		myMatrix[1][2] = -sin(aRotationInRadians);
		myMatrix[2][1] = sin(aRotationInRadians);
		myMatrix[2][2] = cos(aRotationInRadians);
	}

	template <typename T>
	void Matrix33<T>::SetToRoationMatrixY(const T &aRotationInRadians)
	{
		myMatrix[0][0] = cos(aRotationInRadians);
		myMatrix[0][2] = sin(aRotationInRadians);
		myMatrix[2][0] = -sin(aRotationInRadians);
		myMatrix[2][2] = cos(aRotationInRadians);
	}

	template <typename T>
	void Matrix33<T>::SetToRoationMatrixZ(const T &aRotationInRadians)
	{
		myMatrix[0][0] = cos(aRotationInRadians);
		myMatrix[0][1] = -sin(aRotationInRadians);
		myMatrix[1][0] = sin(aRotationInRadians);
		myMatrix[1][1] = cos(aRotationInRadians);
	}

	template <typename T>
	void Matrix33<T>::RotateX(const T& aRotationInRadians)
	{
		Matrix33<T> aRotationMatrix;
		aRotationMatrix.SetToRoationMatrixX(aRotationInRadians);
		*this *= aRotationMatrix;
	}
	
	template <typename T>
	void Matrix33<T>::RotateY(const T& aRotationInRadians)
	{
		Matrix33<T> aRotationMatrix;
		aRotationMatrix.SetToRoationMatrixY(aRotationInRadians);
		*this *= aRotationMatrix;
	}

	template <typename T>
	void Matrix33<T>::RotateZ(const T& aRotationInRadians)
	{
		Matrix33<T> aRotationMatrix;
		aRotationMatrix.SetToRoationMatrixZ(aRotationInRadians);
		*this *= aRotationMatrix;
	}

	//////////////////////////////////////////////////////////////////////////
	//																		//
	//						Operator Overloading							//
	//																		//
	//////////////////////////////////////////////////////////////////////////

	template <typename T>
	Matrix33<T>& Matrix33<T>::operator =(const Matrix33<T>& aRightHandMatrix)
	{
		for(unsigned int rowCounter = 0; rowCounter < 3; rowCounter++)
		{
			for(unsigned int columnCounter = 0; columnCounter < 3; columnCounter++)
			{
				this->myMatrix[rowCounter][columnCounter] = aRightHandMatrix.myMatrix[rowCounter][columnCounter];
			}
		}
		return(*this);
	}

	template <typename T>
	Matrix33<T>& Matrix33<T>::operator *=(const T &aNumberToScaleWith)
	{
		for(unsigned int rowCounter = 0; rowCounter < 3; rowCounter++)
		{
			for(unsigned int columnCounter = 0; columnCounter < 3; columnCounter++)
			{
				this->myMatrix[rowCounter][columnCounter] *= aNumberToScaleWith;
			}
		}
		return(*this);
	}

	template <typename T>
	Matrix33<T>& Matrix33<T>::operator *=(const Matrix33<T>& aRightHandMatrix)
	{
		Matrix33<T> tempMatrix;
		T currentValue = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for(int k = 0; k < 3; k++)
				{
					currentValue += myMatrix[k][i] * aRightHandMatrix.myMatrix[j][k];
				}
				tempMatrix.myMatrix[j][i] = currentValue;
				currentValue = 0;
			}
		}
		*this = tempMatrix;
		return(*this);
	}

	template <typename T>
	Matrix33<T>& Matrix33<T>::operator /=(const T &aNumberToDivideBy)
	{
		for(unsigned int columnCounter = 0; columnCounter < 3; columnCounter++)
		{
			for(unsigned int rowCounter = 0; rowCounter < 3; rowCounter++)
			{
				this->myMatrix[columnCounter][rowCounter] /= aNumberToDivideBy;
			}
		}
		return(*this);
	}

	template <typename T>
	bool Matrix33<T>::operator ==(const Matrix33<T>& aRightHandMatrix)
	{
		for(unsigned int columnCounter = 0; columnCounter < 3; columnCounter++)
		{
			for(unsigned int rowCounter = 0; rowCounter < 3; rowCounter++)
			{
				if(this->myMatrix[columnCounter][rowCounter] != aRightHandMatrix.myMatrix[columnCounter][rowCounter])
					return(false);
			}
		}
		return(true);
	}

	template <typename T>
	bool Matrix33<T>::operator !=(const Matrix33<T>& aRightHandMatrix)
	{
		for(unsigned int columnCounter = 0; columnCounter < 3; columnCounter++)
		{
			for(unsigned int rowCounter = 0; rowCounter < 3; rowCounter++)
			{
				if(this->myMatrix[columnCounter][rowCounter] != aRightHandMatrix.myMatrix[columnCounter][rowCounter])
					return(true);
			}
		}
		return(false);
	}

	template <typename T>
	Matrix33<T> operator*(const Matrix33<T>& aLeftSideMatrix, const Matrix33<T>& aRightSideMatrix)
	{
		Matrix33<T> aResultMatrix(aLeftSideMatrix);
		aResultMatrix *= aRightSideMatrix;

		return(aResultMatrix);
	}

	template <typename T>
	Matrix33<T> operator*(const Matrix33<T>& aLeftSideMatrix, const T& aRightSideScalar)
	{
		Matrix33<T> aResultMatrix(aLeftSideMatrix);
		aResultMatrix *= aRightSideScalar;

		return(aResultMatrix);
	}

	template <typename T>
	Vector3<T> operator*(const Matrix33<T>& aLeftSideMatrix, const Vector3<T>& aRightSideVector)
	{
		Vector3<T> aResultVector(0,0,0);

		for(unsigned int i = 0; i < 3; i++)
		{
			for(unsigned int j = 0; j < 3; j++)
			{
				aResultVector[i] += aLeftSideMatrix.myMatrix[i][j] * aRightSideVector[j];
			}
		}

		return(aResultVector);
	}

	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aRightSideVector, const Matrix33<T>& aLeftSideMatrix)
	{
		Vector3<T> aResultVector(0,0,0);

		for(unsigned int i = 0; i < 3; i++)
		{
			for(unsigned int j = 0; j < 3; j++)
			{
				aResultVector[i] += aLeftSideMatrix.myMatrix[i][j] * aRightSideVector[j];
			}
		}

		return(aResultVector);
	}



	typedef Matrix33<float>		Matrix33f;
	typedef Matrix33<double>	Matrix33d;
	typedef Matrix33<int>		Matrix33i;
}

#endif