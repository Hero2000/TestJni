#include <jni.h>
#include <string>
#include <android/log.h>
#include <pthread.h>

// __VA_ARGS__ 代表 ...的可变参数
#define TAG "native-lib"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_testjni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGD("12334 %d",12);
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_testjni_MainActivity_stringFromJNI2(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI2()
    std::string hello = "stringFromJNI2";
    LOGD("12334 %d",12);
    return env->NewStringUTF(hello.c_str());
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjni_MainActivity_test1(JNIEnv *env, jobject instance,
                                              jboolean jboolean1,
                                              jbyte jbyte1,
                                              jchar jchar1,
                                              jshort jshort1,
                                              jlong jlong1,
                                              jfloat jfloat1,
                                              jdouble jdouble1,
                                              jstring name_,
                                              jint age,
                                              jintArray i_,
                                              jobjectArray strs,
                                              jobject person,
                                              jbooleanArray bArray_) {

    //1. 接收 Java 传递过来的 boolean 值
    unsigned char b_boolean = jboolean1;
    LOGD("boolean-> %d", b_boolean);

    //2. 接收 Java 传递过来的 boolean 值
    char c_byte = jbyte1;
    LOGD("jbyte-> %d", c_byte);

    //3. 接收 Java 传递过来的 char 值
    unsigned short c_char = jchar1;
    LOGD("char-> %d", c_char);


    //4. 接收 Java 传递过来的 short 值
    short s_short = jshort1;
    LOGD("short-> %d", s_short);


    //5. 接收 Java 传递过来的 long 值
    long l_long = jlong1;
    LOGD("long-> %d", l_long);

    //6. 接收 Java 传递过来的 float 值
    float f_float = jfloat1;
    LOGD("float-> %f", f_float);


    //7. 接收 Java 传递过来的 double 值
    double d_double = jdouble1;
    LOGD("double-> %f", d_double);


    //8. 接收 Java 传递过来的 String 值

    jsize  length = env->GetStringUTFLength(name_);
    LOGD("length-> %d", length);


    const char *name_string = env->GetStringUTFChars(name_, 0);
    LOGD("string-> %s", name_string);

    //9. 接收 Java 传递过来的 int 值
    int age_java = age;
    LOGD("int:%d", age_java);

    //10. 打印 Java 传递过来的 int []
    jint *intArray = env->GetIntArrayElements(i_, NULL);
    //拿到数组长度
    jsize intArraySize = env->GetArrayLength(i_);
    for (int i = 0; i < intArraySize; ++i) {
        LOGD("intArray->%d：", intArray[i]);
    }
    //释放数组
    env->ReleaseIntArrayElements(i_, intArray, 0);


    //11. 打印 Java 传递过来的 String[]
    jsize stringArrayLength = env->GetArrayLength(strs);
    for (int i = 0; i < stringArrayLength; ++i) {
        jobject jobject1 = env->GetObjectArrayElement(strs, i);
        //强转 JNI String
        jstring stringArrayData = static_cast<jstring >(jobject1);

        //转 C  String
        const char *itemStr = env->GetStringUTFChars(stringArrayData, NULL);
        LOGD("String[%d]: %s", i, itemStr);
        //回收 String[]
        env->ReleaseStringUTFChars(stringArrayData, itemStr);
        env->DeleteLocalRef(jobject1); // 回收

    }

    //12. 打印 Java 传递过来的 Object 对象
    //12.1 获取字节码
    const char *person_class_str = "com/example/testjni/Person";
    //12.2 转 jni jclass
    jclass person_class = env->FindClass(person_class_str);
    //12.3 拿到方法签名 javap -a
    const char *sig = "()Ljava/lang/String;";
    jmethodID jmethodID1 = env->GetMethodID(person_class, "getName", sig);

    jobject obj_string = env->CallObjectMethod(person, jmethodID1);
    jstring perStr = static_cast<jstring >(obj_string);
    const char *itemStr2 = env->GetStringUTFChars(perStr, NULL);
    LOGD("Person: %s", itemStr2);

    env->ReleaseStringUTFChars(perStr, itemStr2);
    env->DeleteLocalRef(person_class); // 回收
    env->DeleteLocalRef(person); // 回收

    //13. 打印 Java 传递过来的 booleanArray
    jsize booArrayLength = env->GetArrayLength(bArray_);
    jboolean *bArray = env->GetBooleanArrayElements(bArray_, NULL);
    for (int i = 0; i < booArrayLength; ++i) {
        bool b =  bArray[i];
        jboolean b2 =  bArray[i];
        LOGD("boolean:%d",b)
        LOGD("jboolean:%d",b2)
    }
    //回收
    env->ReleaseBooleanArrayElements(bArray_, bArray, 0);


}extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_testjni_MainActivity_getPerson(JNIEnv *env, jobject thiz) {
    // TODO: implement getPerson()
    //1. 拿到 Java 类的全路径
    const char *person_java = "com/example/testjni/Person";
    const char *method = "<init>"; // Java构造方法的标识

    //2. 找到需要处理的 Java 对象 class
    jclass j_person_class = env->FindClass(person_java);

    //3. 拿到空参构造方法
    jmethodID person_constructor = env->GetMethodID(j_person_class, method, "()V");

    //4. 创建对象
    jobject person_obj = env->NewObject(j_person_class, person_constructor);

    //5. 拿到 setName 方法的签名，并拿到对应的 setName 方法
    const char *nameSig = "(Ljava/lang/String;)V";
    jmethodID nameMethodId = env->GetMethodID(j_person_class, "setName", nameSig);

    //6. 拿到 setAge 方法的签名，并拿到 setAge 方法
    const char *ageSig = "(I)V";
    jmethodID ageMethodId = env->GetMethodID(j_person_class, "setAge", ageSig);

    //7. 正在调用 Java 对象函数
    const char *name = "Hero";
    jstring newStringName = env->NewStringUTF(name);
    env->CallVoidMethod(person_obj, nameMethodId, newStringName);
    env->CallVoidMethod(person_obj, ageMethodId, 28);

    const char *sig = "()Ljava/lang/String;";
    jmethodID jtoString = env->GetMethodID(j_person_class, "toString", sig);
    jobject obj_string = env->CallObjectMethod(person_obj, jtoString);
    jstring perStr = static_cast<jstring >(obj_string);
    const char *itemStr2 = env->GetStringUTFChars(perStr, NULL);
    LOGD("Person: %s", itemStr2);
    return person_obj;

}

/**
 * TODO 动态注册
*/

/**
 * 对应java类的全路径名，.用/代替
 */
const char *classPathName = "com/example/testjni/MainActivity";
extern "C"  //支持 C 语言
JNIEXPORT void JNICALL //告诉虚拟机，这是jni函数
native_dynamicRegister(JNIEnv *env, jobject instance, jstring name) {
    const char *j_name = env->GetStringUTFChars(name, NULL);
    LOGD("动态注册: %s", j_name)
    //释放
    env->ReleaseStringUTFChars(name, j_name);
}

JavaVM * jvm;
jobject instance_custom;
void * customThread(void * pVoid) {

    // 调用的话，一定需要JNIEnv *env
    // JNIEnv *env 无法跨越线程，只有JavaVM才能跨越线程
    LOGD("动态注册: customThread result == %d",99);
    JNIEnv * env = NULL; // 全新的env
    int result = jvm->AttachCurrentThread(&env, 0); // 把native的线程，附加到JVM
    LOGD("动态注册: customThread result == %d",result);
    if (result != 0) {
        return 0;
    }

    jclass mainActivityClass = env->GetObjectClass(instance_custom);

    // 拿到MainActivity的updateUI
    const char * sig = "()V";
    jmethodID updateUI = env->GetMethodID(mainActivityClass, "updateUI", sig);

    env->CallVoidMethod(instance_custom, updateUI);

    // 解除 附加 到 JVM 的native线程
    jvm->DetachCurrentThread();

    return 0;
}



JNIEXPORT int JNICALL //告诉虚拟机，这是jni函数
native_printInfo(JNIEnv *env, jobject instance, jfloat info) {
    float f_float = info;
    f_float = f_float + 1.1;
    return  f_float;
}

extern "C"  //支持 C 语言
JNIEXPORT void JNICALL //告诉虚拟机，这是jni函数
native_testThread(JNIEnv *env, jobject thiz) {
    LOGD("动态注册: native_testThread");
    instance_custom = env->NewGlobalRef(thiz); // 全局的，就不会被释放，所以可以在线程里面用
    // 如果是非全局的，函数一结束，就被释放了
    pthread_t pthreadID;
    pthread_create(&pthreadID, 0, customThread, instance_custom);
    pthread_join(pthreadID, 0);
}

extern "C"  //支持 C 语言
JNIEXPORT void JNICALL //告诉虚拟机，这是jni函数
native_unThread(JNIEnv *env, jobject thiz) {
    if (NULL != instance_custom) {
        env->DeleteGlobalRef(instance_custom);
        instance_custom = NULL;
    }
}


/* 源码结构体
 * typedef struct {
    const char* name;
    const char* signature;
    void*       fnPtr;
    } JNINativeMethod;
 */
static const JNINativeMethod jniNativeMethod[] = {
        {"dynamicRegister", "(Ljava/lang/String;)V", (void *) (native_dynamicRegister)},

        {"printInfo", "(F)F", (void *) (native_printInfo)},
        {"testThread", "()V", (void *) (native_testThread)},
        {"unThread", "()V", (void *) (native_unThread)},

};

//public native void testThread();
//public native void unThread();
/**
 * 该函数定义在jni.h头文件中，System.loadLibrary()时会调用JNI_OnLoad()函数
 */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *javaVm, void *pVoid) {
    //通过虚拟机 创建爱你全新的 evn
    JNIEnv *jniEnv = nullptr;

    /*
      获取JavaVM接口两种直接方式
      JavaVM接口
      第一种方式，在加载动态链接库的时候，JVM会调用JNI_OnLoad(JavaVM* jvm, void* reserved)（如果定义了该函数）。第一个参数会传入JavaVM指针。
      第二种方式，在native code中调用JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args)可以得到JavaVM指针。
      两种情况下，都可以用全局变量，比如JavaVM* g_jvm来保存获得的指针以便在任意上下文中使用。
      Android系统是利用第二种方式Invocation interface来创建JVM的。

     * */

    jvm = javaVm;
    jint result = javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6);
    if (result != JNI_OK) {
        return JNI_ERR; // 主动报错
    }
    jclass mainActivityClass = jniEnv->FindClass(classPathName);
    jniEnv->RegisterNatives(mainActivityClass, jniNativeMethod,
                            sizeof(jniNativeMethod) / sizeof(JNINativeMethod));//动态注册的数量

    return JNI_VERSION_1_6;
}
