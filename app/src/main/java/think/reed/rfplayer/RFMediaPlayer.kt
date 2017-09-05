package think.reed.rfplayer

/**
 * Created by thinkreed on 2017/9/5.
 */
class RFMediaPlayer {

    fun play() {
        nativePlay()
    }

    fun pause() {
        nativePause()
    }

    fun stop() {
        nativeStop()
    }

    fun init(path: String) {
        nativeInit(path)
    }

    fun setSurface() {

    }

    external fun nativeInit(path: String): Int

    external fun nativeStop()

    external fun nativePlay()

    external fun nativePause()
}