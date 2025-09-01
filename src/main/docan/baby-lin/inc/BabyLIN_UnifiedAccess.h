#ifndef BABYLIN_UNIFIEDACCESS_H
#define BABYLIN_UNIFIEDACCESS_H

/**
 * @addtogroup ua Unified Access
 * @brief In the Unified Access interface the available features and values are structured in a tree
 * of objects.
 *
 * @details
 * Every object may have children, properties and methods, that are accessible through the __path__
 * parameter of the functions. The children, properties and methods are identified by __tags__.
 * Those tags are handle specific and described in this document. Additionally they can be listed by
 * calling @ref BLC_discover with the handle you are interested in.
 *
 * ### Creation of new Objects
 *  To add a new Object into the tree use the @ref BLC_createHandle function. To create a new object
 * a using __key value pairs__ ("<key>=<value>") is required. In a path each key value pair has to
 * be separated by one space character. Tags valid for the creation keys can be taken from the
 * "Creat tags" tables of the Objects documented in this document. The value is specifying the name
 * property of the new child. Additionally key value pairs with property tags can be appended, to
 * set properties during the object creation, so that less calls to the Setters are required
 * afterwards. e.g. creating a @ref ua_protocol_iso_tp in a @ref ua_channel with the name "my_dtl" :
 * ~~~.c
 * BL_HANDLE protocol_handle;
 * BLC_createHandle(channel_handle, "new_iso_tp_protocol=my_dtl",
 * &protocol_handle);
 * ~~~
 *
 * ### Handles of existing Objects
 *  To find an existing Object in the tree use the @ref BLC_createHandle function. Navigating the
 * tree is done by constructing a path by using __key value pairs__ ("<key>=<value>"). Tags valid
 * for the keys can be taken from the "Child tags" tables of the Objects documented in this
 * document. In a path each key value pair has to be separated by one space character. e.g. getting
 * the handle to the previously created @ref ua_protocol_iso_tp of that @ref ua_channel :
 * ~~~.c
 * BL_HANDLE protocol_handle;
 * BLC_createHandle(channel_handle, "protocol=my_dtl", &protocol_handle);
 * ~~~
 *
 * ### Getters
 *  To read values of properties use @ref BLC_getSignedNumber, @ref BLC_getUnsignedNumber or @ref
 * BLC_getBinary functions. The __path__ parameter has to end with the tag identifying the property
 * to read. Valid tags can be taken from the "Property tags" tables of the Objects documented in
 * this document. e.g. reading the requestFrameID from a @ref ua_service_iso_tp :
 * ~~~.c
 * uint64_t requestFrameID;
 * BLC_getUnsignedNumber(service_handle, "req_frame_id", &requestFrameID);
 * ~~~
 *
 * ### Setters
 *  To store values of properties use @ref BLC_setSignedNumber, @ref BLC_setUnsignedNumber, @ref
 * BLC_setBinary or @ref BLC_setCallback functions. The __path__ parameter has to end with the tag
 * identifying the property to store. Valid tags can be taken from the "Property tags" tables of the
 * Objects documented in this document. e.g. setting the requestFrameID of a @ref ua_service_iso_tp
 * to 59 :
 * ~~~.c
 * BLC_setUnsignedNumber(service_handle, "req_frame_id", 59);
 * ~~~
 *
 * ### Execution of Methods
 *  To execute an object's method use @ref BLC_execute or @ref BLC_execute_async functions. In the
 * path variable only the identifying tag is required. Valid tags can be taken from the "Method
 * tags" tables of the Objects documented in this document. Functions might have parameters. Those
 * can be specified by appending key value pairs to the path in the same manner as when creating new
 * objects. The order of the parameters is not relevant. In some cases a synchronous call is not
 * applicable, in these cases use @ref BLC_execute_async to execute the method in a dedicated
 * thread. e.g. executing a @ref ua_service_iso_tp :
 * ~~~.c
 * BLC_execute(service_handle, "execute");
 * ~~~
 * @{
 */

#include "BabyLINCAN.h"

