#pragma once

class CDXModel;

class CHUGModel
{
public:
	CHUGModel();
	~CHUGModel();

	void Init();
	void Render();

private:
	CDXModel * myModel;
};