#include "Framework.h"

UIManager::UIManager()
{
	clockFrame = new Quad(L"Textures/UI/ClockFrame.png");
	clockFrame->Pos() = { 120,960,0 };
	clockFrame->Scale() *= 1.5f;
	clockFrame->UpdateWorld();

	durability = new Quad(L"Textures/UI/Durability_magenta.png");
	durability->Pos() = { 300,900,0 };
	durability->Scale() *= 1.5f;
	durability->UpdateWorld();

	durability_back = new Quad(L"Textures/UI/Durability_Gauge2.png");
	durability_back->Pos() = { 303,900,0 };
	durability_back->Scale() *= 1.5f;

	hpBar = new Quad(L"Textures/UI/HpBar_noColor1.png");
	hpBar->Pos() = { 540,975,0 };
	hpBar->Scale() *= 1.5f;

	idBar = new Quad(L"Textures/UI/IDBar.png");
	idBar->Pos() = { 330,1020,0 };
	idBar->Scale() *= 1.5f;
	idBar->UpdateWorld();

	itemSlot = new Quad(L"Textures/UI/ItemSlot.png");
	itemSlot->Pos() = { 1740,120,0 };
	itemSlot->Scale() *= 1.5f;
	itemSlot->UpdateWorld();

	lsGauge = new Quad(L"Textures/UI/LSGauge.png");
	lsGauge->Pos() = { 510,900,0 };
	lsGauge->Scale() *= 1.5f;
	lsGauge->UpdateWorld();

	quickSlot = new Quad(L"Textures/UI/ActionSlide.png");
	quickSlot->Pos() = { 1500,120,0 };
	quickSlot->Scale() *= 1.5f;
	quickSlot->UpdateWorld();

	slingerBug = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug->Scale() *= 1.5f;

	slingerBug2 = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug2->Scale() *= 1.5f;

	slingerBug3 = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug3->Scale() *= 1.5f;
	slingerBug3->SetActive(false);

	staminarBar = new Quad(L"Textures/UI/StaminaBar_noColor.png");
	staminarBar->Pos() = { 540,945,0 };
	staminarBar->Scale() *= 1.5f;

	monsterIcon = new Quad(L"Textures/UI/monsterIcon.png");
	monsterIcon->Pos() = { 1830,990,0 };
	monsterIcon->Scale() *= 0.45f;
	monsterIcon->UpdateWorld();

	iconFrame = new Quad(L"Textures/UI/frame2.png");
	iconFrame->Pos() = { 1830,990,0 };
	iconFrame->Scale() *= 2.4f;
	iconFrame->SetActive(false);

	hpBarEdge = new Quad(L"Textures/UI/BarEdge.png");
	hpBarEdge->Pos() = { 885,975,0 };
	hpBarEdge->Scale() *= 1.5f;
	hpBarEdge->UpdateWorld();

	staminarBarEdge = new Quad(L"Textures/UI/BarEdge2.png");
	staminarBarEdge->Pos() = { 885,945,0 };
	staminarBarEdge->Scale() *= 1.5f;
	staminarBarEdge->UpdateWorld();

	clockHand = new Quad(L"Textures/UI/clockhand.png");
	clockHand->Pos() = { 129,963,0 };
	clockHand->Scale() *= 1.5f;

	clockHand2 = new Quad(L"Textures/UI/clockhand2.png");
	clockHand2->Pos() = { 129,963,0 };
	clockHand2->Scale() *= 1.5f;
	clockHand2->Rot().z += XM_PIDIV2 * 2 / 3;
	clockHand2->UpdateWorld();

	blackCircle = new Quad(L"Textures/UI/blackCircle.png");
	blackCircle->SetActive(false);
	blackCircle2 = new Quad(L"Textures/UI/blackCircle.png");
	blackCircle2->SetActive(false);
	blackCircle3 = new Quad(L"Textures/UI/blackCircle.png");
	blackCircle3->SetActive(false);

	blackHalfCircle = new Quad(L"Textures/UI/blackHalfCircle.png");
	blackHalfCircle->SetActive(false);
	blackHalfCircle2 = new Quad(L"Textures/UI/blackHalfCircle.png");
	blackHalfCircle2->SetActive(false);
	blackHalfCircle3 = new Quad(L"Textures/UI/blackHalfCircle.png");
	blackHalfCircle3->SetActive(false);

	orangeLeftHalfCircle = new Quad(L"Textures/UI/orangeHalfCircle.png");
	orangeLeftHalfCircle->SetActive(false);
	orangeLeftHalfCircle2 = new Quad(L"Textures/UI/orangeHalfCircle.png");
	orangeLeftHalfCircle2->SetActive(false);
	orangeLeftHalfCircle3 = new Quad(L"Textures/UI/orangeHalfCircle.png");
	orangeLeftHalfCircle3->SetActive(false);

	orangeRightHalfCircle = new Quad(L"Textures/UI/orangeHalfCircle2.png");
	orangeRightHalfCircle->SetActive(false);
	orangeRightHalfCircle2 = new Quad(L"Textures/UI/orangeHalfCircle2.png");
	orangeRightHalfCircle2->SetActive(false);
	orangeRightHalfCircle3 = new Quad(L"Textures/UI/orangeHalfCircle2.png");
	orangeRightHalfCircle3->SetActive(false);

	questClearUI = new Quad(L"Textures/Quest/0.png");

	// 퀵슬롯 UI 추가
	quickSlot_Back = new Quad(L"Textures/UI/QickSlot_Back.png");
	quickSlot_Back->Pos() = { 1224, 200, 0 };
	quickSlot_Back->Scale() *= 0.3f;
	quickSlot_Back->UpdateWorld();

	quickSlot_Select = new Quad(L"Textures/UI/QickSlot_Select.png");
	quickSlot_Select->Pos() = { quickSlot_Back->Pos().x, quickSlot_Back->Pos().y, 0};
	quickSlot_Select->Scale() *= 0.42f;
	quickSlot_Select->Scale().x *= 0.88f;

	quickSlot_Button = new Quad(L"Textures/UI/MouseKeyIcon_WheelClick.png");
	quickSlot_Button->Pos() = { quickSlot_Back->Pos().x, quickSlot_Back->Pos().y };
	quickSlot_Button->Scale() *= 2.0f;

	// 드래그 UI 추가
	dragSlotBox = new Quad(L"Textures/UI/DragSlotBox.png");
	dragSlotBox->Scale() *= 2.3f;
	dragSlotBox->Scale().x *= 1.2f;
	dragSlotBox->Scale().y *= 1.25f;
	dragSlotBox->Pos() = { itemSlot->Pos().x + 10,itemSlot->Pos().y - 45,0};

	dragSlot_ButtonUp = new Quad(L"Textures/UI/MouseKeyIcon_WheelUp.png");
	dragSlot_ButtonUp->Pos() = { quickSlot->Pos().x + 130, quickSlot->Pos().y - 35 };
	dragSlot_ButtonUp->Scale() *= 0.9f;
	dragSlot_ButtonWheel = new Quad(L"Textures/UI/MouseKeyIcon_Wheel.png");
	dragSlot_ButtonWheel->Pos() = { quickSlot->Pos().x + 190, quickSlot->Pos().y };
	dragSlot_ButtonWheel->Scale() *= 0.9f;
	dragSlot_ButtonDown = new Quad(L"Textures/UI/MouseKeyIcon_WheelDown.png");
	dragSlot_ButtonDown->Pos() = { quickSlot->Pos().x + 358, quickSlot->Pos().y - 35 };
	dragSlot_ButtonDown->Scale() *= 0.9f;
	dragSlot_KeyButton = new Quad(L"Textures/UI/Keybord_E.png");
	dragSlot_KeyButton->Pos() = { quickSlot->Pos().x + 213, quickSlot->Pos().y - 35 };
	dragSlot_KeyButton->Scale() *= 0.9f;

	rideGarukIcon = new Quad(L"Textures/UI/RideGaruk_Icon.png");
	rideGarukIcon->Pos() = { quickSlot->Pos().x, quickSlot->Pos().y + 4,0 };
	rideGarukIcon->Scale() *= 1.2f;
	rideGarukIcon->UpdateWorld();

	// 슬롯 내임 들어갈 박스 추가
	FOR(11)
	{
		Quad* quad = new Quad(L"Textures/UI/SlotName.png");
		if (i == 0)
		{
			quad->Scale() *= 2.0f;
			quad->Scale().x *= 2.1f;
			quad->Pos() = { quickSlot->Pos().x - 28 , quickSlot->Pos().y + 43, 0};
		}
		if (i == 1)
		{
			quad->Scale() *= 2.0f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { quickSlot_Back->Pos().x - 24, quickSlot_Back->Pos().y - 77, 0 };
		}
		if (i == 2)
		{
			quad->Scale() *= 2.0f;
			quad->Scale().x *= 2.1f;
			quad->Pos() = { itemSlot->Pos().x - 20, itemSlot->Pos().y - 85, 0 };
		}
		if (i == 3)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 193, 160, 0 };
		}
		if (i == 4)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 393, 160, 0 };
		}
		if (i == 5)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 593, 160, 0 };
		}

		if (i == 6)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 793, 160, 0 };
		}

		if (i == 7)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 993, 160, 0 };
		}

		if (i == 8)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 1193, 160, 0 };
		}

		if (i == 9)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 1393, 160, 0 };
		}

		if (i == 10)
		{
			quad->Scale() *= 1.8f;
			quad->Scale().x *= 1.6f;
			quad->Pos() = { 1593, 160, 0 };
		}
		slotNames.push_back(quad);
		slotNames[i]->UpdateWorld();
	}

	FOR(8)
	{
		Quad* quad = new Quad(L"Textures/UI/ItemSlotBox.png");
		quad->Scale() *= 0.5f;
		if (i == 0)
		{
			quad->Pos() = { quickSlot_Back->Pos().x, quickSlot_Back->Pos().y + 130, 0}; // 0 번째
		}
		if (i == 1)
		{
			quad->Pos() = { quickSlot_Back->Pos().x + 93, quickSlot_Back->Pos().y + 85, 0 }; // 1 번째
		}
		if (i == 2)
		{
			quad->Pos() = { quickSlot_Back->Pos().x + 130, quickSlot_Back->Pos().y, 0 }; // 2 번째
		}
		if (i == 3)
		{
			quad->Pos() = { quickSlot_Back->Pos().x + 93, quickSlot_Back->Pos().y - 90, 0 }; // 3 번째
		}
		if (i == 4)
		{
			quad->Pos() = { quickSlot_Back->Pos().x, quickSlot_Back->Pos().y - 129, 0 }; // 4 번째
		}
		if (i == 5)
		{
			quad->Pos() = { quickSlot_Back->Pos().x - 93, quickSlot_Back->Pos().y - 90, 0 }; // 5 번째
		}
		if (i == 6)
		{
			quad->Pos() = { quickSlot_Back->Pos().x - 130, quickSlot_Back->Pos().y, 0 }; // 6 번째
		}
		if (i == 7)
		{
			quad->Pos() = { quickSlot_Back->Pos().x - 93, quickSlot_Back->Pos().y + 85, 0 }; // 7 번째
		}
		selectBoxs.push_back(quad);
		selectBoxs[i]->UpdateWorld();
	}

	FOR(8)
	{
		Quad* quad = new Quad(L"Textures/UI/ItemSlot.png");
		quad->Scale() *= 1.28f;
		quad->Pos().x = selectBoxs[i]->Pos().x - 3;
		quad->Pos().y = selectBoxs[i]->Pos().y + 2;
		selectBoxFrames.push_back(quad);
		selectBoxFrames[i]->UpdateWorld();
	}

	FOR(8)
	{
		Quad* quad = new Quad(L"Textures/UI/KeyNumber_SlotBox.png");
		quad->Scale() *= 1.5f;
		if (i == 0)
		{
			quad->Pos() = { 210, 220, 0 }; // 0 번째
		}
		if (i == 1)
		{
			quad->Pos() = { 410, 220, 0 }; // 1 번째
		}
		if (i == 2)
		{
			quad->Pos() = { 610, 220, 0 }; // 2 번째
		}
		if (i == 3)
		{
			quad->Pos() = { 810, 220, 0 }; // 3 번째
		}
		if (i == 4)
		{
			quad->Pos() = { 1010, 220, 0 }; // 4 번째
		}
		if (i == 5)
		{
			quad->Pos() = { 1210, 220, 0 }; // 5 번째
		}
		if (i == 6)
		{
			quad->Pos() = { 1410, 220, 0 }; // 6 번째
		}
		if (i == 7)
		{
			quad->Pos() = { 1610, 220, 0 }; // 7 번째
		}
		numberBoxs.push_back(quad);
		numberBoxs[i]->UpdateWorld();
	}
	FOR(8)
	{
		Quad* quad = new Quad(L"Textures/UI/ItemSlot.png");
		quad->Scale() *= 1.33f;
		quad->Pos() = numberBoxs[i]->Pos();
		numberBoxFrames.push_back(quad);
		numberBoxFrames[i]->UpdateWorld();
	}

	//캐릭터용 UI 추가
	hp = new ProgressBar(
		L"Textures/Color/Hp.png",
		L"Textures/UI/HpBar_noColor1.png"
	);
	recover = new ProgressBar(
		L"Textures/Color/Damaged.png",
		L"Textures/Color/Black.png"
	);
	stamina = new ProgressBar(
		L"Textures/Color/Staminar.png",
		L"Textures/UI/StaminaBar_noColor.png"
	);

	durability_gauge = new ProgressBar(
		L"Textures/Color/Durability.png",
		L"Textures/UI/StaminaBar_noColor.png"
	);
	lsGauge2 = new ProgressBar(
		L"Textures/UI/LSGauge2.png",
		L"Textures/UI/nonebg.png"
	);
	lsCoting = new ProgressBar(
		L"Textures/UI/LSCoting_none.png",
		L"Textures/UI/LSCoting_none.png"
	);

	valphalkStateIcon1 = new Quad(L"Textures/UI/StateIcon.png");
	valphalkStateIcon1->Pos() = { 1700, 600 };
	valphalkStateIcon2 = new Quad(L"Textures/UI/StateIcon.png");
	valphalkStateIcon2->Pos() = { 1700, 500 };

	// 아이템 아이콘 추가 (퀵슬롯 쪽)
	potionIcon_Q = new Quad(L"Textures/UI/Potion.png");
	potionIcon_Q->Pos() = { quickSlot_Back->Pos().x + 89.5f, quickSlot_Back->Pos().y + 87, 0 };
	potionIcon_Q->Scale() *= 0.9;
	greatepotionIcon_Q = new Quad(L"Textures/UI/GreatePotion.png");
	greatepotionIcon_Q->Pos() = { quickSlot_Back->Pos().x - 4.5f, quickSlot_Back->Pos().y + 133.5f, 0 };
	greatepotionIcon_Q->Scale() *= 0.9;
	whetstoneIcon_Q = new Quad(L"Textures/UI/Whetstone-icon.png");
	whetstoneIcon_Q->Pos() = { quickSlot_Back->Pos().x + 127.5f, quickSlot_Back->Pos().y + 2.5f, 0 };
	whetstoneIcon_Q->Scale() *= 0.95;
	// 아이템 아이콘 추가 (드래그 슬롯 쪽)
	//FOR(2)
	//{
	//	if (i == 0)
	//	{
	//		Quad* quad = new Quad(L"Textures/UI/ItemSlot.png");
	//		quad->Pos() = { itemSlot->Pos().x + 81,itemSlot->Pos().y + 4,0 };
	//		quad->Scale() *= 1.25f;
	//		inItDragItem_D.push_back(quad);
	//	}
	//	if (i == 1)
	//	{
	//		Quad* quad = new Quad(L"Textures/UI/Whetstone-icon.png");
	//		quad->Pos() = { itemSlot->Pos().x + 81,itemSlot->Pos().y + 4,0 };
	//		quad->Scale() *= 1.25f;
	//		inItDragItem_D.push_back(quad);
	//	}
	//}
	potionIcon_D = new Quad(L"Textures/UI/Potion.png");
	potionIcon_D->Pos() = { itemSlot->Pos().x -83,itemSlot->Pos().y + 2,0 };
	potionIcon_D->Scale() *= 1.2;
	greatepotionIcon_D = new Quad(L"Textures/UI/GreatePotion.png");
	greatepotionIcon_D->Pos() = { itemSlot->Pos().x - 3,itemSlot->Pos().y + 3,0 };
	greatepotionIcon_D->Scale() *= 1.2;
	whetstoneIcon_D = new Quad(L"Textures/UI/Whetstone-icon.png");
	whetstoneIcon_D->Pos() = { itemSlot->Pos().x + 81,itemSlot->Pos().y + 4,0 };
	whetstoneIcon_D->Scale() *= 1.25;
	// 아이템 아이콘 추가 (넘버 슬롯 쪽)
	potionIcon_N = new Quad(L"Textures/UI/Potion.png");
	potionIcon_N->Pos() = { 210, 220, 0 };
	potionIcon_N->Scale() *= 1.1;
	greatepotionIcon_N = new Quad(L"Textures/UI/GreatePotion.png");
	greatepotionIcon_N->Pos() = { 408, 220, 0 };
	greatepotionIcon_N->Scale() *= 1.1;
	whetstoneIcon_N = new Quad(L"Textures/UI/Whetstone-icon.png");
	whetstoneIcon_N->Pos() = { 610, 222, 0 };
	whetstoneIcon_N->Scale() *= 1.25;

	FOR(20)
	{
		wstring texture;
		if (i < 10)
		{
			texture = L"Textures/UI/Number" + to_wstring(i) + L".png";
			Quad* quad = new Quad(texture);
			quad->Pos().x = greatepotionIcon_Q->Pos().x + 15;
			quad->Pos().y = greatepotionIcon_Q->Pos().y - 16;
			quad->Scale() *= 0.4;
			itemNumber_Q.push_back(quad);
			itemNumber_Q[i]->UpdateWorld();
		}
		else if (i >= 10)
		{
			texture = L"Textures/UI/Number" + to_wstring(i - 10) + L".png";
			Quad* quad = new Quad(texture);
			quad->Pos().x = potionIcon_Q->Pos().x + 15;
			quad->Pos().y = potionIcon_Q->Pos().y - 16;
			quad->Scale() *= 0.4;
			itemNumber_Q.push_back(quad);
			itemNumber_Q[i]->UpdateWorld();
		}
	}

	FOR(10)
	{
		wstring texture;
		texture = L"Textures/UI/Number" + to_wstring(i) + L".png";
		Quad* quad = new Quad(texture);
		quad->Pos().x = greatepotionIcon_D->Pos().x + 15;
		quad->Pos().y = greatepotionIcon_D->Pos().y - 16;
		quad->Scale() *= 0.4;
		itemNumber_D.push_back(quad);
		itemNumber_D[i]->UpdateWorld();
	}

	FOR(20)
	{
		wstring texture;
		if (i < 10)
		{
			texture = L"Textures/UI/Number" + to_wstring(i) + L".png";
			Quad* quad = new Quad(texture);
			quad->Pos().x = greatepotionIcon_N->Pos().x + 15;
			quad->Pos().y = greatepotionIcon_N->Pos().y - 16;
			quad->Scale() *= 0.4;
			itemNumber_N.push_back(quad);
			itemNumber_N[i]->UpdateWorld();
		}
		else if (i >= 10)
		{
			texture = L"Textures/UI/Number" + to_wstring(i - 10) + L".png";
			Quad* quad = new Quad(texture);
			quad->Pos().x = potionIcon_N->Pos().x + 15;
			quad->Pos().y = potionIcon_N->Pos().y - 16;
			quad->Scale() *= 0.4;
			itemNumber_N.push_back(quad);
			itemNumber_N[i]->UpdateWorld();
		}
	}

	FOR(8)
	{
		wstring texture;
		texture = L"Textures/UI/KeybordNumber" + to_wstring(i+1) + L".png";
		Quad* quad = new Quad(texture);
		quad->Pos().x = slotNames[i + 3]->Pos().x + 17;
		quad->Pos().y = slotNames[i + 3]->Pos().y - 18;
		itemKeyNumber_N.push_back(quad);
		itemKeyNumber_N[i]->UpdateWorld();
	}

	// hp bar ui
	hp->Scale() = { 2.625f,0.03f,0 };
	hp->Pos() = hpBar->Pos();
	hp->Pos().x -= 0.1f;
	curHP = maxHP;
	recover->Scale() = hp->Scale();
	recover->Pos() = hp->Pos();

	// stamina bar ui
	stamina->Scale() = { 2.625f,0.03f,0 };
	stamina->Pos() = staminarBar->Pos();
	stamina->Pos().x -= 0.1f;
	curStamina = maxStamina;

	//durability_gauge ui
	durability_gauge->Scale() = { 0.45f,0.03f,0 };
	durability_gauge->Pos() = durability_back->Pos();
	curDurability = maxDurability;

	//기인게이지 UI
	lsGauge2->Scale() = { 1.5f,1.35f,0 };
	lsGauge2->Pos() = lsGauge->Pos();
	lsGauge2->Pos().x += 13.0f;

	//코팅 UI
	lsCoting->Pos() = { 510,900,0 };
	lsCoting->Scale() *= 1.5f;

	// 퀘스트 클리어 UI
	questClearUI->Pos() = { CENTER_X , CENTER_Y, 0 };

	ItemManager::Get();
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
	delete slingerBug2;
	delete slingerBug3;
	delete staminarBar;
	delete hp;
	delete recover;
	delete stamina;
	delete durability_gauge;
	delete monsterIcon;
	delete iconFrame;
	delete hpBarEdge;
	delete staminarBarEdge;
	delete clockHand;
	delete clockHand2;
	delete blackCircle;
	delete blackCircle2;
	delete blackCircle3;
	delete blackHalfCircle;
	delete blackHalfCircle2;
	delete blackHalfCircle3;
	delete orangeLeftHalfCircle;
	delete orangeLeftHalfCircle2;
	delete orangeLeftHalfCircle3;
	delete orangeRightHalfCircle;
	delete orangeRightHalfCircle2;
	delete orangeRightHalfCircle3;
	delete quickSlot_Back;
	delete quickSlot_Select;
	delete quickSlot_Button;
	FOR(selectBoxs.size())
	{
		delete selectBoxs[i];
	}
	FOR(selectBoxFrames.size())
	{
		delete selectBoxFrames[i];
	}
	FOR(numberBoxs.size())
	{
		delete numberBoxs[i];
	}
	FOR(numberBoxFrames.size())
	{
		delete numberBoxFrames[i];
	}
	delete dragSlotBox;
	delete dragSlot_ButtonUp;
	delete dragSlot_ButtonWheel;
	delete dragSlot_ButtonDown;
	delete dragSlot_KeyButton;
	FOR(slotNames.size())
	{
		delete slotNames[i];
	}
	delete potionIcon_Q;
	delete greatepotionIcon_Q;
	delete whetstoneIcon_Q;
	//FOR(inItDragItem_D.size())
	//{
	//	delete inItDragItem_D[i];
	//}
	delete potionIcon_D;
	delete greatepotionIcon_D;
	delete whetstoneIcon_D;
	delete potionIcon_N;
	delete greatepotionIcon_N;
	delete whetstoneIcon_N;
	FOR(itemNumber_Q.size())
	{
		delete itemNumber_Q[i];
	}
	FOR(itemNumber_D.size())
	{
		delete itemNumber_D[i];
	}
	FOR(itemNumber_N.size())
	{
		delete itemNumber_N[i];
	}
	FOR(itemKeyNumber_N.size())
	{
		delete itemKeyNumber_N[i];
	}
	delete valphalkStateIcon1;
	delete valphalkStateIcon2;
	delete questClearUI;
}