#if defined(__cplusplus)
#include <cstddef>
#include <cstdint>
extern "C" {
#else
#include <stddef.h>
#include <stdint.h>
#endif

/**
 * @brief The function prototype used for registering callbacks.
 *
 * The handle is the handle to the Object, that triggered the callback.<br/> The userdata pointer is
 * the userdata specified when registering the callback.
 *
 * The device, that generated the callback must not be closed from within the callback.
 */
typedef void (*BLC_unifiedaccess_callback_func_ptr)(BL_HANDLE handle, void* userdata);
/**
 * @brief The function prototype used for executing asynchron tasks.
 *
 * The result value is the value returned by the actual execute call.<br/> The handle is the handle
 * to the Object, that triggered the callback.<br/> The userdata pointer is the userdata specified
 * when registering the callback.<br/>
 */
typedef void (*BLC_unifiedaccess_async_callback_func_ptr)(int32_t result,
                                                          BL_HANDLE handle,
                                                          void* userdata);

/**
 * @brief BLC_createHandle retrieves a handle to a loaded Object or creates a new Object.
 *
 *  These Objects can range from Devices and SDFs down to Signals.<br> When retrieving a handle to
 * an existing item the path has to end with a key value pair, where the key is a tag of the objects
 * children list. When creating a new Object the "new_*=*" key value pair can be followed by key
 * value pairs from the new objects property list, to initialize them.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from key value pairs, separated by spaces e.g.
 *                  "protocol=1 service=2".
 * @param result    Value to store the new handle in.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 * BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the corresponding
 * key-value-pair in the path parameter could not be resolved correctly.<br> If the returned value
 * is between @ref BLC_UA_REQUESTED_OBJECT_NOT_FOUND_FIRST and @ref
 * BLC_UA_REQUESTED_OBJECT_NOT_FOUND_MAX the corresponding key-value-pair in the path parameter
 * tries to access a non existing Object.<br> If @ref BLC_UA_GET_VALUE_REJECTED is returned the
 * requested Object was found but handles to this type of Object can not be created.<br> In case of
 * Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_createHandle(BL_HANDLE handle, const char* path, BL_HANDLE* result);

/**
 * @brief BLC_destroy removes the handle from the currently opened Objects and removes the Object
 * from its parent.
 *
 *  The given handle will be removed from the available handles and the Object behind it will be
 * destroyed.
 * @param handle    The handle of the object to destroy.
 * @return          @ref BL_OK if no error occurred. In case of Error refer to the @ref
 *                  BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_destroy(BL_HANDLE handle);

/**
 * @brief BLC_releaseHandle removes the handle from the currently opened Objects.
 *
 *  The given handle will be release, but a new handle to the underling object can be retrieved
 * again.
 * @param handle    The handle to release.
 * @return          @ref BL_OK if no error occurred. In case of Error refer to the @ref
 *                  BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_releaseHandle(BL_HANDLE handle);

/**
 * @brief BLC_discover fills the result array with space separated identifiers, that can be used in
 * the path parameters.
 *
 *  Lists the available __Tags__ of the object separated by spaces.
 * @param handle    the handle to start the query from.
 * @param path      the query, it is a cstring build from entries of tags ending with either
 * "property","child", "create", "execute" or "all".<br> "property" will list all __Tags__ usable in
 * BLC_get...() and or BLC_set...().<br> "child" will list all __Tags__ usable in BLC_createHandle
 * for already existing objects.<br> "create"  will list all __Tags__ usable in BLC_createHandle for
 * creating new objects.<br> "execute"  will list all __Tags__ usable in BLC_execute and
 * BLC_execute_async.<br> "all" will list all __Tags__ in the form of "property:=<tags
 * >\nchild:=<tags >\ncreate:=<tags >\nexecute:=<tags>".
 * @param result    The buffer to fill, if a null pointer is provided here only the result_length
 *                  will be filled.
 * @param result_length Is a pointer to the length of the buffer, that will be set to the length of
 *                  the result data.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_discover(BL_HANDLE handle,
                                  const char* path,
                                  uint8_t* result,
                                  uint32_t* result_length);

/**
 * @brief BLC_getSignedNumber gets a signed value from the given handle.
 *
 *  The path will be followed and the last __Tag__ has to identify a Number or Boolean property. If
 * that property is signed and has less then 64 bits sign extension will be applied, so negative
 * values stay negative.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from entries of tags.
 * @param result    The target value.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and  @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_getSignedNumber(BL_HANDLE handle, const char* path, int64_t* result);

/**
 * @brief BLC_getUnsignedNumber gets a unsigned value from the given handle.
 *
 *  The path will be followed and the last __Tag__ has to identify a Number or Boolean property. If
 * that property is signed no sign extension will be applied, so 8 bit -1 will be 255.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from entries of tags.
 * @param result    The target value.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_getUnsignedNumber(BL_HANDLE handle, const char* path, uint64_t* result);

/**
 * @brief BLC_getBinary gets a binary value from the given handle.
 *
 *  The path will be followed and the last __Tag__ has to identify a property. A only Number or only
 * Boolean property will be read as a string representation of it.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from entries of tags.
 * @param result    The buffer to fill, if a null pointer is provided here only the result_length
 *                  will be filled.
 * @param result_length Is a pointer to the length of the buffer, this parameter will be set to the
 *                  length of the result data. If the result buffer is too small no data will be
 *                  copied and only result_length will be updated.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_getBinary(BL_HANDLE handle,
                                   const char* path,
                                   uint8_t* result,
                                   uint32_t* result_length);

/**
 * @brief BLC_setSignedNumber sets a signed value of the given handle.
 *
 * The path will be followed and the last __Tag__ has to identify a Number or Boolean property. If
 * that property is too small to represent the value the set is rejected.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from entries of tags.
 * @param value     The value to set.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and  @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_setSignedNumber(BL_HANDLE handle, const char* path, int64_t value);

/**
 * @brief BLC_setUnsignedNumber sets an unsigned value of the given handle.
 *
 * The path will be followed and the last __Tag__ has to identify a Number or Boolean property. If
 * that property is too small to represent the value the set is rejected.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from entries of tags.
 * @param value     The value to set.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_setUnsignedNumber(BL_HANDLE handle, const char* path, uint64_t value);

/**
 * @brief BLC_setBinary sets a binary value of the given handle.
 *
 *  The path will be followed and the last __Tag__ has to identify a property. For a only Number or
 * only Boolean property the given value will be parsed as a string, that is then handed to @ref
 * BLC_setUnsignedNumber or @ref BLC_setSignedNumber.
 * @param handle        The handle to start the query from.
 * @param path          The query, it is a cstring build from entries of tags.
 * @param value         The value to set.
 * @param value_length  The length of the value to set.
 * @return              @ref BL_OK if no error occurred. If the returned value is between @ref
 *                      BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                      corresponding key-value-pair in the path parameter could not be resolved
 *                      correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_setBinary(BL_HANDLE handle,
                                   const char* path,
                                   const uint8_t* value,
                                   uint32_t value_length);

/**
 * @brief BLC_setCallback sets a callback function for an event of the given handle.
 *
 *  The path will be followed and the last __Tag__ has to identify a Callback property. Only one
 * callback can be registered per event per object.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from entries of tags.
 * @param callback  The callback to set, use a null pointer to deactivate the callback.
 * @param userdata  The parameter to call the callback with.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_setCallback(BL_HANDLE handle,
                                     const char* path,
                                     BLC_unifiedaccess_callback_func_ptr callback,
                                     void* userdata);

/**
 * @brief BLC_execute executes a method of the given handle.
 *
 *  The path will be followed and a __Tag__ that identifies a Method property, followed by the
 * __Tags__ to set additional parameters of that method. The Method will be executed in a blocking
 * manner.
 * @param handle    the handle to start the query from.
 * @param path      the query, it is a cstring build from entries of tags.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_execute(BL_HANDLE handle, const char* path);

/**
 * @brief BLC_execute_async a method of the given handle.
 *
 *  The path will be followed and a __Tag__ that identifies a Method property, followed by the
 * __Tags__ to set additional parameters of that method. The Method will be executed in a non
 * blocking manner, so the returned value does not state anything about whether the operation was
 * successful, or not, but only if it was found or not. To get the result value you would get from
 * @ref BLC_execute use the first parameter of the @ref BLC_unifiedaccess_async_callback_func_ptr.
 * @param handle    The handle to start the query from.
 * @param path      The query, it is a cstring build from entries of tags.
 * @param callback  The callback to call once the operation is complete.
 * @param userdata  The additional parameter to call the callback with.
 * @return          @ref BL_OK if no error occurred. If the returned value is between @ref
 *                  BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX the
 *                  corresponding key-value-pair in the path parameter could not be resolved
 *                  correctly. In case of Error refer to the @ref BabyLINReturncodes.h file.
 */
int32_t BL_DLLIMPORT BLC_execute_async(BL_HANDLE handle,
                                       const char* path,
                                       BLC_unifiedaccess_async_callback_func_ptr callback,
                                       void* userdata);

#if defined(__cplusplus)
}
#endif
/**
 * @}
 */
#endif  // BABYLIN_UNIFIEDACCESS_H
