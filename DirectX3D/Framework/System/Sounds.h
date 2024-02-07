#pragma once

using namespace FMOD;

class Sounds : public Singleton<Sounds>
{
public:
	friend Singleton<Sounds>;

	void Update();

	void AddSound(string name, wstring file, bool bLoop = false);

	void Play(string name, float volume = 0.3f);
	void Stop(string name);
	void Pause(string name);
	void Resume(string name);

	bool IsPlaying(string name);
	bool IsPaused(string name);

	void SetVolume(string name, float volume);
	void SetPitch(string name, float pitch);
	float GetVolume() { return volume; }

private:
	Sounds();
	~Sounds();

private:
	System* system;
	Sound** sound;
	Channel** channel;

	UINT count;

	map<string, Sound**> sounds;
	map<string, Sound**>::iterator iter;

	float volume;
};