void UIManager::Update()
{
	ItemManager::Get()->Update();
	DragInvenItem();
	NumberSlotBar();
	DragSlotBar();
	QuickSlotBar();
	StateIcon();

	UIAlphaOn();

	stamina->UpdateWorld();
	recover->UpdateWorld();
	hp->UpdateWorld();
	durability_back->UpdateWorld();
	hpBar->UpdateWorld();
	lsCoting->UpdateWorld();
	lsGauge2->UpdateWorld();
	slingerBug->UpdateWorld();
	slingerBug2->UpdateWorld();
	slingerBug3->UpdateWorld();
	staminarBar->UpdateWorld();
	durability_gauge->UpdateWorld();
	iconFrame->UpdateWorld();
	clockHand->UpdateWorld();
	blackCircle->UpdateWorld();
	blackCircle2->UpdateWorld();
	blackCircle3->UpdateWorld();
	blackHalfCircle->UpdateWorld();
	blackHalfCircle2->UpdateWorld();
	blackHalfCircle3->UpdateWorld();
	orangeLeftHalfCircle->UpdateWorld();
	orangeLeftHalfCircle2->UpdateWorld();
	orangeLeftHalfCircle3->UpdateWorld();
	orangeRightHalfCircle->UpdateWorld();
	orangeRightHalfCircle2->UpdateWorld();
	orangeRightHalfCircle3->UpdateWorld();
	quickSlot_Back->UpdateWorld();
	quickSlot_Select->UpdateWorld();
	quickSlot_Button->UpdateWorld();
	dragSlotBox->UpdateWorld();
	dragSlot_ButtonUp->UpdateWorld();
	dragSlot_ButtonWheel->UpdateWorld();
	dragSlot_ButtonDown->UpdateWorld();
	dragSlot_KeyButton->UpdateWorld();
	questClearUI->UpdateWorld();
	// 잠시 넣음
	//===================
	potionIcon_Q->UpdateWorld();
	greatepotionIcon_Q->UpdateWorld();
	whetstoneIcon_Q->UpdateWorld();
	//FOR(inItDragItem_D.size())
	//{
	//	inItDragItem_D[i]->UpdateWorld();
	//}
	potionIcon_D->UpdateWorld();
	greatepotionIcon_D->UpdateWorld();
	whetstoneIcon_D->UpdateWorld();
	potionIcon_N->UpdateWorld();
	greatepotionIcon_N->UpdateWorld();
	whetstoneIcon_N->UpdateWorld();
	FOR(itemNumber_Q.size())
	{
		itemNumber_Q[i]->UpdateWorld();
	}
	FOR(itemNumber_D.size())
	{
		itemNumber_D[i]->UpdateWorld();
	}
	FOR(itemNumber_N.size())
	{
		itemNumber_N[i]->UpdateWorld();
	}
	FOR(itemKeyNumber_N.size())
	{
		itemKeyNumber_N[i]->UpdateWorld();
	}
	//===================

	FOR(selectBoxs.size())
	{
		selectBoxs[i]->UpdateWorld();
	}
	FOR(selectBoxFrames.size())
	{
		selectBoxFrames[i]->UpdateWorld();
	}
	FOR(numberBoxs.size())
	{
		numberBoxs[i]->UpdateWorld();
	}
	FOR(numberBoxFrames.size())
	{
		numberBoxFrames[i]->UpdateWorld();
	}
	valphalkStateIcon1->UpdateWorld();
	valphalkStateIcon2->UpdateWorld();
	//hp, stamina 부분
	hp->SetAmount(curHP / maxHP);
	recover->SetAmount(recoverHP / maxHP);
	stamina->SetAmount(curStamina / maxStamina);
	if (curHP < recoverHP) // 빨간체력까지 자연회복
		curHP += 0.1f * DELTA;
	if (curHP > recoverHP)
		recoverHP = curHP;

	if (staminaActive == false) // 행동이 끝나면 스태미너 자연회복
		curStamina += 7.5f * DELTA;
	if (curStamina >= maxStamina) // 최대 스태미나까지만 자연회복
		curStamina = maxStamina;


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
	//예리도는 0 이하로 떨어지지 않는다.
	if (curDurability <= 0.0f)
		curDurability = 0;

	//if (curDurability < 0.0f)
	//	SharpeningStone();
	////////////////////////////////

	//기인게이지 부분
	lsGauge2->SetAmount(curSpiritGauge / maxSpiritGauge);

	if (curSpiritGauge > 0.0f)
		curSpiritGauge -= 0.1f * DELTA;
	if (curSpiritGauge <= 0)
		curSpiritGauge = 0;

	if (isBonus)
	{
		bonusTime += 0.1f * DELTA;
		curSpiritGauge += 0.2f * DELTA;
	}

	if (bonusTime > limitTime)
	{
		bonusTime = 0.0f;
		isBonus = false;
		lsGauge2->SetTexture(L"Textures/UI/LSGauge2.png");
	}

	if (bonus154 == true)
	{
		bonusTime += DELTA;
		if (bonusTime < limitTime)
		{
			lsGauge2->SetTexture(L"Textures/UI/LSGauge2_blue.png");
			curSpiritGauge += 2.f * DELTA;
		}
		else
		{
			lsGauge2->SetTexture(L"Textures/UI/LSGauge2.png");
			bonus154 = false;
		}
	}

	////////////////////////////////
	//기인게이지 샘플상황, 변경 필요
	//if (curGauge < 100.0f)
	//	curGauge += 0.2f;

	//if (curGauge > 100.0f)
	//{
	//	curGauge = 0.0f;
	//	curCoting = 100.0f;

	//	if (cotingLevel < 3)
	//		cotingLevel += 1 * DELTA;
	//}

	//if (KEY_PRESS('W'))
	//	GaugeBonus();

	if (cotingLevel <= 3 && cotingLevel > 0) // 코팅레벨이 1이상이라면 게이지 주기적 감소
	{
		curCoting -= .3f * DELTA;
	}
	////////////////////////////////

	//코팅 부분
	lsCoting->SetAmount(curCoting / maxCoting);

	if (cotingLevel == 0)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_none.png");
	if (cotingLevel == 1)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_white.png");
	if (cotingLevel == 2)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_yellow.png");
	if (cotingLevel == 3)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_red.png");

	if (curCoting <= 0.0f) // 게이지는 100을 넘지않고 0을 넘지않게
		curCoting = 0;
	if (curCoting >= 100.0f)
		curCoting = 100;

	//타켓 아이콘 샘플 상황, 추후 변경 필요
	TargetMonster();

	//시곗바늘 부분 : 목표 : 5분당 30도 돌아가게 해야함
	//밑의 샘플은 빠르게 돌아가는걸 보여주는 예시
	if (clockHand->Rot().z > -XM_PIDIV2 * 10 / 3)
		clockHand->Rot().z -= XM_PIDIV2 * 1 / 720;

	//밧줄벌레 쿨타임 부분 - 회복속도는 샘플, 조정 필요
	if (bugCount == 2)
	{
		slingerBug->Pos() = { 997.5,120,0 };
		slingerBug2->Pos() = { 922.5,120,0 };

		slingerBug3->SetActive(false);
		blackCircle3->SetActive(false);
		blackHalfCircle3->SetActive(false);
		orangeLeftHalfCircle3->SetActive(false);
		orangeRightHalfCircle3->SetActive(false);
	}
	else if (bugCount == 3)
	{
		slingerBug->Pos() = { 960,120,0 };
		slingerBug2->Pos() = { 885,120,0 };

		slingerBug3->SetActive(true);
		slingerBug3->Pos() = { 1035,120,0 };
	}

	if (getWildBug)
		wildBugDuration += DELTA;

	if (wildBugDuration > wildBugDurationLimit)
	{
		getWildBug = false;
		bugCount = 2;
		wildBugDuration = 0.0f;
	}

	blackCircle->Pos() = slingerBug->Pos();
	blackHalfCircle->Pos() = slingerBug->Pos();
	orangeLeftHalfCircle->Pos() = slingerBug->Pos();
	orangeRightHalfCircle->Pos() = slingerBug->Pos();

	blackCircle2->Pos() = slingerBug2->Pos();
	blackHalfCircle2->Pos() = slingerBug2->Pos();
	orangeLeftHalfCircle2->Pos() = slingerBug2->Pos();
	orangeRightHalfCircle2->Pos() = slingerBug2->Pos();

	blackCircle3->Pos() = slingerBug3->Pos();
	blackHalfCircle3->Pos() = slingerBug3->Pos();
	orangeLeftHalfCircle3->Pos() = slingerBug3->Pos();
	orangeRightHalfCircle3->Pos() = slingerBug3->Pos();



	if (isCoolTime1)
	{
		slingerBug->SetActive(false);
		blackCircle->SetActive(true);
		blackHalfCircle->SetActive(true);
		orangeLeftHalfCircle->SetActive(true);
		orangeRightHalfCircle->SetActive(true);
	}

	if (isCoolTime2)
	{
		slingerBug2->SetActive(false);
		blackCircle2->SetActive(true);
		blackHalfCircle2->SetActive(true);
		orangeLeftHalfCircle2->SetActive(true);
		orangeRightHalfCircle2->SetActive(true);
	}

	if (bugCount == 3 && isCoolTime3)
	{
		slingerBug3->SetActive(false);
		blackCircle3->SetActive(true);
		blackHalfCircle3->SetActive(true);
		orangeLeftHalfCircle3->SetActive(true);
		orangeRightHalfCircle3->SetActive(true);
	}

	/////////////////////////
	//샘플 상황
	if (orangeLeftHalfCircle->Active())
		orangeLeftHalfCircle->Rot().z += XM_PIDIV2 * 1 / 360; // 쿨타임 회복속도 부분

	if (orangeLeftHalfCircle2->Active())
		orangeLeftHalfCircle2->Rot().z += XM_PIDIV2 * 1 / 360; // 쿨타임 회복속도 부분

	if (orangeLeftHalfCircle3->Active() || bugCount == 2)
		orangeLeftHalfCircle3->Rot().z += XM_PIDIV2 * 1 / 360; // 쿨타임 회복속도 부분

	/////////////////////////

	if (orangeLeftHalfCircle->Rot().z > XM_2PI)
	{
		orangeLeftHalfCircle->Rot().z -= XM_2PI;
		isCoolTime1 = false;

		slingerBug->SetActive(true);
		blackCircle->SetActive(false);
		blackHalfCircle->SetActive(false);
		orangeLeftHalfCircle->SetActive(false);
		orangeRightHalfCircle->SetActive(false);
	}

	if (orangeLeftHalfCircle2->Rot().z > XM_2PI)
	{
		orangeLeftHalfCircle2->Rot().z -= XM_2PI;
		isCoolTime2 = false;

		slingerBug2->SetActive(true);
		blackCircle2->SetActive(false);
		blackHalfCircle2->SetActive(false);
		orangeLeftHalfCircle2->SetActive(false);
		orangeRightHalfCircle2->SetActive(false);
	}

	if (orangeLeftHalfCircle3->Rot().z > XM_2PI)
	{
		orangeLeftHalfCircle3->Rot().z -= XM_2PI;
		isCoolTime3 = false;

		slingerBug3->SetActive(true);
		blackCircle3->SetActive(false);
		blackHalfCircle3->SetActive(false);
		orangeLeftHalfCircle3->SetActive(false);
		orangeRightHalfCircle3->SetActive(false);
	}
}

