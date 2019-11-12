//
// Created by hzhuqi on 2019/6/25.
//

#ifndef JNIOOR_COMMON_H
#define JNIOOR_COMMON_H

#include <jni.h>
#include <string>
#include <android/log.h>

using namespace std;

#define DEBUG
#ifdef DEBUG
#ifndef TAG
#define TAG "JniReflect"
#endif
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))
#define LOGV(...) ((void)__android_log_print(ANDROID_LOG_VERBOSE,TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,TAG, __VA_ARGS__))
#define ASSERT(cond, fmt, ...)                                \
  if (!(cond)) {                                              \
    __android_log_assert(#cond, LOG_TAG, fmt, ##__VA_ARGS__); \
  }

#else
#define LOGD(...)
#define LOGE(...)
#define LOGV(...)
#define LOGI(...)
#define LOGW(...)
#endif


#endif //JNIOOR_COMMON_H
