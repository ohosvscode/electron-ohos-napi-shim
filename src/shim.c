#include <dlfcn.h>
#include <stdint.h>
#include <stddef.h>
#include "node_api.h"

// 符号表结构，用于存储动态解析的函数指针
typedef struct {
    // NAPI 基础函数
    napi_status (*napi_get_last_error_info)(napi_env env, const napi_extended_error_info** result);
    napi_status (*napi_get_undefined)(napi_env env, napi_value* result);
    napi_status (*napi_get_null)(napi_env env, napi_value* result);
    napi_status (*napi_get_global)(napi_env env, napi_value* result);
    napi_status (*napi_get_boolean)(napi_env env, bool value, napi_value* result);
    
    // 对象创建函数
    napi_status (*napi_create_object)(napi_env env, napi_value* result);
    napi_status (*napi_create_array)(napi_env env, napi_value* result);
    napi_status (*napi_create_array_with_length)(napi_env env, size_t length, napi_value* result);
    
    // 数值创建函数
    napi_status (*napi_create_double)(napi_env env, double value, napi_value* result);
    napi_status (*napi_create_int32)(napi_env env, int32_t value, napi_value* result);
    napi_status (*napi_create_uint32)(napi_env env, uint32_t value, napi_value* result);
    napi_status (*napi_create_int64)(napi_env env, int64_t value, napi_value* result);
    
    // 字符串创建函数
    napi_status (*napi_create_string_latin1)(napi_env env, const char* str, size_t length, napi_value* result);
    napi_status (*napi_create_string_utf8)(napi_env env, const char* str, size_t length, napi_value* result);
    napi_status (*napi_create_string_utf16)(napi_env env, const char16_t* str, size_t length, napi_value* result);
    napi_status (*node_api_create_external_string_latin1)(napi_env env, char* str, size_t length, napi_finalize finalize_cb, void* finalize_hint, napi_value* result, bool* copied);
    napi_status (*node_api_create_external_string_utf16)(napi_env env, char16_t* str, size_t length, napi_finalize finalize_cb, void* finalize_hint, napi_value* result, bool* copied);
    
    // Symbol 相关
    napi_status (*napi_create_symbol)(napi_env env, napi_value description, napi_value* result);
    napi_status (*node_api_symbol_for)(napi_env env, const char* utf8description, size_t length, napi_value* result);
    
    // 函数创建
    napi_status (*napi_create_function)(napi_env env, const char* utf8name, size_t length, napi_callback cb, void* data, napi_value* result);
    
    // 错误处理
    napi_status (*napi_create_error)(napi_env env, napi_value code, napi_value msg, napi_value* result);
    napi_status (*napi_create_type_error)(napi_env env, napi_value code, napi_value msg, napi_value* result);
    napi_status (*napi_create_range_error)(napi_env env, napi_value code, napi_value msg, napi_value* result);
    napi_status (*node_api_create_syntax_error)(napi_env env, napi_value code, napi_value msg, napi_value* result);
    
    // 类型检查和转换
    napi_status (*napi_typeof)(napi_env env, napi_value value, napi_valuetype* result);
    napi_status (*napi_get_value_double)(napi_env env, napi_value value, double* result);
    napi_status (*napi_get_value_int32)(napi_env env, napi_value value, int32_t* result);
    napi_status (*napi_get_value_uint32)(napi_env env, napi_value value, uint32_t* result);
    napi_status (*napi_get_value_int64)(napi_env env, napi_value value, int64_t* result);
    napi_status (*napi_get_value_bool)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_get_value_string_latin1)(napi_env env, napi_value value, char* buf, size_t bufsize, size_t* result);
    napi_status (*napi_get_value_string_utf8)(napi_env env, napi_value value, char* buf, size_t bufsize, size_t* result);
    napi_status (*napi_get_value_string_utf16)(napi_env env, napi_value value, char16_t* buf, size_t bufsize, size_t* result);
    
    // 类型转换
    napi_status (*napi_coerce_to_bool)(napi_env env, napi_value value, napi_value* result);
    napi_status (*napi_coerce_to_number)(napi_env env, napi_value value, napi_value* result);
    napi_status (*napi_coerce_to_object)(napi_env env, napi_value value, napi_value* result);
    napi_status (*napi_coerce_to_string)(napi_env env, napi_value value, napi_value* result);
    
    // 对象操作
    napi_status (*napi_get_prototype)(napi_env env, napi_value object, napi_value* result);
    napi_status (*napi_get_property_names)(napi_env env, napi_value object, napi_value* result);
    napi_status (*napi_set_property)(napi_env env, napi_value object, napi_value key, napi_value value);
    napi_status (*napi_has_property)(napi_env env, napi_value object, napi_value key, bool* result);
    napi_status (*napi_get_property)(napi_env env, napi_value object, napi_value key, napi_value* result);
    napi_status (*napi_delete_property)(napi_env env, napi_value object, napi_value key, bool* result);
    napi_status (*napi_has_own_property)(napi_env env, napi_value object, napi_value key, bool* result);
    
    // 命名属性操作
    napi_status (*napi_set_named_property)(napi_env env, napi_value object, const char* utf8name, napi_value value);
    napi_status (*napi_has_named_property)(napi_env env, napi_value object, const char* utf8name, bool* result);
    napi_status (*napi_get_named_property)(napi_env env, napi_value object, const char* utf8name, napi_value* result);
    
    // 数组元素操作
    napi_status (*napi_set_element)(napi_env env, napi_value object, uint32_t index, napi_value value);
    napi_status (*napi_has_element)(napi_env env, napi_value object, uint32_t index, bool* result);
    napi_status (*napi_get_element)(napi_env env, napi_value object, uint32_t index, napi_value* result);
    napi_status (*napi_delete_element)(napi_env env, napi_value object, uint32_t index, bool* result);
    
    // 属性定义
    napi_status (*napi_define_properties)(napi_env env, napi_value object, size_t property_count, const napi_property_descriptor* properties);
    
    // 数组检查
    napi_status (*napi_is_array)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_get_array_length)(napi_env env, napi_value value, uint32_t* result);
    
    // 值比较
    napi_status (*napi_strict_equals)(napi_env env, napi_value lhs, napi_value rhs, bool* result);
    
    // 函数调用
    napi_status (*napi_call_function)(napi_env env, napi_value recv, napi_value func, size_t argc, const napi_value* argv, napi_value* result);
    napi_status (*napi_new_instance)(napi_env env, napi_value constructor, size_t argc, const napi_value* argv, napi_value* result);
    napi_status (*napi_instanceof)(napi_env env, napi_value object, napi_value constructor, bool* result);
    
    // 回调信息
    napi_status (*napi_get_cb_info)(napi_env env, napi_callback_info cbinfo, size_t* argc, napi_value* argv, napi_value* this_arg, void** data);
    napi_status (*napi_get_new_target)(napi_env env, napi_callback_info cbinfo, napi_value* result);
    
    // 类定义
    napi_status (*napi_define_class)(napi_env env, const char* utf8name, size_t length, napi_callback constructor, void* data, size_t property_count, const napi_property_descriptor* properties, napi_value* result);
    
    // 对象包装
    napi_status (*napi_wrap)(napi_env env, napi_value js_object, void* native_object, napi_finalize finalize_cb, void* finalize_hint, napi_ref* result);
    napi_status (*napi_unwrap)(napi_env env, napi_value js_object, void** result);
    napi_status (*napi_remove_wrap)(napi_env env, napi_value js_object, void** result);
    
    // External 对象
    napi_status (*napi_create_external)(napi_env env, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result);
    napi_status (*napi_get_value_external)(napi_env env, napi_value value, void** result);
    
    // 引用管理
    napi_status (*napi_create_reference)(napi_env env, napi_value value, uint32_t initial_refcount, napi_ref* result);
    napi_status (*napi_delete_reference)(napi_env env, napi_ref ref);
    napi_status (*napi_reference_ref)(napi_env env, napi_ref ref, uint32_t* result);
    napi_status (*napi_reference_unref)(napi_env env, napi_ref ref, uint32_t* result);
    napi_status (*napi_get_reference_value)(napi_env env, napi_ref ref, napi_value* result);
    
    // Handle Scope
    napi_status (*napi_open_handle_scope)(napi_env env, napi_handle_scope* result);
    napi_status (*napi_close_handle_scope)(napi_env env, napi_handle_scope scope);
    napi_status (*napi_open_escapable_handle_scope)(napi_env env, napi_escapable_handle_scope* result);
    napi_status (*napi_close_escapable_handle_scope)(napi_env env, napi_escapable_handle_scope scope);
    napi_status (*napi_escape_handle)(napi_env env, napi_escapable_handle_scope scope, napi_value escapee, napi_value* result);
    
    // 异常处理
    napi_status (*napi_throw)(napi_env env, napi_value error);
    napi_status (*napi_throw_error)(napi_env env, const char* code, const char* msg);
    napi_status (*napi_throw_type_error)(napi_env env, const char* code, const char* msg);
    napi_status (*napi_throw_range_error)(napi_env env, const char* code, const char* msg);
    napi_status (*node_api_throw_syntax_error)(napi_env env, const char* code, const char* msg);
    napi_status (*napi_is_error)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_is_exception_pending)(napi_env env, bool* result);
    napi_status (*napi_get_and_clear_last_exception)(napi_env env, napi_value* result);
    
    // Buffer 相关
    napi_status (*napi_is_buffer)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_create_buffer)(napi_env env, size_t length, void** data, napi_value* result);
    napi_status (*napi_create_external_buffer)(napi_env env, size_t length, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result);
    napi_status (*napi_create_buffer_copy)(napi_env env, size_t length, const void* data, void** result_data, napi_value* result);
    napi_status (*napi_get_buffer_info)(napi_env env, napi_value value, void** data, size_t* length);
    
    // ArrayBuffer 相关
    napi_status (*napi_is_arraybuffer)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_create_arraybuffer)(napi_env env, size_t byte_length, void** data, napi_value* result);
    napi_status (*napi_create_external_arraybuffer)(napi_env env, void* external_data, size_t byte_length, napi_finalize finalize_cb, void* finalize_hint, napi_value* result);
    napi_status (*napi_get_arraybuffer_info)(napi_env env, napi_value arraybuffer, void** data, size_t* byte_length);
    napi_status (*napi_detach_arraybuffer)(napi_env env, napi_value arraybuffer);
    napi_status (*napi_is_detached_arraybuffer)(napi_env env, napi_value arraybuffer, bool* result);
    
    // TypedArray 相关
    napi_status (*napi_is_typedarray)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_create_typedarray)(napi_env env, napi_typedarray_type type, size_t length, napi_value arraybuffer, size_t byte_offset, napi_value* result);
    napi_status (*napi_get_typedarray_info)(napi_env env, napi_value typedarray, napi_typedarray_type* type, size_t* length, void** data, napi_value* arraybuffer, size_t* byte_offset);
    
    // DataView 相关
    napi_status (*napi_create_dataview)(napi_env env, size_t byte_length, napi_value arraybuffer, size_t byte_offset, napi_value* result);
    napi_status (*napi_is_dataview)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_get_dataview_info)(napi_env env, napi_value dataview, size_t* bytelength, void** data, napi_value* arraybuffer, size_t* byte_offset);
    
    // 版本信息
    napi_status (*napi_get_version)(napi_env env, uint32_t* result);
    
    // Promise 相关
    napi_status (*napi_create_promise)(napi_env env, napi_deferred* deferred, napi_value* promise);
    napi_status (*napi_resolve_deferred)(napi_env env, napi_deferred deferred, napi_value resolution);
    napi_status (*napi_reject_deferred)(napi_env env, napi_deferred deferred, napi_value rejection);
    napi_status (*napi_is_promise)(napi_env env, napi_value value, bool* result);
    
    // 脚本执行
    napi_status (*napi_run_script)(napi_env env, napi_value script, napi_value* result);
    
    // 内存管理
    napi_status (*napi_adjust_external_memory)(napi_env env, int64_t change_in_bytes, int64_t* adjusted_value);
    
    // Date 相关
    napi_status (*napi_create_date)(napi_env env, double time, napi_value* result);
    napi_status (*napi_is_date)(napi_env env, napi_value value, bool* result);
    napi_status (*napi_get_date_value)(napi_env env, napi_value value, double* result);
    
    // Finalizer 相关
    napi_status (*napi_add_finalizer)(napi_env env, napi_value js_object, void* finalize_data, napi_finalize finalize_cb, void* finalize_hint, napi_ref* result);
    napi_status (*node_api_post_finalizer)(napi_env env, napi_finalize finalize_cb, void* finalize_data, void* finalize_hint);
    
    // BigInt 相关
    napi_status (*napi_create_bigint_int64)(napi_env env, int64_t value, napi_value* result);
    napi_status (*napi_create_bigint_uint64)(napi_env env, uint64_t value, napi_value* result);
    napi_status (*napi_create_bigint_words)(napi_env env, int sign_bit, size_t word_count, const uint64_t* words, napi_value* result);
    napi_status (*napi_get_value_bigint_int64)(napi_env env, napi_value value, int64_t* result, bool* lossless);
    napi_status (*napi_get_value_bigint_uint64)(napi_env env, napi_value value, uint64_t* result, bool* lossless);
    napi_status (*napi_get_value_bigint_words)(napi_env env, napi_value value, int* sign_bit, size_t* word_count, uint64_t* words);
    
    // 高级属性操作
    napi_status (*napi_get_all_property_names)(napi_env env, napi_value object, napi_key_collection_mode key_mode, napi_key_filter key_filter, napi_key_conversion key_conversion, napi_value* result);
    
    // 实例数据
    napi_status (*napi_set_instance_data)(napi_env env, void* data, napi_finalize finalize_cb, void* finalize_hint);
    napi_status (*napi_get_instance_data)(napi_env env, void** result);
    
    // 对象标记
    napi_status (*napi_type_tag_object)(napi_env env, napi_value js_object, const napi_type_tag* type_tag);
    napi_status (*napi_check_object_type_tag)(napi_env env, napi_value js_object, const napi_type_tag* type_tag, bool* result);
    
    // 对象冻结/密封
    napi_status (*napi_object_freeze)(napi_env env, napi_value object);
    napi_status (*napi_object_seal)(napi_env env, napi_value object);
    
    // 模块注册
    void (*napi_module_register)(napi_module* mod);
    
    // 致命错误
    void (*napi_fatal_error)(const char* location, size_t location_len, const char* message, size_t message_len);
    
    // 异步相关
    napi_status (*napi_async_init)(napi_env env, napi_value async_resource, napi_value async_resource_name, napi_async_context* result);
    napi_status (*napi_async_destroy)(napi_env env, napi_async_context async_context);
    napi_status (*napi_make_callback)(napi_env env, napi_async_context async_context, napi_value recv, napi_value func, size_t argc, const napi_value* argv, napi_value* result);
    
    // 异步工作
    napi_status (*napi_create_async_work)(napi_env env, napi_value async_resource, napi_value async_resource_name, napi_async_execute_callback execute, napi_async_complete_callback complete, void* data, napi_async_work* result);
    napi_status (*napi_delete_async_work)(napi_env env, napi_async_work work);
    napi_status (*napi_queue_async_work)(napi_env env, napi_async_work work);
    napi_status (*napi_cancel_async_work)(napi_env env, napi_async_work work);
    
    // Node.js 相关
    napi_status (*napi_get_node_version)(napi_env env, const napi_node_version** version);
    napi_status (*napi_get_uv_event_loop)(napi_env env, struct uv_loop_s** loop);
    napi_status (*napi_fatal_exception)(napi_env env, napi_value err);
    
    // 环境清理钩子
    napi_status (*napi_add_env_cleanup_hook)(napi_env env, void (*fun)(void* arg), void* arg);
    napi_status (*napi_remove_env_cleanup_hook)(napi_env env, void (*fun)(void* arg), void* arg);
    
    // 回调作用域
    napi_status (*napi_open_callback_scope)(napi_env env, napi_value resource_object, napi_async_context context, napi_callback_scope* result);
    napi_status (*napi_close_callback_scope)(napi_env env, napi_callback_scope scope);
    
    // 线程安全函数
    napi_status (*napi_create_threadsafe_function)(napi_env env, napi_value func, napi_value async_resource, napi_value async_resource_name, size_t max_queue_size, size_t initial_thread_count, void* thread_finalize_data, napi_finalize thread_finalize_cb, void* context, napi_threadsafe_function_call_js call_js_cb, napi_threadsafe_function* result);
    napi_status (*napi_get_threadsafe_function_context)(napi_threadsafe_function func, void** result);
    napi_status (*napi_call_threadsafe_function)(napi_threadsafe_function func, void* data, napi_threadsafe_function_call_mode is_blocking);
    napi_status (*napi_acquire_threadsafe_function)(napi_threadsafe_function func);
    napi_status (*napi_release_threadsafe_function)(napi_threadsafe_function func, napi_threadsafe_function_release_mode mode);
    napi_status (*napi_unref_threadsafe_function)(napi_env env, napi_threadsafe_function func);
    napi_status (*napi_ref_threadsafe_function)(napi_env env, napi_threadsafe_function func);
    
    // 异步清理钩子
    napi_status (*napi_add_async_cleanup_hook)(napi_env env, napi_async_cleanup_hook hook, void* arg, napi_async_cleanup_hook_handle* remove_handle);
    napi_status (*napi_remove_async_cleanup_hook)(napi_async_cleanup_hook_handle remove_handle);
    
    // 模块文件名
    napi_status (*node_api_get_module_file_name)(napi_env env, const char** result);
    
    // libuv 函数
    void (*uv_close)(void* handle, void* close_cb);
    int (*uv_mutex_init)(void* handle);
    int (*uv_mutex_init_recursive)(void* handle);
    void (*uv_mutex_destroy)(void* handle);
    void (*uv_mutex_lock)(void* handle);
    int (*uv_mutex_trylock)(void* handle);
    void (*uv_mutex_unlock)(void* handle);
    int (*uv_async_init)(void* loop, void* async, void* async_cb);
    int (*uv_async_send)(void* async);
    
} ElectronSymbolTable;

