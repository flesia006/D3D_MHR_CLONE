#include "Framework.h"

ItemManager::ItemManager()
{
	// 여기에 아이템 박스 모델 이랑
	// 여기 아이템 박스 UI 가 들어갔다 치고

	itemBoxList = new Quad(L"Textures/UI/ItemBox.png");
	itemBoxList->Scale() *= 2;
	itemBoxList->Pos() = { CENTER_X / 3 , CENTER_Y - 100 };
	itemBoxList->UpdateWorld();

	FOR(21)
	{
		Quad* quad = new Quad(L"Textures/UI/ItemBoxBack.png");
		quad->Scale() *= 1.2;
		if (i < 7)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * i) , itemBoxList->Pos().y + 300 };
		else if (i >= 7 && i < 14)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * (i - 7)) , itemBoxList->Pos().y + 235 };
		else if (i >= 14 && i < 21)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * (i - 14)) , itemBoxList->Pos().y + 170 };
		quad->InItPos(quad->Pos()); // <= 이것으로 마우스 온 위치 잡아줌
		//quad->SetActive(false);
		itemBoxBack.push_back(quad);

		quad = new Quad(L"Textures/UI/ItemBoxFrame.png");
		quad->Scale() *= 1.2;
		if (i < 7)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * i) , itemBoxList->Pos().y + 300 };
		else if (i >= 7 && i < 14)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * (i - 7)) , itemBoxList->Pos().y + 235 };
		else if (i >= 14 && i < 21)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * (i - 14)) , itemBoxList->Pos().y + 170 };
		
		quad->InItPos(quad->Pos());
		quad->SetActive(false);
		itemBoxFrame.push_back(quad);
	}

	// 현재 박스 안에 아이템 리스트
	FOR(4)
	{
		if (i <= 1)
		{
			Quad* quad = new Quad(L"Textures/UI/Potion.png");
			quad->Pos() = itemBoxBack[i]->Pos();
			quad->InItPos(quad->Pos());
			quad->SetTag("Potion");
			quad->SetActive(false);
			itemList.push_back(quad);
		}
		else if (i > 1)
		{
			Quad* quad = new Quad(L"Textures/UI/GreatePotion.png");
			quad->Pos() = itemBoxBack[i]->Pos();
			quad->InItPos(quad->Pos());
			quad->SetTag("GreatePotion");
			quad->SetActive(false);
			itemList.push_back(quad);
		}

	}

	FOR(4)
	{
		wstring texture;
		texture = L"Textures/UI/Number" + to_wstring(5) + L".png";
		Quad* quad = new Quad(texture);
		quad->Pos().x = itemBoxBack[i]->Pos().x + 15;
		quad->Pos().y = itemBoxBack[i]->Pos().y - 16;
		quad->Scale() *= 0.4;
		potionNumber.push_back(quad);
		potionNumber[i]->UpdateWorld();
	}

	BlueBox = new Model("BlueBox");
	BlueBox->Pos() = { -1000, 0 , 200 };

	BoxIcon = new Quad(L"Textures/UI/BoxIcon.png");
	BoxIcon->Scale() *= 1.5f;
	BoxIcon->Pos() = { 1000, 550 };

	MouseIcon = new Quad(L"Textures/UI/MouseCursor.png");
	MouseIcon->Scale() *= 0.85f;

	ThisIcon1 = new Quad(L"Textures/UI/ThisIcon.png");
	ThisIcon1->Pos() = BlueBox->Pos();
	ThisIcon1->Pos().y += 200;
	ThisIcon2 = new Quad(L"Textures/UI/ThisIcon.png");
	ThisIcon2->Scale().x *= -1;
	ThisIcon2->Pos() = BlueBox->Pos();
	ThisIcon2->Pos().y += 200;

	FOR(2) rasterizerState[i] = new RasterizerState();
	FOR(2) blendState[i] = new BlendState();
	blendState[1]->Alpha(true);
	rasterizerState[1]->CullMode(D3D11_CULL_NONE);
	//depthState[0] = new DepthStencilState();
	//depthState[1] = new DepthStencilState();
	//depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

