#include "stdafx.h"
#include "result.h"
#include "score.h"
#include "title.h"
#include "GameSence.h"

result::result()
{
}

result::~result()
{
	DeleteGO(m_SpriteTitle);
	DeleteGO(m_SpriteReStart);
	DeleteGO(m_SpriteSelect);
	DeleteGO(m_Spritefade);
}

bool result::Start()
{
	NewGO<score>(0);
	m_Spritefade = NewGO<prefab::CSpriteRender>(3);
	m_Spritefade->Init(L"sprite/haikei.dds", 1280.0f, 720.0f);
	m_Spritefade->SetMulColor(m_FadeColor);					//絵の濃さ
	m_SpriteTitle = NewGO<prefab::CSpriteRender>(1);
	m_SpriteTitle->SetPosition(m_TitlePosition);
	m_SpriteReStart = NewGO < prefab::CSpriteRender>(1);
	m_SpriteReStart->SetPosition(m_ReStartPosition);
	m_SpriteSelect = NewGO<prefab::CSpriteRender>(0);
	m_Spritefade->SetMulColor(m_FadeColor);
	m_GameDelete = FindGO<GameDelete>("GameDelete");
	return true;
}

void result::Update()
{
	SpriteGO += GameTime().GetFrameDeltaTime();
	if (SpriteGO >= 1.0f)
	{
		if (!New)
		{
			m_SpriteTitle->Init(L"sprite/result_restart.dds", 400.0f, 300.0f);
			m_SpriteTitle->SetPosition(m_TitlePosition);
			m_SpriteReStart->Init(L"sprite/result_title.dds", 400.0f, 300.0f);
			m_SpriteReStart->SetPosition(m_ReStartPosition);
			m_SpriteSelect->Init(L"sprite/result_select.dds", 405.0f, 305.0);
			New = true;
		}
		if (Pad(0).IsPress(enButtonRight))							//選択肢の移動
		{
			m_SelectPosition.x += 600.0f;
		}
		if (Pad(0).IsPress(enButtonLeft))
		{
			m_SelectPosition.x -= 600.0f;
		}
		if (m_SelectPosition.x >= 300.0f)
		{
			m_SelectPosition.x = 300.0f;
		}
		if (m_SelectPosition.x <= -300.0f)
		{
			m_SelectPosition.x = -300.0f;
		}
		m_SpriteSelect->SetPosition(m_SelectPosition);
		if (m_SelectPosition.x == 300.0f && Pad(0).IsPress(enButtonB) && !fadeout)		//フェードとリスタートの文
		{
			m_Spritefade->Init(L"sprite/haikei.dds", 1280.0f, 720.0f);
			m_GameDelete->DeleteArm = true;
			m_GameDelete->DeleteGameSence = true;
			m_GameDelete->DeleteScore = true;
			m_GameDelete->DeleteClaftScreen = true;
			m_GameDelete->DeleteBuckGround = true;
			fadeout = true;
			restart = true;
			m_FadeColor.a = 1.0f;
			SpriteGO = 0.0f;
			fadedown = true;
			//DeleteGO(this);
		}
		if (m_SelectPosition.x == -300.0f && Pad(0).IsPress(enButtonB) && !fadeout)		//フェードとタイトルへ行く文
		{
			m_Spritefade->Init(L"sprite/haikei.dds", 1280.0f, 720.0f);
			m_GameDelete->DeleteClaftScreen = true;
			m_GameDelete->DeleteArm = true;
			m_GameDelete->DeleteGameSence = true;
			m_GameDelete->DeleteScore = true;
			m_GameDelete->DeleteBuckGround = true;
			title = true;
			fadeout = true;
			m_FadeColor.a = 1.0f;
			SpriteGO = 0.0f;
			fadedown = true;
		}
	}
	if (SpriteGO >= 1.0f)
	{
		if (fadeout == true)
		{
			m_FadeColor.a -= 0.05f;
		}
	}

	if (m_FadeColor.a <= 0.5f&&fadedown)								//ゲームにあるインスタンスをすべて消す
	{
		if (restart)
		{
			if (!Newgo) 
			{
				NewGO<Title>(0, "title");
				Newgo = true;
			}
		}
		if (title)
		{
			if (!Newgo)
			{
				NewGO<GameSence>(0, "GameSence");
				Newgo = true;
			}
		}
		DeleteGO(this);
	}
	m_Spritefade->SetMulColor(m_FadeColor);					//絵の濃さ
}
