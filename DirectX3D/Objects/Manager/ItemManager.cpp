#include "Framework.h"

ItemManager::ItemManager()
{
	// ���⿡ ������ �ڽ� �� �̶�
	// ���� ������ �ڽ� UI �� ���� ġ��

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

	// ���� �ڽ� �ȿ� ������ ����Ʈ
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
		invenSize = inventoryList.size(); // �κ��丮 ������ ��ŭ ������ �þ

		FOR(inventoryList.size())
		{
			if (inventoryList.size() > 0)
			{
				// �ӽ÷� ���� �����
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

void ItemManager::GetBoxItem() // ���⼭ �������� Ŭ���ϸ� �߻��ϴ� �̺�Ʈ ����
{
	FOR(itemList.size()) // ���� ���� ����ǰ �ڽ�����
	{
		if (itemList[i]->IsOnMouseCursor() && KEY_DOWN(VK_LBUTTON)) // Ŭ���� �ϸ�
		{
			Quad* quad = new Quad(itemList[i]->GetMaterial()->GetDiffuseMap()->GetFile());
			if (inventoryList.size() == 0) // �켱 0���� 
			{
				inventoryList.push_back(quad); // ������ Ǫ��
			}
			else if (inventoryList.size() > 0) // ����� 1�����ʹ�
			{
				if (InvenCheck(quad) == nullptr) // �κ�üũ�� �Ѿ��
				{
					itemGetCount++; // ī��Ʈ�� �ö󰡸� ��������
				}
				else if (InvenCheck(quad)->GetMaterial()->GetDiffuseMap()->GetFile() !=
						 quad->GetMaterial()->GetDiffuseMap()->GetFile())
				{
					inventoryList.push_back(quad); // �ٸ� �׸��̸� ��
				}
			}
			itemList.erase(itemList.begin()+i);
		}
	}
}

Quad* ItemManager::InvenCheck(Quad* quad)
{
	vector<Quad*>::iterator iter = inventoryList.begin(); // ���� ��ŭ
	vector<Quad*>::iterator collisionItem = inventoryList.end(); // �� �ڿ��� ����

	for (iter; iter != inventoryList.end(); ++iter)
	{
		if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() ==
			quad->GetMaterial()->GetDiffuseMap()->GetFile())
		{
			return nullptr; // ���� �̹����� �ƹ��͵� �ȳ�����
		}
		else if ((*iter)->GetMaterial()->GetDiffuseMap()->GetFile() !=
				 quad->GetMaterial()->GetDiffuseMap()->GetFile())
		{
			collisionItem = iter; // �ٸ� �̹����� �װɷ� �ٲ�
		}
	}

	Quad* Item = *collisionItem; // ���� ���� ����
	return Item; // ������
}

Quad* ItemManager::InvenCheck(Quad* quad, vector<Quad*> List) 
// �̰� UI ���� ������ �κ� ����Ʈ ������� ������µ�
// ������ �ϴ� ����
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
// UI �޴������� inItDragItem_D �� draMain�� ���� �׸��� �ִµ�
// ���� �̹��� ��� ��� ���� ����
// �ٸ� ������ ��� ���
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
