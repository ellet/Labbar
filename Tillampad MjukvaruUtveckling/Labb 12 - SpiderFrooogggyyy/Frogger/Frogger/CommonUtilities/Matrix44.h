#ifndef MATRIX44_H
#define MATRIX44_H

#include "stdafx.h"
#include "math.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix33.h"
#include "staticArray.h"

namespace CommonUtilities
{
	template <typename T>
	class Matrix44
	{
	public:
		Matrix44();
		Matrix44(const Matrix44<T>& aMatrixToCopy);
		Matrix44(const T* aD3DMatrix);
		Matrix44(
			const T& aXX, const T& aXY, const T& aXZ, const T& aXW, 
			const T& aYX, const T& aYY, const T& aYZ, const T& aYW, 
			const T& aZX, const T& aZY, const T& aZZ, const T& aZW,
			const T& aWX, const T& aWY, const T& aWZ, const T& aWW);
		~Matrix44();


		void			Set(
			const T& aXX, const T& aXY, const T& aXZ, const T& aXW, 
			const T& aYX, const T& aYY, const T& aYZ, const T& aYW, 
			const T& aZX, const T& aZY, const T& aZZ, const T& aZW,
			const T& aWX, const T& aWY, const T& aWZ, const T& aWW);

		static Matrix44 Identity();
		void 			GenerateRotationMatrixByAxisX(const T& aRotationInRadians);
		void 			GenerateRotationMatrixByAxisY(const T& aRotationInRadians);
		void 			GenerateRotationMatrixByAxisZ(const T& aRotationInRadians);
		void			RotateFrame(float anAngle, CU::Vector3<T> aDirection, CU::Vector3<T> aTranslation);
		void 			RotateX(const T& aRotationInRadians);
		void 			RotateY(const T& aRotationInRadians);
		void 			RotateZ(const T& aRotationInRadians);

        CU::Vector3<T>  GetForwardVector();

		void 			SetTranslation(const Vector3<T>& aTranslationVector);
		void 			SetTranslation(const T& aX, const T& aY, const T& aZ);
		void 			SetPosition(const Vector3<T>& aPosition);
		void 			SetPosition(const T& aX, const T& aY, const T& aZ);
        void            Set33(CU::Matrix33f aMatrix);
		void 			SetScaling(const T& aXScale, const T& aYScale, const T& aZScale);
		void			ModifyScale(const T& aXScale, const T& aYScale, const T& aZScale);
		void 			SetToIdentityMatrix();

		void			SetRightVec(const CU::Vector3<T>& aVector);
		void			SetUpVec(const CU::Vector3<T>& aVector);
		void			SetLookAt(const CU::Vector3<T>& aVector);

		CU::Vector3<T>	GetRightVec() const;
		CU::Vector3<T>	GetUpVec() const;
		CU::Vector3<T>	GetLookAt() const;
		CU::Vector3<T>	GetPosition() const;

		Matrix33<T> 	GetMatrix33() const;

		Matrix44<T>		GetTranspose() const;
		Matrix44<T>&	Transpose();
		Matrix44<T>		CopyFromD3DMatrix(const T* aD3DMatrix);
		Matrix44<T>&	Inverse();
		Matrix44<T>		GetInverse() const;

		//////////////////////////////////////////////////////////////////////////
		//																		//
		//						Operator Overloading							//
		//																		//
		//////////////////////////////////////////////////////////////////////////


		Matrix44<T>& operator=(const Matrix44<T>& aRightHandMatrix);
		Matrix44<T>& operator*=(const T& aNumberToScaleWith);
		Matrix44<T>& operator*=(const Matrix44<T>& aRightHandMatrix);
		Matrix44<T>& operator/=(const T& aNumberToDivideBy);
		Matrix44<T>& operator*=(const Matrix33<T>& aRightHandMatrix);
		Matrix44<T>& operator+=(const Matrix33<T>& aRightHandMatrix);

		bool operator==(const Matrix44<T>& aRightHandMatrix);
		bool operator!=(const Matrix44<T>& aRightHandMatrix); 

		T myMatrix[4][4];
	};

	template <typename T>
	Matrix44<T>::Matrix44()
	{
		SetToIdentityMatrix();
	}

