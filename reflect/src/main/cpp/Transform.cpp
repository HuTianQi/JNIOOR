//
// Created by hzhuqi on 2019/6/25.
//

#include "Transform.h"

/**
 * 将JNI中的jstring对象转为c++中的string对象
 * @param env
 * @param jstr_string
 * @param encoding
 * @return
 */
string Transform::jstring2String(JNIEnv *env, jstring jstr_string, const char *encoding) {
    string result;
    if (env == NULL) { return result; }
    jstring jstr_encoding;
    if (encoding == NULL) {
        jstr_encoding = env->NewStringUTF("utf_8");
    } else {
        jstr_encoding = env->NewStringUTF(encoding);
    }
    //定义java String类
    jclass jcls_String = (env)->FindClass("java/lang/String");
    jmethodID jmid_getBytes = env->GetMethodID(jcls_String, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray jba_bytes = (jbyteArray) env->CallObjectMethod(jstr_string, jmid_getBytes,
                                                              jstr_encoding);
    jsize arrayLen = env->GetArrayLength(jba_bytes);
    jbyte *pByteArray = env->GetByteArrayElements(jba_bytes, JNI_FALSE);
    if (arrayLen > 0) {
        result.assign((const char *) pByteArray, arrayLen);
    } else {
        LOGE("convert error arrayLen: %d", (int) arrayLen);
    }
    env->ReleaseByteArrayElements(jba_bytes, pByteArray, 0);
    env->DeleteLocalRef(jba_bytes);
    env->DeleteLocalRef(jcls_String);
    env->DeleteLocalRef(jstr_encoding);
    return result;
}