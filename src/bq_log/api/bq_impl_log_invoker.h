/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class bq_impl_log_invoker */

#ifndef _Included_bq_impl_log_invoker
#define _Included_bq_impl_log_invoker
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1version(JNIEnv*, jclass);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_enable_auto_crash_handler
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1enable_1auto_1crash_1handler(JNIEnv*, jclass);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_create_log
 * Signature: (Ljava/lang/String;Ljava/lang/String;J[Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_bq_impl_log_1invoker__1_1api_1create_1log(JNIEnv*, jclass, jstring, jstring, jlong, jobjectArray);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_reset_config
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1reset_1config(JNIEnv*, jclass, jstring, jstring);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_ring_buffer
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1ring_1buffer(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_buffer_alloc
 * Signature: (JJSJLjava/lang/String;J)J
 */
JNIEXPORT jlong JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1buffer_1alloc(JNIEnv*, jclass, jlong, jlong, jshort, jlong, jstring, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_arg_push_utf16_string
 * Signature: (JJLjava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1arg_1push_1utf16_1string(JNIEnv*, jclass, jlong, jlong, jstring, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_buffer_commit
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1buffer_1commit(JNIEnv*, jclass, jlong, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_set_appenders_enable
 * Signature: (JLjava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1set_1appenders_1enable(JNIEnv*, jclass, jlong, jstring, jboolean);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_logs_count
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1logs_1count(JNIEnv*, jclass);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_id_by_index
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1id_1by_1index(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_name_by_id
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1name_1by_1id(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_categories_count
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1categories_1count(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_category_name_by_index
 * Signature: (JJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1category_1name_1by_1index(JNIEnv*, jclass, jlong, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_merged_log_level_bitmap_by_log_id
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1merged_1log_1level_1bitmap_1by_1log_1id(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_category_masks_array_by_log_id
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1category_1masks_1array_1by_1log_1id(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_log_print_stack_level_bitmap_by_log_id
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1log_1print_1stack_1level_1bitmap_1by_1log_1id(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_device_console
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1device_1console(JNIEnv*, jclass, jint, jstring);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_force_flush
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1force_1flush(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_get_file_base_dir
 * Signature: (Z)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_bq_impl_log_1invoker__1_1api_1get_1file_1base_1dir(JNIEnv*, jclass, jboolean);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_decoder_create
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1decoder_1create(JNIEnv*, jclass, jstring);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_decoder_decode
 * Signature: (JLbq/def/string_holder;)I
 */
JNIEXPORT jint JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1decoder_1decode(JNIEnv*, jclass, jlong, jobject);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_decoder_destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1decoder_1destroy(JNIEnv*, jclass, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_log_decode
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_bq_impl_log_1invoker__1_1api_1log_1decode(JNIEnv*, jclass, jstring, jstring);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_enable_snapshot
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1enable_1snapshot(JNIEnv*, jclass, jlong, jlong);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_take_snapshot_string
 * Signature: (JZ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_bq_impl_log_1invoker__1_1api_1take_1snapshot_1string(JNIEnv*, jclass, jlong, jboolean);

/*
 * Class:     bq_impl_log_invoker
 * Method:    __api_set_console_callback
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_bq_impl_log_1invoker__1_1api_1set_1console_1callback(JNIEnv*, jclass, jboolean);

#ifdef __cplusplus
}
#endif
#endif