	template <typename T>
	Matrix44<T>::Matrix44(const Matrix44<T>& aMatrixToCopy)
	{
		*this = aMatrixToCopy;
	}

    template <typename T>
    CU::Vector3<T>  Matrix44<T>::GetForwardVector()
    {
        return CU::Vector3<T>(myMatrix[2][0], myMatrix[2][1], myMatrix[2][2]);
    }

	template <typename T>
	Matrix44<T> Matrix44<T>::Identity()
	{
		CU::Matrix44f aIdentityMatrix;
		aIdentityMatrix.SetToIdentityMatrix();
		return aIdentityMatrix;
	}

	template <typename T>
	Matrix44<T>::Matrix44(
		const T& aXX, const T& aXY, const T& aXZ, const T& aXW, 
		const T& aYX, const T& aYY, const T& aYZ, const T& aYW, 
		const T& aZX, const T& aZY, const T& aZZ, const T& aZW,
		const T& aWX, const T& aWY, const T& aWZ, const T& aWW)
	{
		myMatrix[0][0] = aXX;
		myMatrix[0][1] = aXY;
		myMatrix[0][2] = aXZ;
		myMatrix[0][3] = aXW;

		myMatrix[1][0] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[1][2] = aYZ;
		myMatrix[1][3] = aYW;

		myMatrix[2][0] = aZX;
		myMatrix[2][1] = aZY;
		myMatrix[2][2] = aZZ;
		myMatrix[2][3] = aZW;

		myMatrix[3][0] = aWX;
		myMatrix[3][1] = aWY;
		myMatrix[3][2] = aWZ;
		myMatrix[3][3] = aWW;
	}

	template <typename T>
	Matrix44<T>::Matrix44(const T* aD3DMatrix)
	{
		myMatrix[0][0] = aD3DMatrix[0];
		myMatrix[0][1] = aD3DMatrix[1];
		myMatrix[0][2] = aD3DMatrix[2];
		myMatrix[0][3] = aD3DMatrix[3];

		myMatrix[1][0] = aD3DMatrix[4];
		myMatrix[1][1] = aD3DMatrix[5];
		myMatrix[1][2] = aD3DMatrix[6];
		myMatrix[1][3] = aD3DMatrix[7];

		myMatrix[2][0] = aD3DMatrix[8];
		myMatrix[2][1] = aD3DMatrix[9];
		myMatrix[2][2] = aD3DMatrix[10];
		myMatrix[2][3] = aD3DMatrix[11];

		myMatrix[3][0] = aD3DMatrix[12];
		myMatrix[3][1] = aD3DMatrix[13];
		myMatrix[3][2] = aD3DMatrix[14];
		myMatrix[3][3] = aD3DMatrix[15];
	}

	template <typename T>
	Matrix44<T>::~Matrix44()
	{

	}

	template <typename T>
	Matrix44<T>& Matrix44<T>::Inverse()
	{
		Matrix33<T> inverse33 = GetMatrix33(); 
		CU::Vector3f pos(-myMatrix[3][0],-myMatrix[3][1],-myMatrix[3][2]);
		pos = inverse33*pos;
		inverse33.Transpose();
		Set(inverse33.myMatrix[0][0],inverse33.myMatrix[0][1],inverse33.myMatrix[0][2],0,
			inverse33.myMatrix[1][0],inverse33.myMatrix[1][1],inverse33.myMatrix[1][2],0,
			inverse33.myMatrix[2][0],inverse33.myMatrix[2][1],inverse33.myMatrix[2][2],0,
		pos.myX,pos.myY,pos.myZ,1);
		return *this;

	}

	template <typename T>
	Matrix44<T>	Matrix44<T>::GetInverse() const
	{
		CU::Matrix44<T> returnMatrix;
		returnMatrix = *this;
		returnMatrix.Inverse();
		return returnMatrix;
	}

