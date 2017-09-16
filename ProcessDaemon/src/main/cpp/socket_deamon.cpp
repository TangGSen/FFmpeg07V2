#include <string>
#include <unistd.h>
#include <android/log.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "SocketNativeDaemon.h"
#define LOG_TAG "sensen"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int m_child;
int m_parent;

char *user_id;
const char *PATH = "/data/data/sen.com.ffmpeg07v2/my.sock";

JNIEXPORT void JNICALL Java_sen_com_ffmpeg07v2_SocketNativeDaemon_startDaemon
(JNIEnv *env, jobject jobj, jstring userid){
    user_id = (char *) env->GetStringUTFChars(userid, NULL);
    create_child_dameon();
};
void * run(void *arg){
    int connetfd ;
    while (1){
        //直到连上
        connetfd =socket(AF_LOCAL,SOCK_STREAM,0);
        if (connetfd<0){
            LOGE("父进程正在链接...");
            continue;
        }
        LOGE("父进程正在链接2...");
        struct sockaddr_un addr;
        memset(&addr,0, sizeof(sockaddr_un));
        addr.sun_family=AF_LOCAL;
        strcpy(addr.sun_path,PATH);
        if(connect(connetfd, (const sockaddr *) &addr, sizeof(addr))<0){
            close(connetfd);
            sleep(1);
            //重新链接
            continue;
        };
        m_parent = connetfd;
        LOGE("父进程连上了");
        break;
    }
    return 0;
}
//父进程链接子进程socket
JNIEXPORT void JNICALL Java_sen_com_ffmpeg07v2_SocketNativeDaemon_connetToMonior
(JNIEnv * env, jobject jobj){
    pthread_t pthread;
   pthread_create(&pthread,NULL,run,NULL);


};


void create_child_dameon(){
    //forck 进程，并判断是不是子进程
    pid_t pid = fork();
    //pid >0 是父进程
    if (pid ==0){
        //守护进程
//        pthread_t pthreadfork;
//        pthread_create(&pthreadfork,NULL,child_do_work,NULL);
        child_do_workV1();
    }
}

void* child_do_work(void *args) {
    //1.建立socket 服务
    if( child_create_channel()){
        child_listen_msg();
    }
}

void child_do_workV1() {
    //1.建立socket 服务
    if( child_create_channel()){
        child_listen_msg();
    }
}

void child_listen_msg() {
    fd_set rfds;
    while (1){
        //清空端口号
        FD_ZERO(&rfds);
        FD_SET(m_child,&rfds);
        //设置超时时间
        struct timeval timeout ={3,0};
       int r =  select(m_child+1,&rfds,NULL,NULL,&timeout);
        LOGE("读取消息前  %d  ",r);
        //大于0 设置成功
        if(r >0){
            char pkg[256] ={0};
            //确保读到的内容是指定的端口号
            if (FD_ISSET(m_child,&rfds)){
                //父进程链接上seket 服务端，并没有写，那么这时，唯一能读到内容就是服务端断开
                int result = read(m_child,pkg, sizeof(pkg));
                    LOGE("重启父进程");
                    execlp("am", "am", "startservice", "--user", user_id,
                           "sen.com.ffmpeg07v2/sen.com.ffmpeg07v2.SocketWatcherService", (char*)NULL);

                break;
            }
        }

    }
}

int child_create_channel() {
    //创建socket listendfd
    int listendfd =socket(AF_LOCAL,SOCK_STREAM,0);
//    取消之前进程文件连接
    unlink(PATH);
    //绑定端口号
    struct sockaddr_un addr;
    //清空内存，有可能上一次保留
    memset(&addr,0, sizeof(sockaddr_un));
    addr.sun_family =AF_LOCAL;
    strcpy(addr.sun_path,PATH);
   if( bind(listendfd, (const sockaddr *) &addr, sizeof(addr))<0){
       LOGE("bind error");
       return 0;
   };
    //开始监听 5 为最大的监听数量
    listen(listendfd,5);
    int connfd = 0;
    while(1){
        LOGE("accept ...");
        //不断的接受客户端的请求数据,这里只要客户端链接就好了，不需要接受数据，所以为NULL
        //等待 客户端链接,
        if((connfd =accept(listendfd,NULL,NULL))<0){
            LOGE("accept ...connfd");
            if(errno ==EINTR){
                continue;
            }else{
                LOGE("读取 error");
                return 0;
            }
        };
        //不是上面那个情况，就是apk 链接上了
        m_child = connfd;
        LOGE("父进程链接 true");
        break;
    }

    return 1;
}