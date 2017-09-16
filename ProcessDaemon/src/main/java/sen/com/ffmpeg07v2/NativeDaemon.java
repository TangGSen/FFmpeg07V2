package sen.com.ffmpeg07v2;

/**
 * Author : 唐家森
 * Version: 1.0
 * On     : 2017/9/8 09:22
 * Des    :
 */

public class NativeDaemon {
    static {
        System.loadLibrary("native-lib");
    }

    public native void startDaemon(String userId);

}