	template <typename T>
	void Matrix44<T>::Set(
		const T& aXX, const T& aXY, const T& aXZ, const T& aXW, 
		const T& aYX, const T& aYY, const T& aYZ, const T& aYW, 
		const T& aZX, const T& aZY, const T& aZZ, const T& aZW,
		const T& aWX, const T& aWY, const T& aWZ, const T& aWW)
	{
		myMatrix[0][0] = aXX;
		myMatrix[0][1] = aXY;
		myMatrix[0][2] = aXZ;
		myMatrix[0][3] = aXW;

		myMatrix[1][0] = aYX;
		myMatrix[1][1] = aYY;
		myMatrix[1][2] = aYZ;
		myMatrix[1][3] = aYW;

		myMatrix[2][0] = aZX;
		myMatrix[2][1] = aZY;
		myMatrix[2][2] = aZZ;
		myMatrix[2][3] = aZW;

		myMatrix[3][0] = aWX;
		myMatrix[3][1] = aWY;
		myMatrix[3][2] = aWZ;
		myMatrix[3][3] = aWW;
	}

	template <typename T>
	void Matrix44<T>::SetToIdentityMatrix()
	{
		Set(1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1);
	}

	template <typename T>
	Matrix33<T> Matrix44<T>::GetMatrix33() const
	{
		Matrix33<T> aResultMatrix;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				aResultMatrix.myMatrix[i][j] = this->myMatrix[i][j];
			}
		}
		return(aResultMatrix);
	}

	template <typename T>
	void Matrix44<T>::RotateFrame(float anAngle, CU::Vector3<T> aDirection, CU::Vector3<T> aTranslation)
	{
		float x = aDirection.myX;
		float y = aDirection.myY;
		float z = aDirection.myZ;

		Matrix44<T> tempMatrix = *this;
		tempMatrix.SetToIdentityMatrix();

		tempMatrix.myMatrix[0][0] = x*x * (1-cos(anAngle)) + cos(anAngle);
		tempMatrix.myMatrix[1][0] = x*y * (1-cos(anAngle)) - z*sin(anAngle);
		tempMatrix.myMatrix[2][0] = x*z * (1-cos(anAngle)) + y*sin(anAngle);

		tempMatrix.myMatrix[0][1] = y*x * (1-cos(anAngle)) + z*sin(anAngle);
		tempMatrix.myMatrix[1][1] = y*y * (1-cos(anAngle)) + cos(anAngle);
		tempMatrix.myMatrix[2][1] = y*z * (1-cos(anAngle)) - x*sin(anAngle);

		tempMatrix.myMatrix[0][2] = x*z * (1-cos(anAngle)) - y*sin(anAngle);
		tempMatrix.myMatrix[1][2] = y*z * (1-cos(anAngle)) + x*sin(anAngle);
		tempMatrix.myMatrix[2][2] = z*z * (1-cos(anAngle)) + cos(anAngle);

		tempMatrix.myMatrix[3][0] = aTranslation.myX;
		tempMatrix.myMatrix[3][1] = aTranslation.myY;
		tempMatrix.myMatrix[3][2] = aTranslation.myZ;

		*this = tempMatrix;
	}

    template <typename T>
    void Matrix44<T>::Set33(CU::Matrix33f aMatrix)
    {
        for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
                myMatrix[i][j] = aMatrix.myMatrix[i][j];
			}
		}
    }

	template <typename T>
	void Matrix44<T>::GenerateRotationMatrixByAxisX(const T& aRotationInRadians)
	{
		myMatrix[1][1] = cos(aRotationInRadians);
		myMatrix[1][2] = -sin(aRotationInRadians);
		myMatrix[2][1] = sin(aRotationInRadians);
		myMatrix[2][2] = cos(aRotationInRadians);
	}

	template <typename T>
	void Matrix44<T>::GenerateRotationMatrixByAxisY(const T& aRotationInRadians)
	{
		myMatrix[0][0] = cos(aRotationInRadians);
		myMatrix[0][2] = sin(aRotationInRadians);
		myMatrix[2][0] = -sin(aRotationInRadians);
		myMatrix[2][2] = cos(aRotationInRadians);
	}

	template <typename T>
	void Matrix44<T>::GenerateRotationMatrixByAxisZ(const T& aRotationInRadians)
	{
		myMatrix[0][0] = cos(aRotationInRadians);
		myMatrix[0][1] = -sin(aRotationInRadians);
		myMatrix[1][0] = sin(aRotationInRadians);
		myMatrix[1][1] = cos(aRotationInRadians);
	}

	template <typename T>
	void Matrix44<T>::RotateX(const T& aRotationInRadians)
	{
		Matrix44<T> aRotationMatrix;
		aRotationMatrix.GenerateRotationMatrixByAxisX(aRotationInRadians);
		*this *= aRotationMatrix.GetMatrix33();
	}

	template <typename T>
	void Matrix44<T>::RotateY(const T& aRotationInRadians)
	{
		Matrix44<T> aRotationMatrix;
		aRotationMatrix.GenerateRotationMatrixByAxisY(aRotationInRadians);
		*this *= aRotationMatrix.GetMatrix33();
	}

	template <typename T>
	void Matrix44<T>::RotateZ(const T& aRotationInRadians)
	{
		Matrix44<T> aRotationMatrix;
		aRotationMatrix.GenerateRotationMatrixByAxisZ(aRotationInRadians);
		*this *= aRotationMatrix.GetMatrix33();
	}

	template <typename T>
	void Matrix44<T>::SetTranslation(const Vector3<T>& aTranslationVector)
	{
		myMatrix[3][0] = aTranslationVector.myX;
		myMatrix[3][1] = aTranslationVector.myY;
		myMatrix[3][2] = aTranslationVector.myZ;
	}

	template <typename T>
	void Matrix44<T>::SetRightVec(const CU::Vector3<T>& aVector)
	{
		myMatrix[0][0] = aVector.myX;
		myMatrix[0][1] = aVector.myY;
		myMatrix[0][2] = aVector.myZ;	
	}

	template <typename T>
	void Matrix44<T>::SetUpVec(const CU::Vector3<T>& aVector)
	{
		myMatrix[1][0] = aVector.myX;
		myMatrix[1][1] = aVector.myY;
		myMatrix[1][2] = aVector.myZ;
	}

	template <typename T>
	void Matrix44<T>::SetLookAt(const CU::Vector3<T>& aVector)
	{
		myMatrix[2][0] = aVector.myX;
		myMatrix[2][1] = aVector.myY;
		myMatrix[2][2] = aVector.myZ;
	}

	template <typename T>
	CU::Vector3<T>	Matrix44<T>::GetRightVec() const
	{
		return CU::Vector3<T>(
			myMatrix[0][0],
			myMatrix[0][1],
			myMatrix[0][2]);
	}

	template <typename T>
	CU::Vector3<T>	Matrix44<T>::GetUpVec() const
	{
		return CU::Vector3<T>(
			myMatrix[1][0],
			myMatrix[1][1],
			myMatrix[1][2]);
	}

	template <typename T>
	CU::Vector3<T>	Matrix44<T>::GetLookAt() const
	{
		return CU::Vector3<T>(
			myMatrix[2][0],
			myMatrix[2][1],
			myMatrix[2][2]);
	}

	template <typename T>
	CU::Vector3<T>	Matrix44<T>::GetPosition() const
	{
		return CU::Vector3<T>(
			myMatrix[3][0],
			myMatrix[3][1],
			myMatrix[3][2]);
	}

	template <typename T>
	void Matrix44<T>::SetTranslation(const T& aX, const T& aY, const T& aZ)
	{	
		myMatrix[3][0] = aX;
		myMatrix[3][1] = aY;
		myMatrix[3][2] = aZ;
	}

	template <typename T>
	void Matrix44<T>::SetPosition(const CommonUtilities::Vector3<T> &aPosition)
	{
		SetTranslation(aPosition);
	}

	template <typename T>
	void Matrix44<T>::SetPosition(const T &aX, const T &aY, const T &aZ)
	{
		SetTranslation(aX, aY, aZ);
	}

	template <typename T>
	void Matrix44<T>::SetScaling(const T& aXScale, const T& aYScale, const T& aZScale)
	{
		myMatrix[0][0] = aXScale;
		myMatrix[1][1] = aYScale;
		myMatrix[2][2] = aZScale;
	}

	template <typename T>
	void Matrix44<T>::ModifyScale(const T& aXScale, const T& aYScale, const T& aZScale)
	{
		myMatrix[0][0] += aXScale;
		myMatrix[1][1] += aYScale;
		myMatrix[2][2] += aZScale;
	}


	template <typename T>
	Matrix44<T>& Matrix44<T>::Transpose()
	{
		Matrix44<T> aTempMatrix;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				aTempMatrix.myMatrix[j][i] = myMatrix[i][j];
			}
		}
		*this = aTempMatrix;
		return(*this);
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::GetTranspose() const
	{
		Matrix44<T> aTempMatrix;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				aTempMatrix.myMatrix[j][i] = myMatrix[i][j];
			}
		}
		aTempMatrix;
		return(aTempMatrix);
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::CopyFromD3DMatrix(const T* aD3DMatrix)
	{
		myMatrix[0][0] = aD3DMatrix[0];
		myMatrix[0][1] = aD3DMatrix[1];
		myMatrix[0][2] = aD3DMatrix[2];
		myMatrix[0][3] = aD3DMatrix[3];

		myMatrix[1][0] = aD3DMatrix[4];
		myMatrix[1][1] = aD3DMatrix[5];
		myMatrix[1][2] = aD3DMatrix[6];
		myMatrix[1][3] = aD3DMatrix[7];

		myMatrix[2][0] = aD3DMatrix[8];
		myMatrix[2][1] = aD3DMatrix[9];
		myMatrix[2][2] = aD3DMatrix[10];
		myMatrix[2][3] = aD3DMatrix[11];

		myMatrix[3][0] = aD3DMatrix[12];
		myMatrix[3][1] = aD3DMatrix[13];
		myMatrix[3][2] = aD3DMatrix[14];
		myMatrix[3][3] = aD3DMatrix[15];

		return(*this);
	}

	//////////////////////////////////////////////////////////////////////////
	//																		//
	//						Operator Overloading							//
	//																		//
	//////////////////////////////////////////////////////////////////////////

	template <typename T>
	Matrix44<T>& Matrix44<T>::operator =(const Matrix44<T>& aRightHandMatrix)
	{
		memcpy(&myMatrix, &aRightHandMatrix.myMatrix, sizeof(T)*16);
		return(*this);
	}

	template <typename T>
	Matrix44<T>& Matrix44<T>::operator *=(const T &aNumberToScaleWith)
	{
		for(unsigned int rowCounter = 0; rowCounter < 4; rowCounter++)
		{
			for(unsigned int columnCounter = 0; columnCounter < 4; columnCounter++)
			{
				this->myMatrix[rowCounter][columnCounter] *= aNumberToScaleWith;
			}
		}
		return(*this);
	}

    template <typename T>
	Matrix44<T>& Matrix44<T>::operator *=(const Matrix44<T>& aRightHandMatrix)
	{
		Matrix44<T> tempMatrix;		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
                T c = 0;                
				for(int k = 0; k < 4; k++)
				{
                    T a = myMatrix[j][k];
                    T b = aRightHandMatrix.myMatrix[k][i];
                    c += a * b;
					//tempMatrix.myMatrix[j][i] += myMatrix[j][k] * aRightHandMatrix.myMatrix[k][i];
				}
                tempMatrix.myMatrix[j][i] = c;
			}
		}
		*this = tempMatrix;
		return(*this);
	}

	//template <typename T>
	//Matrix44<T>& Matrix44<T>::operator *=(const Matrix44<T>& aRightHandMatrix)
	//{
	//	Matrix44<T> tempMatrix;
	//	T currentValue = 0;
	//	for (int i = 0; i < 4; i++)
	//	{
	//		for (int j = 0; j < 4; j++)
	//		{
	//			for(int k = 0; k < 4; k++)
	//			{
	//				currentValue += myMatrix[j][k] * aRightHandMatrix.myMatrix[k][i];
	//			}
	//			tempMatrix.myMatrix[j][i] = currentValue;
	//			currentValue = 0;
	//		}
	//	}
	//	*this = tempMatrix;
	//	return(*this);
	//}

	template <typename T>
	Matrix44<T>& Matrix44<T>::operator *=(const Matrix33<T>& aRightHandMatrix)
	{
		Matrix33<T> aTempMatrix = this->GetMatrix33();

		aTempMatrix *= aRightHandMatrix;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				this->myMatrix[i][j] = aTempMatrix.myMatrix[i][j];
			}
		}
		return(*this);
	}

	template <typename T>
	Matrix44<T>& Matrix44<T>::operator /=(const T &aNumberToDivideBy)
	{
		for(unsigned int columnCounter = 0; columnCounter < 4; columnCounter++)
		{
			for(unsigned int rowCounter = 0; rowCounter < 4; rowCounter++)
			{
				this->myMatrix[columnCounter][rowCounter] /= aNumberToDivideBy;
			}
		}
		return(*this);
	}

	template <typename T>
	bool Matrix44<T>::operator ==(const Matrix44<T>& aRightHandMatrix)
	{
		for(unsigned int columnCounter = 0; columnCounter < 4; columnCounter++)
		{
			for(unsigned int rowCounter = 0; rowCounter < 4; rowCounter++)
			{
				if(this->myMatrix[columnCounter][rowCounter] != aRightHandMatrix.myMatrix[columnCounter][rowCounter])
					return(false);
			}
		}
		return(true);
	}

	template <typename T>
	Matrix44<T>& Matrix44<T>::operator+=(const Matrix33<T>& aRightHandMatrix)
	{
		for(int x = 0;x < 4;x++)
		{
			for(int y = 0;y < 4;y++)
			{
				myMatrix[x][y] += aRightHandMatrix.myMatrix[x][y];
			}
		}
		return *this;
	}

	template <typename T>
	Matrix44<T> operator+(const Matrix44<T>& aLeftSideMatrix, const Matrix44<T>& aRightSideMatrix)
	{
		Matrix44<T> aResultMatrix(aLeftSideMatrix);
		aResultMatrix *= aRightSideMatrix;

		return(aResultMatrix);
	}

	template <typename T>
	bool Matrix44<T>::operator !=(const Matrix44<T>& aRightHandMatrix)
	{
		return(!(*this == aRightHandMatrix));
	}

	template <typename T>
	Matrix44<T> operator*(const Matrix44<T>& aLeftSideMatrix, const Matrix44<T>& aRightSideMatrix)
	{
		Matrix44<T> aResultMatrix(aLeftSideMatrix);
		aResultMatrix *= aRightSideMatrix;

		return(aResultMatrix);
	}

	template <typename T>
	Matrix44<T> operator*(const Matrix44<T>& aLeftSideMatrix, const Matrix33<T> aRightSideMatrix)
	{
		//not debuged properly yet!
		Matrix33<T> aTempMatrix = aLeftSideMatrix.GetMatrix33();
		aTempMatrix*=aRightSideMatrix;
		Matrix44<T> aReturnMatrix;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				aReturnMatrix.myMatrix[i][j] = aTempMatrix[i][j];
			}
		}

		return(aReturnMatrix);
	}

	template <typename T>
	Matrix44<T> operator*(const Matrix44<T>& aLeftSideMatrix, const T& aRightSideScalar)
	{
		Matrix44<T> aResultMatrix(aLeftSideMatrix);
		aResultMatrix *= aRightSideScalar;

		return(aResultMatrix);
	}

	template <typename T>
	Vector4<T> operator*(const Matrix44<T>& aLeftSideMatrix, const Vector4<T>& aRightSideVector)
	{
		Vector4<T> aResultVector(0,0,0,0);

		for(unsigned int i = 0; i < 4; i++)
		{
			for(unsigned int j = 0; j < 4; j++)
			{
				aResultVector[i] += aLeftSideMatrix.myMatrix[j][i] * aRightSideVector[j];
			}
		}

		aResultVector.Homogenize();
		return(aResultVector);
	}

	template <typename T>
	Vector3<T> operator*(const Matrix44<T>& aLeftSideMatrix, const Vector3<T>& aRightSideVector)
	{
		Vector4<T> aVector4(aRightSideVector);
		Vector4<T> aResultFromMuiltiplication = aLeftSideMatrix * aVector4;
		Vector3<T> aReturnVector(aResultFromMuiltiplication.myX,aResultFromMuiltiplication.myY,aResultFromMuiltiplication.myZ);
		return(aReturnVector);
	}


	typedef Matrix44<float>		Matrix44f;
	typedef Matrix44<double>	Matrix44d;
	typedef Matrix44<int>		Matrix44i;
}

namespace CU = CommonUtilities;

#endif