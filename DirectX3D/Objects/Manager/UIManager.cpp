#include "Framework.h"

UIManager::UIManager()
{
	clockFrame = new Quad(L"Textures/UI/ClockFrame.png");
	clockFrame->Pos() = { 80,640,0 };
	clockFrame->UpdateWorld();

	durability = new Quad(L"Textures/UI/Durability_magenta.png");
	durability->Pos() = { 200,600,0 };
	durability->UpdateWorld();

	durability_back = new Quad(L"Textures/UI/Durability_Gauge2.png");
	durability_back->Pos() = { 202,600,0 };

	hpBar = new Quad(L"Textures/UI/HpBar_noColor1.png");
	hpBar->Pos() = { 360,650,0 };

	idBar = new Quad(L"Textures/UI/IDBar.png");
	idBar->Pos() = { 220,680,0 };
	idBar->UpdateWorld();

	itemSlot = new Quad(L"Textures/UI/ItemSlot.png");
	itemSlot->Pos() = { 1160,120,0 };
	itemSlot->UpdateWorld();

	lsGauge = new Quad(L"Textures/UI/LSGauge.png");
	lsGauge->Pos() = { 340,600,0 };
	lsGauge->UpdateWorld();

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

	durability_gauge = new ProgressBar(
		L"Textures/Color/Durability.png",
		L"Textures/UI/StaminaBar_noColor.png"
	);
	lsGauge2 = new ProgressBar(
		L"Textures/UI/LSGauge2.png",
		L"Textures/UI/LSGauge2_bg.png"
	);
	lsCoting = new ProgressBar(
		L"Textures/UI/LSCoting_none.png",
		L"Textures/UI/LSCoting_none.png"
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

	//durability_gauge ui
	durability_gauge->Scale() = { 0.30f,0.02f,0 };
	durability_gauge->Pos() = durability_back->Pos();
	curDurability = maxDurability;

	//기인게이지 UI
	lsGauge2->Scale() = { 1.0f,0.9f,0 };
	lsGauge2->Pos() = lsGauge->Pos();
	lsGauge2->Pos().x += 13.0f;

	//코팅 UI
	lsCoting->Pos() = { 340,600,0 };
}

UIManager::~UIManager()
{
	delete clockFrame;
	delete durability;
	delete durability_back;
	delete hpBar;
	delete idBar;
	delete itemSlot;
	delete lsCoting;
	delete lsGauge;
	delete lsGauge2;
	delete quickSlot;
	delete slingerBug;
	delete staminarBar;
	delete hp;
	delete recover;
	delete stamina;
	delete durability_gauge;
}

void UIManager::Update()
{
	stamina->UpdateWorld();
	recover->UpdateWorld();
	hp->UpdateWorld();
	durability_back->UpdateWorld();
	hpBar->UpdateWorld();
	lsCoting->UpdateWorld();
	lsGauge2->UpdateWorld();
	slingerBug->UpdateWorld();
	staminarBar->UpdateWorld();
	durability_gauge->UpdateWorld();

	//hp, stamina 부분
	hp->SetAmount(curHP / maxHP);
	recover->SetAmount(recoverHP / maxHP);
	stamina->SetAmount(curStamina / maxStamina);
	if (curHP < recoverHP)
		curHP += 0.001f;

	curStamina += 0.001f;

	if (curHP > recoverHP)
		recoverHP = curHP;

	//예리도 부분
	durability_gauge->SetAmount(curDurability / maxDurability);

	if (curDurability <= 80.0f && curDurability > 60.0f)
		durability->SetTexture(L"Textures/UI/Durability_magenta.png");
	else if (curDurability < 60.0f && curDurability > 40.0f)
		durability->SetTexture(L"Textures/UI/Durability_white.png");
	else if (curDurability < 40.0f && curDurability > 20.0f)
		durability->SetTexture(L"Textures/UI/Durability_blue.png");
	else if (curDurability < 20.0f && curDurability > 0.0f)
		durability->SetTexture(L"Textures/UI/Durability_green.png");

	////////////////////////////////
	//예리도 샘플 상황, 변경 필요
	if (curDurability > 0.0f)
		curDurability -= 0.1f;

	if (curDurability < 0.0f)
		SharpeningStone();
	////////////////////////////////

	//기인게이지 부분
	lsGauge2->SetAmount(curGauge / maxGauge);

	if (curGauge > 0.0f)
		curGauge -= 0.1f;

	if (isBonus)
	{
		bonusTime += 0.1f;
		curGauge += 0.2f;
	}

	if (bonusTime > limitTime)
	{
		bonusTime = 0.0f;
		isBonus = false;
		lsGauge2->SetTexture(L"Textures/UI/LSGauge2.png");
	}

	////////////////////////////////
	//기인게이지 샘플상황, 변경 필요
	if (curGauge < 100.0f)
		curGauge += 0.2f;

	if (curGauge > 100.0f)
	{
		curGauge = 0.0f;
		curCoting = 100.0f;

		if (cotingLevel < 3)
			cotingLevel += 1;
	}

	if (KEY_PRESS('W'))
		GaugeBonus();

	if (cotingLevel == 3)
		curGauge -= 0.2f;
	////////////////////////////////

	//코팅 부분
	lsCoting->SetAmount(curCoting / maxCoting);

	if (cotingLevel == 0)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_none.png");
	if (cotingLevel == 1)
	{
		lsCoting->SetTexture(L"Textures/UI/LSCoting_white.png");
		curCoting -= 0.05f;
	}
	if (cotingLevel == 2)
	{
		lsCoting->SetTexture(L"Textures/UI/LSCoting_yellow.png");
		curCoting -= 0.05f;
	}
	if (cotingLevel == 3)
	{
		lsCoting->SetTexture(L"Textures/UI/LSCoting_red.png");
		curCoting -= 0.05f;
	}

	if (curCoting < 0.0f)
	{
		curCoting = 100.0f;
		cotingLevel -= 1;
	}
}

void UIManager::PostRender()
{
	recover->Render();
	hp->Render();
	stamina->Render();
	clockFrame->Render();
	durability->Render();
	durability_back->Render();
	hpBar->Render();
	idBar->Render();
	itemSlot->Render();
	lsCoting->Render();
	lsGauge->Render();
	lsGauge2->Render();
	quickSlot->Render();
	slingerBug->Render();
	staminarBar->Render();
	durability_gauge->Render();
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
	curStamina -= 0.01f;
}

void UIManager::Roll()
{
	curStamina -= 20.f;
}

void UIManager::ReduceDurability()
{
	curDurability -= 0.1f;
}

void UIManager::SharpeningStone()
{
	curDurability = maxDurability;
}

void UIManager::GaugeBonus()
{
	if (!isBonus)
	{
		isBonus = true;
		lsGauge2->SetTexture(L"Textures/UI/LSGauge2_blue.png");
	}
}
