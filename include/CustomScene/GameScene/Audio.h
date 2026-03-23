#ifndef AUDIO_H_
#define AUDIO_H_

#include "engine/Components/Component.h"
#include "engine/dg_time.h"

class Audio : public Component
{
	private:
		std::string m_filepath;
		float m_timeSinceStartedPlaying = 0.0f;
		float m_duration = 10.0f;
		bool m_playing = false;

		SDL_AudioStream* m_stream;
		Uint8 *wav_data = NULL;
		Uint32 wav_data_len;
	public:
		Audio(GameObject*, std::string, float);
		~Audio();
		void OnIterate();
		void Play();
		std::unique_ptr<Component> copy();
};

#endif