// 全局符号表实例
static ElectronSymbolTable g_electronSymbolTable = {0};

// 确保 Electron 符号已解析的函数
static void ensure_electron_symbols_resolved() {
    // 如果第一个函数指针已经被设置，说明已经初始化过了
    if (g_electronSymbolTable.napi_get_last_error_info != NULL) {
        return;
    }
    
    // 使用 RTLD_LAZY 模式打开 libelectron.so
    void* handle = dlopen("libelectron.so", RTLD_LAZY);
    if (!handle) {
        // 如果无法打开库，这里应该有错误处理
        // 但从汇编代码看，似乎没有特别的错误处理
        return;
    }
    
    // 逐个解析所有符号
    g_electronSymbolTable.napi_get_last_error_info = dlsym(handle, "napi_get_last_error_info");
    g_electronSymbolTable.napi_get_undefined = dlsym(handle, "napi_get_undefined");
    g_electronSymbolTable.napi_get_null = dlsym(handle, "napi_get_null");
    g_electronSymbolTable.napi_get_global = dlsym(handle, "napi_get_global");
    g_electronSymbolTable.napi_get_boolean = dlsym(handle, "napi_get_boolean");
    g_electronSymbolTable.napi_create_object = dlsym(handle, "napi_create_object");
    g_electronSymbolTable.napi_create_array = dlsym(handle, "napi_create_array");
    g_electronSymbolTable.napi_create_array_with_length = dlsym(handle, "napi_create_array_with_length");
    g_electronSymbolTable.napi_create_double = dlsym(handle, "napi_create_double");
    g_electronSymbolTable.napi_create_int32 = dlsym(handle, "napi_create_int32");
    g_electronSymbolTable.napi_create_uint32 = dlsym(handle, "napi_create_uint32");
    g_electronSymbolTable.napi_create_int64 = dlsym(handle, "napi_create_int64");
    g_electronSymbolTable.napi_create_string_latin1 = dlsym(handle, "napi_create_string_latin1");
    g_electronSymbolTable.napi_create_string_utf8 = dlsym(handle, "napi_create_string_utf8");
    g_electronSymbolTable.napi_create_string_utf16 = dlsym(handle, "napi_create_string_utf16");
    g_electronSymbolTable.node_api_create_external_string_latin1 = dlsym(handle, "node_api_create_external_string_latin1");
    g_electronSymbolTable.node_api_create_external_string_utf16 = dlsym(handle, "node_api_create_external_string_utf16");
    g_electronSymbolTable.napi_create_symbol = dlsym(handle, "napi_create_symbol");
    g_electronSymbolTable.node_api_symbol_for = dlsym(handle, "node_api_symbol_for");
    g_electronSymbolTable.napi_create_function = dlsym(handle, "napi_create_function");
    g_electronSymbolTable.napi_create_error = dlsym(handle, "napi_create_error");
    g_electronSymbolTable.napi_create_type_error = dlsym(handle, "napi_create_type_error");
    g_electronSymbolTable.napi_create_range_error = dlsym(handle, "napi_create_range_error");
    g_electronSymbolTable.node_api_create_syntax_error = dlsym(handle, "node_api_create_syntax_error");
    g_electronSymbolTable.napi_typeof = dlsym(handle, "napi_typeof");
    g_electronSymbolTable.napi_get_value_double = dlsym(handle, "napi_get_value_double");
    g_electronSymbolTable.napi_get_value_int32 = dlsym(handle, "napi_get_value_int32");
    g_electronSymbolTable.napi_get_value_uint32 = dlsym(handle, "napi_get_value_uint32");
    g_electronSymbolTable.napi_get_value_int64 = dlsym(handle, "napi_get_value_int64");
    g_electronSymbolTable.napi_get_value_bool = dlsym(handle, "napi_get_value_bool");
    g_electronSymbolTable.napi_get_value_string_latin1 = dlsym(handle, "napi_get_value_string_latin1");
    g_electronSymbolTable.napi_get_value_string_utf8 = dlsym(handle, "napi_get_value_string_utf8");
    g_electronSymbolTable.napi_get_value_string_utf16 = dlsym(handle, "napi_get_value_string_utf16");
    g_electronSymbolTable.napi_coerce_to_bool = dlsym(handle, "napi_coerce_to_bool");
    g_electronSymbolTable.napi_coerce_to_number = dlsym(handle, "napi_coerce_to_number");
    g_electronSymbolTable.napi_coerce_to_object = dlsym(handle, "napi_coerce_to_object");
    g_electronSymbolTable.napi_coerce_to_string = dlsym(handle, "napi_coerce_to_string");
    g_electronSymbolTable.napi_get_prototype = dlsym(handle, "napi_get_prototype");
    g_electronSymbolTable.napi_get_property_names = dlsym(handle, "napi_get_property_names");
    g_electronSymbolTable.napi_set_property = dlsym(handle, "napi_set_property");
    g_electronSymbolTable.napi_has_property = dlsym(handle, "napi_has_property");
    g_electronSymbolTable.napi_get_property = dlsym(handle, "napi_get_property");
    g_electronSymbolTable.napi_delete_property = dlsym(handle, "napi_delete_property");
    g_electronSymbolTable.napi_has_own_property = dlsym(handle, "napi_has_own_property");
    g_electronSymbolTable.napi_set_named_property = dlsym(handle, "napi_set_named_property");
    g_electronSymbolTable.napi_has_named_property = dlsym(handle, "napi_has_named_property");
    g_electronSymbolTable.napi_get_named_property = dlsym(handle, "napi_get_named_property");
    g_electronSymbolTable.napi_set_element = dlsym(handle, "napi_set_element");
    g_electronSymbolTable.napi_has_element = dlsym(handle, "napi_has_element");
    g_electronSymbolTable.napi_get_element = dlsym(handle, "napi_get_element");
    g_electronSymbolTable.napi_delete_element = dlsym(handle, "napi_delete_element");
    g_electronSymbolTable.napi_define_properties = dlsym(handle, "napi_define_properties");
    g_electronSymbolTable.napi_is_array = dlsym(handle, "napi_is_array");
    g_electronSymbolTable.napi_get_array_length = dlsym(handle, "napi_get_array_length");
    g_electronSymbolTable.napi_strict_equals = dlsym(handle, "napi_strict_equals");
    g_electronSymbolTable.napi_call_function = dlsym(handle, "napi_call_function");
    g_electronSymbolTable.napi_new_instance = dlsym(handle, "napi_new_instance");
    g_electronSymbolTable.napi_instanceof = dlsym(handle, "napi_instanceof");
    g_electronSymbolTable.napi_get_cb_info = dlsym(handle, "napi_get_cb_info");
    g_electronSymbolTable.napi_get_new_target = dlsym(handle, "napi_get_new_target");
    g_electronSymbolTable.napi_define_class = dlsym(handle, "napi_define_class");
    g_electronSymbolTable.napi_wrap = dlsym(handle, "napi_wrap");
    g_electronSymbolTable.napi_unwrap = dlsym(handle, "napi_unwrap");
    g_electronSymbolTable.napi_remove_wrap = dlsym(handle, "napi_remove_wrap");
    g_electronSymbolTable.napi_create_external = dlsym(handle, "napi_create_external");
    g_electronSymbolTable.napi_get_value_external = dlsym(handle, "napi_get_value_external");
    g_electronSymbolTable.napi_create_reference = dlsym(handle, "napi_create_reference");
    g_electronSymbolTable.napi_delete_reference = dlsym(handle, "napi_delete_reference");
    g_electronSymbolTable.napi_reference_ref = dlsym(handle, "napi_reference_ref");
    g_electronSymbolTable.napi_reference_unref = dlsym(handle, "napi_reference_unref");
    g_electronSymbolTable.napi_get_reference_value = dlsym(handle, "napi_get_reference_value");
    g_electronSymbolTable.napi_open_handle_scope = dlsym(handle, "napi_open_handle_scope");
    g_electronSymbolTable.napi_close_handle_scope = dlsym(handle, "napi_close_handle_scope");
    g_electronSymbolTable.napi_open_escapable_handle_scope = dlsym(handle, "napi_open_escapable_handle_scope");
    g_electronSymbolTable.napi_close_escapable_handle_scope = dlsym(handle, "napi_close_escapable_handle_scope");
    g_electronSymbolTable.napi_escape_handle = dlsym(handle, "napi_escape_handle");
    g_electronSymbolTable.napi_throw = dlsym(handle, "napi_throw");
    g_electronSymbolTable.napi_throw_error = dlsym(handle, "napi_throw_error");
    g_electronSymbolTable.napi_throw_type_error = dlsym(handle, "napi_throw_type_error");
    g_electronSymbolTable.napi_throw_range_error = dlsym(handle, "napi_throw_range_error");
    g_electronSymbolTable.node_api_throw_syntax_error = dlsym(handle, "node_api_throw_syntax_error");
    g_electronSymbolTable.napi_is_error = dlsym(handle, "napi_is_error");
    g_electronSymbolTable.napi_is_exception_pending = dlsym(handle, "napi_is_exception_pending");
    g_electronSymbolTable.napi_get_and_clear_last_exception = dlsym(handle, "napi_get_and_clear_last_exception");
    g_electronSymbolTable.napi_is_arraybuffer = dlsym(handle, "napi_is_arraybuffer");
    g_electronSymbolTable.napi_create_arraybuffer = dlsym(handle, "napi_create_arraybuffer");
    g_electronSymbolTable.napi_create_external_arraybuffer = dlsym(handle, "napi_create_external_arraybuffer");
    g_electronSymbolTable.napi_get_arraybuffer_info = dlsym(handle, "napi_get_arraybuffer_info");
    g_electronSymbolTable.napi_is_typedarray = dlsym(handle, "napi_is_typedarray");
    g_electronSymbolTable.napi_create_typedarray = dlsym(handle, "napi_create_typedarray");
    g_electronSymbolTable.napi_get_typedarray_info = dlsym(handle, "napi_get_typedarray_info");
    g_electronSymbolTable.napi_create_dataview = dlsym(handle, "napi_create_dataview");
    g_electronSymbolTable.napi_is_dataview = dlsym(handle, "napi_is_dataview");
    g_electronSymbolTable.napi_get_dataview_info = dlsym(handle, "napi_get_dataview_info");
    g_electronSymbolTable.napi_get_version = dlsym(handle, "napi_get_version");
    g_electronSymbolTable.napi_create_promise = dlsym(handle, "napi_create_promise");
    g_electronSymbolTable.napi_resolve_deferred = dlsym(handle, "napi_resolve_deferred");
    g_electronSymbolTable.napi_reject_deferred = dlsym(handle, "napi_reject_deferred");
    g_electronSymbolTable.napi_is_promise = dlsym(handle, "napi_is_promise");
    g_electronSymbolTable.napi_run_script = dlsym(handle, "napi_run_script");
    g_electronSymbolTable.napi_adjust_external_memory = dlsym(handle, "napi_adjust_external_memory");
    g_electronSymbolTable.napi_create_date = dlsym(handle, "napi_create_date");
    g_electronSymbolTable.napi_is_date = dlsym(handle, "napi_is_date");
    g_electronSymbolTable.napi_get_date_value = dlsym(handle, "napi_get_date_value");
    g_electronSymbolTable.napi_add_finalizer = dlsym(handle, "napi_add_finalizer");
    g_electronSymbolTable.node_api_post_finalizer = dlsym(handle, "node_api_post_finalizer");
    g_electronSymbolTable.napi_create_bigint_int64 = dlsym(handle, "napi_create_bigint_int64");
    g_electronSymbolTable.napi_create_bigint_uint64 = dlsym(handle, "napi_create_bigint_uint64");
    g_electronSymbolTable.napi_create_bigint_words = dlsym(handle, "napi_create_bigint_words");
    g_electronSymbolTable.napi_get_value_bigint_int64 = dlsym(handle, "napi_get_value_bigint_int64");
    g_electronSymbolTable.napi_get_value_bigint_uint64 = dlsym(handle, "napi_get_value_bigint_uint64");
    g_electronSymbolTable.napi_get_value_bigint_words = dlsym(handle, "napi_get_value_bigint_words");
    g_electronSymbolTable.napi_get_all_property_names = dlsym(handle, "napi_get_all_property_names");
    g_electronSymbolTable.napi_set_instance_data = dlsym(handle, "napi_set_instance_data");
    g_electronSymbolTable.napi_get_instance_data = dlsym(handle, "napi_get_instance_data");
    g_electronSymbolTable.napi_detach_arraybuffer = dlsym(handle, "napi_detach_arraybuffer");
    g_electronSymbolTable.napi_is_detached_arraybuffer = dlsym(handle, "napi_is_detached_arraybuffer");
    g_electronSymbolTable.napi_type_tag_object = dlsym(handle, "napi_type_tag_object");
    g_electronSymbolTable.napi_check_object_type_tag = dlsym(handle, "napi_check_object_type_tag");
    g_electronSymbolTable.napi_object_freeze = dlsym(handle, "napi_object_freeze");
    g_electronSymbolTable.napi_object_seal = dlsym(handle, "napi_object_seal");
    g_electronSymbolTable.napi_module_register = dlsym(handle, "napi_module_register");
    g_electronSymbolTable.napi_fatal_error = dlsym(handle, "napi_fatal_error");
    g_electronSymbolTable.napi_async_init = dlsym(handle, "napi_async_init");
    g_electronSymbolTable.napi_async_destroy = dlsym(handle, "napi_async_destroy");
    g_electronSymbolTable.napi_make_callback = dlsym(handle, "napi_make_callback");
    g_electronSymbolTable.napi_create_buffer = dlsym(handle, "napi_create_buffer");
    g_electronSymbolTable.napi_create_external_buffer = dlsym(handle, "napi_create_external_buffer");
    g_electronSymbolTable.napi_create_buffer_copy = dlsym(handle, "napi_create_buffer_copy");
    g_electronSymbolTable.napi_is_buffer = dlsym(handle, "napi_is_buffer");
    g_electronSymbolTable.napi_get_buffer_info = dlsym(handle, "napi_get_buffer_info");
    g_electronSymbolTable.napi_create_async_work = dlsym(handle, "napi_create_async_work");
    g_electronSymbolTable.napi_delete_async_work = dlsym(handle, "napi_delete_async_work");
    g_electronSymbolTable.napi_queue_async_work = dlsym(handle, "napi_queue_async_work");
    g_electronSymbolTable.napi_cancel_async_work = dlsym(handle, "napi_cancel_async_work");
    g_electronSymbolTable.napi_get_node_version = dlsym(handle, "napi_get_node_version");
    g_electronSymbolTable.napi_get_uv_event_loop = dlsym(handle, "napi_get_uv_event_loop");
    g_electronSymbolTable.napi_fatal_exception = dlsym(handle, "napi_fatal_exception");
    g_electronSymbolTable.napi_add_env_cleanup_hook = dlsym(handle, "napi_add_env_cleanup_hook");
    g_electronSymbolTable.napi_remove_env_cleanup_hook = dlsym(handle, "napi_remove_env_cleanup_hook");
    g_electronSymbolTable.napi_open_callback_scope = dlsym(handle, "napi_open_callback_scope");
    g_electronSymbolTable.napi_close_callback_scope = dlsym(handle, "napi_close_callback_scope");
    g_electronSymbolTable.napi_create_threadsafe_function = dlsym(handle, "napi_create_threadsafe_function");
    g_electronSymbolTable.napi_get_threadsafe_function_context = dlsym(handle, "napi_get_threadsafe_function_context");
    g_electronSymbolTable.napi_call_threadsafe_function = dlsym(handle, "napi_call_threadsafe_function");
    g_electronSymbolTable.napi_acquire_threadsafe_function = dlsym(handle, "napi_acquire_threadsafe_function");
    g_electronSymbolTable.napi_release_threadsafe_function = dlsym(handle, "napi_release_threadsafe_function");
    g_electronSymbolTable.napi_unref_threadsafe_function = dlsym(handle, "napi_unref_threadsafe_function");
    g_electronSymbolTable.napi_ref_threadsafe_function = dlsym(handle, "napi_ref_threadsafe_function");
    g_electronSymbolTable.napi_add_async_cleanup_hook = dlsym(handle, "napi_add_async_cleanup_hook");
    g_electronSymbolTable.napi_remove_async_cleanup_hook = dlsym(handle, "napi_remove_async_cleanup_hook");
    g_electronSymbolTable.node_api_get_module_file_name = dlsym(handle, "node_api_get_module_file_name");
    
    // libuv 函数
    g_electronSymbolTable.uv_close = dlsym(handle, "uv_close");
    g_electronSymbolTable.uv_mutex_init = dlsym(handle, "uv_mutex_init");
    g_electronSymbolTable.uv_mutex_init_recursive = dlsym(handle, "uv_mutex_init_recursive");
    g_electronSymbolTable.uv_mutex_destroy = dlsym(handle, "uv_mutex_destroy");
    g_electronSymbolTable.uv_mutex_lock = dlsym(handle, "uv_mutex_lock");
    g_electronSymbolTable.uv_mutex_trylock = dlsym(handle, "uv_mutex_trylock");
    g_electronSymbolTable.uv_mutex_unlock = dlsym(handle, "uv_mutex_unlock");
    g_electronSymbolTable.uv_async_init = dlsym(handle, "uv_async_init");
    g_electronSymbolTable.uv_async_send = dlsym(handle, "uv_async_send");
}