ItemManager::~ItemManager()
{
	FOR(itemList.size())
	{
		delete itemList[i];
	}
	FOR(itemBoxBack.size())
	{
		delete itemBoxBack[i];
	}
	FOR(itemBoxFrame.size())
	{
		delete itemBoxFrame[i];
	}
	
	delete itemBoxList;

	FOR(potionNumber.size())
	{
		delete potionNumber[i];
	}

	delete BlueBox;
	delete BoxIcon;
	delete MouseIcon;

	delete ThisIcon1;
	delete ThisIcon2;

	FOR(2)
	{
		delete rasterizerState[i];
		delete blendState[i];
		//delete depthState[i];
	}
}

void ItemManager::Update()
{
	FOR(itemList.size())
	{
		if (useBlueBox)
			itemList[i]->SetActive(true);
		else
			itemList[i]->SetActive(false);

		itemList[i]->UpdateWorld();
	}
	FOR(itemBoxBack.size())
	{
		if (useBlueBox)
			itemBoxBack[i]->SetActive(true);
		else
			itemBoxBack[i]->SetActive(false);

		itemBoxBack[i]->UpdateWorld();
	}
	FOR(itemBoxFrame.size())
	{
		if (useBlueBox && itemBoxBack[i]->IsOnMouseCursor())
		{
			if (!itemBoxFrame[i]->Active())
			{
				itemBoxFrame[i]->SetActive(true);
				Sounds::Get()->Play("Boxframe_select", 1.1f);
			}
		}
		else if (useBlueBox && !itemBoxBack[i]->IsOnMouseCursor())
			itemBoxFrame[i]->SetActive(false);

		itemBoxFrame[i]->UpdateWorld();
	}
	MouseIcon->Pos() = { mousePos.x + 2, mousePos.y - 15 };
	MouseIcon->UpdateWorld();

	if (mouseOn)
	{
		MouseIcon->Pos() = { mousePos.x + 2, mousePos.y - 15 };
		MouseIcon->UpdateWorld();
	}
	
	BlueBox->UpdateWorld();
	BoxIcon->UpdateWorld();

	ThisIcon1->Rot().y += 0.5f * DELTA;
	ThisIcon2->Rot().y += 0.5f * DELTA;
	ThisIcon1->UpdateWorld();
	ThisIcon2->UpdateWorld();
}

void ItemManager::Render()
{
	BlueBox->Render();
	if (lookBoxIcon)
	{
		rasterizerState[1]->SetState();
		blendState[1]->SetState();
		//depthState[1]->SetState();
		ThisIcon1->Render();
		ThisIcon2->Render();
		blendState[0]->SetState();
		//depthState[0]->SetState();
		rasterizerState[0]->SetState();
	}

}

void ItemManager::PostRender()
{
	if (useBlueBox)
	{
		itemBoxList->Render();
		FOR(itemBoxBack.size())
			itemBoxBack[i]->Render();
		FOR(itemBoxFrame.size())
			itemBoxFrame[i]->Render();
		FOR(itemList.size())
			itemList[i]->Render();
		FOR(potionNumber.size())
			potionNumber[i]->Render();
	}

	if (mouseOn)
		MouseIcon->Render();
	if (lookBoxIcon)
	{
		if (iconSoundTimer <= 0.0001f)
			Sounds::Get()->Play("Icon_on", 1.4f);
		iconSoundTimer += DELTA;
		BoxIcon->Render();
	}
	if (KEY_DOWN(VK_F4))
	{
		mouseOn = true;
		isCursorOn = true;
	}

	if(isCursorOn)
		MouseIcon->Render();

	if (KEY_DOWN(VK_F5))
	{
		mouseOn = false;
		isCursorOn = false;
	}
}

