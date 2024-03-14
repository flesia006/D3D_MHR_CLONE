#pragma once
class WireBug : public ModelAnimator
{
private:
	enum State
	{
		IDLE
	};

public:
	WireBug();
	~WireBug();

	void Update();
	void Render();
	void GUIRender();
	void PostRender();

	void Respawn();

	bool isPlay = true;
	void SetWireBugPickUpUIActive(bool isActive) { isWireBugPickUpUIActive = isActive; }

	void UpdateUI();

private:
	void SetAnimation();
	void SetState(State state);


private:
	State curState = IDLE;

	float respawnDuration = 0.0f;
	const float respawnDurationLimit = 5.0f;
	ParticleSystem* bugParticle;
	ParticleSystem* bugLightParticle;
	ParticleSystem* bugLightParticle2;
	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	// ���ٹ��� �ݴ� UI
	Quad* wireBugPickUpUI;

	// ���ٹ��� �ݴ� UI ���� ���� bool��
	bool isWireBugPickUpUIActive = false;

	Vector3 UIPos;
};