// 下面是所有的包装函数实现
// 每个函数都遵循相同的模式：确保符号解析，然后调用真实函数

napi_status napi_get_last_error_info(napi_env env, const napi_extended_error_info** result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_last_error_info(env, result);
}

napi_status napi_get_undefined(napi_env env, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_undefined(env, result);
}

napi_status napi_get_null(napi_env env, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_null(env, result);
}

napi_status napi_get_global(napi_env env, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_global(env, result);
}

napi_status napi_get_boolean(napi_env env, bool value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_boolean(env, value, result);
}

napi_status napi_create_object(napi_env env, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_object(env, result);
}

napi_status napi_create_array(napi_env env, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_array(env, result);
}

napi_status napi_create_array_with_length(napi_env env, size_t length, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_array_with_length(env, length, result);
}

napi_status napi_create_double(napi_env env, double value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_double(env, value, result);
}

napi_status napi_create_int32(napi_env env, int32_t value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_int32(env, value, result);
}

napi_status napi_create_uint32(napi_env env, uint32_t value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_uint32(env, value, result);
}

napi_status napi_create_int64(napi_env env, int64_t value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_int64(env, value, result);
}

napi_status napi_create_string_latin1(napi_env env, const char* str, size_t length, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_string_latin1(env, str, length, result);
}