void ItemManager::GUIRender()
{
	//BlueBox->GUIRender();
}

void ItemManager::GetBoxItem(vector<Quad*> invenList) // 여기서 아이템을 클릭하면 발생하는 이벤트 실행
{
	FOR(itemList.size()) // 지금 현재 지급품 박스에서
	{
		if (useBlueBox && itemList[i]->IsOnMouseCursor() && KEY_DOWN(VK_LBUTTON)) // 클릭을 하면
		{
			Quad* quad = new Quad(itemList[i]->GetMaterial()->GetDiffuseMap()->GetFile());
			quad->SetTag(itemList[i]->GetTag());
			if (invenList.size() == 0) // 우선 0개라서 
			{
				Sounds::Get()->Play("Boxitem_select", 1.2f);
				invenList.push_back(quad); // 무조건 푸쉬
				UI->inItDragItem_D.push_back(quad);
			}
			else if (invenList.size() > 0) // 사이즈가 1개부터는
			{
				if (InvenCheck(quad, invenList) == nullptr) // 인벤체크로 넘어가서
				{
					Sounds::Get()->Play("Boxitem_select", 1.2f);
				}
				else if (InvenCheck(quad, invenList)->GetMaterial()->GetDiffuseMap()->GetFile() !=
					quad->GetMaterial()->GetDiffuseMap()->GetFile())
				{
					Sounds::Get()->Play("Boxitem_select", 1.2f);
					invenList.push_back(quad);
					UI->inItDragItem_D.push_back(quad);
				}
			}
			if (itemList[i]->GetTag() == "Potion")
			{
				UI->havePotion += 5;
			}
			else if (itemList[i]->GetTag() == "GreatePotion")
			{
				UI->haveGPotion += 5;
			}
			itemList.erase(itemList.begin() + i);
			potionNumber.erase(potionNumber.begin() + i);
		}
	}
}

Quad* ItemManager::InvenCheck(Quad* quad, vector<Quad*> invenList)
{
	vector<Quad*>::iterator iter = invenList.begin();
	vector<Quad*>::iterator collisionItem = invenList.end();

	for (iter; iter != invenList.end(); ++iter)
	{
		if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() ==
			quad->GetMaterial()->GetDiffuseMap()->GetFile())
		{
			return nullptr;
		}
		else if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() !=
			quad->GetMaterial()->GetDiffuseMap()->GetFile())
		{
			collisionItem = iter;
		}
	}

	Quad* Item = *collisionItem;
	return Item;
}

bool ItemManager::UseItem(Quad* quad)
{
	Vector3 pos = { 1740, 122, 0 };

	if (quad->Pos() == pos)
	{
		this->tag = quad->GetTag();
		return true;
	}
	else if (quad->Pos() != pos)
	{
		this->tag = "";
		return false;
	}
}

void ItemManager::UseBlueBox(Vector3 Pos)
{
	float distance = (Pos - BlueBox->Pos()).Length();

	if (distance <= 250)
	{
		lookBoxIcon = true;
		if (KEY_DOWN('G') && !useBlueBox)
		{
			Sounds::Get()->Play("Boxopen", 1.2f);
			useBlueBox = true;
			mouseOn = true;
			lookBoxIcon = false;
			BoxIcon->SetActive(false);
			ThisIcon1->SetActive(false);
			ThisIcon2->SetActive(false);
		}
		else if (KEY_DOWN(VK_ESCAPE))
		{
			useBlueBox = false;
			mouseOn = false;
			lookBoxIcon = true;
			BoxIcon->SetActive(true);
			ThisIcon1->SetActive(true);
			ThisIcon2->SetActive(true);
		}
	}
	else
	{
		mouseOn = false;
		lookBoxIcon = false;
		useBlueBox = false;
		iconSoundTimer = 0.0f;
		BoxIcon->SetActive(true);
		ThisIcon1->SetActive(true);
		ThisIcon2->SetActive(true);
	}
}