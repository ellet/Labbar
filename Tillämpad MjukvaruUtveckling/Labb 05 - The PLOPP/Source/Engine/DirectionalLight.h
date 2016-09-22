#pragma once
class DirectionalLight
{
public:
	DirectionalLight();
	~DirectionalLight();

	const Vector3f & GetDirection() const;
	const Vector3f & GetColor() const;

	void SetDirection(const Vector3f & aDirection);
	void SetColor(const Vector3f & aColor);

	void Saturate();

private:
	Vector3f myDirection;
	Vector3f myColor;
};