napi_status napi_create_string_utf8(napi_env env, const char* str, size_t length, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_string_utf8(env, str, length, result);
}

napi_status napi_create_string_utf16(napi_env env, const char16_t* str, size_t length, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_string_utf16(env, str, length, result);
}

napi_status node_api_create_external_string_latin1(napi_env env, char* str, size_t length, napi_finalize finalize_cb, void* finalize_hint, napi_value* result, bool* copied) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.node_api_create_external_string_latin1(env, str, length, finalize_cb, finalize_hint, result, copied);
}

napi_status node_api_create_external_string_utf16(napi_env env, char16_t* str, size_t length, napi_finalize finalize_cb, void* finalize_hint, napi_value* result, bool* copied) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.node_api_create_external_string_utf16(env, str, length, finalize_cb, finalize_hint, result, copied);
}

napi_status napi_create_symbol(napi_env env, napi_value description, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_symbol(env, description, result);
}

napi_status node_api_symbol_for(napi_env env, const char* utf8description, size_t length, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.node_api_symbol_for(env, utf8description, length, result);
}

napi_status napi_create_function(napi_env env, const char* utf8name, size_t length, napi_callback cb, void* data, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_function(env, utf8name, length, cb, data, result);
}

napi_status napi_create_error(napi_env env, napi_value code, napi_value msg, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_error(env, code, msg, result);
}

