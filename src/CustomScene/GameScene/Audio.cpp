#include "CustomScene/GameScene/Audio.h"

Audio::Audio(GameObject* obj, std::string filepath, float duration) : Component("Audio", obj), m_filepath(filepath), m_duration(duration)
{
	char* wav_path = NULL;
	SDL_AudioSpec spec;
	SDL_asprintf(&wav_path, m_filepath.c_str(), SDL_GetBasePath());
	
	if(!SDL_LoadWAV(wav_path, &spec, &wav_data, &wav_data_len))
	{
		std::cout << "error when loading " + m_filepath << std::endl;
	}

	SDL_free(wav_path);

	m_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
	if(!m_stream)
	{
		std::cout << "couldn't create audio stream" << SDL_GetError() << std::endl;
	}

	SDL_ResumeAudioStreamDevice(m_stream);
}

Audio::~Audio()
{

}

void Audio::OnIterate()
{
	m_timeSinceStartedPlaying += DGTime_deltaTime();

	if(m_timeSinceStartedPlaying > m_duration)
	{
		m_playing = false;
		m_timeSinceStartedPlaying = 0.0f;
	}

	if(!m_playing) 
	{
		SDL_PauseAudioStreamDevice(m_stream);
	};

	if(SDL_GetAudioStreamQueued(m_stream) < (int)wav_data_len)
	{
		SDL_PutAudioStreamData(m_stream, wav_data, wav_data_len);
	}
}

void Audio::Play()
{
	m_playing = true;
	SDL_ResumeAudioStreamDevice(m_stream);
}

std::unique_ptr<Component> Audio::copy()
{
	return std::make_unique<Audio>(gameObject, m_filepath, m_duration);
}
