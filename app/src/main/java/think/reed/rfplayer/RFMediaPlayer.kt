package think.reed.rfplayer

/**
 * Created by thinkreed on 2017/9/5.
 */
class RFMediaPlayer {

    fun init(path: String): Int {
        return nativeInit(path)
    }

    fun decode() {
        nativeDecode()
    }

    external fun nativeInit(path: String): Int

    external fun nativeDecode(): Int
}