napi_status napi_create_type_error(napi_env env, napi_value code, napi_value msg, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_type_error(env, code, msg, result);
}

napi_status napi_create_range_error(napi_env env, napi_value code, napi_value msg, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_range_error(env, code, msg, result);
}

napi_status node_api_create_syntax_error(napi_env env, napi_value code, napi_value msg, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.node_api_create_syntax_error(env, code, msg, result);
}

napi_status napi_typeof(napi_env env, napi_value value, napi_valuetype* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_typeof(env, value, result);
}

napi_status napi_get_value_double(napi_env env, napi_value value, double* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_double(env, value, result);
}

napi_status napi_get_value_int32(napi_env env, napi_value value, int32_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_int32(env, value, result);
}

napi_status napi_get_value_uint32(napi_env env, napi_value value, uint32_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_uint32(env, value, result);
}

napi_status napi_get_value_int64(napi_env env, napi_value value, int64_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_int64(env, value, result);
}

napi_status napi_get_value_bool(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_bool(env, value, result);
}

napi_status napi_get_value_string_latin1(napi_env env, napi_value value, char* buf, size_t bufsize, size_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_string_latin1(env, value, buf, bufsize, result);
}

napi_status napi_get_value_string_utf8(napi_env env, napi_value value, char* buf, size_t bufsize, size_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_string_utf8(env, value, buf, bufsize, result);
}

