#pragma once
#include "Utilities\Math\Vector3.h"
#include "Utilities\Math\Vector4.h"

namespace SB
{
	class Color
	{
	public:
		Color() 
		{
			r = 1.f;
			g = 1.f;
			b = 1.f;
			a = 1.f;
		}

		Color(const float aR, const float aG, const float aB)
		{
			SetNormalized(aR, aG, aB);
			a = 1.f;
		}

		Color(const float aR, const float aG, const float aB, const float aA)
		{
			SetNormalized(aR, aG, aB, aA);
		}

		Color(const Vector3f & aVector)
		{
			SetNormalized(aVector);
			a = 1.f;
		}

		Color(const Vector4f & aVector)
		{
			SetNormalized(aVector);
		}

		~Color()
		{
		}

		void SetWithRGBA(const float aR, const float aG, const float aB, const float aA);
		void SetWithRGBA(const Vector4f & aVector);

		void SetWithRGB(const float aR, const float aG, const float aB);
		void SetWithRGB(const Vector3f & aVector);
		
		void SetNormalized(const float aR, const float aG, const float aB);
		void SetNormalized(const float aR, const float aG, const float aB, const float aA);
		void SetNormalized(const Vector3f & aVector);
		void SetNormalized(const Vector4f & aVector);

		float r;
		float g;
		float b;
		float a;

		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Purple;
		static const Color Black;
		static const Color Yellow;
		static const Color Orange;

	};

	inline void Color::SetWithRGBA(const float aR, const float aG, const float aB, const float aA)
	{
		r = aR / 255.f;
		g = aG / 255.f;
		b = aB / 255.f;
		a = aA / 255.f;
	}

	inline void Color::SetWithRGB(const float aR, const float aG, const float aB)
	{
		r = aR / 255.f;
		g = aG / 255.f;
		b = aB / 255.f;
	}

	inline void Color::SetWithRGB(const Vector3f & aVector)
	{
		SetWithRGB(aVector.x, aVector.y, aVector.z);
	}

	inline void Color::SetNormalized(const Vector3f & aVector)
	{
		SetNormalized(aVector.x, aVector.y, aVector.z);
	}

	inline void Color::SetNormalized(const Vector4f & aVector)
	{
		SetNormalized(aVector.x, aVector.y, aVector.z, aVector.w);
	}

	inline void Color::SetNormalized(const float aR, const float aG, const float aB, const float aA)
	{
		r = aR;
		g = aG;
		b = aB;
		a = aA;
	}

	inline void Color::SetNormalized(const float aR, const float aG, const float aB)
	{
		r = aR;
		g = aG;
		b = aB;
	}

	inline void Color::SetWithRGBA(const Vector4f & aVector)
	{
		SetWithRGBA(aVector.x, aVector.y, aVector.z, aVector.w);
	}
}

