#pragma once
class PlayerWireBug : public ModelAnimator
{
private:
	enum State
	{
		IDLE, FLY
	};

public:
	PlayerWireBug();
	~PlayerWireBug();

	void Update();
	void Render();
	void GUIRender();
	void PostRender();

	void SetMove(Vector3 startPos, bool isMoving, Vector3 moveVec);
	bool GetisMoving() { return isMoving; }
	void SetStop() { moveVec = Vector3::Zero(); }

private:
	void SetAnimation();
	void SetState(State state);
	void Move();

private:
	State curState = IDLE;
	bool isMoving = false;
	Vector3 moveVec;
};

