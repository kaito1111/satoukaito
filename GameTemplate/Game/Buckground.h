#pragma once
#include "GameDelete.h"

class Buckground : public IGameObject
{
public:
	Buckground();
	~Buckground();
	bool Start();
	void Update();
	//メンバ変数//
	prefab::CSpriteRender* m_spriteRender = nullptr;
	CVector3 m_SpritePos = { 0.0f,0.0f,-400.0f };
	CVector4 m_SpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	float Rotritu = 0.0f;
	GameDelete* m_GameDelete = nullptr;
};

