#pragma once

class CDXModel;

class CHUGModel
{
public:
	CHUGModel();
	~CHUGModel();

	void InitAsTriangle();
	void InitAsQuad();

	void Init();
	void Render();

private:
	CDXModel * myModel;
};