void UIManager::PostRender()
{
	if (!isRender)
	{
		questClearUI->Render();
		return;
	}

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

	// 이건 한번 더 봐야 알듯
	// 액션 슬롯 내임 스페이스
	slotNames[0]->Render();
	Font::Get()->RenderText("탑승한다", {slotNames[0]->Pos().x + 70 ,slotNames[0]->Pos().y + 18});

	quickSlot->Render();
	slingerBug->Render();
	slingerBug2->Render();
	slingerBug3->Render();
	staminarBar->Render();
	durability_gauge->Render();
	monsterIcon->Render();
	iconFrame->Render();
	hpBarEdge->Render();
	staminarBarEdge->Render();
	clockHand->Render();
	clockHand2->Render();

	rideGarukIcon->Render();

	blackCircle->Render();
	orangeLeftHalfCircle->Render();
	if (orangeLeftHalfCircle->Rot().z < XM_PI)
		blackHalfCircle->Render();
	if (orangeLeftHalfCircle->Rot().z > XM_PI)
		orangeRightHalfCircle->Render();

	blackCircle2->Render();
	orangeLeftHalfCircle2->Render();
	if (orangeLeftHalfCircle2->Rot().z < XM_PI)
		blackHalfCircle2->Render();
	if (orangeLeftHalfCircle2->Rot().z > XM_PI)
		orangeRightHalfCircle2->Render();

	blackCircle3->Render();
	orangeLeftHalfCircle3->Render();
	if (orangeLeftHalfCircle3->Rot().z < XM_PI)
		blackHalfCircle3->Render();
	if (orangeLeftHalfCircle3->Rot().z > XM_PI)
		orangeRightHalfCircle3->Render();

	DragSlot();
	QuickSlot();
	NumberSlot();
	if (partDestruct)
	{
		valphalkStateIcon1->Render();
		Font::Get()->RenderText("영묘한 광채의 발파루크", { valphalkStateIcon1->Pos().x + 108, valphalkStateIcon1->Pos().y + 18 });
		Font::Get()->RenderText("부위 파괴", { valphalkStateIcon1->Pos().x - 18, valphalkStateIcon1->Pos().y - 15 });
	}
	if (partDestruct2)
	{
		valphalkStateIcon2->Render();
		Font::Get()->RenderText("영묘한 광채의 발파루크", { valphalkStateIcon2->Pos().x + 108, valphalkStateIcon2->Pos().y + 18 });
		Font::Get()->RenderText("부위 파괴", { valphalkStateIcon2->Pos().x - 18, valphalkStateIcon2->Pos().y - 15 });
	}
	if (specialMove)
	{
		valphalkStateIcon1->Render();
		Font::Get()->RenderText("영묘한 광채의 발파루크", { valphalkStateIcon1->Pos().x + 108, valphalkStateIcon1->Pos().y + 18 });
		Font::Get()->RenderText("습격", { valphalkStateIcon1->Pos().x - 68, valphalkStateIcon1->Pos().y - 15 });	
	}
	if (specialMove2)
	{
		valphalkStateIcon2->Render();
		Font::Get()->RenderText("영묘한 광채의 발파루크", { valphalkStateIcon2->Pos().x + 108, valphalkStateIcon2->Pos().y + 18 });
		Font::Get()->RenderText("습격", { valphalkStateIcon2->Pos().x - 68, valphalkStateIcon2->Pos().y - 15 });
	}

	//ItemManager::Get()->PostRender();

	//FOR(inItDragItem_D.size())
	//{
	//	inItDragItem_D[i]->Render();
	//}
}

