#include "engine/Components/VideoPlayer.h"
#include "engine/GameObject.h"


VideoPlayer::VideoPlayer(GameObject* obj, SDL_Renderer* renderer, const std::string& filepath, int width, int height) : Component("VideoPlayer", obj), m_renderer(renderer), m_filepath(filepath), m_width(width), m_height(height)
{
	m_format_context = NULL;
	avformat_open_input(&m_format_context, m_filepath.c_str(), NULL, NULL);
	avformat_find_stream_info(m_format_context, NULL);

	const AVCodec *codec = NULL;
	m_video_stream_index = av_find_best_stream(m_format_context, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
	AVStream* video_stream = m_format_context->streams[m_video_stream_index];
	for(int stream_index = 0; stream_index < m_format_context->nb_streams; ++stream_index)
	{
		if(stream_index != m_video_stream_index)
		{
			m_format_context->streams[stream_index]->discard = AVDISCARD_ALL;
		}
	}

	m_decoder = avcodec_alloc_context3(codec);
	m_decoder->thread_count = 0;
	avcodec_parameters_to_context(m_decoder, m_format_context->streams[m_video_stream_index]->codecpar);
	avcodec_open2(m_decoder, codec, NULL);
	SDL_assert(m_decoder->pix_fmt == AV_PIX_FMT_YUV420P);

	m_packet = av_packet_alloc();
	m_frame = av_frame_alloc();
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

	m_last_frame = 0;
	m_timebase = av_q2d(video_stream->time_base);
}

VideoPlayer::~VideoPlayer()
{
	SDL_DestroyTexture(m_texture);
}

void VideoPlayer::OnIterate()
{
	if(av_read_frame(m_format_context, m_packet) < 0)
	{
		return;
	}

	if(m_packet->stream_index != m_video_stream_index)
	{
		return;
	}

	avcodec_send_packet(m_decoder, m_packet);
	while (avcodec_receive_frame(m_decoder, m_frame) == 0)
	{
		double frame_time_s = (double) m_frame->best_effort_timestamp * m_timebase;
		m_last_frame += DGTime_deltaTime();

		if(m_last_frame < frame_time_s)
		{
			break;
		}

		SDL_UpdateYUVTexture(m_texture, NULL, m_frame->data[0], m_frame->linesize[0], m_frame->data[1],
				m_frame->linesize[1], m_frame->data[2], m_frame->linesize[2]);

		Vector3 pos = gameObject->GetTransform()->GetPosition();
		SDL_Rect viewport;
		viewport.x = pos.x;
		viewport.y = pos.y;
		viewport.w = m_width;
		viewport.h = m_height;

		const float frame_width = (float) m_decoder->width;
		const float frame_height = (float) m_decoder->height;
		const float scale_w = (float) m_width / frame_width;
		const float scale_h = (float) m_height / frame_height;
		const float scale = SDL_min(scale_w, scale_h);

		SDL_FRect dstrect;
		dstrect.x = pos.x;
		dstrect.y = pos.y;
		dstrect.w = frame_width * scale;
		dstrect.w = frame_height * scale;

		SDL_SetRenderViewport(m_renderer, &viewport);
		SDL_RenderTexture(m_renderer, m_texture, NULL, &dstrect);
		SDL_SetRenderViewport(m_renderer, NULL);
	}
}

std::unique_ptr<Component> VideoPlayer::copy()
{
	return std::make_unique<VideoPlayer>(gameObject, m_renderer, m_filepath, m_width, m_height);
}
