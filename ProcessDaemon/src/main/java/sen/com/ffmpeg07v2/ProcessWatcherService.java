package sen.com.ffmpeg07v2;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.support.annotation.Nullable;

/**
 * Author : 唐家森
 * Version: 1.0
 * On     : 2017/9/8 09:21
 * Des    :
 */

public class ProcessWatcherService extends Service {
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        NativeDaemon nativeDaemon = new NativeDaemon();
        nativeDaemon.startDaemon(String.valueOf(Process.myUid()));
    }
}
