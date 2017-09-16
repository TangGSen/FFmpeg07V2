#include "NativeDaemon.h"
#include <string>
#include <unistd.h>
#include <android/log.h>
#include <signal.h>
#include <sys/wait.h>
#define LOG_TAG "sensen"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
char* user_id;


//子进程变成僵尸进程会调用这个方法
void sig_handler(int sino) {
//
    int status;
//    阻塞式函数
    LOGE("等待死亡信号");
    wait(&status);

    LOGE("创建进程");
    create_dameon();

}
void *thread_run(void *arg){
    pid_t pid;
    while( (pid =getppid())!=1){
        //该子进程的父进程的父进程还在zyote进程中
        LOGE("父进程活着");
        sleep(2);

    }
    //如果跳出了循环
    LOGE("父进程正在复活...");
    execlp("am", "am", "startservice", "--user", user_id,
           "sen.com.ffmpeg07v2/sen.com.ffmpeg07v2.ProcessWatcherService", (char*)NULL);
   // execlp("am","am","startservice","--user",user_id,"sen.com.ffmpeg07v2/sen.com.ffmpeg07v2.ProcessWatcherService",(char*)NULL);
}

void JNICALL
Java_sen_com_ffmpeg07v2_NativeDaemon_startDaemon(JNIEnv *env, jobject instance,jstring userid) {
    user_id = (char *) env->GetStringUTFChars(userid, NULL);

    //    //为了防止子进程被弄成僵尸进程   不要    1
    struct  sigaction sa;
    sa.sa_flags=0;

    sa.sa_handler = sig_handler;
    sigaction(SIGCHLD, &sa, NULL);
    create_dameon();
}

void create_dameon(){
    //forck 进程，并判断是不是子进程
    pid_t pid = fork();
    //pid >0 是父进程
    if (pid ==0){
        //开启线程轮询并守护
        create_pthread_dameon();
    }
}

void create_pthread_dameon() {
    pthread_t thread;
    pthread_create(&thread,NULL,thread_run,NULL);
}


