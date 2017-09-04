#include <jni.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "player_jni.h"

JNIEXPORT jstring JNICALL
Java_think_reed_rfplayer_MainActivity_stringFromFFmpeg(JNIEnv *env, jobject instance) {

    // TODO
    char info[10000] = {0};
    sprintf(info, "the result is %d\n", open_ffmpeg());

    return (*env)->NewStringUTF(env, info);
}

int open_ffmpeg() {

    AVFormatContext *pFormatCtx = NULL;
    int i, videoStream;
    AVCodecParameters *pCodecParam;
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;
    AVFrame *pFrame;
    AVFrame *pFrameYUV;
    AVPacket *packet;
    int frameFinished;
    int numBytes;
    uint8_t *buffer;

    char filePath[] = "/sdcard/video/dcw.mp4";

    //register all codecs
    av_register_all();

    //init network module
    avformat_network_init();

    pFormatCtx = avformat_alloc_context();

    if (avformat_open_input(pFormatCtx, filePath, NULL, NULL) != 0) {
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

    pFrameYUV = av_frame_alloc();

    packet = (AVPacket*) av_malloc(sizeof(AVPacket));



    return 0;
}