#include "Framework.h"
#include "Explosion.h"

Explosion::Explosion()
{
	explosionParticle = new ParticleSystem("TextData/Particles/explosion_Particle.fx");
	sprite1 = new Sprite(L"Textures/Effect/Boom.png",  1500, 1500, 5, 4, false);
	sprite2 = new Sprite(L"Textures/Effect/Boom.png",  1500, 1500, 5, 4, false);
	sprite3 = new Sprite(L"Textures/Effect/Boom.png",  1500, 1500, 5, 4, false);
	sprite4 = new Sprite(L"Textures/Effect/Boom.png",  1500, 1500, 5, 4, false);
	sprite5 = new Sprite(L"Textures/Effect/Boom.png",  1500, 1500, 5, 4, false);
	sprite6 = new Sprite(L"Textures/Effect/Boom.png",  1500, 1500, 5, 4, false);
													   
	sprite7 = new Sprite(L"Textures/Effect/Boom.png",  1000, 1000, 5, 4, false);
	sprite8 = new Sprite(L"Textures/Effect/Smoke.png", 1200, 1200, 8, 6, false);
	sprite9 = new Sprite(L"Textures/Effect/Smoke.png", 800,  800,  8, 6, false);

	spark_sprite = new Sprite(L"Textures/Effect/val_spark.png", 2000, 2000, 8, 4, true);


	////////////////////////////////////////////////////
	// Bullet Exlposion
	bulletExplosion1 = new Sprite(L"Textures/Effect/Smoke.png", 550, 550, 8, 6, false);
	bulletExplosion2 = new Sprite(L"Textures/Effect/Boom.png",  750, 750, 5, 4, false);
	bulletExplosion3 = new Sprite(L"Textures/Effect/Boom.png", 750, 750, 5, 4, false);
	bulletExplosion4 = new Sprite(L"Textures/Effect/Boom.png",  750, 750, 5, 4, false);	
}

Explosion::~Explosion()
{
	delete explosionParticle;
	delete sprite1;
	delete sprite2;
	delete sprite3;
	delete sprite4;
	delete sprite5;
	delete sprite6;
	delete sprite7;
	delete sprite8;
	delete sprite9;
	delete bulletExplosion1;
	delete bulletExplosion2;
	delete bulletExplosion3;
	delete bulletExplosion4;
	delete spark_sprite;
}

void Explosion::Update()
{
	explosionParticle->Update();
	sprite1->Update();
	sprite2->Update();
	sprite3->Update();
	sprite4->Update();
	sprite5->Update();
	sprite6->Update();
	sprite7->Update();
	sprite8->Update();
	sprite9->Update();
	bulletExplosion1->Update();
	bulletExplosion2->Update();
	bulletExplosion3->Update();
	bulletExplosion4->Update();
	spark_sprite->Update();
}

void Explosion::Render()
{
	explosionParticle->Render();
	bulletExplosion1->Render();
	bulletExplosion2->Render();
	bulletExplosion3->Render();
	bulletExplosion4->Render();
	sprite9->Render();
	sprite8->Render();
	sprite7->Render();
	sprite6->Render();
	sprite5->Render();
	sprite4->Render();
	sprite3->Render();
	sprite2->Render();
	sprite1->Render();
	spark_sprite->Render();
}

void Explosion::GUIRender()
{
}

void Explosion::Play(Vector3 pos, Vector3 rot)
{
	Play1(pos,rot);
	Play2(pos,rot);
	Play3(pos,rot);
}

void Explosion::Play1(Vector3 pos, Vector3 rot)
{
	explosionParticle->Play(pos);
	sprite8->Play(pos);
	sprite1->Play(pos);	
	sprite2->Play({ pos.x - 100,pos.y - 100,pos.z });
}

void Explosion::Play2(Vector3 pos, Vector3 rot)
{
	sprite3->Play({ pos.x - 100, pos.y + 100, pos.z });
	sprite4->Play({ pos.x + 100, pos.y - 100, pos.z });
}

void Explosion::Play3(Vector3 pos, Vector3 rot)
{
	sprite5->Play({ pos.x - 100, pos.y + 100, pos.z });
	sprite6->Play({ pos.x + 100, pos.y + 100, pos.z });
}

void Explosion::PlaySpark(Vector3 pos, Vector3 rot)
{
	spark_sprite->Play(pos);
}

void Explosion::PlaySmall(Vector3 pos, Vector3 rot)
{	
	explosionParticle->Play(pos);
	float i = Random(-100, 100);
	sprite9->Play(pos + i);
	sprite7->Play(pos + i);	
}


void Explosion::Stop()
{
	sprite1->Stop();
	sprite2->Stop();
	sprite3->Stop();
	sprite4->Stop();
	sprite5->Stop();
	sprite5->Stop();
	sprite6->Stop();
	sprite7->Stop();
	sprite8->Stop();
}

void Explosion::BulletExpoision(Vector3 pos, Vector3 rot)
{
	bulletExplosion1->Play(pos);
	bulletExplosion2->Play(pos);
	bulletExplosion3->Play(pos);
	bulletExplosion4->Play(pos);
}

