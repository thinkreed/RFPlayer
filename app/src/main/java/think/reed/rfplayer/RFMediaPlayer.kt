package think.reed.rfplayer

import android.media.AudioFormat
import android.media.AudioManager
import android.media.AudioTrack
import android.util.Log

/** Created by thinkreed on 2017/9/5. */
class RFMediaPlayer {
    private lateinit var mAudioTrack: AudioTrack
    fun init(path: String): Int {
        return nativeInit(path)
    }

    fun decode() {
        Log.e("thinkreed", "the result is " + nativeDecode())
    }

    fun getAudioTrack():AudioTrack {
        return mAudioTrack
    }

    private fun initAudioTrack() {
        val channelCount = if (nativeGetChannelCount() == 1) AudioFormat.CHANNEL_OUT_MONO else AudioFormat.CHANNEL_OUT_STEREO
        val audioMinBufSize = AudioTrack.getMinBufferSize(nativeGetSampleRate(), channelCount, AudioFormat.ENCODING_PCM_16BIT)
        mAudioTrack = AudioTrack(AudioManager.STREAM_MUSIC, nativeGetSampleRate(), channelCount, AudioFormat
                .ENCODING_PCM_16BIT, audioMinBufSize, AudioTrack.MODE_STREAM)
    }

    external fun nativeInit(path: String): Int

    external fun nativeDecode(): Int

    external fun nativeGetSampleRate(): Int

    external fun nativeGetChannelCount(): Int


}