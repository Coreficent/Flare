#include "AudioEngine.h"
#include <sdl/SDL_mixer.h>

namespace Dove {
	void SoundEffect::play(int loop)
	{
		if(Mix_PlayChannel(-1, this->mix_chunk, loop)==-1)
		{
			if (Mix_PlayChannel(rand()%8, this->mix_chunk, loop) == -1){
				printf("no channel left");
			}
		}
	}

	void Music::play(int loop)
	{
		Mix_PlayMusic(this->mix_music,loop);
	}

	void Music::stop()
	{
		Mix_PauseMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}

	void Music::pause()
	{
		Mix_PauseMusic();
	}

	AudioEngine::AudioEngine()
	{

	}


	AudioEngine::~AudioEngine()
	{
		this->finalize();
	}

	void AudioEngine::initialize()
	{
		if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)==-1)
		{
			// TODO 
			printf("mixer initilization failed");
		}
		if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,1024))
		{
			//TODO
			printf("audio failed to open");
		}

	}

	void AudioEngine::finalize()
	{
		Mix_Quit();
	}

	SoundEffect AudioEngine::load_sound_effect(const std::string& file_path)
	{
		auto it = this->effect_map.find(file_path);

		SoundEffect effect;

		if(it == this->effect_map.end())
		{
			Mix_Chunk* chunk = Mix_LoadWAV(file_path.c_str());
			if(chunk == nullptr)
			{
				printf("load sound filed");
			}
			effect.mix_chunk = chunk;
			this->effect_map[file_path] = chunk;
		}else
		{
			effect.mix_chunk = it->second;
		}
		return effect;
	}

	Music AudioEngine::load_music(const std::string& file_path)
	{
		auto it = this->music_map.find(file_path);

		Music effect;

		if (it == this->music_map.end())
		{
			Mix_Music* music = Mix_LoadMUS(file_path.c_str());
			if (music == nullptr)
			{
				printf("load sound filed");
			}
			effect.mix_music = music;
			this->music_map[file_path] = music;
		}
		else
		{
			effect.mix_music = it->second;
		}
		return effect;
	}
}
