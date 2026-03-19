#ifndef VIDEO_PLAYER_H_
#define VIDEO_PLAYER_H_

#include "Component.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "engine/dg_time.h"

class VideoPlayer : public Component
{
	private:
		SDL_Renderer* m_renderer;
		std::string m_filepath;
		
		AVPacket* m_packet;
		AVFrame* m_frame;
		AVCodecContext* m_decoder;
		AVFormatContext* m_format_context;
		SDL_Texture* m_texture;

		Uint64 m_last_frame;
		double m_timebase;

		int m_video_stream_index;
		int m_width;
		int m_height;
	public:
		VideoPlayer(GameObject* obj, SDL_Renderer* renderer, const std::string& filepath, int width, int height);
		~VideoPlayer();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
