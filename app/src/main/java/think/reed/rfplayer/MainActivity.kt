package think.reed.rfplayer

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val player = RFMediaPlayer()
        player.init("/sdcard/music/qhc.mp3")
        player.decode()
    }

    external fun stringFromFFmpeg(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("player_jni")
        }
    }
}
