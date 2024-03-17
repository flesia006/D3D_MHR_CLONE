#pragma once
class ItemManager : public Singleton<ItemManager>
{
private:
	friend class Singleton;
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	//void GetBoxItem();
	void GetBoxItem(vector<Quad*> invenList);
	//vector<Quad*> GetBoxItem(vector<Quad*> invenList);
	//void GetQuadItem();
	//Quad* InvenCheck(Quad* quad);
	Quad* InvenCheck(Quad* quad, vector<Quad*> invenList);
	bool UseItem(Quad* quad);

	void UseBlueBox(Vector3 Pos);

public: // 임시로 놓은거임
	string tag;
	bool lookBoxIcon = false;
	bool useBlueBox = false;
	bool mouseOn = false;
private:
	vector<Quad*> inventoryList;
	vector<Quad*> itemBoxBack;
	vector<Quad*> itemBoxFrame;
	vector<Quad*> itemList;

	Quad* itemBoxList;

	int itemGetCount = 0;
	int invenSize = 0;
	vector<Quad*> potionNumber;

	Model* BlueBox;
	Quad* BoxIcon;
	Quad* MouseIcon;


};