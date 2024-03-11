#include "Framework.h"
#include "Kunai.h"

Kunai::Kunai(Transform* transform)
    : transform(transform)
{
    // ������ �ܰ迡�� Ʈ�������� ������ �޾Ƽ� �����Ѵ�
    // -> ���� �ۿ��� �����

    transform->Scale() = { 1, 1, 1 }; // ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ���� �ʿ�)

    collider = new CapsuleCollider(10, 10);
    collider->SetParent(transform); // �浹ü�� Ʈ�������� �����ϱ�

    collider->Scale() = { 1, 1, 1 }; // �浹ü ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ����)
    collider->Pos() = {}; // ���� ��ġ ���� (�𵨰� �浹ü ���̿� ������ ������ ���⼭ ����
}

Kunai::~Kunai()
{
    delete collider;
}

void Kunai::Update()
{
    if (!transform->Active()) return; // Ȱ��ȭ�� �ƴϸ� ��������

    time += DELTA;

    if (time > LIFE_SPAN)
        transform->SetActive(false);

    transform->Pos() += direction * speed * DELTA;

	if (val != nullptr)
	{
		atkCoolDown -= DELTA;
        Attack();
	}

    collider->UpdateWorld();
}

void Kunai::Render()
{
    collider->Render();
}

void Kunai::PostRender()
{
	if (val == nullptr)
		return;

	for (auto& d : damages)
	{
		d.timer += DELTA;
		static bool calculatedOnce;

		if (d.timer < 1.5f)
		{
			wstring dmg = to_wstring(d.damage);
			Vector3 pos = CAM->WorldToScreen(d.pos);

			FOR(dmg.size())
				Font::Get()->RenderText(dmg.substr(i, 1), { pos.x + temp3 * i + temp ,  pos.y - temp2 }, "Black");

			Font::Get()->RenderText(dmg, { pos.x, pos.y }, "RealGray");
		}

		else if (d.timer >= 1.5f && d.timer < 2.0f)
		{
			d.pos += Vector3::Up() * 100 * DELTA;
			wstring dmg = to_wstring(d.damage);
			Vector3 pos = CAM->WorldToScreen(d.pos);

			float alpha = (2.0f - d.timer) / 0.5f;

			FOR(dmg.size())
				Font::Get()->RenderText(dmg.substr(i, 1), { pos.x + temp3 * i + temp ,  pos.y - temp2 }, "Black", Float2(), alpha);
			Font::Get()->RenderText(dmg, { pos.x, pos.y }, "RealGray", Float2(), alpha);
		}

	}

	auto eraseiter = damages.end();
	for (auto iter = damages.begin(); iter != damages.end(); iter++)
	{
		if ((*iter).timer > 6.0f)
			eraseiter = iter;
	}
	if (eraseiter != damages.end())
		damages.erase(eraseiter);

}

//�ۿ��� �θ��� ���� ��ô ���
void Kunai::Throw(Vector3 pos, Vector3 dir)
{
    transform->SetActive(true);

    transform->Pos() = pos;
    direction = dir;

    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90); //�Ʒ� �ڵ�� ����
    transform->Rot().y = atan2(dir.x, dir.z) ;

    time = 0; // ���� �ð��� 0
}

void Kunai::Attack()
{
	Contact contact;
	
	auto colliders = val->GetCollider();

	CapsuleCollider* playerCollider = collider;

	for (auto collider : colliders)
	{
		if (playerCollider->IsCapsuleCollision(collider, &contact) && atkCoolDown <= 0.0f)
		{
			if (!collider->Active())
				return ;

			float hardness = 1.0f;
			switch (collider->part)
			{
			case Valphalk::HEAD: hardness = 55; break;
			case Valphalk::NECK: hardness = 55; break;
			case Valphalk::CHEST: hardness = 30; break;
			case Valphalk::BODY: hardness = 30; break;
			case Valphalk::LWING: hardness = 22; break;
			case Valphalk::LWING_RADIUS: hardness = 22; break;
			case Valphalk::RWING: hardness = 22; break;
			case Valphalk::RWING_RADIUS: hardness = 22; break;
			case Valphalk::LLEG1: hardness = 25; break;
			case Valphalk::LLEG1_FOOT: hardness = 25; break;
			case Valphalk::LLEG2: hardness = 25; break;
			case Valphalk::LLEG2_FOOT: hardness = 25; break;
			case Valphalk::RLEG1: hardness = 25; break;
			case Valphalk::RLEG1_FOOT: hardness = 25; break;
			case Valphalk::RLEG2: hardness = 25; break;
			case Valphalk::RLEG2_FOOT: hardness = 25; break;
			case Valphalk::TAIL_START: hardness = 45; break;
			case Valphalk::TAIL_1: hardness = 45; break;
			case Valphalk::TAIL_2: hardness = 45; break;
			case Valphalk::TAIL: hardness = 45; break;
			default: hardness = 1; break;
			}

			Damage damage;
			float deal = 300 * 0.06 * 3 * hardness * 0.01f;
			damage.damage = (int)deal;
			// ((���ݷ�/�������) * ��� ���� * (����/100 )) * ������ ���� ��� * ���� ���� ���
			damage.pos = contact.hitPoint;
			damage.hitPart = collider->part;

			val->minusCurHP(deal);

			if (collider->part == Valphalk::HEAD
				|| collider->part == Valphalk::NECK)
				val->minusHeadHP(deal);

			if ((collider->part == Valphalk::CHEST
				|| collider->part == Valphalk::BODY) && val->GetIsHupgi())
				val->minusChestHP(deal);

			if (collider->part == Valphalk::LLEG1
				|| collider->part == Valphalk::LLEG1_FOOT)
				val->minusLLegHP(deal);

			if (collider->part == Valphalk::RLEG1
				|| collider->part == Valphalk::RLEG1_FOOT)
				val->minusRLegHP(deal);

			if (collider->part == Valphalk::TAIL_START
				|| collider->part == Valphalk::TAIL_1
				|| collider->part == Valphalk::TAIL_2
				|| collider->part == Valphalk::TAIL)
				val->minusTailHP(deal);

			damage.isWeakness = false;
			atkCoolDown = coolDown;

			damages.push_back(damage);

			return;
		}
	}

}
