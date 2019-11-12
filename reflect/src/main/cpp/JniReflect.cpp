//
// Created by hzhuqi on 2019/6/21.
//

#include "JniReflect.h"
#include <stdarg.h>

Reflect Reflect::field(const string fieldName, const string fieldSign) {
    if (object == NULL) {
        throw "object is null,you must call [on(jobject object)] method before use [field] method";
    }
    jclass clazz = env->GetObjectClass(object);
    if (clazz != NULL) {
        isStaticField = false;
        fieldID = env->GetFieldID(clazz, fieldName.c_str(), fieldSign.c_str());
        env->DeleteLocalRef(clazz);
    }
    if (env->ExceptionCheck()) {
        clearException(env);
    }
    return *this;
}

Reflect Reflect::staticField(const string fieldName, const string fieldSign) {
    if (clazz == NULL) {
        if (object != NULL) { clazz = env->GetObjectClass(object); }
        if (clazz == NULL) {
            throw "clazz is null,you must call [on(jclass clazz)] method before use [staticField] method";
        }
    }
    isStaticField = true;
    fieldID = env->GetStaticFieldID(clazz, fieldName.c_str(), fieldSign.c_str());
    if (env->ExceptionCheck()) {
        clearException(env);
    }
    return *this;
}

template<>
jobject Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.o = env->GetStaticObjectField(clazz, fieldID);
        } else {
            result.o = env->GetObjectField(object, fieldID);
        }
    }
    return result.o;
}

template<>
void Reflect::set(jobject newVal) {
    if (fieldID != NULL) {
        if (isStaticField) {
            env->SetStaticObjectField(clazz, fieldID, newVal);
        } else {
            env->SetObjectField(object, fieldID, newVal);
        }
    }
}

template<>
jstring Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.o = env->GetStaticObjectField(clazz, fieldID);
        } else {
            result.o = env->GetObjectField(object, fieldID);
        }
    }
    return (jstring) result.o;
}

template<>
jobjectArray Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.o = env->GetStaticObjectField(clazz, fieldID);
        } else {
            result.o = env->GetObjectField(object, fieldID);
        }
    }
    return (jobjectArray) result.o;
}

template<>
jshort Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.s = env->GetStaticShortField(clazz, fieldID);
        } else {
            result.s = env->GetShortField(object, fieldID);
        }
    }
    return result.s;
}

template<>
void Reflect::set(jshort newVal) {
    if (fieldID != NULL) {
        if (isStaticField) {
            env->SetStaticShortField(clazz, fieldID, newVal);
        } else {
            env->SetShortField(object, fieldID, newVal);
        }
    }
}

template<>
jint Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.i = env->GetStaticIntField(clazz, fieldID);
        } else {
            result.i = env->GetIntField(object, fieldID);
        }
    }
    return result.i;
}

template<>
void Reflect::set(jint newVal) {
    if (fieldID != NULL) {
        if (isStaticField) {
            env->SetStaticIntField(clazz, fieldID, newVal);
        } else {
            env->SetIntField(object, fieldID, newVal);
        }

    }
}

template<>
jlong Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.l = env->GetStaticLongField(clazz, fieldID);
        } else {
            result.l = env->GetLongField(object, fieldID);
        }
    }
    return result.l;
}

template<>
void Reflect::set(jlong newVal) {
    if (isStaticField) {
        env->SetStaticLongField(clazz, fieldID, newVal);
    } else {
        env->SetLongField(object, fieldID, newVal);
    }
}

template<>
jfloat Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.f = env->GetStaticFloatField(clazz, fieldID);
        } else {
            result.f = env->GetFloatField(object, fieldID);
        }
    }
    return result.f;
}

template<>
void Reflect::set(jfloat newVal) {
    if (isStaticField) {
        env->SetStaticFloatField(clazz, fieldID, newVal);
    } else {
        env->SetFloatField(object, fieldID, newVal);
    }
}

template<>
jdouble Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.d = env->GetStaticDoubleField(clazz, fieldID);
        } else {
            result.d = env->GetDoubleField(object, fieldID);
        }
    }
    return result.d;
}

template<>
void Reflect::set(jdouble newVal) {
    if (isStaticField) {
        env->SetStaticDoubleField(clazz, fieldID, newVal);
    } else {
        env->SetDoubleField(object, fieldID, newVal);
    }
}

template<>
jboolean Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.boolean = env->GetStaticBooleanField(clazz, fieldID);
        } else {
            result.boolean = env->GetBooleanField(object, fieldID);
        }
    }
    return result.boolean;
}

template<>
void Reflect::set(jboolean newVal) {
    if (isStaticField) {
        env->SetStaticBooleanField(clazz, fieldID, newVal);
    } else {
        env->SetBooleanField(object, fieldID, newVal);
    }
}

template<>
jbyte Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.byte = env->GetStaticByteField(clazz, fieldID);
        } else {
            result.byte = env->GetByteField(object, fieldID);
        }
    }
    return result.byte;
}

template<>
void Reflect::set(jbyte newVal) {
    if (isStaticField) {
        env->SetStaticByteField(clazz, fieldID, newVal);
    } else {
        env->SetByteField(object, fieldID, newVal);
    }
}

template<>
jchar Reflect::get() {
    if (fieldID != NULL) {
        if (isStaticField) {
            result.c = env->GetStaticCharField(clazz, fieldID);
        } else {
            result.c = env->GetCharField(object, fieldID);
        }
    }
    return result.c;
}

template<>
void Reflect::set(jchar newVal) {
    if (isStaticField) {
        env->SetStaticCharField(clazz, fieldID, newVal);
    } else {
        env->SetCharField(object, fieldID, newVal);
    }
}

void Reflect::clearException(JNIEnv *env) {
#ifdef DEBUG
    env->ExceptionDescribe();
#endif
    env->ExceptionClear();
}


int Reflect::getDataType(string dataSign) {
    if (dataSign.compare("S") == 0) return TYPE_SHORT;       // short
    if (dataSign.compare("I") == 0) return TYPE_INT;         // int
    if (dataSign.compare("J") == 0) return TYPE_LONG;        // long
    if (dataSign.compare("F") == 0) return TYPE_FLOAT;       // float
    if (dataSign.compare("D") == 0) return TYPE_DOUBLE;      // double
    if (dataSign.compare("Z") == 0) return TYPE_BOOLEAN;     // bool
    if (dataSign.compare("B") == 0) return TYPE_BYTE;        // byte
    if (dataSign.compare("C") == 0) return TYPE_CHAR;        // char
    return TYPE_OBJECT;
}

string Reflect::getMethodReturnValueSign(string sign) {
    int right = sign.rfind(")");
    return sign.substr(right + 1, sign.length());
}