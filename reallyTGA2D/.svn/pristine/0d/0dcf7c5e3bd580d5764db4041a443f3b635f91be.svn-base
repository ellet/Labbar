#pragma once
#include "..\engine_defines.h"

#ifdef USE_VIDEO
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#include "ffmpeg-2.0/libavcodec/avcodec.h"
#include "ffmpeg-2.0/libavdevice/avdevice.h"
#include "ffmpeg-2.0/libavfilter/avfilter.h"
#include "ffmpeg-2.0/libavformat/avformat.h"
#include "ffmpeg-2.0/libavformat/avio.h"
#include "ffmpeg-2.0/libavutil/avutil.h"
#include "ffmpeg-2.0/libpostproc/postprocess.h"
#include "ffmpeg-2.0/libswresample/swresample.h"
#include "ffmpeg-2.0/libswscale/swscale.h"
#include <wtypes.h>
#ifdef __cplusplus
} // end extern "C".
#endif // __cplusplus

namespace Tga2D
{
	class CVideoPlayer
	{
	public:
		CVideoPlayer();
		~CVideoPlayer();
		bool Init(const char* aPath);
		bool DoFirstFrame();
		bool Update(int*& aBuffer);

		void Stop();
		int GrabNextFrame();
		void RestartStream();

		double GetFps();

		AVCodec*            l_pCodec;
		AVCodecContext*     l_pAVCodecContext;
		SwsContext*         l_pSWSContext;
		AVFormatContext*    l_pAVFormatContext;
		AVFrame*            l_pAVFrame;
		AVFrame*            l_pAVFrameBGR;
		AVPacket            l_AVPacket;
		std::string         l_sFile;
		uint8_t*            l_puiBuffer;
		int                 l_iResult;
		int                 l_iFrameCount = 0;
		int                 l_iGotFrame;
		int                 l_iDecodedBytes;
		int                 l_iVideoStreamIdx;
		int                 l_iNumBytes;
	//	AVCodecContext *video_dec_ctx;


	};
}
#endif