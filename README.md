# JNIOOR

基于C++模板函数与Fluent API设计的JNI反射库，极大的简化JNI反射调用。

### 设计目标
- 弱化数据类型概念，强化操作意图

  > 在执行中间任何操作的时候无需关心数据类型，内部会依据传入的参数签名自动调用对应数据类型的原JNI函数，只需要在最终进行get操作与set操作时通过泛型指定数据类型

在执行中间操作时只需关注操作意图，即：
   1. 对什么操作：on
   2. 操作什么：构造函数用construct，域用field，静态域用staicField，函数调用用call，静态函数调用用staticCall
   3. 最终目的：获取值用get，修改值用set

### 功能特性
- 基于OOD设计的Fluent API：

  ```
  int intField = Reflect::on(env, object).field("intField", "I").get<jint>(); // 获取Filed
  Reflect::on(env, object).field("intField", "I").set<jint>(1); // 设置Field
  jobject object = Reflect::on(env, "tech/huqi/jnioor/Sample").construct("()V").get<jobject>();   // 调用构造函数
  jstring content = Reflect::on(env, object).call("toString"，"()Ljava/lang/String;").get<jstring>(); // 调用toString函数
  ```

  

- 完善的判空与异常检测逻辑

  > 当执行JNI函数的GetFieldID，GetMethodID，CallXxxMethod，CallStaticXxxMethod调用时，如果**获取的域，方法，调用的方法不存在时会抛出异常导致程序奔溃**

  这在对一些非官方系统(如非安卓原生，java原生)的类进行JNI调用时很常见，比如Xposed检测，如果你的代码运行在一个未安装Xposed框架的机器上，那么关于Xposed的域，方法操作都会出现异常导致崩溃。所以一个健壮稳定的JNI调用一般类似这样：

  ```
  jclass jcls_Sample = env->FindClass("tech/huqi/jnioor/Sample");
  if (jcls_Sample != NULL) {
      jmethodID jmid_init = env->GetMethodID(jcls_Sample, "<init>", "()V");
      if (jmid_init != NULL) {
          jobject job_Sample = env->NewObject(jcls_Sample, jmid_init);
          if (job_Sample != NULL) {
              jfieldID jfid_intField = env->GetFieldID(jcls_Sample, "intField", "I");
              if (jfid_intField != NULL) {
                  int intField = env->GetIntField(job_Sample, jfid_intField);
                  // ...... 省略后续其他逻辑
              } else {
                  checkAndClearException(env);// 检测并清理异常
              }
          } else {
              checkAndClearException(env);// 检测并清理异常
          }
      } else {
          checkAndClearException(env);// 检测并清理异常
      }
  } else {
      checkAndClearException(env);// 检测并清理异常
  }
  env->DeleteLocalRef(jcls_Sample); // 释放局部引用
  ```

  即对三方框架的类进行JNI调用时进行判空或异常检测后再进行下一步操作，如果为空进行异常检测并清理，如果中间产生了一些临时局部引用，还需要释放局部引用。但这样做代码结构嵌套太深，不利于阅读与后期维护，虽然这种嵌套可以采用goto语句来避免

  **现在有了这个库，只需要这样就包含了上述代码的功能：**

  ```
  jobject object = Reflect::on(env, "tech/huqi/jnioor/Sample").construct("()V").get<jobject>();
  if(object!=NULL){
      int intField = Reflect::on(env, object).field("intField", "I").get<jint>();
  }
  ```

  

### 示例

（以下示例基于文档最后的Sample类进行操作）

  ```
  // 获取非态域
  int intField = Reflect::on(env, object).field("intField", "I").get<jint>();
  long longField = Reflect::on(env, object).field("longField", "J").get<jlong>();
  float floatField = Reflect::on(env, object).field("floatField", "F").get<jfloat>();
  double doubleField = Reflect::on(env, object).field("doubleField", "D").get<jdouble>();
  jstring stringField = Reflect::on(env, object).field("stringField",
                                                           "Ljava/lang/String;").get<jstring>();
                                                           
   // 获取静态域
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
           
   // 设置非静态域
   Reflect::on(env, object).field("intField", "I").set<jint>(1);
   Reflect::on(env, object).field("longField", "J").set<jlong>(1);
   Reflect::on(env, object).field("floatField", "F").set<jfloat>(1.0f);
   Reflect::on(env, object).field("doubleField", "D").set<jdouble>(1.0);
   Reflect::on(env, object).field("stringField", "Ljava/lang/String;").set<jobject>(
              env->NewStringUTF("modify stringField value"));
              
   // 设置静态域
   Reflect::on(env, clazz).staticField("staticIntField", "I").set<jint>(1);
   Reflect::on(env, clazz).staticField("staticLongField", "J").set<jlong>(1);
   Reflect::on(env, clazz).staticField("staticFloatField", "F").set<jfloat>(1.0f);
   Reflect::on(env, clazz).staticField("staticDoubleField", "D").set<jdouble>(1.0);
   Reflect::on(env, clazz).staticField("staticStringField","Ljava/lang/String;").set<jobject>(
              env->NewStringUTF("modify staticStringField value"));
   // 调用构造函数
   jobject object = Reflect::on(env, clazz).construct("()V").get<jobject>();
   // 调用函数
   jstring content = Reflect::on(env, object).call("toString"，"()Ljava/lang/String;").get<jstring>();
  ```

  

### Sample类

```
public class Sample {
    private static final String TAG = "JniReflectSample";
    private int intField = 0;
    private static int staticIntField = 0;

    private long longField = 0;
    private static long staticLongField = 0;

    private float floatField = 0.1f;
    private static float staticFloatField = 0.1f;

    private double doubleField = 0.1;
    private static double staticDoubleField = 0.1;

    private String stringField = "this is a non-static String";
    private static String staticStringField = "this is a static String";

    public static native void nativePrint();

    public int getIntField() {
        return intField;
    }

    public long getLongField() {
        return longField;
    }

    public float getFloatField() {
        return floatField;
    }

    public double getDoubleField() {
        return doubleField;
    }

    public String getStringField() {
        return stringField;
    }

    @Override
    public String toString() {
        return "Sample{" +
                "intField=" + intField +
                ", longField=" + longField +
                ", floatField=" + floatField +
                ", doubleField=" + doubleField +
                ", stringField='" + stringField + '\'' +
                ", staticIntField=" + staticIntField +
                ", staticLongField=" + staticLongField +
                ", staticFloatField=" + staticFloatField +
                ", staticDoubleField=" + staticDoubleField +
                ", staticStringField='" + staticStringField + '\'' +
                '}';
    }
}

```


