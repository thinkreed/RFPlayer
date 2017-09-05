#include <jni.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"


AVFormatContext *pFormatCtx = NULL;
int i, videoStream;
AVCodecParameters *pCodecParam;
AVCodecContext *pCodecCtx;
AVFrame *pFrame;
AVFrame *pFrameRGBA = NULL;
AVPacket *packet;
int frameFinished;
int numBytes;
uint8_t *buffer;

int native_init(JNIEnv *pEnv, jobject pObj, jstring pPath) {

    AVCodec *pCodec;


    char *pFilePath = (char *) (*pEnv)->GetStringUTFChars(pEnv, pPath, NULL);

    //register all codecs
    av_register_all();

    //init network module
    avformat_network_init();

    pFormatCtx = avformat_alloc_context();

    if (avformat_open_input(&pFormatCtx, pFilePath, NULL, NULL) != 0) {
        return -1;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        return -1;
    }

    videoStream = -1;

    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }

    if (videoStream == -1) {
        return -1;
    }

    pCodecParam = pFormatCtx->streams[videoStream]->codecpar;

    pCodec = avcodec_find_decoder(pCodecParam->codec_id);

    pCodecCtx = avcodec_alloc_context3(pCodec);

    if (pCodec == NULL) {
        return -1;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        return -1;
    }

    pFrame = av_frame_alloc();

    pFrameRGBA = av_frame_alloc();

    if (pFrameRGBA == NULL) {
        return -1;
    }

    return 0;
}
