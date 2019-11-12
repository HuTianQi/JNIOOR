//
// Created by hzhuqi on 2019/6/25.
//

#ifndef JNIOOR_TRANSFORM_H
#define JNIOOR_TRANSFORM_H

#include "common.h"


class Transform {
public:
    static string jstring2String(JNIEnv *env, jstring jstr, const char *encoding = NULL);
};


#endif //JNIOOR_TRANSFORM_H