void UIManager::GUIRender()
{
	//ImGui::SliderFloat3("qickSlot_Select", (float*)&quickSlot_Select->Rot(), 0, -6.3);
	//ImGui::SliderFloat3("qickSlot_Select", (float*)&quickSlot_Select->Rot(), 0, -1.0f);
	//ImGui::SliderFloat3("selectBoxs", (float*)&selectBoxs[5]->Pos(), 100, 1500);
	//ImGui::SliderFloat3("selectBoxFrames", (float*)&selectBoxFrames[5]->Pos(), 100, 1500);

	//ImGui::SliderFloat3("DragSlotBox", (float*)&dragSlotBox->Pos(), 1500, 2000);
	//ImGui::SliderFloat3("SlotName1", (float*)&slotName1->Pos(), 100, 1500);
	//ImGui::SliderFloat3("SlotName2", (float*)&slotName2->Pos(), 100, 1500);
	//
	//ImGui::Text("MousePos_X : %f", MousePos.x);
	//ImGui::Text("mousePos_X : %f", mousePos.x);
	//ImGui::Text("MousePos_Y : %f", MousePos.y);
	//ImGui::Text("mousePos_Y : %f", mousePos.y);
	//
	//ImGui::Text("CAM_Rot_X: %f", CAM->Rot().x);
	//ImGui::Text("CamRot_X: %f", CamRot);
	//ImGui::Text("CAM_Rot_Y: %f", CAM->Rot().y);
	//ImGui::Text("CamRot_Y: %f", CamRot.y);

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
	curHP += 20.0f * DELTA;
}

