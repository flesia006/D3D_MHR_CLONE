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
			itemList.push_back(quad);
		}
		else if (i > 1)
		{
			Quad* quad = new Quad(L"Textures/UI/GreatePotion.png");
			quad->Pos() = itemBoxBack[i]->Pos();
			quad->InItPos(quad->Pos());
			quad->SetTag("GreatePotion");
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
	BlueBox->Pos() = { -100, 0 , -50 };

	BoxIcon = new Quad(L"Textures/UI/BoxIcon.png");
	BoxIcon->Scale() *= 1.5f;
	BoxIcon->Pos() = { 1000, 550 };

	MouseIcon = new Quad(L"Textures/UI/MouseCursor.png");
	MouseIcon->Scale() *= 0.55f;
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
}

void ItemManager::Update()
{
	FOR(itemList.size())
	{
		itemList[i]->UpdateWorld();
	}
	FOR(itemBoxBack.size())
	{
		itemBoxBack[i]->UpdateWorld();
	}
	FOR(itemBoxFrame.size())
	{
		if (itemBoxBack[i]->IsOnMouseCursor())
		{
			itemBoxFrame[i]->SetActive(true);
		}
		else if (!itemBoxBack[i]->IsOnMouseCursor())
		{
			itemBoxFrame[i]->SetActive(false);
		}
		itemBoxFrame[i]->UpdateWorld();
	}
	FOR(potionNumber.size())
	{
		potionNumber[i]->UpdateWorld();
	}
	if (mouseOn)
	{
		MouseIcon->Pos() = { mousePos.x + 2, mousePos.y - 15 };
		MouseIcon->UpdateWorld();
	}

	//GetBoxItem();
	//GetQuadItem();
	BlueBox->UpdateWorld();
	BoxIcon->UpdateWorld();
}

void ItemManager::Render()
{
	BlueBox->Render();
}

void ItemManager::PostRender()
{
	if (useBlueBox)
	{
		itemBoxList->Render();
		FOR(itemBoxBack.size())
		{
			itemBoxBack[i]->Render();
		}
		FOR(itemBoxFrame.size())
		{
			itemBoxFrame[i]->Render();
		}
		FOR(itemList.size())
		{
			itemList[i]->Render();
		}
		FOR(potionNumber.size())
		{
			potionNumber[i]->Render();
		}
	}

	if (mouseOn)
	{
		MouseIcon->Render();
	}
	if (lookBoxIcon)
	{
		BoxIcon->Render();
	}
}

void ItemManager::GUIRender()
{
	//BlueBox->GUIRender();
}

//void ItemManager::GetBoxItem() // 여기서 아이템을 클릭하면 발생하는 이벤트 실행
//{
//	FOR(itemList.size()) // 지금 현재 지급품 박스에서
//	{
//		if (itemList[i]->IsOnMouseCursor() && KEY_DOWN(VK_LBUTTON)) // 클릭을 하면
//		{
//			Quad* quad = new Quad(itemList[i]->GetMaterial()->GetDiffuseMap()->GetFile());
//			if (inventoryList.size() == 0) // 우선 0개라서 
//			{
//				inventoryList.push_back(quad); // 무조건 푸쉬
//			}
//			else if (inventoryList.size() > 0) // 사이즈가 1개부터는
//			{
//				if (InvenCheck(quad) == nullptr) // 인벤체크로 넘어가서
//				{
//					itemGetCount++; // 카운트가 올라가면 개수증가
//				}
//				else if (InvenCheck(quad)->GetMaterial()->GetDiffuseMap()->GetFile() !=
//						 quad->GetMaterial()->GetDiffuseMap()->GetFile())
//				{
//					inventoryList.push_back(quad); // 다른 그림이면 랜
//				}
//			}
//			itemList.erase(itemList.begin()+i);
//		}
//	}
//}

//vector<Quad*> ItemManager::GetBoxItem(vector<Quad*> invenList) // 여기서 아이템을 클릭하면 발생하는 이벤트 실행
void ItemManager::GetBoxItem(vector<Quad*> invenList) // 여기서 아이템을 클릭하면 발생하는 이벤트 실행
{
	FOR(itemList.size()) // 지금 현재 지급품 박스에서
	{
		if (itemList[i]->IsOnMouseCursor() && KEY_DOWN(VK_LBUTTON)) // 클릭을 하면
		{
			Quad* quad = new Quad(itemList[i]->GetMaterial()->GetDiffuseMap()->GetFile());
			quad->SetTag(itemList[i]->GetTag());
			if (invenList.size() == 0) // 우선 0개라서 
			{
				invenList.push_back(quad); // 무조건 푸쉬
				//inventoryList.push_back(quad);
				UI->inItDragItem_D.push_back(quad);
			}
			else if (invenList.size() > 0) // 사이즈가 1개부터는
			{
				if (InvenCheck(quad, invenList) == nullptr) // 인벤체크로 넘어가서
				{

				}
				else if (InvenCheck(quad, invenList)->GetMaterial()->GetDiffuseMap()->GetFile() !=
					quad->GetMaterial()->GetDiffuseMap()->GetFile())
				{
					invenList.push_back(quad);
					//inventoryList.push_back(quad);
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

//Quad* ItemManager::InvenCheck(Quad* quad)
//{
//	vector<Quad*>::iterator iter = inventoryList.begin(); // 시작 만큼
//	vector<Quad*>::iterator collisionItem = inventoryList.end(); // 이 뒤에는 없음
//
//	for (iter; iter != inventoryList.end(); ++iter)
//	{
//		if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() ==
//			quad->GetMaterial()->GetDiffuseMap()->GetFile())
//		{
//			return nullptr; // 같은 이미지면 아무것도 안내보냄
//		}
//		else if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() !=
//				 quad->GetMaterial()->GetDiffuseMap()->GetFile())
//		{
//			collisionItem = iter; // 다른 이미지면 그걸로 바뀌어서
//		}
//	}
//
//	Quad* Item = *collisionItem; // 새로 쿼드 만들어서
//	return Item; // 내보냄
//}

Quad* ItemManager::InvenCheck(Quad* quad, vector<Quad*> invenList)
// 이건 UI 에서 서로의 인벤 리스트 엮을라고 만들었는데
// 터져서 일단 보류
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
// UI 메니저에서 inItDragItem_D 의 draMain과 같은 그림이 있는데
// 같은 이미지 라면 사용 하지 않음
// 다른 이지미 라면 사용
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
		if (KEY_DOWN('G'))
		{
			useBlueBox = true;
			mouseOn = true;
			BoxIcon->SetActive(false);
		}
		else if (KEY_DOWN(VK_ESCAPE))
		{
			useBlueBox = false;
			mouseOn = false;
			BoxIcon->SetActive(true);
		}
	}
	else
	{
		mouseOn = false;
		lookBoxIcon = false;
		useBlueBox = false;
		BoxIcon->SetActive(true);
	}
}
