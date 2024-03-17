#include "Framework.h"
#include "headBreakAtk.h"

headBreakAtk::headBreakAtk()
{
	cut = new Quad(L"Textures/Effect/critical.png");

	cut->Pos() = { WIN_WIDTH / 2 , 3000 ,0 };
	cut->Rot().z -= XM_PIDIV2;
	cut->Scale() = { 3.8, 0.3, 1 };
}

headBreakAtk::~headBreakAtk()
{
}

void headBreakAtk::Update()
{
	if (!active)
		return;
	cut->Pos().y -= 20000 * DELTA;
	if (cut->Pos().y < -3000)
	{
		cut->Pos().y = 3000;
		active = false;
	}
	cut->UpdateWorld();
}

void headBreakAtk::PostRender()
{
	if (!active)
		return;
	cut->Render();
}
