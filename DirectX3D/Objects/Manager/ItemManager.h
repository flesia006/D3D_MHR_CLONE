#pragma once
class ItemManager : public Singleton<ItemManager>
{
private:
	friend class Singleton;
public:
	ItemManager();
	~ItemManager();

	void Update();
	void PostRender();

	void GetBoxItem();
	//void GetQuadItem();
	Quad* InvenCheck(Quad* quad);
	Quad* InvenCheck(Quad* quad, vector<Quad*> List);
	bool UseItem(Quad* quad);

	vector<Quad*> inventoryList;
	int invenSize = 0;
	vector<Quad*> itemList;
private:
	vector<Quad*> itemBoxBack;
	vector<Quad*> itemBoxFrame;

	Quad* itemBoxList;
	int itemGetCount = 0;

	// 드래그 슬롯 내용
	Quad* dragMain;
};