napi_status napi_get_value_string_utf16(napi_env env, napi_value value, char16_t* buf, size_t bufsize, size_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_string_utf16(env, value, buf, bufsize, result);
}

napi_status napi_coerce_to_bool(napi_env env, napi_value value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_coerce_to_bool(env, value, result);
}

napi_status napi_coerce_to_number(napi_env env, napi_value value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_coerce_to_number(env, value, result);
}

napi_status napi_coerce_to_object(napi_env env, napi_value value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_coerce_to_object(env, value, result);
}

napi_status napi_coerce_to_string(napi_env env, napi_value value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_coerce_to_string(env, value, result);
}

napi_status napi_get_prototype(napi_env env, napi_value object, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_prototype(env, object, result);
}

napi_status napi_get_property_names(napi_env env, napi_value object, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_property_names(env, object, result);
}

napi_status napi_set_property(napi_env env, napi_value object, napi_value key, napi_value value) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_set_property(env, object, key, value);
}

napi_status napi_has_property(napi_env env, napi_value object, napi_value key, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_has_property(env, object, key, result);
}

napi_status napi_get_property(napi_env env, napi_value object, napi_value key, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_property(env, object, key, result);
}

napi_status napi_delete_property(napi_env env, napi_value object, napi_value key, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_delete_property(env, object, key, result);
}

napi_status napi_has_own_property(napi_env env, napi_value object, napi_value key, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_has_own_property(env, object, key, result);
}

napi_status napi_set_named_property(napi_env env, napi_value object, const char* utf8name, napi_value value) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_set_named_property(env, object, utf8name, value);
}

napi_status napi_has_named_property(napi_env env, napi_value object, const char* utf8name, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_has_named_property(env, object, utf8name, result);
}

napi_status napi_get_named_property(napi_env env, napi_value object, const char* utf8name, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_named_property(env, object, utf8name, result);
}

napi_status napi_set_element(napi_env env, napi_value object, uint32_t index, napi_value value) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_set_element(env, object, index, value);
}

napi_status napi_has_element(napi_env env, napi_value object, uint32_t index, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_has_element(env, object, index, result);
}

napi_status napi_get_element(napi_env env, napi_value object, uint32_t index, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_element(env, object, index, result);
}

napi_status napi_delete_element(napi_env env, napi_value object, uint32_t index, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_delete_element(env, object, index, result);
}

napi_status napi_define_properties(napi_env env, napi_value object, size_t property_count, const napi_property_descriptor* properties) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_define_properties(env, object, property_count, properties);
}

napi_status napi_is_array(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_array(env, value, result);
}

napi_status napi_get_array_length(napi_env env, napi_value value, uint32_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_array_length(env, value, result);
}

napi_status napi_strict_equals(napi_env env, napi_value lhs, napi_value rhs, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_strict_equals(env, lhs, rhs, result);
}

napi_status napi_call_function(napi_env env, napi_value recv, napi_value func, size_t argc, const napi_value* argv, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_call_function(env, recv, func, argc, argv, result);
}

napi_status napi_new_instance(napi_env env, napi_value constructor, size_t argc, const napi_value* argv, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_new_instance(env, constructor, argc, argv, result);
}

napi_status napi_instanceof(napi_env env, napi_value object, napi_value constructor, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_instanceof(env, object, constructor, result);
}

napi_status napi_get_cb_info(napi_env env, napi_callback_info cbinfo, size_t* argc, napi_value* argv, napi_value* this_arg, void** data) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_cb_info(env, cbinfo, argc, argv, this_arg, data);
}

napi_status napi_get_new_target(napi_env env, napi_callback_info cbinfo, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_new_target(env, cbinfo, result);
}

napi_status napi_define_class(napi_env env, const char* utf8name, size_t length, napi_callback constructor, void* data, size_t property_count, const napi_property_descriptor* properties, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_define_class(env, utf8name, length, constructor, data, property_count, properties, result);
}

napi_status napi_wrap(napi_env env, napi_value js_object, void* native_object, napi_finalize finalize_cb, void* finalize_hint, napi_ref* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_wrap(env, js_object, native_object, finalize_cb, finalize_hint, result);
}

