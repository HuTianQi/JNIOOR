#include <jni.h>
#include <string>
#include "./third_part/include/JniReflect.h"
#include "./third_part/include/Transform.h"

void printNonStaticValue(JNIEnv *env, jobject object);

void printStaticValue(JNIEnv *env, jclass clazz);

void modifyStaticField(JNIEnv *env, jclass clazz);

void modifyNonStaticField(JNIEnv *env, jobject object);

void printToString(JNIEnv *env, jobject object);

extern "C" JNIEXPORT
void JNICALL Java_tech_huqi_jnioor_Sample_nativePrint(JNIEnv *env, jclass clazz) {
    ///////////////////构造方法调用//////////////////
    jobject object = Reflect::on(env, clazz).construct("()V").get<jobject>();
    if (object == NULL) { return; }
    /////////////////////获取域//////////////////////
    printNonStaticValue(env, object);
    printStaticValue(env, clazz);
    /////////////////////设置域//////////////////////
    modifyStaticField(env, clazz);
    modifyNonStaticField(env, object);
    LOGD("%s", "========================after modify========================");
    printNonStaticValue(env, object);
    printStaticValue(env, clazz);
    /////////////////////方法调用/////////////////////
    LOGD("%s", "========================call toString method========================");
    printToString(env, object);
}

void printNonStaticValue(JNIEnv *env, jobject object) {
    int intField = Reflect::on(env, object).field("intField", "I").get<jint>();
    long longField = Reflect::on(env, object).field("longField", "J").get<jlong>();
    float floatField = Reflect::on(env, object).field("floatField", "F").get<jfloat>();
    double doubleField = Reflect::on(env, object).field("doubleField", "D").get<jdouble>();
    jstring stringField = Reflect::on(env, object).field("stringField",
                                                         "Ljava/lang/String;").get<jstring>();
    LOGD("intField is: %d, longField is: %ld, floatField is: %f, doubleField is: %lf stringField is:%s ",
         intField, longField, floatField, doubleField,
         Transform::jstring2String(env, stringField).c_str());
}

void printStaticValue(JNIEnv *env, jclass clazz) {
    int staticIntField = Reflect::on(env, clazz).staticField("staticIntField",
                                                             "I").get<jint>();
    long staticLongField = Reflect::on(env, clazz).staticField("staticLongField",
                                                               "J").get<jlong>();
    float staticFloatField = Reflect::on(env, clazz).staticField("staticFloatField",
                                                                 "F").get<jfloat>();
    double staticDoubleField = Reflect::on(env, clazz).staticField("staticDoubleField",
                                                                   "D").get<jdouble>();
    jstring staticStringField = Reflect::on(env, clazz).staticField("staticStringField",
                                                                    "Ljava/lang/String;").get<jstring>();
    LOGD("staticIntField is %d, staticLongField is: %ld, staticFloatField is: %f, "
         "staticDoubleField is: %lf staticStringField is:%s ", staticIntField, staticLongField,
         staticFloatField, staticDoubleField,
         Transform::jstring2String(env, staticStringField).c_str());
}

void modifyNonStaticField(JNIEnv *env, jobject object) {
    Reflect::on(env, object).field("intField", "I").set<jint>(1);
    Reflect::on(env, object).field("longField", "J").set<jlong>(1);
    Reflect::on(env, object).field("floatField", "F").set<jfloat>(1.0f);
    Reflect::on(env, object).field("doubleField", "D").set<jdouble>(1.0);
    Reflect::on(env, object).field("stringField", "Ljava/lang/String;").set<jobject>(
            env->NewStringUTF("modify stringField value"));
}

void modifyStaticField(JNIEnv *env, jclass clazz) {
    Reflect::on(env, clazz).staticField("staticIntField", "I").set<jint>(1);
    Reflect::on(env, clazz).staticField("staticLongField", "J").set<jlong>(1);
    Reflect::on(env, clazz).staticField("staticFloatField", "F").set<jfloat>(1.0f);
    Reflect::on(env, clazz).staticField("staticDoubleField", "D").set<jdouble>(1.0);
    Reflect::on(env, clazz).staticField("staticStringField",
                                        "Ljava/lang/String;").set<jobject>(
            env->NewStringUTF("modify staticStringField value"));
}

void printToString(JNIEnv *env, jobject object) {
    jstring content = Reflect::on(env, object).call("toString",
                                                    "()Ljava/lang/String;").get<jstring>();
    LOGD("toString content is:%s", Transform::jstring2String(env, content).c_str());
}

extern "C" JNIEXPORT jstring
JNICALL
Java_tech_huqi_jnioor_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



