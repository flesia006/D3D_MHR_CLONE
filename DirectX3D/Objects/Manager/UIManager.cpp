#include "Framework.h"

UIManager::UIManager()
{
	clockFrame = new Quad(L"Textures/UI/ClockFrame.png");
	clockFrame->Pos() = { 80,640,0 };
	clockFrame->UpdateWorld();

	durability = new Quad(L"Textures/UI/Durability.png");
	durability->Pos() = { 200,600,0 };
	durability->UpdateWorld();

	durability_gauge = new Quad(L"Textures/UI/Durability_Gauge.png");
	durability_gauge->Pos() = { 200,600,0 };

	hpBar = new Quad(L"Textures/UI/HpBar_noColor1.png");
	hpBar->Pos() = { 360,650,0 };

	idBar = new Quad(L"Textures/UI/IDBar.png");
	idBar->Pos() = { 220,680,0 };
	idBar->UpdateWorld();

	itemSlot = new Quad(L"Textures/UI/ItemSlot.png");
	itemSlot->Pos() = { 1160,120,0 };
	itemSlot->UpdateWorld();

	lsCoting = new Quad(L"Textures/UI/LSCoting.png");
	lsCoting->Pos() = { 340,600,0 };

	lsCoting2 = new Quad(L"Textures/UI/LSCoting2.png");
	lsCoting2->Pos() = { 340,600,0 };

	lsGauge = new Quad(L"Textures/UI/LSGauge.png");
	lsGauge->Pos() = { 340,600,0 };
	lsGauge->UpdateWorld();

	lsGauge2 = new Quad(L"Textures/UI/LSGauge2.png");
	lsGauge2->Pos() = { 347,600,0 };

	quickSlot = new Quad(L"Textures/UI/QuickSlot.png");
	quickSlot->Pos() = { 1000,120,0 };
	quickSlot->UpdateWorld();

	slingerBug = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug->Pos() = { 640,120,0 };

	staminarBar = new Quad(L"Textures/UI/StaminaBar_noColor.png");
	staminarBar->Pos() = { 360,630,0 };

	//캐릭터용 UI 추가
	hp = new ProgressBar(
		L"Textures/Color/Green.png",
		L"Textures/UI/HpBar_noColor1.png"
	);
	recover = new ProgressBar(
		L"Textures/Color/Red.png",
		L"Textures/Color/Black.png"
	);
	stamina = new ProgressBar(
		L"Textures/Color/Yellow.png",
		L"Textures/UI/StaminaBar_noColor.png"
	);
	// hp bar ui
	hp->Scale() = { 1.75f,0.02f,0 };
	hp->Pos() = hpBar->Pos();
	hp->Pos().x -= 0.1f;
	curHP = maxHP;
	recover->Scale() = hp->Scale();
	recover->Pos() = hp->Pos();
	
	// stamina bar ui
	stamina->Scale() = { 1.75f,0.02f,0 };
	stamina->Pos() = staminarBar->Pos();
	stamina->Pos().x -= 0.1f;
	curStamina = maxStamina;
}

UIManager::~UIManager()
{
	delete clockFrame;
	delete durability;
	delete durability_gauge;
	delete hpBar;
	delete idBar;
	delete itemSlot;
	delete lsCoting;
	delete lsCoting2;
	delete lsGauge;
	delete lsGauge2;
	delete quickSlot;
	delete slingerBug;
	delete staminarBar;
	delete hp;
	delete recover;
	delete stamina;

}

void UIManager::Update()
{
	stamina->UpdateWorld();
	recover->UpdateWorld();
	hp->UpdateWorld();
	durability_gauge->UpdateWorld();
	hpBar->UpdateWorld();
	lsCoting->UpdateWorld();
	lsCoting2->UpdateWorld();
	lsGauge2->UpdateWorld();
	slingerBug->UpdateWorld();
	staminarBar->UpdateWorld();

	hp->SetAmount(curHP / maxHP);
	recover->SetAmount(recoverHP / maxHP);
	stamina->SetAmount(curStamina / maxStamina);
	if(curHP<recoverHP)
	curHP += 0.001f;

	curStamina += 0.001f;

	if (curHP > recoverHP)
		recoverHP = curHP;
}

void UIManager::PostRender()
{
	recover->Render();
	hp->Render();
	stamina->Render();
	clockFrame->Render();
	durability->Render();
	durability_gauge->Render();
	hpBar->Render();
	idBar->Render();
	itemSlot->Render();
	lsCoting->Render();
	lsCoting2->Render();
	lsGauge->Render();
	lsGauge2->Render();
	quickSlot->Render();
	slingerBug->Render();
	staminarBar->Render();
}

void UIManager::Hit(float damage)
{
	curHP = curHP - damage;	
	hp->SetAmount(curHP / maxHP);

	recoverHP = recoverHP - damage / 2;
	recover->SetAmount(recoverHP / maxHP);
}

void UIManager::HealthPotion()
{
	curHP += 0.02f;
}

void UIManager::LargeHealthPotion()
{
	curHP += 0.04f;
}

void UIManager::Running()
{
	if (curStamina > 0.01f)
		curStamina -= 0.01f;
	else
		return;
}

void UIManager::Roll()
{
	curStamina -= 20.f;
}