napi_status napi_unwrap(napi_env env, napi_value js_object, void** result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_unwrap(env, js_object, result);
}

napi_status napi_remove_wrap(napi_env env, napi_value js_object, void** result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_remove_wrap(env, js_object, result);
}

napi_status napi_create_external(napi_env env, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_external(env, data, finalize_cb, finalize_hint, result);
}

napi_status napi_get_value_external(napi_env env, napi_value value, void** result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_external(env, value, result);
}

napi_status napi_create_reference(napi_env env, napi_value value, uint32_t initial_refcount, napi_ref* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_reference(env, value, initial_refcount, result);
}

napi_status napi_delete_reference(napi_env env, napi_ref ref) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_delete_reference(env, ref);
}

napi_status napi_reference_ref(napi_env env, napi_ref ref, uint32_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_reference_ref(env, ref, result);
}

napi_status napi_reference_unref(napi_env env, napi_ref ref, uint32_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_reference_unref(env, ref, result);
}

napi_status napi_get_reference_value(napi_env env, napi_ref ref, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_reference_value(env, ref, result);
}

napi_status napi_open_handle_scope(napi_env env, napi_handle_scope* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_open_handle_scope(env, result);
}

napi_status napi_close_handle_scope(napi_env env, napi_handle_scope scope) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_close_handle_scope(env, scope);
}

napi_status napi_open_escapable_handle_scope(napi_env env, napi_escapable_handle_scope* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_open_escapable_handle_scope(env, result);
}

napi_status napi_close_escapable_handle_scope(napi_env env, napi_escapable_handle_scope scope) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_close_escapable_handle_scope(env, scope);
}

napi_status napi_escape_handle(napi_env env, napi_escapable_handle_scope scope, napi_value escapee, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_escape_handle(env, scope, escapee, result);
}

napi_status napi_throw(napi_env env, napi_value error) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_throw(env, error);
}

napi_status napi_throw_error(napi_env env, const char* code, const char* msg) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_throw_error(env, code, msg);
}

napi_status napi_throw_type_error(napi_env env, const char* code, const char* msg) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_throw_type_error(env, code, msg);
}

napi_status napi_throw_range_error(napi_env env, const char* code, const char* msg) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_throw_range_error(env, code, msg);
}

napi_status node_api_throw_syntax_error(napi_env env, const char* code, const char* msg) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.node_api_throw_syntax_error(env, code, msg);
}

napi_status napi_is_error(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_error(env, value, result);
}

napi_status napi_is_exception_pending(napi_env env, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_exception_pending(env, result);
}

napi_status napi_get_and_clear_last_exception(napi_env env, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_and_clear_last_exception(env, result);
}

napi_status napi_is_arraybuffer(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_arraybuffer(env, value, result);
}

napi_status napi_create_arraybuffer(napi_env env, size_t byte_length, void** data, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_arraybuffer(env, byte_length, data, result);
}

napi_status napi_create_external_arraybuffer(napi_env env, void* external_data, size_t byte_length, napi_finalize finalize_cb, void* finalize_hint, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_external_arraybuffer(env, external_data, byte_length, finalize_cb, finalize_hint, result);
}

napi_status napi_get_arraybuffer_info(napi_env env, napi_value arraybuffer, void** data, size_t* byte_length) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_arraybuffer_info(env, arraybuffer, data, byte_length);
}

napi_status napi_detach_arraybuffer(napi_env env, napi_value arraybuffer) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_detach_arraybuffer(env, arraybuffer);
}

napi_status napi_is_detached_arraybuffer(napi_env env, napi_value arraybuffer, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_detached_arraybuffer(env, arraybuffer, result);
}

napi_status napi_is_typedarray(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_typedarray(env, value, result);
}

napi_status napi_create_typedarray(napi_env env, napi_typedarray_type type, size_t length, napi_value arraybuffer, size_t byte_offset, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_typedarray(env, type, length, arraybuffer, byte_offset, result);
}

napi_status napi_get_typedarray_info(napi_env env, napi_value typedarray, napi_typedarray_type* type, size_t* length, void** data, napi_value* arraybuffer, size_t* byte_offset) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_typedarray_info(env, typedarray, type, length, data, arraybuffer, byte_offset);
}

napi_status napi_create_dataview(napi_env env, size_t byte_length, napi_value arraybuffer, size_t byte_offset, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_dataview(env, byte_length, arraybuffer, byte_offset, result);
}

napi_status napi_is_dataview(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_dataview(env, value, result);
}

napi_status napi_get_dataview_info(napi_env env, napi_value dataview, size_t* bytelength, void** data, napi_value* arraybuffer, size_t* byte_offset) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_dataview_info(env, dataview, bytelength, data, arraybuffer, byte_offset);
}

napi_status napi_get_version(napi_env env, uint32_t* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_version(env, result);
}

napi_status napi_create_promise(napi_env env, napi_deferred* deferred, napi_value* promise) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_promise(env, deferred, promise);
}

napi_status napi_resolve_deferred(napi_env env, napi_deferred deferred, napi_value resolution) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_resolve_deferred(env, deferred, resolution);
}

napi_status napi_reject_deferred(napi_env env, napi_deferred deferred, napi_value rejection) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_reject_deferred(env, deferred, rejection);
}

napi_status napi_is_promise(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_promise(env, value, result);
}

napi_status napi_run_script(napi_env env, napi_value script, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_run_script(env, script, result);
}

napi_status napi_adjust_external_memory(napi_env env, int64_t change_in_bytes, int64_t* adjusted_value) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_adjust_external_memory(env, change_in_bytes, adjusted_value);
}

napi_status napi_create_date(napi_env env, double time, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_date(env, time, result);
}

napi_status napi_is_date(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_date(env, value, result);
}

napi_status napi_get_date_value(napi_env env, napi_value value, double* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_date_value(env, value, result);
}

napi_status napi_add_finalizer(napi_env env, napi_value js_object, void* finalize_data, napi_finalize finalize_cb, void* finalize_hint, napi_ref* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_add_finalizer(env, js_object, finalize_data, finalize_cb, finalize_hint, result);
}

napi_status node_api_post_finalizer(napi_env env, napi_finalize finalize_cb, void* finalize_data, void* finalize_hint) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.node_api_post_finalizer(env, finalize_cb, finalize_data, finalize_hint);
}

napi_status napi_create_bigint_int64(napi_env env, int64_t value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_bigint_int64(env, value, result);
}

napi_status napi_create_bigint_uint64(napi_env env, uint64_t value, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_bigint_uint64(env, value, result);
}

napi_status napi_create_bigint_words(napi_env env, int sign_bit, size_t word_count, const uint64_t* words, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_bigint_words(env, sign_bit, word_count, words, result);
}

napi_status napi_get_value_bigint_int64(napi_env env, napi_value value, int64_t* result, bool* lossless) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_bigint_int64(env, value, result, lossless);
}

napi_status napi_get_value_bigint_uint64(napi_env env, napi_value value, uint64_t* result, bool* lossless) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_bigint_uint64(env, value, result, lossless);
}

napi_status napi_get_value_bigint_words(napi_env env, napi_value value, int* sign_bit, size_t* word_count, uint64_t* words) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_value_bigint_words(env, value, sign_bit, word_count, words);
}

