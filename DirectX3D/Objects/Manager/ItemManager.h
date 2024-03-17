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

	void GetBoxItem(vector<Quad*> invenList);

	Quad* InvenCheck(Quad* quad, vector<Quad*> invenList);
	bool UseItem(Quad* quad);

	void UseBlueBox(Vector3 Pos);

	void Sound();

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
	vector<Quad*> potionNumber;

	Model* BlueBox;
	Quad* BoxIcon;
	Quad* MouseIcon;
	Quad* ThisIcon1;
	Quad* ThisIcon2;

	float iconSoundTimer = 0.0f;

	RasterizerState* rasterizerState[2];
	BlendState* blendState[2];
	//DepthStencilState* depthState[2];
};