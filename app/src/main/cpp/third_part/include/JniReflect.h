//
// Created by hzhuqi on 2019/6/21.
//

#ifndef REFLECT_H
#define REFLECT_H

#include "common.h"
#include <algorithm>

enum DataType {
    TYPE_OBJECT,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_BOOLEAN,
    TYPE_BYTE,
    TYPE_CHAR,
};
union ResultUnion {
    jobject o;
    jshort s;
    jint i;
    jlong l;
    jfloat f;
    jdouble d;
    jboolean boolean;
    jbyte byte;
    jchar c;
};

class Reflect {
public:

    static Reflect on(JNIEnv *env, jobject object) {
        return Reflect(env, object);;
    }

    static Reflect on(JNIEnv *env, jclass clazz) {
        return Reflect(env, clazz);;
    }

    static Reflect on(JNIEnv *env, string className) {
        return Reflect(env, className);;
    }

    /**
     * 获取一个域(field)
     * @param fieldName: 域的名称
     * @param fieldSign: 域名称签名
     * @return
     */
    Reflect field(const string fieldName, const string fieldSign);

    /**
     * 获取一个静态域(static field)
     * @param fieldName
     * @param fieldSign
     * @return
     */
    Reflect staticField(const string fieldName, const string fieldSign);

    /**
     * 调用非静态方法
     * @tparam Args: 可变模板参数
     * @param methodName: 方法名
     * @param methodSign: 方法签名
     * @param args: 方法参数，可变参数
     * @return
     */
    template<typename ...Args>
    Reflect call(const string methodName, const string methodSign, Args ...args) {
        if (object == NULL) {
            throw "object is null,you must call [on(jobject object)] method before use [call] method";
        }
        jclass clazz = env->GetObjectClass(object);
        if (clazz != NULL) {
            jmethodID methodID = env->GetMethodID(clazz, methodName.c_str(), methodSign.c_str());
            if (methodID != NULL) {
                switch (getDataType(getMethodReturnValueSign(methodSign))) {
                    case TYPE_SHORT: {
                        result.s = env->CallShortMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_INT: {
                        result.i = env->CallIntMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_LONG: {
                        result.l = env->CallLongMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_FLOAT: {
                        result.f = env->CallFloatMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_DOUBLE: {
                        result.d = env->CallDoubleMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_BOOLEAN: {
                        result.boolean = env->CallBooleanMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_BYTE: {
                        result.byte = env->CallByteMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_CHAR: {
                        result.c = env->CallCharMethod(object, methodID, args...);
                    }
                        break;
                    case TYPE_OBJECT: {
                        result.o = env->CallObjectMethod(object, methodID, args...);
                    }
                        break;
                }
            }
            env->DeleteLocalRef(clazz);
        }
        if (env->ExceptionCheck()) {
            clearException(env);
        }
        return *this;
    }

    /**
     * 调用静态方法
     * @tparam Args: 可变模板参数
     * @param methodName: 方法名
     * @param methodSign: 方法签名
     * @param args: 方法参数，可变参数
     * @return
     */
    template<typename ...Args>
    Reflect
    staticCall(const string methodName, const string methodSign, Args ...args) {
        if (clazz == NULL) {
            if (object != NULL) { clazz = env->GetObjectClass(object); }
            if (clazz == NULL) {
                throw "clazz is null,you must call [on(jclass clazz)] method before use [staticCall] method";
            }
        }
        jmethodID methodID = env->GetStaticMethodID(clazz, methodName.c_str(), methodSign.c_str());
        if (methodID != NULL) {
            switch (getDataType(getMethodReturnValueSign(methodSign))) {
                case TYPE_SHORT: {
                    result.s = env->CallStaticShortMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_INT: {
                    result.i = env->CallStaticIntMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_LONG: {
                    result.l = env->CallStaticLongMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_FLOAT: {
                    result.f = env->CallStaticFloatMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_DOUBLE: {
                    result.d = env->CallStaticDoubleMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_BOOLEAN: {
                    result.boolean = env->CallStaticBooleanMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_BYTE: {
                    result.byte = env->CallStaticByteMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_CHAR: {
                    result.c = env->CallStaticCharMethod(clazz, methodID, args...);
                }
                    break;
                case TYPE_OBJECT: {
                    result.o = env->CallStaticObjectMethod(clazz, methodID, args...);
                }
                    break;
            }
        }
        if (env->ExceptionCheck()) {
            clearException(env);
        }
        return *this;
    }

    /**
     * 调用构造函数
     * @tparam Args: 可变模板参数
     * @param constructorSign: 构造方法的签名
     * @param args: 构造方法需要的参数，可变参数
     * @return
     */
    template<typename ...Args>
    Reflect construct(const string constructorSign, Args ...args) {
        if (clazz == NULL) {
            throw "clazz is null,you must call [on(jclass clazz)] method before use [construct] method";
        }
        jmethodID methodID = env->GetMethodID(clazz, "<init>", constructorSign.c_str());
        if (methodID != NULL) {
            result.o = env->NewObject(clazz, methodID, args...);
        }
        if (env->ExceptionCheck()) {
            clearException(env);
        }
        return *this;
    }

    template<typename T>
    T get();

    template<typename T>
    void set(T newVal);

private:
    Reflect(JNIEnv *env, jobject object) {
        this->env = env;
        this->object = object;
        this->clazz = env->GetObjectClass(object);
    }

    Reflect(JNIEnv *env, jclass clazz) {
        this->env = env;
        this->clazz = clazz;
    }

    Reflect(JNIEnv *env, string className) {
        this->env = env;
        replace(className.begin(), className.end(), '.', '/'); // replace all . to /
        jclass clazz = env->FindClass(className.c_str());
        if (clazz != NULL) {
            this->clazz = clazz;
        }
    }

    template<typename T>
    Reflect on(T t) {
        return create<T>(t);
    }

    template<typename T>
    Reflect create(T t);

    JNIEnv *env;
    jobject object = NULL;
    jclass clazz = NULL;
    jfieldID fieldID = NULL;
    bool isStaticField = false;
    ResultUnion result;

    void clearException(JNIEnv *env);

    int getDataType(string dataSign);

    string getMethodReturnValueSign(string sign);
};

#endif //REFLECT_H