napi_status napi_get_all_property_names(napi_env env, napi_value object, napi_key_collection_mode key_mode, napi_key_filter key_filter, napi_key_conversion key_conversion, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_all_property_names(env, object, key_mode, key_filter, key_conversion, result);
}

napi_status napi_set_instance_data(napi_env env, void* data, napi_finalize finalize_cb, void* finalize_hint) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_set_instance_data(env, data, finalize_cb, finalize_hint);
}

napi_status napi_get_instance_data(napi_env env, void** result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_instance_data(env, result);
}

napi_status napi_type_tag_object(napi_env env, napi_value js_object, const napi_type_tag* type_tag) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_type_tag_object(env, js_object, type_tag);
}

napi_status napi_check_object_type_tag(napi_env env, napi_value js_object, const napi_type_tag* type_tag, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_check_object_type_tag(env, js_object, type_tag, result);
}

napi_status napi_object_freeze(napi_env env, napi_value object) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_object_freeze(env, object);
}

napi_status napi_object_seal(napi_env env, napi_value object) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_object_seal(env, object);
}

void napi_module_register(napi_module* mod) {
    ensure_electron_symbols_resolved();
    g_electronSymbolTable.napi_module_register(mod);
}

void napi_fatal_error(const char* location, size_t location_len, const char* message, size_t message_len) {
    ensure_electron_symbols_resolved();
    g_electronSymbolTable.napi_fatal_error(location, location_len, message, message_len);
    // This function should not return, but we add this for safety
    __builtin_unreachable();
}

napi_status napi_async_init(napi_env env, napi_value async_resource, napi_value async_resource_name, napi_async_context* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_async_init(env, async_resource, async_resource_name, result);
}

napi_status napi_async_destroy(napi_env env, napi_async_context async_context) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_async_destroy(env, async_context);
}

napi_status napi_make_callback(napi_env env, napi_async_context async_context, napi_value recv, napi_value func, size_t argc, const napi_value* argv, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_make_callback(env, async_context, recv, func, argc, argv, result);
}

napi_status napi_create_buffer(napi_env env, size_t length, void** data, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_buffer(env, length, data, result);
}

napi_status napi_create_external_buffer(napi_env env, size_t length, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_external_buffer(env, length, data, finalize_cb, finalize_hint, result);
}

napi_status napi_create_buffer_copy(napi_env env, size_t length, const void* data, void** result_data, napi_value* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_buffer_copy(env, length, data, result_data, result);
}

napi_status napi_is_buffer(napi_env env, napi_value value, bool* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_is_buffer(env, value, result);
}

napi_status napi_get_buffer_info(napi_env env, napi_value value, void** data, size_t* length) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_buffer_info(env, value, data, length);
}

napi_status napi_create_async_work(napi_env env, napi_value async_resource, napi_value async_resource_name, napi_async_execute_callback execute, napi_async_complete_callback complete, void* data, napi_async_work* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_async_work(env, async_resource, async_resource_name, execute, complete, data, result);
}

napi_status napi_delete_async_work(napi_env env, napi_async_work work) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_delete_async_work(env, work);
}

napi_status napi_queue_async_work(napi_env env, napi_async_work work) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_queue_async_work(env, work);
}

napi_status napi_cancel_async_work(napi_env env, napi_async_work work) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_cancel_async_work(env, work);
}

napi_status napi_get_node_version(napi_env env, const napi_node_version** version) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_node_version(env, version);
}

napi_status napi_get_uv_event_loop(napi_env env, struct uv_loop_s** loop) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_uv_event_loop(env, loop);
}

napi_status napi_fatal_exception(napi_env env, napi_value err) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_fatal_exception(env, err);
}

napi_status napi_add_env_cleanup_hook(napi_env env, void (*fun)(void* arg), void* arg) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_add_env_cleanup_hook(env, fun, arg);
}

napi_status napi_remove_env_cleanup_hook(napi_env env, void (*fun)(void* arg), void* arg) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_remove_env_cleanup_hook(env, fun, arg);
}

napi_status napi_open_callback_scope(napi_env env, napi_value resource_object, napi_async_context context, napi_callback_scope* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_open_callback_scope(env, resource_object, context, result);
}

napi_status napi_close_callback_scope(napi_env env, napi_callback_scope scope) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_close_callback_scope(env, scope);
}

napi_status napi_create_threadsafe_function(napi_env env, napi_value func, napi_value async_resource, napi_value async_resource_name, size_t max_queue_size, size_t initial_thread_count, void* thread_finalize_data, napi_finalize thread_finalize_cb, void* context, napi_threadsafe_function_call_js call_js_cb, napi_threadsafe_function* result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_create_threadsafe_function(env, func, async_resource, async_resource_name, max_queue_size, initial_thread_count, thread_finalize_data, thread_finalize_cb, context, call_js_cb, result);
}

napi_status napi_get_threadsafe_function_context(napi_threadsafe_function func, void** result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_get_threadsafe_function_context(func, result);
}

napi_status napi_call_threadsafe_function(napi_threadsafe_function func, void* data, napi_threadsafe_function_call_mode is_blocking) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_call_threadsafe_function(func, data, is_blocking);
}

napi_status napi_acquire_threadsafe_function(napi_threadsafe_function func) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_acquire_threadsafe_function(func);
}

napi_status napi_release_threadsafe_function(napi_threadsafe_function func, napi_threadsafe_function_release_mode mode) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_release_threadsafe_function(func, mode);
}

napi_status napi_unref_threadsafe_function(napi_env env, napi_threadsafe_function func) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_unref_threadsafe_function(env, func);
}

napi_status napi_ref_threadsafe_function(napi_env env, napi_threadsafe_function func) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_ref_threadsafe_function(env, func);
}

napi_status napi_add_async_cleanup_hook(napi_env env, napi_async_cleanup_hook hook, void* arg, napi_async_cleanup_hook_handle* remove_handle) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_add_async_cleanup_hook(env, hook, arg, remove_handle);
}

napi_status napi_remove_async_cleanup_hook(napi_async_cleanup_hook_handle remove_handle) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.napi_remove_async_cleanup_hook(remove_handle);
}

napi_status node_api_get_module_file_name(napi_env env, const char** result) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.node_api_get_module_file_name(env, result);
}

// libuv 包装函数
void uv_close(void* handle, void* close_cb) {
    ensure_electron_symbols_resolved();
    g_electronSymbolTable.uv_close(handle, close_cb);
}

int uv_mutex_init(void* handle) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.uv_mutex_init(handle);
}

int uv_mutex_init_recursive(void* handle) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.uv_mutex_init_recursive(handle);
}

void uv_mutex_destroy(void* handle) {
    ensure_electron_symbols_resolved();
    g_electronSymbolTable.uv_mutex_destroy(handle);
}

void uv_mutex_lock(void* handle) {
    ensure_electron_symbols_resolved();
    g_electronSymbolTable.uv_mutex_lock(handle);
}

int uv_mutex_trylock(void* handle) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.uv_mutex_trylock(handle);
}

void uv_mutex_unlock(void* handle) {
    ensure_electron_symbols_resolved();
    g_electronSymbolTable.uv_mutex_unlock(handle);
}

int uv_async_init(void* loop, void* async, void* async_cb) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.uv_async_init(loop, async, async_cb);
}

int uv_async_send(void* async) {
    ensure_electron_symbols_resolved();
    return g_electronSymbolTable.uv_async_send(async);
}

// 完整版本 - 所有函数都已实现
