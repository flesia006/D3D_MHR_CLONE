#include "Framework.h"

ItemManager::ItemManager()
{
	// 여기에 아이템 박스 모델 이랑
	// 여기 아이템 박스 UI 가 들어갔다 치고

	itemBoxList = new Quad(L"Textures/UI/ItemBox2.png");
	itemBoxList->Scale() *= 2;
	itemBoxList->Pos() = { CENTER_X / 3 , CENTER_Y - 100 };
	itemBoxList->UpdateWorld();

	FOR(21)
	{
		Quad* quad = new Quad(L"Textures/UI/ItemBoxBack2.png");
		quad->Scale() *= 1.2;
		if (i < 7)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * i) , itemBoxList->Pos().y + 300 };
		else if (i >= 7 && i < 14)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * (i - 7)) , itemBoxList->Pos().y + 235 };
		else if (i >= 14 && i < 21)
			quad->Pos() = { (itemBoxList->Pos().x - 183) + (60 * (i - 14)) , itemBoxList->Pos().y + 170 };
		quad->InItPos(quad->Pos());
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
			itemList.push_back(quad);
		}
		else if (i > 1)
		{
			Quad* quad = new Quad(L"Textures/UI/GreatePotion.png");
			quad->Pos() = itemBoxBack[i]->Pos();
			quad->InItPos(quad->Pos());
			itemList.push_back(quad);
		}

	}

	dragMain = new Quad(L"Textures/UI/ItemSlot.png");
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

	if (inventoryList.size() > 0)
	{
		invenSize = inventoryList.size(); // 인벤토리 사이즈 만큼 사이즈 늘어남

		FOR(inventoryList.size())
		{
			if (inventoryList.size() > 0)
			{
				// 임시로 포즈 잡아줌
				FOR(inventoryList.size())
				{
					inventoryList[i]->Pos() = itemBoxFrame[i + 7]->Pos();
				}
			}
			inventoryList[i]->UpdateWorld();
		}
	}

	GetBoxItem();
	//GetQuadItem();
}

void ItemManager::PostRender()
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
	if (inventoryList.size() > 0)
	{
		FOR(inventoryList.size())
		{
			inventoryList[i]->Render();
		}
	}
}

void ItemManager::GetBoxItem() // 여기서 아이템을 클릭하면 발생하는 이벤트 실행
{
	FOR(itemList.size()) // 지금 현재 지급품 박스에서
	{
		if (itemList[i]->IsOnMouseCursor() && KEY_DOWN(VK_LBUTTON)) // 클릭을 하면
		{
			Quad* quad = new Quad(itemList[i]->GetMaterial()->GetDiffuseMap()->GetFile());
			if (inventoryList.size() == 0) // 우선 0개라서 
			{
				inventoryList.push_back(quad); // 무조건 푸쉬
			}
			else if (inventoryList.size() > 0) // 사이즈가 1개부터는
			{
				if (InvenCheck(quad) == nullptr) // 인벤체크로 넘어가서
				{
					itemGetCount++; // 카운트가 올라가면 개수증가
				}
				else if (InvenCheck(quad)->GetMaterial()->GetDiffuseMap()->GetFile() !=
						 quad->GetMaterial()->GetDiffuseMap()->GetFile())
				{
					inventoryList.push_back(quad); // 다른 그림이면 랜
				}
			}
			itemList.erase(itemList.begin()+i);
		}
	}
}

Quad* ItemManager::InvenCheck(Quad* quad)
{
	vector<Quad*>::iterator iter = inventoryList.begin(); // 시작 만큼
	vector<Quad*>::iterator collisionItem = inventoryList.end(); // 이 뒤에는 없음

	for (iter; iter != inventoryList.end(); ++iter)
	{
		if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() ==
			quad->GetMaterial()->GetDiffuseMap()->GetFile())
		{
			return nullptr; // 같은 이미지면 아무것도 안내보냄
		}
		else if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() !=
				 quad->GetMaterial()->GetDiffuseMap()->GetFile())
		{
			collisionItem = iter; // 다른 이미지면 그걸로 바뀌어서
		}
	}

	Quad* Item = *collisionItem; // 새로 쿼드 만들어서
	return Item; // 내보냄
}

Quad* ItemManager::InvenCheck(Quad* quad, vector<Quad*> List) 
// 이건 UI 에서 서로의 인벤 리스트 엮을라고 만들었는데
// 터져서 일단 보류
{
	vector<Quad*>::iterator iter = List.begin();
	vector<Quad*>::iterator collisionItem = List.end();

	for (iter; iter != List.end(); ++iter)
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
	wstring file = dragMain->GetMaterial()->GetDiffuseMap()->GetFile();
	wstring file2 = quad->GetMaterial()->GetDiffuseMap()->GetFile();

	if (file == file2)
	{
		return false;
	}
	else if (file != file2)
	{
		return true;
	}
}