void UIManager::LargeHealthPotion()
{
	curHP += 30.f * DELTA;
}

void UIManager::Running()
{
	curStamina -= 3.2f * DELTA;
}

void UIManager::Roll()
{
	curStamina -= 15.f;
}

void UIManager::ReduceDurability()
{
	curDurability -= 0.1f * DELTA;
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

void UIManager::TargetMonster()
{
	if (KEY_DOWN('G'))
	{
		if (iconFrame->Active() == false)
			iconFrame->SetActive(true);
		else if (iconFrame->Active() == true)
			iconFrame->SetActive(false);
	}
}

void UIManager::GetWildBug()
{
	bugCount++;

	getWildBug = true;
}

void UIManager::PlusSpritGauge()
{
	curSpiritGauge += 15.0f;
	if (curSpiritGauge > maxSpiritGauge)
		curSpiritGauge = maxSpiritGauge;
}

void UIManager::DoublePlusSpritGauge()
{
	curSpiritGauge += 25.0f;
	if (curSpiritGauge > maxSpiritGauge)
		curSpiritGauge = maxSpiritGauge;
}

void UIManager::MinusSpiritGauge()
{
	curSpiritGauge -= 20.0f;
	if (curSpiritGauge < 0)
		curSpiritGauge = 0;
}

void UIManager::UIAlphaOn()
{
	if (isRender)
		return;

	clearUITimer += DELTA;

	if (clearUITimer > 0.01f && clearCount < 11)
	{
		questClearUI->SetTexture(L"Textures/Quest/" + to_wstring(clearCount) + L".png");
		clearCount++;
		clearUITimer = 0.0f;
	}
}

void UIManager::QuickSlot()
{

	if (KEY_PRESS('X')) // X 만 누르면 슬롯만 나옴
	{
		quickSlot_Back->Render();
		slotNames[1]->Render();

		FOR(selectBoxs.size())
		{
			selectBoxs[i]->Render();
		}

		if (quickSlot_Select->Rot().z > -0.42f && useSelectBar)
		{
			selectBoxFrames[0]->Render();
			Font::Get()->RenderText("그레이트 물약", { slotNames[1]->Pos().x + 88, slotNames[1]->Pos().y + 18 });
		}
		if (quickSlot_Select->Rot().z < -5.98f && useSelectBar)
		{
			selectBoxFrames[0]->Render();
			Font::Get()->RenderText("그레이트 물약", { slotNames[1]->Pos().x + 88, slotNames[1]->Pos().y + 18 });
		}
		if (quickSlot_Select->Rot().z <= -0.42f && quickSlot_Select->Rot().z > -1.2f && useSelectBar)
		{
			selectBoxFrames[1]->Render();
			Font::Get()->RenderText("일반 물약", { slotNames[1]->Pos().x + 70, slotNames[1]->Pos().y + 18 });

		}
		if (quickSlot_Select->Rot().z <= -1.2f && quickSlot_Select->Rot().z > -1.98f && useSelectBar)
		{
			selectBoxFrames[2]->Render();
			Font::Get()->RenderText("숫돌", { slotNames[1]->Pos().x + 40, slotNames[1]->Pos().y + 18 });

		}
		if (quickSlot_Select->Rot().z <= -1.98f && quickSlot_Select->Rot().z > -2.78f && useSelectBar)
		{
			selectBoxFrames[3]->Render();

		}
		if (quickSlot_Select->Rot().z <= -2.78f && quickSlot_Select->Rot().z > -3.6f && useSelectBar)
		{
			selectBoxFrames[4]->Render();

		}
		if (quickSlot_Select->Rot().z <= -3.6f && quickSlot_Select->Rot().z > -4.38f && useSelectBar)
		{
			selectBoxFrames[5]->Render();

		}
		if (quickSlot_Select->Rot().z <= -4.38f && quickSlot_Select->Rot().z > -5.12f && useSelectBar)
		{
			selectBoxFrames[6]->Render();

		}
		if (quickSlot_Select->Rot().z <= -5.12f && quickSlot_Select->Rot().z > -5.98f && useSelectBar)
		{
			selectBoxFrames[7]->Render();

		}
		if (useSelectBar)
		{
			quickSlot_Select->Render();
		}
		quickSlot_Button->Render();

		potionIcon_Q->Render();
		greatepotionIcon_Q->Render();
		whetstoneIcon_Q->Render();

		if (haveGPotion < 10)
		{
			itemNumber_Q[haveGPotion]->Pos().x = 1234.5;
			itemNumber_Q[haveGPotion]->Render();
		}
		else if (haveGPotion == 10)
		{
			itemNumber_Q[1]->Pos().x = 1228;
			itemNumber_Q[0]->Pos().x = 1241;
			itemNumber_Q[1]->Render();
			itemNumber_Q[0]->Render();
		}

		if (10 <= havePotion && havePotion < 20)
		{
			itemNumber_Q[havePotion]->Pos().x = 1328.5;
			itemNumber_Q[havePotion]->Render();
		}
		else if (havePotion == 20)
		{
			itemNumber_Q[11]->Pos().x = 1317;
			itemNumber_Q[10]->Pos().x = 1330;
			itemNumber_Q[11]->Render();
			itemNumber_Q[10]->Render();
		}
	}
}

void UIManager::QuickSlotBar()
{

	if (quickSlot_Select->Rot().z <= -3.0f && quickSlot_Select->Rot().z >= -6.0f)
	{
		quickSlot_Select->Pos() = { quickSlot_Back->Pos().x - 2.5f, quickSlot_Back->Pos().y, 0 };
	}
	else if (quickSlot_Select->Rot().z > -3.0f && quickSlot_Select->Rot().z < -6.0f)
	{
		quickSlot_Select->Pos() = { quickSlot_Back->Pos().x, quickSlot_Back->Pos().y, 0 };
	}

	if (KEY_DOWN('X'))
	{
		MousePos = mousePos;
	}
	else if (KEY_UP('X'))
	{
		useSelectBar = false;
		if (MousePos.y > CENTER_Y)
		{
			SetCursorPos(MousePos.x + 8.0f, CENTER_Y - Distance(MousePos.y, CENTER_Y) + 31.0f);
		}
		else if (MousePos.y <= CENTER_Y)
		{
			SetCursorPos(MousePos.x + 8.0f, CENTER_Y + Distance(MousePos.y, CENTER_Y) + 31.0f);
		}
	}

	if (KEY_PRESS('X'))
	{
		if (MousePos.y > CENTER_Y && !KEY_PRESS(VK_MBUTTON))// C 누르기 에서 마우스 휠 버튼 누르기로
		{
			SetCursorPos(MousePos.x + 8.0f, CENTER_Y - Distance(MousePos.y, CENTER_Y) + 31.0f);
		}
		else if (MousePos.y <= CENTER_Y && !KEY_PRESS(VK_MBUTTON))// C 누르기 에서 마우스 휠 버튼 누르기로
		{
			SetCursorPos(MousePos.x + 8.0f, CENTER_Y + Distance(MousePos.y, CENTER_Y) + 31.0f);
		}
		if (KEY_PRESS(VK_MBUTTON)) // 마우스 휠 버튼 을 누른다면 Bar 활성화
		{
			useSelectBar = true;
		}
	}

	if (KEY_PRESS('X') && KEY_PRESS(VK_MBUTTON))
		// X 와 마우스 휠 버튼 을 누르면 Bar 보이면서 마우스 휠 버튼 누르기 를 때어도 Bar는 보임 
		// 대신 X 를 놓는거 아님 사용 하는거 아님
	{
		// 마우스가 오른쪽으로 가면 오른쪽 방향으로 바늘이 회전
		// 마우스가 왼쪽 으로 가면 왼쪽으로 회전
		//SetCursorPos(quickSlot_Back->Pos().x + 8.069f, quickSlot_Back->Pos().y);
		//Vector3 pos = mousePos - Vector3(quickSlot_Back->Pos().x, quickSlot_Back->Pos().y);
		if (MousePos.y > CENTER_Y)
		{
			SetCursorPos(MousePos.x + 8.0f, CENTER_Y - Distance(MousePos.y, CENTER_Y) + 31.0f);
		}
		else if (MousePos.y <= CENTER_Y)
		{
			SetCursorPos(MousePos.x + 8.0f, CENTER_Y + Distance(MousePos.y, CENTER_Y) + 31.0f);
		}
		Vector3 pos = mousePos - Vector3(MousePos.x , CENTER_Y - Distance(MousePos.y, CENTER_Y));
		quickSlot_Select->Rot().z -= pos.x * 0.4f * DELTA;

		if (0.01f <= quickSlot_Select->Rot().z)
		{
			quickSlot_Select->Rot().z = -6.3f;
		}
		else if (quickSlot_Select->Rot().z <= -6.31f)
		{
			quickSlot_Select->Rot().z = 0.0f;
		}
	}

	if (KEY_PRESS('X') && KEY_UP(VK_MBUTTON)) // C 누르기 에서 마우스 휠 버튼 누르기로
		// X 를 누른 상태에서 C 를 누르면 지금 선택 되어있는 슬롯을 잡아줌
	{
		if (quickSlot_Select->Rot().z > -0.42f || quickSlot_Select->Rot().z < -5.98f)
		{
			quickSlot_Select->Rot().z = 0.0f;
			useQuickSlot1 = true;
		}
		if (quickSlot_Select->Rot().z <= -0.42f && quickSlot_Select->Rot().z > -1.2f)
		{
			quickSlot_Select->Rot().z = -0.8f;
			useQuickSlot2 = true;
		}
		if (quickSlot_Select->Rot().z <= -1.2f && quickSlot_Select->Rot().z > -1.98f)
		{
			quickSlot_Select->Rot().z = -1.56f;
			useQuickSlot3 = true;
		}
		if (quickSlot_Select->Rot().z <= -1.98f && quickSlot_Select->Rot().z > -2.78f)
		{
			quickSlot_Select->Rot().z = -2.38f;
			useQuickSlot4 = true;
		}
		if (quickSlot_Select->Rot().z <= -2.78f && quickSlot_Select->Rot().z > -3.6f)
		{
			quickSlot_Select->Rot().z = -3.173f;
			useQuickSlot5 = true;
		}
		if (quickSlot_Select->Rot().z <= -3.6f && quickSlot_Select->Rot().z > -4.38f)
		{
			quickSlot_Select->Rot().z = -3.992f;
			useQuickSlot6 = true;
		}
		if (quickSlot_Select->Rot().z <= -4.38f && quickSlot_Select->Rot().z > -5.12f)
		{
			quickSlot_Select->Rot().z = -4.77f;
			useQuickSlot7 = true;
		}
		if (quickSlot_Select->Rot().z <= -5.12f && quickSlot_Select->Rot().z > -5.98f)
		{
			quickSlot_Select->Rot().z = -5.543f;
			useQuickSlot8 = true;
		}
	}
}

void UIManager::DragInvenItem()
{
	// 오류 나서 일단 주석
	//if (ItemManager::Get()->invenSize > 0)
	//{
	//	FOR(ItemManager::Get()->invenSize)
	//	{
	//		if (ItemManager::Get()->itemList[i]->IsOnMouseCursor() && KEY_DOWN(VK_LBUTTON))
	//		{
	//			Quad* quad = new Quad(ItemManager::Get()->inventoryList[i]->GetMaterial()->GetDiffuseMap()->GetFile());
	//			if (ItemManager::Get()->InvenCheck(quad, inItDragItem_D)->GetMaterial()->GetDiffuseMap()->GetFile() !=
	//				quad->GetMaterial()->GetDiffuseMap()->GetFile())
	//			{
	//				quad->Pos() = { CENTER_X, CENTER_Y + 10 * i };
	//				inItDragItem_D.push_back(quad);
	//			}
	//		}
	//		
	//	}
	//}
}

void UIManager::DragSlot()
{
	dragSlot_ButtonWheel->Render();
	dragSlot_KeyButton->Render();
	if (useDragBar)
	{
		dragSlot_ButtonWheel->SetActive(false);
		dragSlot_KeyButton->SetActive(false);
		dragSlotBox->Render();
		itemSlot->Render();

		if (DragCout == 0) // 그레이트 포션 중앙
		{
			potionIcon_D->Pos() = { itemSlot->Pos().x - 83,itemSlot->Pos().y + 2,0 };
			greatepotionIcon_D->Pos() = { itemSlot->Pos().x - 3,itemSlot->Pos().y + 3,0 };
			whetstoneIcon_D->Pos() = { itemSlot->Pos().x + 81,itemSlot->Pos().y + 4,0 };
			potionIcon_D->Render();
			greatepotionIcon_D->Render();
			whetstoneIcon_D->Render();
			useDragSlot1 = true;
			useDragSlot2 = false;
			useDragSlot3 = false;
		}
		if (DragCout == 1 || DragCout == -2) // 숫돌 중앙 1740 120
		{
			potionIcon_D->Pos() = { itemSlot->Pos().x + 81,itemSlot->Pos().y + 2,0 };
			greatepotionIcon_D->Pos() = { itemSlot->Pos().x - 83,itemSlot->Pos().y + 2,0 };
			whetstoneIcon_D->Pos() = { itemSlot->Pos().x + 1,itemSlot->Pos().y + 3,0 }; 
			potionIcon_D->Render();
			greatepotionIcon_D->Render();
			whetstoneIcon_D->Render();
			useDragSlot1 = false;
			useDragSlot2 = true;
			useDragSlot3 = false;
		}
		if (DragCout == 2 || DragCout == -1) // 일반 포션 중앙
		{
			potionIcon_D->Pos() = { itemSlot->Pos().x - 1,itemSlot->Pos().y + 1,0 };
			greatepotionIcon_D->Pos() = { itemSlot->Pos().x + 81,itemSlot->Pos().y + 2,0 };
			whetstoneIcon_D->Pos() = { itemSlot->Pos().x - 83,itemSlot->Pos().y + 4,0 };
			potionIcon_D->Render();
			greatepotionIcon_D->Render();
			whetstoneIcon_D->Render();
			useDragSlot1 = false;
			useDragSlot2 = false;
			useDragSlot3 = true;
		}
		dragSlot_ButtonUp->Render();
		dragSlot_ButtonDown->Render();
	}

	if (useDragSlot1)
	{
		slotNames[2]->Render();
		Font::Get()->RenderText("그레이트 물약", { slotNames[2]->Pos().x + 90,slotNames[2]->Pos().y + 16.5f });
		greatepotionIcon_D->Render();
		if (haveGPotion < 10)
		{
			itemNumber_D[haveGPotion]->Pos().x = 1752;
			itemNumber_D[haveGPotion]->Render();
		}
		else if (haveGPotion == 10)
		{
			itemNumber_D[1]->Pos().x = 1746;
			itemNumber_D[0]->Pos().x = 1758;
			itemNumber_D[1]->Render();
			itemNumber_D[0]->Render();
		}
	}
	if (useDragSlot2)
	{
		slotNames[2]->Render();
		Font::Get()->RenderText("숫돌", { slotNames[2]->Pos().x + 42,slotNames[2]->Pos().y + 16.5f });
		whetstoneIcon_D->Render();
	}
	if (useDragSlot3)
	{
		slotNames[2]->Render();
		Font::Get()->RenderText("일반 물약", { slotNames[2]->Pos().x + 65,slotNames[2]->Pos().y + 16.5f });
		potionIcon_D->Render();
		if (10 <= havePotion && havePotion < 20)
		{
			itemNumber_D[havePotion - 10]->Pos().x = 1752;
			itemNumber_D[havePotion - 10]->Render();
		}
		else if (havePotion == 20)
		{
			itemNumber_D[1]->Pos().x = 1746;
			itemNumber_D[0]->Pos().x = 1758;
			itemNumber_D[1]->Render();
			itemNumber_D[0]->Render();
		}
	}
}

void UIManager::DragSlotBar()
{
	if (useDragBar)
	{
		dragTimer += DELTA;
		if (dragTimer > 1.0f)
		{
			useDragBar = false;
			dragSlot_ButtonWheel->SetActive(true);
			dragSlot_KeyButton->SetActive(true);
		}
	}
	if (wheelPos.z > 0)
	{
		DragCout--;
		useDragBar = true;
		dragTimer = 0.0f;
		if (DragCout < -2)
		{
			DragCout = 0;
		}
		wheelPos = {};
	}
	else if (wheelPos.z < 0)
	{
		DragCout++;
		useDragBar = true;
		dragTimer = 0.0f;
		if (DragCout > 2)
		{
			DragCout = 0;
		}
		wheelPos = {};
	}
}

void UIManager::NumberSlot()
{
	if (useNumberBar)
	{
		timer += DELTA;
		FOR(numberBoxs.size())
		{
			numberBoxs[i]->Render();
		}
		if (useNumberSlot1)
		{
			numberBoxFrames[0]->Render();
		}
		if (useNumberSlot2)
		{
			numberBoxFrames[1]->Render();
		}
		if (useNumberSlot3)
		{
			numberBoxFrames[2]->Render();
		}
		if (useNumberSlot4)
		{
			numberBoxFrames[3]->Render();
		}
		if (useNumberSlot5)
		{
			numberBoxFrames[4]->Render();
		}
		if (useNumberSlot6)
		{
			numberBoxFrames[5]->Render();
		}
		if (useNumberSlot7)
		{
			numberBoxFrames[6]->Render();
		}
		if (useNumberSlot8)
		{
			numberBoxFrames[7]->Render();
		}
		potionIcon_N->Render();
		greatepotionIcon_N->Render();
		whetstoneIcon_N->Render();

		if (haveGPotion < 10)
		{
			itemNumber_N[haveGPotion]->Pos().x = 423;
			itemNumber_N[haveGPotion]->Render();
		}
		else if (haveGPotion == 10)
		{
			itemNumber_N[1]->Pos().x = 417;
			itemNumber_N[0]->Pos().x = 428;
			itemNumber_N[1]->Render();
			itemNumber_N[0]->Render();
		}

		if (10 <= havePotion && havePotion < 20)
		{
			itemNumber_N[havePotion]->Pos().x = 225;
			itemNumber_N[havePotion]->Render();
		}
		else if (havePotion == 20)
		{
			itemNumber_N[11]->Pos().x = 219;
			itemNumber_N[10]->Pos().x = 230;
			itemNumber_N[11]->Render();
			itemNumber_N[10]->Render();
		}

		FOR(8)
		{
			slotNames[i + 3]->Render();
		}
		Font::Get()->RenderText("일반 물약", { slotNames[3]->Pos().x + 65, slotNames[3]->Pos().y + 17 });
		Font::Get()->RenderText("그레이트 물약", { slotNames[4]->Pos().x + 85, slotNames[4]->Pos().y + 17 });
		Font::Get()->RenderText("숫돌", { slotNames[5]->Pos().x + 37, slotNames[5]->Pos().y + 17 });
		FOR(itemKeyNumber_N.size())
		{
			itemKeyNumber_N[i]->Render();
		}
	}

}

void UIManager::NumberSlotBar()
{

	if (useNumberBar && KEY_DOWN('1'))
	{
		useNumberSlot1 = true;
		useNumberSlot2 = false;
		useNumberSlot3 = false;
		useNumberSlot4 = false;
		useNumberSlot5 = false;
		useNumberSlot6 = false;
		useNumberSlot7 = false;
		useNumberSlot8 = false;
		timer = 0;
	}
	else if (useNumberBar && KEY_DOWN('2'))
	{
		useNumberSlot1 = false;
		useNumberSlot2 = true;
		useNumberSlot3 = false;
		useNumberSlot4 = false;
		useNumberSlot5 = false;
		useNumberSlot6 = false;
		useNumberSlot7 = false;
		useNumberSlot8 = false;
		timer = 0;
	}
	else if (useNumberBar && KEY_DOWN('3'))
	{
		useNumberSlot1 = false;
		useNumberSlot2 = false;
		useNumberSlot3 = true;
		useNumberSlot4 = false;
		useNumberSlot5 = false;
		useNumberSlot6 = false;
		useNumberSlot7 = false;
		useNumberSlot8 = false;
		timer = 0;
	}
	else if (useNumberBar && KEY_DOWN('4'))
	{
		useNumberSlot1 = false;
		useNumberSlot2 = false;
		useNumberSlot3 = false;
		useNumberSlot4 = true;
		useNumberSlot5 = false;
		useNumberSlot6 = false;
		useNumberSlot7 = false;
		useNumberSlot8 = false;
		timer = 0;
	}
	else if (useNumberBar && KEY_DOWN('5'))
	{
		useNumberSlot1 = false;
		useNumberSlot2 = false;
		useNumberSlot3 = false;
		useNumberSlot4 = false;
		useNumberSlot5 = true;
		useNumberSlot6 = false;
		useNumberSlot7 = false;
		useNumberSlot8 = false;
		timer = 0;
	}
	else if (useNumberBar && KEY_DOWN('6'))
	{
		useNumberSlot1 = false;
		useNumberSlot2 = false;
		useNumberSlot3 = false;
		useNumberSlot4 = false;
		useNumberSlot5 = false;
		useNumberSlot6 = true;
		useNumberSlot7 = false;
		useNumberSlot8 = false;
		timer = 0;
	}
	else if (useNumberBar && KEY_DOWN('7'))
	{
		useNumberSlot1 = false;
		useNumberSlot2 = false;
		useNumberSlot3 = false;
		useNumberSlot4 = false;
		useNumberSlot5 = false;
		useNumberSlot6 = false;
		useNumberSlot7 = true;
		useNumberSlot8 = false;
		timer = 0;
	}
	else if (useNumberBar && KEY_DOWN('8'))
	{
		useNumberSlot1 = false;
		useNumberSlot2 = false;
		useNumberSlot3 = false;
		useNumberSlot4 = false;
		useNumberSlot5 = false;
		useNumberSlot6 = false;
		useNumberSlot7 = false;
		useNumberSlot8 = true;
		timer = 0;
	}
	if (!useNumberBar && KEY_UP('1') || !useNumberBar && KEY_UP('2') || !useNumberBar && KEY_UP('3')
		|| !useNumberBar && KEY_UP('4') || !useNumberBar && KEY_UP('5') || !useNumberBar && KEY_UP('6')
		|| !useNumberBar && KEY_UP('7') || !useNumberBar && KEY_UP('8'))
	{
		useNumberBar = true;
	}
	if (timer >= 3.0f || KEY_DOWN(VK_ESCAPE))
	{
		useNumberBar = false;
		useNumberSlot1 = false;
		useNumberSlot2 = false;
		useNumberSlot3 = false;
		useNumberSlot4 = false;
		useNumberSlot5 = false;
		useNumberSlot6 = false;
		useNumberSlot7 = false;
		useNumberSlot8 = false;
		timer = 0;
	}

}

void UIManager::StateIcon()
{
	if (partDestruct || specialMove)
	{
		stateIconTimer += DELTA;
		if (stateIconTimer > 5.0f)
		{
			valphalkStateIcon1->Pos().y += 15.0f * DELTA;
			if (stateIconTimer > 6.5f)
			{
				partDestruct = false;
				specialMove = false;
				stateIconTimer = 0.0f;
				valphalkStateIcon1->Pos() = { 1700, 600 };
			}
		}
	}
	if (partDestruct2 || specialMove2)
	{
		stateIconTimer2 += DELTA;

		if (stateIconTimer2 > 5.0f)
		{
			valphalkStateIcon2->Pos().y += 15.0f * DELTA;
			if (stateIconTimer2 > 6.5f)
			{
				partDestruct2 = false;
				specialMove2 = false;
				stateIconTimer2 = 0.0f;
				valphalkStateIcon2->Pos() = { 1700, 500 };
			}
		}
	}
}

bool UIManager::IsAbleBugSkill()
{
	if (bugCount == 2 && isCoolTime1 && isCoolTime2)
		return false;
	else if (bugCount == 3 && isCoolTime1 && isCoolTime2 && isCoolTime3)
		return false;
	else
		return true;
}

void UIManager::UseBugSkill()
{
	if (!isCoolTime1)
		isCoolTime1 = true;
	else if (isCoolTime1 && !isCoolTime2)
		isCoolTime2 = true;
	else if (bugCount == 3 && isCoolTime1 && isCoolTime2 && !isCoolTime3)
		isCoolTime3 = true;
}
