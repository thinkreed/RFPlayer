package think.reed.rfplayer

/**
 * Created by thinkreed on 2017/9/10.
 */
class PlayTimeCalculator {

    private var mStartTime: Long = 0;

    fun startCount() {
        mStartTime = System.currentTimeMillis()
    }

    fun getPlayTime(): Long {
        return System.currentTimeMillis() - mStartTime
    }
}