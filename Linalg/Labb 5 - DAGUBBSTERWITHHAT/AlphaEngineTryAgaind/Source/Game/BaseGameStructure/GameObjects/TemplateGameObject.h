#pragma once

class BaseGameObject;

class TemplateGameObject
{
public:
	TemplateGameObject();
	~TemplateGameObject();

	void Init();

private:
	BaseGameObject & GetMyBaseGameObject();

	size_t myBaseGameObjectIndex;
};

