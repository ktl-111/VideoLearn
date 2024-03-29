#include <jni.h>
#include "FFMpegPlayer.h"

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result = -1;
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    LOGI("JNI_OnLoad");

    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativeInit(JNIEnv *env, jobject thiz) {
    auto *player = new FFMpegPlayer();
    player->init(env, thiz);
    return reinterpret_cast<long>(player);
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativePrepare(JNIEnv *env, jobject thiz,
                                                      jlong native_manager, jstring path,
                                                      jobject surface) {
    LOGI("nativePrepare manager:%ld", native_manager)
    auto *pPlayer = reinterpret_cast<FFMpegPlayer *>(native_manager);
    LOGI("nativePrepare manager:%p", &pPlayer)
    const char *c_path = env->GetStringUTFChars(path, nullptr);
    std::string s_path = c_path;
    bool result = false;
    if (pPlayer != nullptr) {
        result = pPlayer->prepare(env, s_path, surface);
    }
    if (c_path != nullptr) {
        env->ReleaseStringUTFChars(path, c_path);
    }
    return result;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativeStart(JNIEnv *env, jobject thiz,
                                                    jlong native_manager) {
    FFMpegPlayer *pPlayer = reinterpret_cast<FFMpegPlayer *>(native_manager);
    if (pPlayer != nullptr) {
        pPlayer->start();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativeStop(JNIEnv *env, jobject thiz,
                                                   jlong native_manager) {
    FFMpegPlayer *pPlayer = reinterpret_cast<FFMpegPlayer *>(native_manager);
    if (pPlayer != nullptr) {
        pPlayer->stop();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativeResume(JNIEnv *env, jobject thiz,
                                                     jlong native_manager) {
    FFMpegPlayer *pPlayer = reinterpret_cast<FFMpegPlayer *>(native_manager);
    if (pPlayer != nullptr) {
        pPlayer->resume();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativePause(JNIEnv *env, jobject thiz,
                                                    jlong native_manager) {
    FFMpegPlayer *pPlayer = reinterpret_cast<FFMpegPlayer *>(native_manager);
    if (pPlayer != nullptr) {
        pPlayer->pause();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativeRelease(JNIEnv *env, jobject thiz,
                                                      jlong native_manager) {
    FFMpegPlayer *pPlayer = reinterpret_cast<FFMpegPlayer *>(native_manager);
    if (pPlayer != nullptr) {
        pPlayer->release();
    }
    delete pPlayer;
}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_play_proxy_FFMpegProxy_nativeTest(JNIEnv *env, jobject thiz) {
    return 479815690048;
}