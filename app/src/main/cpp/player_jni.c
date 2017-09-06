#include <jni.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "libavutil/frame.h"
#include "libavutil/mem.h"


#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

AVFormatContext *pFormatCtx = NULL;
int i, audioStream;
AVCodecParameters *pCodecParam = NULL;
AVCodecParserContext *pParserCtx = NULL;
AVCodecContext *pCodecCtx = NULL;
AVCodec *pCodec = NULL;
AVFrame *pFrame = NULL;
AVFrame *pFrameRGBA = NULL;
AVPacket *pPacket = NULL;
int frameFinished;
int numBytes;
uint8_t inputBuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
uint8_t *data = NULL;
int dataSize;
char *pFilePath = NULL;

int native_init(JNIEnv *pEnv, jobject pObj, jstring pPath) {

    init_codec(pEnv, pObj, pPath);

    pFrame = av_frame_alloc();

    pFrameRGBA = av_frame_alloc();

    if (pFrameRGBA == NULL) {
        return -1;
    }

    return 0;
}

int decode() {
    int ret;
    while (av_read_frame(pFormatCtx, pPacket) > 0) {
        ret = avcodec_send_packet(pCodecCtx, pPacket);
        if (ret < 0) {
            return -1;
        }

        return receiveOutFrame(ret);
    }
}

int receiveOutFrame(int ret) {
    while (ret >= 0) {
        ret = avcodec_receive_frame(pCodecCtx, pFrame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            return 0;
        } else if (ret < 0) {
            return -1;
        }
        dataSize = av_get_bytes_per_sample(pCodecCtx->sample_fmt);
        if (dataSize < 0) {
            return -1;
        }
    }
    return 0;
}

void release() {

}

int init_codec(JNIEnv *pEnv, jobject pObj, jstring pPath) {
    pFilePath = (char *) (*pEnv)->GetStringUTFChars(pEnv, pPath, NULL);

    if (pFilePath == NULL) {
        return -1;
    }

    //register all codecs
    av_register_all();

    pPacket = av_packet_alloc();

    if (pPacket == NULL) {
        return -1;
    }

    //init network module
    avformat_network_init();

    pFormatCtx = avformat_alloc_context();

    if (avformat_open_input(&pFormatCtx, pFilePath, NULL, NULL) != 0) {
        return -1;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        return -1;
    }

    audioStream = -1;

    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audioStream = i;
            break;
        }
    }

    if (audioStream == -1) {
        return -1;
    }

    pCodecParam = pFormatCtx->streams[audioStream]->codecpar;

    pCodec = avcodec_find_decoder(pCodecParam->codec_id);

    if (pCodec == NULL) {
        return -1;
    }

    pParserCtx = av_parser_init(pCodec->id);

    if (!pParserCtx) {
        return -1;
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);

    if (pCodecCtx == NULL) {
        return -1;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        return -1;
    }
}
