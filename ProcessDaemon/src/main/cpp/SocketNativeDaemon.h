/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class sen_com_ffmpeg07v2_SocketNativeDaemon */

#ifndef _Included_sen_com_ffmpeg07v2_SocketNativeDaemon
#define _Included_sen_com_ffmpeg07v2_SocketNativeDaemon
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     sen_com_ffmpeg07v2_SocketNativeDaemon
 * Method:    startDaemon
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_sen_com_ffmpeg07v2_SocketNativeDaemon_startDaemon
  (JNIEnv *, jobject, jstring);

/*
 * Class:     sen_com_ffmpeg07v2_SocketNativeDaemon
 * Method:    connetToMonior
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_sen_com_ffmpeg07v2_SocketNativeDaemon_connetToMonior
  (JNIEnv *, jobject);
void* child_do_work(void *args);
int child_create_channel();
void create_child_dameon();
void child_listen_msg();
void child_do_workV1();

#ifdef __cplusplus
}
#endif
#endif