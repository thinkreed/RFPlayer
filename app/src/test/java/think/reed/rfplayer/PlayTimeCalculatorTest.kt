package think.reed.rfplayer

import org.junit.Assert.assertThat
import org.junit.Test
import org.mockito.internal.matchers.GreaterOrEqual

/**
 * Created by thinkreed on 2017/9/10.
 */
class PlayTimeCalculatorTest {
    @Test
    fun getPlayTime() {
        val calculator = PlayTimeCalculator()
        calculator.startCount()
        Thread.sleep(2000)
        assertThat(calculator.getPlayTime(), GreaterOrEqual<Long>(2000))
    }

}