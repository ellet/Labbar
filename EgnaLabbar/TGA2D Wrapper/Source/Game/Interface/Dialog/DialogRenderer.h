#pragma once

#include <Vectors/vector2.h>

class Dialog;
class TextRenderer;

namespace DX2D
{
	class CSprite;
}

class DialogRenderer
{
public:

	DialogRenderer();
	~DialogRenderer();

	void LoadFont(const std::string &aFontPath);

	size_t NextDialogIndex(const Dialog &aDialog, const size_t aStartIndex);

	void DrawDialog(const Dialog &aDialog, const size_t aStartIndex) const;

	void LoadBackground(const std::string &aSpritePath);

	inline const Point2f& GetPosition() const;
	inline void SetPosition(const Point2f &aPosition);
	inline const Vector2f& GetSize() const;
	inline void SetSize(const Vector2f &aSize);

	inline const Point2f& GetTextPosition() const;
	inline void SetTextPosition(const Point2f &aPosition);
	inline const Vector2f& GetTextSize() const;
	inline void SetTextSize(const Vector2f &aSize);

	inline float GetFontSize() const;
	inline void SetFontSize(const float aSize);

	inline const Point2f& GetAvatarPosition() const;
	inline void SetAvatarPosition(const Point2f &aPosition);

private:

	TextRenderer *myTextRenderer;

	size_t myMaxDialogRows;

	Point2f myPosition;
	Vector2f mySize;

	Point2f myTextPosition;
	Vector2f myTextSize;

	float myFontSize;
	Vector2f myAvatarPosition;

	DX2D::CSprite *myBackgroundSprite;

};

inline const Point2f& DialogRenderer::GetPosition() const
{
	return myPosition;
}
inline void DialogRenderer::SetPosition(const Point2f &aPosition)
{
	myPosition = aPosition;
}
inline const Vector2f& DialogRenderer::GetSize() const
{
	return mySize;
}
inline void DialogRenderer::SetSize(const Vector2f &aSize)
{
	mySize = aSize;
}

inline const Point2f& DialogRenderer::GetTextPosition() const
{
	return myTextPosition;
}
inline void DialogRenderer::SetTextPosition(const Point2f &aPosition)
{
	myTextPosition = aPosition;
}
inline const Vector2f& DialogRenderer::GetTextSize() const
{
	return myTextSize;
}
inline void DialogRenderer::SetTextSize(const Vector2f &aSize)
{
	myTextSize = aSize;
}

inline float DialogRenderer::GetFontSize() const
{
	return myFontSize;
}
inline void DialogRenderer::SetFontSize(const float aSize)
{
	myFontSize = aSize;
}

inline const Point2f& DialogRenderer::GetAvatarPosition() const
{
	return myAvatarPosition;
}
inline void DialogRenderer::SetAvatarPosition(const Point2f &aPosition)
{
	myAvatarPosition = aPosition;
}
