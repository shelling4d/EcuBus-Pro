#ifndef BABYLIN_H
#define BABYLIN_H

#include "BabyLINCAN_types.h"

#if defined(__cplusplus)
#include <cstddef>  // get "size_t", used by function BL_encodeSignal())
#include <cstdint>
extern "C" {
#else
#include <stddef.h>  // get "size_t", used by function BL_encodeSignal())
#include <stdint.h>
#endif

/** @brief Registers a callback function, which is called on every reception of a (monitored) jumbo
 * frame.
 *
 * @deprecated Use @ref BLC_registerUserDataJumboFrameCallback instead
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called from another
 * thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel id which the frame occurred
 * @param[in] callback  Pointer to a function call-compatible to  @ref BLC_jumboframe_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerJumboFrameCallback(BL_HANDLE handle,
                                                BLC_jumboframe_callback_func* callback);

/** @brief Registers a callback function, which is called on every reception of a (monitored) frame.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel id which the frame occurred
 * @param[in] callback  Pointer to a function call-compatible to  @ref BLC_frame_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerFrameCallback(BL_HANDLE handle, BLC_frame_callback_func* callback);

/** @brief Registers a callback function, which is called on every reception of a monitored signal.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel on which the signal occurred;
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_signal_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerSignalCallback(BL_HANDLE handle, BLC_signal_callback_func* callback);

/** @brief Registers a callback function, which is called on every reception of an error message
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_error_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerErrorCallback(BL_HANDLE handle, BLC_error_callback_func* callback);

/** @brief Registers a callback function, which is called whenever the execution
 * state of a macro changes
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_macrostate_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerMacroStateCallback(BL_HANDLE handle,
                                                BLC_macrostate_callback_func* callback);

/** @brief Registers a callback function, which is called whenever a debug message from a
 * BabyLIN-Device is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_debug_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerDebugCallback(BL_HANDLE handle, BLC_debug_callback_func* callback);

/** @brief Registers a callback function, which is called whenever dtl request is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref
 *                      BLC_dtl_request_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerDTLRequestCallback(BL_HANDLE handle,
                                                BLC_dtl_request_callback_func* callback);

/** @brief Registers a callback function, which is called whenever dtl response is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref
 *                      BLC_dtl_response_callback_func.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise.
 *                      See standard return values for error, or for textual representation (for
 *                      return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerDTLResponseCallback(BL_HANDLE handle,
                                                 BLC_dtl_response_callback_func* callback);

/** @brief Registers a callback function, which is called on every reception of
 * a (monitored) jumbo frame.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel id which the frame occurred
 * @param[in] callback  Pointer to a function call-compatible to @ref
 *                      BLC_jumboframe_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref
 *                      BLC_jumboframe_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataJumboFrameCallback(BL_HANDLE handle,
                                                        BLC_jumboframe_callback_func_ptr* callback,
                                                        void* userdata);

/** @brief Registers a callback function, which is called on every reception of
 * a (monitored) frame.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel id which the frame occurred
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_frame_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_frame_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataFrameCallback(BL_HANDLE handle,
                                                   BLC_frame_callback_func_ptr* callback,
                                                   void* userdata);

/** @brief Registers a callback function, which is called on every reception of an event report.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel id which the event occurred
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_event_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_event_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataEvent(BL_HANDLE handle,
                                           BLC_event_callback_func_ptr* callback,
                                           void* userdata);

/** @brief Alias for BLC_registerUserDataEvent
 */
int BL_DLLIMPORT BLC_registerUserDataEventCallback(BL_HANDLE handle,
                                                   BLC_event_callback_func_ptr* callback,
                                                   void* userdata);

/** @brief Alias for BLC_registerUserDataEvent without user data
 */
int BL_DLLIMPORT BLC_registerEventCallback(BL_HANDLE handle, BLC_event_callback_func* callback);

/** @brief Registers a callback function, which is called on every reception of a monitored signal.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel on which the signal occurred;
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_signal_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_signal_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataSignalCallback(BL_HANDLE handle,
                                                    BLC_signal_callback_func_ptr* callback,
                                                    void* userdata);

/** @brief Registers a callback function, which is called on every reception of an error message
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_error_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataErrorCallback(BL_HANDLE handle,
                                                   BLC_error_callback_func_ptr* callback,
                                                   void* userdata);
/** @brief Registers a callback function, which is called whenever the execution state of a macro
 * changes
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref
 *                      BLC_macrostate_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataMacroStateCallback(BL_HANDLE handle,
                                                        BLC_macrostate_callback_func_ptr* callback,
                                                        void* userdata);
/** @brief Registers a callback function, which is called whenever a debug message from a
 * BabyLIN-Device is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref BLC_debug_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataDebugCallback(BL_HANDLE handle,
                                                   BLC_debug_callback_func_ptr* callback,
                                                   void* userdata);
/** @brief Registers a callback function, which is called whenever dtl request is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref
 *                      BLC_dtl_request_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataDTLRequestCallback(BL_HANDLE handle,
                                                        BLC_dtl_request_callback_func_ptr* callback,
                                                        void* userdata);
/** @brief Registers a callback function, which is called whenever dtl response is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param[in] handle    Handle representing the channel emitting the error; returned previously by
 * @param[in] callback  Pointer to a function call-compatible to @ref
 *                      BLC_dtl_request_callback_func_ptr.
 * @param[in] userdata  Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataDTLResponseCallback(BL_HANDLE handle,
                                                         BLC_dtl_response_callback_func_ptr* callback,
                                                         void* userdata);

/**
 * @brief Registers a callback that will be called when the lua "print" function is called.
 *
 *Registers a callback that will be called when the lua "print" function is called.
 *@param[in] handle   The connection for the callback
 *@param[in] func     The function to be called as callback.
 *@param[in] userdata Any user supplied data, which will be available in the callback (e.g as
 *                    connection or channel handle)
 */
int BL_DLLIMPORT BLC_registerLuaPrintCallback(BL_HANDLE handle,
                                              BLC_lua_print_func_ptr* func,
                                              void* userdata);
/**
 * @brief Registers a callback that will be called on any LUA engine error. You can register this
 *callback to debug your script SDFs.
 *
 *Registers a callback that will be called on any LUA engine error. You can register this callback
 *to debug your script SDFs.
 *@param[in] handle   The connection for the callback
 *@param[in] func     The function to be called as callback.
 *@param[in] userdata Any user supplied data, which will be available in the callback (e.g as
 *                    connection or channel handle)
 */
int BL_DLLIMPORT BLC_registerLuaErrorCallback(BL_HANDLE handle,
                                              BLC_lua_print_func_ptr* func,
                                              void* userdata);

/** @brief Registers a callback function, which is called whenever a log message is received
 *
 * Issuing a NULL-pointer de-registers the callback function. Since the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * @param handle    Handle representing the channel the callback for logs must be registered to
 * @param callback  Pointer to a function call-compatible to @ref BLC_log_callback_func_ptr.
 * @param userdata  Pointer to custom user data to pass to @ref BLC_log_callback_func_ptr.
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000)
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataLogCallback(BL_HANDLE handle,
                                                 BLC_log_callback_func_ptr* callback,
                                                 void* userdata);

/** @}*/

////////////////////////////////////////////////////////////////////////////////
/** @}*/

/** @addtogroup connection_handling Connection Handling
 *  @brief List of BabyLIN connection handling and device information functions
 *
 *  The following functions are used to setup a connection to a BabyLIN device.
 *  @{
 */

/** @brief Get the major and minor version number of the library
 *
 *  @deprecated Use @ref BLC_getExtendedVersion instead
 *
 *  This function retrieves the version in the given parameter variables of the library.
 *  @param[out] major     Major part of version number.
 *  @param[out] minor     Minor part of version number.
 */
void BL_DLLIMPORT BLC_getVersion(int* major, int* minor);

/** @brief Get the major, minor and patch version number of the library
 *
 *  This function retrieves the version in the given parameter variables of the library.
 *  @param[out] major     Major part of version number.
 *  @param[out] minor     Minor part of version number.
 *  @param[out] patch     Patch part of version number.
 *  @param[out] buildrev  Build revision of version number.
 */
void BL_DLLIMPORT BLC_getExtendedVersion(int* major, int* minor, int* patch, int* buildrev);

/** @brief Get the version string of the library
 *
 *  This function returns the version string of the library.
 *  @return         Returns a C-string with the version information.
 */
CPCHAR BL_DLLIMPORT BLC_getVersionString(void);

/** @brief Retrieve a list of ports a BabyLIN is connected to
 *
 * The function doesn't try to connect to the found Ports wraps @ref BLC_getBabyLinPortsTimout with
 timout value set to 0ms. This function will not find any network-devices.
 *
 * @param[out] portListToBeFilled Preallocated array to be filled
 * @param[in,out] pFoundPortCount Input the size of the allocated array. Output the filled size of
 *                                the array.
 * @return                        The number of connected BabyLINs found (>=0) or < 0 on error
 *
 *
 * example: @code{.c}
 *          BLC_PORTINFO ports[2];
            int maxPortCount = 2;
 *          int foundCount = BLC_getBabyLinPorts(ports, &maxPortCount);
            int foundEmpty = BLC_getBabyLinPorts(NULL, NULL);
            // if there were 3 BabyLin connected to usb:
            // foundCount == 2
            // foundEmpty == 3

            //if there is only 1 Babylin connected:
            foundCount = BLC_getBabyLinPorts(ports, &maxPortCount);
            foundEmpty = BLC_getBabyLinPorts(NULL, NULL);
            //foundEmpty == 1;
            //foundCount == 1;
            @endcode
 *
 */
int BL_DLLIMPORT BLC_getBabyLinPorts(BLC_PORTINFO portListToBeFilled[], int* pFoundPortCount);

/** @brief Retrieve a list of ports a BabyLIN is connected to
 *
 * The function doesn't try to connect to the found Ports. You can not connect to UDP network
 * devices they are only listed FYI and have to be configured in SimpleMenu mode first. Network
 * devices of type TCP will have the default Port configured(2048) for connection. If the Device's
 * simplemenu-tcp-com-port configuration value was changed. you will have to change the
 * BLC_PORTINFO.port prior to connecting via BLC_openPort(...).
 * @param[out] portListToBeFilled Array to be filled
 * @param[in,out] pFoundPortCount Input the size of the allocated array. Output the filled size of
 *                                the array.
 * @param timoutms                A timeout value in ms to wait for replies of network devices. If
 *                                timoutms is set to <= 0 this Function will not find/look for any
 *                                Network devices.
 * @return                        The number of connected BabyLINs found (>=0) or < 0 on error
 */
int BL_DLLIMPORT BLC_getBabyLinPortsTimout(BLC_PORTINFO portListToBeFilled[],
                                           int* pFoundPortCount,
                                           int timoutms);

/** @brief Open a connection to a BabyLIN USB-Serial device.
 *
 *  This function tries to open the designated port and to start communication with the device.
 *  @param port The port, the BabyLIN is connected to. It uses Windows-style numbering, which means
 *              it starts with '1' for the first serial port. '0' is reserved. On linux systems, the
 *              port is represented by the path to the device file ("/dev/ttyUSB0" f.ex.)
 *  @return     Returns an handle for the BabyLIN-connection or NULL if the connection could not be
 *              established. You may fetch the corresponding (textual) error with @ref
 *              BLC_getLastError.
 * @deprecated use @ref BLC_openPort() together with @ref BLC_convertUrl() or @ref
 * BLC_getBabyLinPorts()
 */
#if defined(_WIN32)
BL_HANDLE BL_DLLIMPORT BLC_open(unsigned int port);
#else
BL_HANDLE BL_DLLIMPORT BLC_open(const char* port);
#endif

/** @brief Open a connection to a BabyLIN device using ethernet.
 *
 *  This function tries to open the designated ip and port and to start communication with the
 * device.
 *  @param[in] ip The ip-address of the BabyLIN to connect to
 *  @param port   The ip-port of the BabyLIN toconnected to
 *  @return       Returns an handle for the BabyLIN-connection or NULL if the connection could not
 *                be established. You may fetch the corresponding (textual) error with @ref
 *                BLC_getLastError.
 * @deprecated use @ref BLC_openPort() together with @ref BLC_convertUrl() or @ref
 * BLC_getBabyLinPorts()
 */
BL_HANDLE BL_DLLIMPORT BLC_openNet(const char* ip, int port);

/** @brief Open a connection to a BabyLIN USB device.
 *
 *  This function tries to open the designated port and to start communication with the device.
 *  @param[in] device The usb device string, the BabyLIN is connected to.
 *  @return           Returns an handle for the BabyLIN-connection or NULL if the connection could
 *                    not be established. You may fetch the corresponding (textual) error with @ref
 *                    BLC_getLastError.
 * @deprecated use @ref BLC_openPort() together with @ref BLC_convertUrl()
 */
BL_HANDLE BL_DLLIMPORT BLC_openUSB(const char* device);

/** @brief Open a connection to a BabyLIN device using @ref BLC_PORTINFO information.
 *
 *  This function tries to open the BabyLIN device of the @ref BLC_PORTINFO information, i.e. works
 * as a wrapper for @ref BLC_open and @ref BLC_openNet which automatically decides which connection
 * to establish.
 *
 * @note Platform independent way of connecting to BabyLIN-devices found by @ref BLC_getBabyLinPorts
 * or @ref BLC_getBabyLinPortsTimout
 *
 *  @param portInfo The @ref BLC_PORTINFO-structure of the BabyLIN to connect to ( see @ref
 *                  BLC_getBabyLinPorts )
 *  @return         Returns an handle for the BabyLIN-connection or NULL if the connection could not
 *                  be established. You may fetch the corresponding (textual) error with @ref
 *                  BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT BLC_openPort(BLC_PORTINFO portInfo);

/** @brief convert a device url to @ref BLC_PORTINFO to use in @ref BLC_openPort
 *
 * this function tries to convert a given url to a complete struct of type @ref BLC_PORTINFO.
 *
 * The device url defines the device and protocol:
 * serial://1 Opens a USB connection on Windows using the BabyLIN library protocol.
 * serial:///dev/ttyUSB1 Opens a USB connection on Linux using the BabyLIN library protocol.
 * tcp://127.0.0.1:2048 Opens a network connection to a Baby-LIN-MB-II using the BabyLIN library
 * protocol of the SimpleMenu mode. ascii://127.0.0.1:10003 Opens a network connection to a
 * Baby-LIN-MB-II using the ASCII protocol of the StandAlone mode.
 * 
 * Note: While using only a port number does work under Linux, it is not recommended to use it.
 *       It will only work for old devices that are listed as "ttyUSB" devices. Newer devices
 *       will be listed as "ttyACM" and will require the full path to the device, as it is
 *       ambiguous which device is meant otherwise.
 *
 * @param[in] url       The device url to convert might be a system path (serial:///dev/ttyUSB1) for
 *                      unix based systems, a comport number (serial://1) as is used for windows or
 *                      a network address (tcp://127.0.0.1:2048) to connect to a network device. The
 *                      ASCII protocol of Baby-LIN-MB-II is supported as well
 *                      (ascii://127.0.0.1:10003). Additionally, there exist a special shortcut for
 *                      serial:://1 resp. serial:///dev/ttyUSB1 consisting of the single port number
 *                      [COM]1. Thus, if an integer is given as a port number (started by an
 *                      optional COM, e.g. COM1), then the protocol is set to BabyLIN library
 *                      protocol (serial).
 * @param[out] portInfo The @ref BLC_PORTINFO struct to fill.
 * @return              @ref BL_OK on success, error code otherwise (in case of error, the
 *                      @ref BLC_PORTINFO structure is left untouched)
 */
int BL_DLLIMPORT BLC_convertUrl(const char* url, BLC_PORTINFO* portInfo);

/** @brief Close connection to Device.
 *
 * close an open connection, given by handle.
 * @param[in] handle  Handle representing the connection ( see @ref BLC_open )
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_close(BL_HANDLE handle);

/** @brief Close ALL connections to ALL Devices.
 *
 *  Close all open connections; all handles are invalidated.
 *  @return Status of operation; '=0' means successful, '!=0' otherwise. See standard return values
 *          for error, or for textual representation @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_closeAll(void);

/** @brief Reset the BabyLIN device to an consistent and deactivated state.
 *
 * Afterwards, the device will no longer monitor the bus, neither acting as slave  nor as master.
 * @param[in] handle  Handle representing a channel; returned previously by @ref
 *                    BLC_getChannelHandle().
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_flush(BL_HANDLE handle);

/** @brief Requests the information about the target
 *
 *  @param[in] handle     Handle representing the connection (see @ref BLC_open )
 *  @param[out] targetID  Pointer to pre-allocated @ref BLC_TARGETID structure to hold the
 *                        information after the successful call
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getTargetID(BL_HANDLE handle, BLC_TARGETID* targetID);

/** @brief Returns the unique hardware type identifier for a device
 *
 *  @param[in] handle   Handle representing the connection ( see @ref BLC_open ) The hardware type
 * or BabyLIN-error return code. See (@ref BLC_TARGETID.type) for hardware types. See standard
 * return values for error, or for textual representation (for return values < -1000) @ref
 * BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getHWType(BL_HANDLE handle);

/** @brief number of channels provided by the BabyLIN-Device
 *
 *  @param[in] handle Handle representing the connection (see @ref BLC_open)
 *  @return           Number of channels >= 0 or < 0 on error. See standard return values for error,
 *                    or for textual representation (for return values < -1000) @ref
 *                    BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getChannelCount(BL_HANDLE handle);

/** @brief Retrieve a handle to the specified channel
 *
 *  This function returns a channel-handle for the specified channelId. A channel-handle is used to
 * control a LIN- or CAN-BUS on the BabyLIN-device.
 *
 *  @param[in] handle Handle representing the Device connection ( see @ref BLC_open )
 *  @param channelId  Identifier for the channel to get the handle of. Ranges from 0 to the number
 *                    of channels supported by the device (see @ref BLC_getChannelCount)
 *  @return           Handle to the channel, 0 on error. You may fetch the corresponding (textual)
 *                    with @ref BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT BLC_getChannelHandle(BL_HANDLE handle, int channelId);

/** @brief Retrieve informations about the Channel
 *
 * @param[in] handle  Channelhandle representing the Channel. (see @ref BLC_getChannelHandle)
 * @param[out] pinfo  Pointer to pre-allocated @ref BLC_CHANNELINFO structure to hold the
 *                    information after the successful call
 * @return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getChannelInfo(BL_HANDLE handle, BLC_CHANNELINFO* pinfo);

/** @brief Returns a C-string with the textual representation of the last error.
 *
 *  Get a textual error message for Errorcodes < -1000.
 *
 * @deprecated use @ref BLC_getDetailedErrorString() instead
 *
 *  @param[in] handle         Handle to the erroneous connection or channel.
 *  @param[out] pErrorBuffer  Pointer to allocated memory buffer to store error message
 *  @param bufferLength       Allocated length of pErrorBuffer
 *  @return                   Status of operation; '=0' means successful, '!=0' otherwise. See
 *                            standard return values for error, or for textual representation (for
 *                            return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getLastError(BL_HANDLE handle, char* pErrorBuffer, int bufferLength);

/** @brief Returns a C-string with the textual representation of an error code
 *
 *  Get a textual error message for an error code.
 *
 * @deprecated use @ref BLC_getDetailedErrorString() instead
 */
CPCHAR BL_DLLIMPORT BLC_getErrorString(int error_code);

/**
 * @brief Returns a C-string with the detailed textual representation of all possible error codes.
 * Get a detailed textual error message for an error code.
 * @param errorCode         The error code.
 * @param reportParameter   If the error code comes from an event or error report, pass the
 *                          additional data/status value. Otherwise just pass 0.
 * @param[out] pErrorBuffer A buffer with enough space.
 * @param bufferLength      The length of the passed buffer
 * @return BL_BUFFER_TOO_SMALL If the buffer is too small, otherwise the number of sources.
 */
int BL_DLLIMPORT BLC_getDetailedErrorString(int errorCode,
                                            int reportParameter,
                                            char* pErrorBuffer,
                                            int bufferLength);

/** @brief Resets the BabyLIN device to an consistent and deactivated state.
 *
 * Afterwards, the device will no longer monitor the bus, neither acting as slave nor as master.
 * @param[in] handle  Handle representing the connection. (see @ref BLC_open )
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_Reset(BL_HANDLE handle);

/** @}*/

/** @addtogroup sdf_handling
 *  @brief List of functions to get information about the loaded SDF
 *
 *  The following functions are used to retrieve information about the elements in a loaded
 * SDF-file.
 *  @{
 */

/** @brief Loads the specified SDF-file into library and optionally the BabyLIN device.
 *
 * The SDF is generated by LINWorks/SessionConf from a LDF file.
 * @attention This resets the device upon download
 *
 * @param[in] handle    Handle representing the connection. (see @ref BLC_open )
 * @param[in] filename  C-string with the (fully qualified) filename (i.e. "mybus.sdf", if in the
 *                      same directory, or "c:/data/mybus.sdf").
 * @param download      Boolean value, determines if the SDF profile gets downloaded into the
 *                      BabyLIN device (!=0) or only used in the library (=0).
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_loadSDF(BL_HANDLE handle, const char* filename, int download);

/** @brief Loads the specified LDFile into library and optionally the BabyLIN device.
 *
 * Loads a given LDF, converts the LDF to a SDF ( without SDF specific features ) and optionally
 * downloads the generated SDF to the device. To actually use the LDF, you almost always need to set
 * the emulated node too. You can do this by using the "setnodesimu" command using @ref
 * BLC_sendCommand.
 * @attention This resets the device upon download
 *
 * @param[in] handle    Handle representing the connection. (see @ref BLC_open )
 * @param[in] filename  C-string with the (fully qualified) filename (i.e. "mybus.ldf", if in the
 *                      same directory, or "c:/data/mybus.ldf").
 * @param download      Boolean value, determines if the generated SDF profile gets downloaded into
 *                      the BabyLIN device (!=0) or only used in the library (=0).
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_loadLDF(BL_HANDLE handle, const char* filename, int download);

/** @brief Loads the previously loaded SDF-file into the BabyLIN device.
 *
 * The SDF could be generated by LINWorks/SessionConf from a LDF file and must
 * have been loaded previously by an BL_loadSDF() command.
 * WARNING: this resets the device!
 * @param[in] handle  Handle representing the connection. (see @ref BLC_open )
 * @param mode        The mode to load the SDF. 0= don't load ; 1= download without check ; 2=
 *                    download only if the CRC of the loaded SDF is different
 * @return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_downloadSDF(BL_HANDLE handle, int mode);

/** @brief Checks whether the given file is already loaded on a device.
 *
 * If the device already has an SDF loaded, this method checks if the SDF at the given path and the
 * SDF on the device are the same. Important: This method only works with SDFv3 devices.
 *
 * @param[in] handle    Handle representing the device. (see @ref BLC_open )
 * @param[in] filename  The path of the SDF to compare.
 * @return              BL_OK = SDFs match
 *                      BL_SDF_INCOMPATIBLE = SDFs do not match
 *                      BL_NO_SDF = no SDF loaded on device
 *                      BL_SDF_INSUFFICIENT_FIRMWARE = the device does not support this feature.
 *                      e.g. a SDFv2 device. See standard return values for error, or for textual
 *                      representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_isSDFOnDevice(BL_HANDLE handle, const char* filename);

/** @brief Retrieve further Information about a loaded SDF
 *
 * Need a loaded SDF (see @ref BLC_loadSDF or @ref BLC_loadLDF )
 * @param[in] handle    handle to a valid connection
 * @param[out] pSDFInfo Points to a pre-allocated @ref BLC_SDFINFO to be filled with information
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 * */
int BL_DLLIMPORT BLC_getSDFInfo(BL_HANDLE handle, BLC_SDFINFO* pSDFInfo);

/** @brief Retrieve informations about a SDF-Section from a loaded SDF
 *
 * @param[in] handle          Handle of a valid connection
 * @param infoAboutSectionNr  The section number to retrieve information of. Ranges from 0 to the
 *                            number of sections in the loaded SDF (see @ref BLC_getSDFInfo and @ref
 *                            BLC_SDFINFO.sectionCount )
 * @param[out] pSectionInfo   Address of a pre-allocated @ref BLC_SECTIONINFO
 * @return                    Status of operation; '=0' means successful, '!=0' otherwise. See
 *                            standard return values for error, or for textual representation (for
 *                            return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSectionInfo(BL_HANDLE handle,
                                    int infoAboutSectionNr,
                                    BLC_SECTIONINFO* pSectionInfo);

/** @brief Retrieve description string of a SDF-Section from a loaded SDF
 *
 * @param[in] handle Handle of the channel to get the sdf section description of
 * @return
 * */
CPCHAR BL_DLLIMPORT BLC_getChannelSectionDescription(BL_HANDLE handle);

/** @brief Returns the number of nodes on the BUS
 *
 * Number of nodes connected to the bus according to the informations in the loaded SDF.
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @return            Number of nodes connected to the bus according to the informations in the
 *                    loaded SDF. Values <0 on error. See standard return values for error, or for
 *                    textual representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNodeCount(BL_HANDLE handle);

/** @brief Returns the name of a given node
 *
 * Name of a node connected to the bus according to the informations in the loaded SDF.
 *  @param[in] handle   Handle representing a channel (see @ref BLC_getChannelHandle )
 *  @param idx          Zero based index of requested node entry (see @ref BLC_getNodeCount )
 *  @param[out] dstbuf  Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 *  @param buflen       How many bytes should get returned.
 *  @return             Status of operation; '>0' is the length of the string in "dstbuf", '<0'
 *                      otherwise. See standard return values for error, or for textual
 *                      representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNodeName(BL_HANDLE handle, int idx, char* dstbuf, int buflen);

/** @brief Returns the number of frames of the BUS description
 *
 * Number of frames of the bus according to the informations in the loaded SDF.
 *  @param[in] handle Handle representing a channel (see @ref BLC_getChannelHandle )
 *  @return           Number of frames of the bus according to the informations in the loaded SDF.
 *                    Values <0 on error. See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getFrameCount(BL_HANDLE handle);

/** @brief Returns the name of a given frame
 *
 * Name of a frame of the bus according to the informations in the loaded SDF.
 *  @param[in] handle   Handle representing a channel (see @ref BLC_getChannelHandle )
 *  @param idx          Zero based index of requested frame entry (see @ref BLC_getFrameCount )
 *  @param[out] dstbuf  Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 *  @param buflen       How many bytes should get returned.
 *  @return             Status of operation; '>=0' means successful and is the length of the frame
 *                      name, excluding the terminating '\0'. See standard return values for values
 *                      '<0', or for textual representation (for return values < -1000) @ref
 *                      BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getFrameName(BL_HANDLE handle, int idx, char* dstbuf, int buflen);

/** @brief Returns the number of signals
 *
 * Number of signals of the bus according to the informations in the loaded SDF.
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @return            Number of signals of the bus according to the informations in the loaded SDF.
 *                    Values <0 on error. See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalCount(BL_HANDLE handle);

/** @brief Returns the name of given signal
 *
 * Name of a signal of the bus according to the informations in the loaded SDF.
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param idx         Zero based index of requested signal entry (see @ref BLC_getSignalCount )
 * @param[out] dstbuf Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 * @param buflen      How many bytes should get returned.
 * @return            Status of operation; '>=0' means successful and is the length of the signal
 *                    name, excluding the terminating '\0'. See standard return values for values
 *                    '<0', or for textual representation (for return values < -1000) @ref
 *                    BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalName(BL_HANDLE handle, int idx, char* dstbuf, int buflen);

/** @brief Retrieve information about wheather a signal is emulated by the BabyLIN-Device or not
 *
 * A signal is emulated if the node to which it belongs (according to the SDF) is emulated by the
 * BabyLIN-Device (see "setnodesimu" sendCommand in @ref babylin_commands_sdf to change node
 * emulation at runtime )
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param idx         Zero based index of requested signal entry (see @ref BLC_getSignalCount )
 * @return            '=0' means signal is not emulated, '=1' if emulated, '<0' denotes error.
 *                    See standard return values for error, or for textual representation (for
 *                    return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_isSignalEmulated(BL_HANDLE handle, int idx);

/** @brief Retrieve size of a signal
 *
 * Size of a signal of the bus according to the informations in the loaded SDF.
 *  @param[in] handle Handle representing a channel (see @ref BLC_getChannelHandle )
 *  @param idx        Zero based index of requested signal entry (see @ref BLC_getSignalCount )
 *  @return           Size of the signal in bits. Values <0 on error. See standard return values for
 *                    error, or for textual representation (for return values < -1000) @ref
 *                    BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalSize(BL_HANDLE handle, int idx);

/** @brief Retrieve the number of signals mapped in a frame
 *
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param idx         Zero based index of requested frame entry (see @ref BLC_getFrameCount )
 * @return            Number of signals mapped in the frame Values <0 on error. See standard return
 *                    values for error, or for textual representation (for return values < -1000)
 *                    @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalsInFrameCount(BL_HANDLE handle, int idx);

/** @brief Retrieve the signal number of a signal mapped in a frame
 *
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param frameIndex  Zero based index of the frame the signal is mapped to (see @ref
 *                    BLC_getFrameCount )
 * @param signalIndex Zero based index of the signal as mapped to the frame (see @ref
 *                    BLC_getSignalsInFrameCount )
 * @return            Zero based index of the signal in the SDF Values <0 on error. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalInFrame(BL_HANDLE handle, int frameIndex, int signalIndex);

/** @brief Retrieve the SDF frame number for a given BUS frame-id
 *
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param frameId     The BUS frameId to get the frame number. Special Bits that change the
 *                    interpretation of frameId: Bit 32(0x80000000) : the given Id is a 29Bit ID.
 * @return            Zero based index of the frame in the SDF Values <0 on error. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getFrameNrForFrameId(BL_HANDLE handle, unsigned int frameId);

/** @brief Retrieve the BUS frame-id for a given SDF frame number
 *
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param frameNr     Zero based index of the frame (see @ref BLC_getFrameCount )
 * @return            BUS frameId to the given frame index Values <0 on error. See standard return
 *                    values for error, or for textual representation (for return values < -1000)
 *                    @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getFrameIdForFrameNr(BL_HANDLE handle, unsigned char frameNr);

/** @}*/

/** @addtogroup command_functions Command Functions
 *  @brief List of functions to send commands to a BabyLIN device
 *
 *  The following functions are used to send commands to a BabyLIN device to set or retrieve
 * simulation or device parameters.
 *  @{
 */

/** @brief Send a (raw!) command to the BabyLIN device.
 *
 * @attention The command must be encoded in the binary DP-Message format of BabyLIN.
 *
 * @param[in] handle      Handle representing the connection. (see @ref BLC_open )
 * @param[in] command     Char*-Buffer with the designated @ref Commands
 * @param[in,out] length  Input length of buffer. Output set to actual sent command's length.
 * @return                Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) BL_getLastError().
 */
int BL_DLLIMPORT BLC_sendRaw(BL_HANDLE handle, const unsigned char* command, unsigned int* length);

/** @brief Set the Diagnostic Transport Layer mode.
 *
 *  There are different Diagnostic modes, which offer different levels of protocol functionality.
 *  The Baby-LIN will start with Diagnostic OFF on Power Up. If the BabyLIN acts as LIN master then
 * the selection of an Diagnostic Mode happens trough the usage of the appropriate API function
 * calls. So the API functions BL_sendRawMasterRequest or BL_sendRawSlaveResponse will start  the
 * Diagnostic RAW mode, where as the API calls BL_sendDTLRequest or BL_sendDTLResponse will start
 * the Diagnostic DTL mode. If the BabyLIN acts as LIN slave then the DTL mode must be set by use of
 * this function. It is not possible to use different Diagnostics modes at the same time !
 *
 * List of DTL modes:
 * | Mode | Name | Description |
 * |-----:|:-----|:------------|
 * |0 | DTL_NONE | no DTL Support |
 * |1 | DTL_RAW  | RAW Mode DTL Support |
 * |2 | DTL_COOKED | Cooked Mode DTL Support |
 *
 *  @param[in] handle Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @param mode       DTL mode
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual representation (for
 *                    return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_setDTLMode(BL_HANDLE handle, int mode);

/** @brief Send a DTL master request to a node
 *
 *  @param[in] handle Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @param nad        NAD of the node the request gets send to.
 *  @param length     Length of the following data array.
 *  @param[out] data  DTL frame data (begins with SID, followed by up to 4095 data bytes).
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_sendDTLRequest(BL_HANDLE handle,
                                    unsigned char nad,
                                    int length,
                                    unsigned char* data);

/** @brief Send a DTL slave response to a node
 *
 *  @param[in] handle Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @param nad        NAD of the node the response gets send for.
 *  @param length     Length of the following data array.
 *  @param[out] data  DTL frame data (begins with RSID, followed by up to 4095 data bytes).
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) BL_getLastError().
 */
int BL_DLLIMPORT BLC_sendDTLResponse(BL_HANDLE handle,
                                     unsigned char nad,
                                     int length,
                                     unsigned char* data);

/** @brief Send a (non-DTL) slave response upon receive of matching master request
 *
 *  Upon the reveive of the next master request frame, every bit of the request is compared to
 * 'reqdata' if the corresponding bit of 'reqmask' is set (1). If all match, Baby-LIN starts to send
 * out the data given in 'data', 8 bytes with each slave response frame.
 *
 *  @param[in] handle   Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @param[in] reqdata  Data of the expected master request (exactly 8 bytes).
 *  @param[in] reqmask  Mask for 'reqdata' to indicate which bits must match (exactly 8 bytes).
 *  @param[out] data    Slave response frame data (multiple of 8 bytes).
 *  @param length       Length of data to send.
 *  @return             Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_sendRawSlaveResponse(BL_HANDLE handle,
                                          unsigned char* reqdata,
                                          unsigned char* reqmask,
                                          unsigned char* data,
                                          int length);

/** @brief Send a (non-DTL) Master request with the specified 8 bytes as data.
 *
 *  The internal raw-SlaveResponse-buffer is being reset and the Baby-LIN device gets instructed to
 * report the next 'count' slave response frames which in turn are accumulated into the
 * slave response-buffer which can be queried by BL_getRawSlaveResponse().
 *
 *  @param[in] handle Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @param[in] data   Master request frame data (exactly 8 bytes).
 *  @param count      Number of expected slave response frames.
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_sendRawMasterRequest(BL_HANDLE handle, unsigned char* data, int count);

/** @brief Returns the status of the last request-send operation.
 *
 *  @param[in] handle Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @return           Status of last request operation if >= 0; see @ref BL_DTL_STATUS for values.
 *                    For < 0, see standard return values for error, or for textual representation
 *                    (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getDTLRequestStatus(BL_HANDLE handle);

/** @brief Returns the status of the last resonse-send operation.
 *
 *  @param[in] handle Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @return           Status of last request operation if >= 0; see @ref BL_DTL_STATUS for values.
 *                    For < 0, see standard return values for error, or for textual representation
 *                    (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getDTLResponseStatus(BL_HANDLE handle);

/** @brief Returns the first 'length' bytes of the current slave response-buffer.
 *
 *  The internal raw-SlaveResponse-buffer is filled continuously with the data bytes of
 *  reported SlaveResp-frames and is being reset upon every call of BL_sendRawMasterRequest().
 *
 *  @param[in] handle Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  @param[out] data  Pointer to char array which gets filled (must hold min. 'length' bytes).
 *  @param length     How many bytes should get returned.
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getRawSlaveResponse(BL_HANDLE handle, unsigned char* data, int length);

/**
 * @brief BLC_updRawSlaveResponse resets the internal dtl buffer.
 *
 * @param[in] handle  Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_updRawSlaveResponse(BL_HANDLE handle);

/** @brief Returns @ref BL_OK if the last answer to a command, send to the given handle, contained
 * additional data.
 *
 *  If there is no additional data present it returns BL_NO_ANSWER_DATA.
 *  @param[in] handle Handle representing the Channel (see @ref BLC_getChannelHandle ).
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_lastAnswerHasData(BL_HANDLE handle);

/** @brief Get type of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function reports the type
 * and size for a specific answer data set. Data set selected by name. The following types of data
 * sets are possible:
 * BL_ANSWER_TYPE_INT - 32bit integer
 * BL_ANSWER_TYPE_STR - zero-terminated string (variable length)
 * BL_ANSWER_TYPE_BIN - binary data (variable length)
 *
 *  @param[in] handle     Handle representing the channel on which the answer data was received (see
 *                        @ref BLC_getChannelHandle )
 *  @param[in] name       Char*-string with the name of answer data set
 *  @param[out] type      Type of data set is returned within
 *  @param[in,out] length Input the length of the allocated parameter type. Output the length of the
 *                        returned data in parameter type.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getAnswerTypeByName(BL_HANDLE handle,
                                         const char* name,
                                         BL_ANSWER_TYPE* type,
                                         size_t* length);

/** @brief Get type of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function reports the type
 * and size for a specific answer data set. Data set selected by index. The following types of data
 * sets are possible:
 * BL_ANSWER_TYPE_INT - 32bit integer
 * BL_ANSWER_TYPE_STR - zero-terminated string (variable length)
 * BL_ANSWER_TYPE_BIN - binary data (variable length)
 *
 *  @param[in] handle     Handle representing the channel on which the answer data was received (see
 *                        @ref BLC_getChannelHandle )
 *  @param index          Zero-based index of the answer data set
 *  @param[out] type      Type of data set is returned within
 *  @param[in,out] length Input the length of the allocated parameter type. Output the length of the
 *                        returned data in parameter type.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getAnswerTypeByIndex(BL_HANDLE handle,
                                          const unsigned int index,
                                          BL_ANSWER_TYPE* type,
                                          size_t* length);

/** @brief Get name of a parameter of the last answer data from a BabyLIN
 *
 *  @param[in] handle               Handle representing the channel on which the answer data was
 *                                  received (see @ref BLC_getChannelHandle )
 *  @param index                    Zero-based index of the answer data set.
 *  @param[out] nameBuffer          The buffer to store the name in.
 *  @param[in,out] nameBufferLength Input a pointer to the length of the nameBuffer. Output the
 *                                  length of the name.
 *  @return                         Status of operation; '=0' means successful, '!=0' otherwise. See
 *                                  standard return values for error, or for textual representation
 *                                  (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getAnswerNameByIndex(BL_HANDLE handle,
                                          int index,
                                          char* nameBuffer,
                                          int* nameBufferLength);

/** @brief Get the value of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function copies the answer
 * data set over into the destination buffer. Data set selected by name.
 *
 *  @param[in] handle     Handle representing the channel on which the answer data was received (see
 *                        @ref BLC_getChannelHandle )
 *  @param[in] name       Char*-string with the name of answer data set
 *  @param[out] buffer    Pointer to destination buffer for the data set
 *  @param[in,out] length Input length of preallocated buffer. Output length of written data.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getAnswerByName(BL_HANDLE handle,
                                     const char* name,
                                     void* buffer,
                                     size_t length);

/** @brief Get the value of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function copies the answer
 * data set over into the destination buffer. Data set selected by index.
 *
 *  @param[in] handle   Handle representing the channel on which the answer data was received (see
 *                      @ref BLC_getChannelHandle )
 *  @param index        Zero-based index of the answer data set
 *  @param[out] buffer  Pointer to destination buffer for the data set
 *  @param length       Length of destination buffer
 *  @return             Status of operation; '=0' means successful, '!=0' otherwise.
 *                      See standard return values for error, or for textual
 *                      representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getAnswerByIndex(BL_HANDLE handle,
                                      const unsigned int index,
                                      void* buffer,
                                      size_t length);

/** @brief Send a command to the BabyLIN device.
 *
 * The command must match the command syntax as specified in the BabyLIN documentation (see @ref
 * babylin_commands). The trailing ';' may be omitted;
 *
 *  @param[in] handle   Handle representing the channel to send the command to (see @ref
 *                      BLC_getChannelHandle )
 *  @param[in] command  C-string with @ref Commands (e.g. "status;")
 *  @return           	Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_sendCommand(BL_HANDLE handle, const char* command);

/**
 * @brief Sends a ASCII protocol command and wait for its response.
 *
 * A command can be sent using the ASCII protocol. The function can be blocked, until a response was
 * received.
 *
 * @param[in] handle    A handle representing an ASCII connection
 * @param[in] command   The command to send.
 * @param[out] buffer   A buffer to receive the answer.
 * @param bufferLength  A buffer with enough space.
 * @param timeout_ms    The length of the passed buffer
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_sendASCIICommand(
    BL_HANDLE handle, const char* command, char* buffer, int bufferLength, int timeout_ms);

/** @brief Shorthand for "setsig" command (see @ref babylin_commands)
 *
 *  @param[in] handle Handle representing the channel to send the command to (see @ref
 *                    BLC_getChannelHandle )
 *  @param signalNr   The signal to set the value
 *  @param value      The value to assign to the signal
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_setsig(BL_HANDLE handle, int signalNr, unsigned long long value);

/** @brief Shorthand for "mon_set" command (see @ref babylin_commands)
 *
 *  @param[in] handle     Handle representing the channel to send the command to (see @ref
 *                        BLC_getChannelHandle )
 *  @param frameid        The BUS-frame-id to set the framedata for
 *  @param[out] databytes Array of databytes to use as the framedata
 *  @param len            The length of the data
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_mon_set(BL_HANDLE handle, int frameid, const int* databytes, int len);

/** @brief Shorthand for "mon_xmit" command (see @ref babylin_commands)
 *
 *  @param[in] handle Handle representing the channel to send the command to (see @ref
 *                    BLC_getChannelHandle )
 *  @param frameId    the BUS-frame-id to transmit
 *  @param slottime   slottime = 0 equals a single transmit, slottime > 0 equals cyclic transmission
 *                    of frame
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_mon_xmit(BL_HANDLE handle, int frameId, int slottime);

/** @brief Shorthand for "mon_set" followed by "mon_xmit" command (see @ref babylin_commands)
 *
 *  @param[in] handle     Handle representing the channel to send the command to (see @ref
 *                        BLC_getChannelHandle )
 *  @param frameId        The BUS-frame-id to set and transmit
 *  @param[out] databytes Array of databytes to use as the framedata
 *  @param len            The length of the data
 *  @param slottime       Slottime = 0 equals a single transmit, slottime > 0 equals cyclic
 *                        transmission of frame
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT
BLC_mon_set_xmit(BL_HANDLE handle, int frameId, const int* databytes, int len, int slottime);

/** @brief Convenience function for command "macro_result" handling answer data
 *
 * Executes "macro_result" in a loop until "macro_result" returns anything else than 150 (macro
 * still running), or timeout_ms is exceeded A possible return value of "macro_result" is stored
 * into return_value if the returncode was 155 (finished with error), 156 (finished with exception)
 * or 0 (macro finished)
 *
 * @param[in] handle        Handle representing the channel to send the command to (see @ref
 *                          BLC_getChannelHandle )
 * @param macro_nr          The index of the macro from the section.
 * @param[out] return_value The memory where to store the received macro result.
 * @param timeout_ms        The timeout in milliseconds for the macro to complete.
 * @return                  BLC_macro_result returns the last return value of the "macro_result"
 *                          command. Return values 0, 155, 156 signal success, for other values see
 *                          standard error values @ref BabyLINReturncodes.h.
 */
int BL_DLLIMPORT BLC_macro_result(BL_HANDLE handle,
                                  int macro_nr,
                                  int64_t* return_value,
                                  unsigned int timeout_ms);

/** @brief Returns the result string of given macro, if it was set within the macro.
 *
 * Requests the result string of a macro. If no result string was set, the function retuns
 * @ref BL_NO_DATA.
 *
 * @param[in] handle    Handle representing a channel (see @ref BLC_getChannelHandle
 * )
 * @param macro_nr    The index of the macro from the section.
 * @param[out] dstbuf Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 * @param buflen      How many bytes should get returned.
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getMacroResultString(BL_HANDLE handle, int macro_nr, char* dstbuf, int buflen);

/** @brief Returns the result of a "varrd" command in a convienent way.
 *
 * Reads a number of signal values and puts them directly into a bytearray. Performs the same
 * operation as a @ref BLC_sendCommand with "varrd" but only allows 8bit signals to be read. This
 * call blocks until all data is read and returned.
 *
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param signal_nr   The index of the first signal to read.
 * @param[out] dstbuf Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 * @param length      How many signals should be read.
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_varRead(BL_HANDLE handle, int signal_nr, char* dstbuf, int length);

/** @brief Writes an array of signals to values given by a bytearray.
 *
 * Writes "data_len" number of signals, starting from "signal_nr" with byte values from the "data"
 * array. Performs the same operation as a @ref BLC_sendCommand with "varwr" in mode 1, but only
 * allows 8bit values to be set.
 *
 * @param[in] handle  Handle representing a channel (see @ref BLC_getChannelHandle )
 * @param signal_nr   The index of the first signal to write.
 * @param[in] data    Byte array with data to write. Each byte will be written in one signal.
 * @param data_len    How long the data buffer is. Also defines how many signals are written.
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_varWrite(BL_HANDLE handle, int signal_nr, char* data, int data_len);

/** @brief Creates a adhoc protocol struct with the default settings for the given protocol type.
 *
 * Creates a adhoc protocol struct with the default settings for the given protocol type.
 * @param type  Type of the protocol to create.
 * @return      A valid struct filled with default values for this protocol.
 */
BLC_ADHOC_PROTOCOL BL_DLLIMPORT BLC_AdHoc_DefaultProtocol(ADHOC_PROTOCOL_TYPE type);

/** @brief Creates a adhoc service struct with the default settings for the service and protocol
 * combination.
 *
 * Creates a adhoc service struct with the default settings for the service and protocol
 * combination.
 * @param protocol  A protocol description struct.
 * @return          A valid struct filled with default values for this service.
 */
BLC_ADHOC_SERVICE BL_DLLIMPORT BLC_AdHoc_DefaultService(const BLC_ADHOC_PROTOCOL protocol);

/** @brief Creates a adhoc execute struct with the default settings for the execution of adhoc
 * protocols.
 *
 * Creates a adhoc execute struct with the default settings for the execution of adhoc protocols.
 * @return A valid struct filled with default values for this service.
 */
BLC_ADHOC_EXECUTE BL_DLLIMPORT BLC_AdHoc_DefaultExecute();

/** @brief Creates a adhoc protocol in the device with the given settings.
 *
 * Creates a adhoc protocol in the device with the given settings.
 * @param[in] channel           A channel handle for the channel on which the protocol shall be
 *                              created.
 * @param[in] protocol          A protocol definition struct containing the settings for the new
 *                              protocol.
 * @param[out] protocol_handle  The pointer to a handle value to return the devices created
 *                              protocol to that is used to identify it. It might be set to NULL in
 *                              case an error occured.
 * @return                      Status of operation; '=0' means successful, '!=0' otherwise. See
 *                              standard return values for error, or for textual representation (for
 *                              return values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_AdHoc_CreateProtocol(BL_HANDLE channel,
                                          BLC_ADHOC_PROTOCOL* protocol,
                                          BL_ADHOC_HANDLE* protocol_handle);

/** @brief Creates a adhoc service in the device with the given settings for an existing protocol.
 *
 * Creates a adhoc service in the device with the given settings for an existing protocol.
 * @param[in] channel         A channel handle for the channel on which the service shall be
 *                            created.
 * @param protocol            A protocol handle referencing a existing protocol in the device.
 * @param[in] service         A service struct containing the settings for this new service.
 * @param[out] service_handle The pointer to a handle value to return the devices created service
 *                            to that is used to identify it. It might be set to NULL in case an
 *                            error occured.
 * @return                    Status of operation; '=0' means successful, '!=0' otherwise. See
 *                            standard return values for error, or for textual representation (for
 *                            return values < -10000) @ref BLC_getLastError.
 * @see                       @ref BLC_AdHoc_CreateProtocol
 */
int BL_DLLIMPORT BLC_AdHoc_CreateService(BL_HANDLE channel,
                                         BL_ADHOC_HANDLE protocol,
                                         BLC_ADHOC_SERVICE* service,
                                         BL_ADHOC_HANDLE* service_handle);

/** @brief Runs a given protocol service on the device in a blocking way, the function returns after
 * the protocol is completly done, or the timeout expires.
 *
 * Runs a given protocol service on the device in a blocking way, the function returns after the
 * protocol is completly done, or the timeout expires.
 * @param[in] channel                 A channel handle for the channel on which the protocol service
 *                                    shall be executed.
 * @param protocol_handle             A protocol handle referencing a existing protocol in the
 *                                    device (see @ref BLC_AdHoc_CreateProtocol).
 * @param service_handle              A service handle referencing a existing service in the device.
 * @param[in] execute_flags           A @ref BLC_ADHOC_EXECUTE struct defining some additional
 *                                    settings for the execute.
 * @param[in] req_payload             The payload for the specified protocol service to use.
 * @param[in] req_payload_length      The size of the payload buffer.
 * @param[out] rsp_payload            A preallocated empty buffer where the protocol service
 *                                    response will be mapped into.
 * @param[in,out] rsp_payload_length  Input the size of the response payload buffer. Output the
 *                                    length of the received payload.
 * @param timeout                     The timeout when the function should return, even when the
 *                                    protocol service is not done. This value is in milliseconds
 *                                    (ms).
 * @return                            Status of operation; '=0' means successful, '!=0' otherwise.
 *                                    See standard return values for error, or for textual
 *                                    representation (for return values < -10000) @ref
 *                                    BLC_getLastError.
 * @see                               @ref BLC_AdHoc_CreateProtocol, @ref BLC_AdHoc_CreateService
 */
int BL_DLLIMPORT BLC_AdHoc_Execute(BL_HANDLE channel,
                                   BL_ADHOC_HANDLE protocol_handle,
                                   BL_ADHOC_HANDLE service_handle,
                                   BLC_ADHOC_EXECUTE* execute_flags,
                                   const unsigned char* req_payload,
                                   int req_payload_length,
                                   unsigned char* rsp_payload,
                                   int* rsp_payload_length,
                                   int timeout);

/** @brief Runs a given protocol service on the device in a non-blocking way, the function returns
 * directly after the protocol has be started in the device.
 *
 * Runs a given protocol service on the device in a non-blocking way, the function returns directly
 * after the protocol has be started in the device.
 * @param[in] channel             A channel handle for the channel on which the protocol service
 *                                shall be executed.
 * @param protocol_handle         A protocol handle referencing a existing protocol in the device.
 * @param service_handle          A service handle referencing a existing service in the device.
 * @param[in] execute_flags       A @ref BLC_ADHOC_EXECUTE struct defining some additional settings
 *                                for the execute.
 * @param[in] req_payload         The payload for the specified protocol service to use.
 * @param[in] req_payload_length  The size of the allocated response payload buffer.
 * @param[out] execute_handle     A pointer to an preallocated instance of the struct. When this
 *                                function is successful (see return values below) this handle will
 *                                contain a reference to the running service, else it may be NULL.
 * @return                        Status of operation; '=0' means successful, '!=0' otherwise. See
 *                                standard return values for error, or for textual representation
 *                                (for return values < -10000) @ref BLC_getLastError.
 * @see                           @ref BLC_AdHoc_CreateProtocol, @ref BLC_AdHoc_CreateService
 */
int BL_DLLIMPORT BLC_AdHoc_ExecuteAsync(BL_HANDLE channel,
                                        BL_ADHOC_HANDLE protocol_handle,
                                        BL_ADHOC_HANDLE service_handle,
                                        BLC_ADHOC_EXECUTE* execute_flags,
                                        const unsigned char* req_payload,
                                        int req_payload_length,
                                        BL_ADHOC_HANDLE* execute_handle);

/** @brief Returns the current state of the given protocol service.
 *
 * Returns the current state of the given protocol service.
 * @param[in] channel     A channel handle for the channel on which the protocol service was
 *                        executed.
 * @param execute_handle  The handle to the executed protocol service.
 * @return                Returns: 0 = Protocol service executed successfully.
 *                        TODO: State ID codes else = An error code, see standard return values
 *                        for error, or for textual representation (for return values < -10000)
 *                        @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_AdHoc_GetState(BL_HANDLE channel, BL_ADHOC_HANDLE execute_handle);

/** @brief Returns the response payload of the given protocol service.
 *
 * Returns the response payload of the given protocol service.
 * @param[in] channel               A channel handle for the channel on which the protocol service
 *                                  was executed.
 * @param execute_handle            The handle to the executed protocol service.
 * @param[out] rsp_payload          A preallocated empty buffer where the protocol service response
 *                                  will be mapped into.
 * @param[in,out] rsp_payload_size  Input the size of the preallocated response buffer. Output the
 *                                  length of received payload.
 * @return                          Returns: 0 = Response was read correctly, the buffer contains
 *                                  valid data. else = An error code, see standard return values for
 *                                  error, or for textual representation (for return values <
 *                                  -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_AdHoc_GetResponse(BL_HANDLE channel,
                                       BL_ADHOC_HANDLE execute_handle,
                                       unsigned char* rsp_payload,
                                       int* rsp_payload_size);

/** @brief Deletes an existing adhoc protocol in the device. This deletes all child services of the
 * protocol too.
 *
 * Deletes an existing adhoc protocol in the device. This deletes all child services of the protocol
 * too.
 * @param[in] channel A channel handle for the channel on which the protocol was created.
 * @param protocol    A handle to the protocol to delete.
 * @return            0 = Protocol was deleted successfully. else = An error code, see standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 * @see               @ref BLC_AdHoc_CreateProtocol
 */
int BL_DLLIMPORT BLC_AdHoc_DeleteProtocol(BL_HANDLE channel, BL_ADHOC_HANDLE protocol);

/** @brief Deletes an existing adhoc service for the given protocol in the device.
 *
 * Deletes an existing adhoc service for the given protocol in the device.
 * @param[in] channel A channel handle for the channel on which the service was created.
 * @param protocol    A handle to the protocol of the service.
 * @param service     A handle to the service which shall be deleted.
 * @return            0 = Service was deleted successfully. else = An error code, see standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 * @see               @ref BLC_AdHoc_CreateProtocol, @ref BLC_AdHoc_CreateService
 */
int BL_DLLIMPORT BLC_AdHoc_DeleteService(BL_HANDLE channel,
                                         BL_ADHOC_HANDLE protocol,
                                         BL_ADHOC_HANDLE service);

/** @brief Deletes all existing adhoc protocol for the given channel. This deletes all services too.
 *
 * Deletes all existing adhoc protocol for the given channel. This deletes all services too.
 * @param[in] channel A channel handle for the channel where all protocols shall be deleted.
 * @return            0 = Protocols were deleted successfully. else = An error code, see standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 * @see               @ref BLC_AdHoc_CreateProtocol
 */
int BL_DLLIMPORT BLC_AdHoc_DeleteAllProtocol(BL_HANDLE channel);

/** @brief Deletes all existing adhoc services for the given channel and protocol.
 *
 * Deletes all existing adhoc services for the given channel and protocol.
 * @param[in] channel A channel handle for the channel where the protocol was  created.
 * @param protocol    A protocol handle referencing the protocol which services shall be deleted.
 * @return            0 = Services were deleted successfully. else = An error code, see standard
 *                    return values for error, or for textual representation (for return values <
 *                    -10000) @ref BLC_getLastError.
 * @see               @ref BLC_AdHoc_CreateProtocol, @ref BLC_AdHoc_CreateService
 */
int BL_DLLIMPORT BLC_AdHoc_DeleteAllService(BL_HANDLE channel, BL_ADHOC_HANDLE protocol);

/** @brief Returns the number of tables currently in the device / the loaded SDF.
 *
 * Returns the number of tables currently in the device / the loaded SDF.
 * @param[in] handle        Channel handle to the channel where the command shall be executed.
 * @param[out] table_count  Preallocated pointer which will be filled with a valid value when the
 *                          return value is @ref BL_OK. Contains the number of tables.
 * @return                  0 = Function has run successfully. else = An error code, see standard
 *                          return values for error, or for textual representation (for return
 *                          values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getTableCount(BL_HANDLE handle, int64_t* table_count);

/** @brief Returns the number of rows currently in the given table.
 *
 * Returns the number of rows currently in the given table.
 * @param[in] handle      Channel handle to the channel where the command shall be executed.
 * @param table_id        The id for the table.
 * @param[out] row_count  Preallocated pointer which will be filled with a valid value when the
 *                        return value is @ref BL_OK. Contains the number of rows in the table.
 * @return                0 = Function has run successfully. else = An error code, see standard
 *                        return values for error, or for textual representation (for return values
 *                        < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getTableRowCount(BL_HANDLE handle, int table_id, int64_t* row_count);

/** @brief Returns the number of columns currently in the given table.
 *
 * Returns the number of columns currently in the given table.
 * @param[in] handle        Channel handle to the channel where the command shall be executed.
 * @param table_id          The id for the table.
 * @param[out] column_count Preallocated pointer which will be filled with a valid value when the
 *                          return value is @ref BL_OK. Contains the number of columns in the table.
 * @return                  0 = Function has run successfully. else = An error code, see standard
 *                          return values for error, or for textual representation (for return
 *                          values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getTableColumnCount(BL_HANDLE handle, int table_id, int64_t* column_count);

/** @brief Returns the value of the specified table cell.
 *
 * Returns the value of the specified table cell.
 * @param[in] handle      Channel handle to the channel where the command shall be executed.
 * @param table_id        The id for the table.
 * @param row             The row of the table to read.
 * @param column          The column of the table to read.
 * @param[out] read_value Preallocated pointer which will be filled with a valid value when the
 *                        return value is @ref BL_OK. If the cell is a integer cell, this will be
 *                        the cells value.
 * @param[out] buf        Preallocated buffer which will be filled when the return value is @ref
 *                        BL_OK. If the cell is a string cell, this will be the cells value.
 * @param[in,out] bufsz   Preallocated pointer to a value of size of buf, which will be filled with
 *                        a valid value when the return value is @ref BL_OK. If the cell is a string
 *                        cell, this returns the length of cells data. For an integer cell this
 *                        value is set to 0.
 * @return                0 = Function has run successfully. else = An error code, see standard
 *                        return values for error, or for textual representation (for return values
 *                        < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_tableRead(BL_HANDLE handle,
                               int table_id,
                               int row,
                               int column,
                               int64_t* read_value,
                               char* buf,
                               int* bufsz);

/** @brief Writes the given integer value into the table cell.
 *
 * Writes the given integer value into the table cell.
 * @param[in] handle  Channel handle to the channel where the command shall be executed.
 * @param table_id    The id for the table.
 * @param row         The row of the table to write.
 * @param column      The column of the table to write.
 * @param value       The integer value to write into the cell.
 * @return            0 = Function has run successfully. else = An error code, see standard return
 *                    values for error, or for textual representation (for return values < -10000)
 *                    @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_tableWrite(BL_HANDLE handle, int table_id, int row, int column, int64_t value);

/** @brief Writes the given string value into the table cell.
 *
 * Writes the given string value into the table cell.
 * @param[in] handle  Channel handle to the channel where the command shall be executed.
 * @param table_id    The id for the table.
 * @param row         The row of the table to write.
 * @param column      The column of the table to write.
 * @param[out] value  The zero-terminated string value to write into the cell.
 * @return            0 = Function has run successfully. else = An error code, see standard return
 *                    values for error, or for textual representation (for return values < -10000)
 *                    @ref BLC_getLastError.
 */
int BL_DLLIMPORT
BLC_tableWriteText(BL_HANDLE handle, int table_id, int row, int column, const char* value);

/** @brief Writes the given values into all table cells than span from (start_row, start_column) to
 * (end_row, end_column).
 *
 * Writes the given values into all table cells than span from (start_row, start_column) to
 * (end_row, end_column).
 * @param[in] handle      Channel handle to the channel where the command shall be executed.
 * @param table_id        The id for the table.
 * @param start_row       The start row of the table to write.
 * @param start_column    The start column of the table to write.
 * @param end_row         The end row of the table to write.
 * @param end_column      The end column of the table to write.
 * @param fill_value      This value is used for integer cells.
 * @param[out] fill_text  This zero-terminated value is used for string cells.
 * @return                0 = Function has run successfully. else = An error code, see standard
 *                        return values for error, or for textual representation (for return values
 *                        < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_tableFill(BL_HANDLE handle,
                               int table_id,
                               int start_row,
                               int start_column,
                               int end_row,
                               int end_column,
                               int64_t fill_value,
                               const char* fill_text);

/** @}*/

/** @addtogroup pull_handling
 *  @brief List of functions to pull retrieved data from a connection
 *
 * The following functions are used to get data which has been received from a BabyLIN-device.
 * This approach uses the pull method, i.e. you will not get any information pushed ( see @ref
 * callback_handling "Callback Handling" ) when it's received. Instead you have to call these
 * functions whenever you want to get retrieved data.
 *  @{
 */

/** @brief Retrieve the last framedata available for a frame
 *
 * @attention The Baby-LIN fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before ( see @ref babylin_commands )
 *  @param[in] handle     Handle representing the channel to get the frame data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param frameNr        Zero based index of requested frame entry.
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_FRAME structure.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getLastFrame(BL_HANDLE handle, int frameNr, BLC_FRAME* framedata);

/** @brief Fetches the next frame on Channel from the receiver queue.
 *
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *  @param[in] handle     Handle representing the channel to get the frame data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_FRAME structure.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextFrame(BL_HANDLE handle, BLC_FRAME* framedata);

/** @brief Fetches the next frames on channel from the receiver queue.
 *
 * @attention The device fills the receiver queue only if command "disframe" sent before.
 *  @param[in] handle     Handle representing the channel to get the frame data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_FRAME (structure) array.
 *  @param[in,out] size   Input size of the preallocated @ref BLC_FRAME array, which must be a
 *                        positive value. On output, the actual number of retrieved @ref BLC_FRAMEs,
 *                        which might be less than *size on input.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextFrames(BL_HANDLE handle, BLC_FRAME* framedata, int* size);

/** @brief Fetches the next frame on Channel from the receiver queue with wait-timeout
 *
 * Retrieves the next frame received from the BabyLIN. If no frame-data is available, the funktion
 * will wait _up to_ timeout_ms milliseconds for new data before it returns with a BL_TIMEOUT
 * returncode
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *  @param[in] handle     Handle representing the channel to get the frame data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_FRAME structure.
 *  @param timeout_ms     Timeout to wait for new framedata
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextFrameTimeout(BL_HANDLE handle, BLC_FRAME* framedata, int timeout_ms);

/** @brief Fetches the next frames on channel from the receiver queue with wait-timeout
 *
 * Retrieves the next frames received from the BabyLIN. If no frame-data is available, the funktion
 * will wait _up to_ timeout_ms milliseconds for new data before it returns with a BL_TIMEOUT
 * returncode
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 *  @param[in] handle     Handle representing the channel to get the frame data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_FRAME structure.
 *  @param timeout_ms     Timeout to wait for new framedata
 *  @param[in,out] size   Input size of the preallocated @ref BLC_FRAME array, which must be a
 *                        positive value. On output, the actual number of retrieved @ref BLC_FRAMEs,
 *                        which might be less than *size on input.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextFramesTimeout(BL_HANDLE handle,
                                          BLC_FRAME* framedata,
                                          int timeout_ms,
                                          int* size);

/** @brief Fetches the next regular or jumbo frame on Channel from the receiver queue.
 *
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *  @param[in] handle     Handle representing the channel to get the jumbo frame data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_JUMBO_FRAME structure.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise.
 *                        See standard return values for error, or for textual
 *                        representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextJumboFrame(BL_HANDLE handle, BLC_JUMBO_FRAME* framedata);

/** @brief Fetches the next regular or jumbo frames on channel from the receiver queue.
 *
 * @attention The device fills the receiver queue only if command "disframe" sent before.
 *  @param[in] handle     Handle representing the channel to get the frame data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_JUMBO_FRAME (structure) array.
 *  @param[in,out] size   Input size of the preallocated @ref BLC_FRAME array, which must be a
 *                        positive value. On output, the actual number of retrieved @ref
 *                        BLC_JUMBO_FRAMEs, which might be less than *size on input.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextJumboFrames(BL_HANDLE handle, BLC_JUMBO_FRAME* framedata, int* size);

/** @brief Fetches the next regular or jumbo frame on Channel from the receiver queue with
 * wait-timeout
 *
 * Retrieves the next jumbo frame received from the BabyLIN. If no frame-data is available, the
 * function will wait _up to_ timeout_ms milliseconds for new data before it returns with a
 * BL_TIMEOUT returncode
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *  @param[in] handle     Handle representing the channel to get the jumbo frame data from (see
 *                        @ref BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_JUMBO_FRAME structure.
 *  @param timeout_ms     Timeout to wait for new framedata
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise.
 *                        See standard return values for error, or for textual representation (for
 *                        return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextJumboFrameTimeout(BL_HANDLE handle,
                                              BLC_JUMBO_FRAME* framedata,
                                              int timeout_ms);

/** @brief Fetches the next regular or jumbo frames on channel from the receiver queue with
 * wait-timeout
 *
 * Retrieves the next jumbo frames received from the BabyLIN. If no frame-data is available, the
 * function will wait _up to_ timeout_ms milliseconds for new data before it returns with a
 * BL_TIMEOUT returncode
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 *  @param[in] handle     Handle representing the channel to get the jumbo frame data from (see
 *                        @ref BLC_getChannelHandle )
 *  @param[out] framedata Pointer to a pre-allocated @ref BLC_JUMBO_FRAME structure.
 *  @param timeout_ms     Timeout to wait for new framedata
 *  @param[in,out] size   Input size of the preallocated @ref BLC_FRAME array, which must be a
 *                        positive value. On output, the actual number of retrieved @ref
 *                        BLC_JUMBO_FRAMEs, which might be less than *size on input.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextJumboFramesTimeout(BL_HANDLE handle,
                                               BLC_JUMBO_FRAME* framedata,
                                               int timeout_ms,
                                               int* size);

/** @brief Fetches the next signal from the receiver queue.
 *
 * @attention The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 *  @param[in] handle       Handle representing the channel to get the signal data from (see @ref
 *                          BLC_getChannelHandle )
 *  @param[out] signaldata  Pointer to a pre-allocated @ref BLC_SIGNAL structure.
 *  @return                 Status of operation; '=0' means successful, '!=0' otherwise. See
 *                          standard return values for error, or for textual representation (for
 *                          return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextSignal(BL_HANDLE handle, BLC_SIGNAL* signaldata);

/** @brief Fetches the next signals from the receiver queue.
 *
 * @attention The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 *  @param[in] handle       Handle representing the channel to get the signal data from (see @ref
 *                          BLC_getChannelHandle )
 *  @param[out] signaldata  Pointer to a pre-allocated @ref BLC_SIGNAL (structure) array.
 *  @param[in,out] size     Input size of the preallocated @ref BLC_SIGNAL array, which must be a
 *                          positive value. On output, the actual number of retrieved @ref
 *                          BLC_SIGNALs, which might be less than *size on input.
 *  @return                 Status of operation; '=0' means successful, '!=' otherwise. See standard
 *                          return values for error, or for textual representation (for return
 *                          values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextSignals(BL_HANDLE handle, BLC_SIGNAL* signaldata, int* size);

/** @brief Fetches the next signals for a specific signal from the receiver queue.
 *
 * @attention The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 * @attention This function will remove the signal values from the queue. Further signal receiving
 * is no longer guaranteed to be in order.
 *
 *  @param[in] handle     Handle representing the channel to get the signal data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[in] signaldata Pointer to a pre-allocated @ref BLC_SIGNAL (structure) array.
 *  @param size           Size of the pre-allocated @ref BLC_SIGNAL array, in units of @ref
 *                        BLC_SIGNAL, which must be a positive value.
 *  @param signalNumber   The signal number to get the signals for
 *  @return               Number of signals found, '<0' on error. See standard return values for
 *                        error, or for textual representation (for return values < -1000) @ref
 *                        BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextSignalsForNumber(BL_HANDLE handle,
                                             BLC_SIGNAL* signaldata,
                                             int size,
                                             int signalNumber);

/** @brief Fetches the next Bus error from the receiver queue.
 *
 *  @param[in] handle     Handle representing the channel to get the error data from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[out] errordata Pointer to a pre-allocated @ref BLC_ERROR structure.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextBusError(BL_HANDLE handle, BLC_ERROR* errordata);

/** @brief Fetches the next complete DTL request from the receiver queue.
 *
 *  @param[in] handle Handle representing the channel to get the dtl data from (see @ref
 *                    BLC_getChannelHandle )
 *  @param[out] frame Pointer to a pre-allocated @ref BLC_DTL structure.
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextDTLRequest(BL_HANDLE handle, BLC_DTL* frame);

/** @brief Fetches the next complete DTL response from the receiver queue.
 *
 *  @param[in] handle Handle representing the channel to get the dtl data from (see @ref
 *                    BLC_getChannelHandle )
 *  @param[out] frame Pointer to a pre-allocated @ref BLC_DTL structure.
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNextDTLResponse(BL_HANDLE handle, BLC_DTL* frame);

/** @brief  Return the current signal value (for non-array signals).
 * @attention The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 * @note Special signalNr '-1' returns always 4711 in *value; signalNr '-2' returns a counter
 * increased by 1 after every call.
 *
 * @param[in] handle  Handle representing the channel to get the signal value from (see @ref
 *                    BLC_getChannelHandle )
 * @param signalNr    Number of the signal according to SDF.
 * @param[out] value  Pointer to an word-sized variable getting the value.
 * @return            Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalValue(BL_HANDLE handle, int signalNr, unsigned long long* value);

/** @brief  Return the current signal value (for non-array signals) with timestamp
 * @attention The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 * @note Special signalNr '-1' returns always 4711 in *value; signalNr '-2' returns a counter
 * increased by 1 after every call.
 *
 * @param[in] handle      Handle representing the channel to get the signal value from (see @ref
 *                        BLC_getChannelHandle )
 * @param signalNr        Number of the signal according to SDF.
 * @param[out] value      Pointer to an word-sized variable getting the value.
 * @param[out] timestamp  Pointer to an word-sized variable getting the timestamp when the signal
 *                        was received (PC-Timestamp (ms)).
 * @return                Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalValueWithTimestamp(BL_HANDLE handle,
                                                 int signalNr,
                                                 unsigned long long* value,
                                                 unsigned long long* timestamp);

/** @brief Returns the current signal value (for non-array signals).
 *
 * @attention The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *  @param[in] handle     Handle representing the channel to get the signal value from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[in] signalName Name of the Signal as declared in LDF.
 *  @param[out] value     Pointer to an word-sized variable getting the value.
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalValueByName(BL_HANDLE handle,
                                          const char* signalName,
                                          unsigned long long* value);

/** @brief Returns the current signal value (for array signals).
 *
 * @attention The Baby-LIN reports the signal value only if command "dissignal" sent before.
 * @note
 * Special signalNr '-1' returns always the hex array { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd,
 * 0xef } in *array; signalNr '-2' returns a counted sequence, where the byte 0 holds the actual
 * counter and the following bytes hold the 'history'; i.e.:
 *
 * @par
 * 1st call: { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 * 2nd call: { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 * 3rd call: { 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 * 4th call: { 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 *                ...etc...
 *
 *  @param[in] handle Handle representing the channel to get the signal value from (see @ref
 *                    BLC_getChannelHandle )
 *  @param signalNr   Number of the signal accordng to SDF.
 *  @param[out] array Pointer to an 8 byte array getting the value. It must always have the size
 *                    of 8 bytes, even for smaller array signals!
 *  @return           Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                    return values for error, or for textual representation (for return values <
 *                    -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalArray(BL_HANDLE handle, int signalNr, unsigned char* array);

/** @brief Returns the current signal value (for array signals) with timstamp.
 *
 * @attention The Baby-LIN reports the signal value only if command "dissignal" sent before.
 * @note
 * Special signalNr '-1' returns always the hex array { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd,
 * 0xef } in *array; signalNr '-2' returns a counted sequence, where the byte 0 holds the actual
 * counter and the following bytes hold the 'history'; i.e.:
 *
 * @par
 * 1st call: { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 * 2nd call: { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 * 3rd call: { 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 * 4th call: { 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * @par
 *                ...etc...
 *
 *  @param[in] handle     Handle representing the channel to get the signal value from (see @ref
 *                        BLC_getChannelHandle )
 *  @param signalNr       Number of the signal accordng to SDF.
 *  @param[out] array     Pointer to an 8 byte array getting the value. It must always have the size
 *                        of 8 bytes, even for smaller array signals!
 *  @param[out] timestamp Pointer to an word-sized variable getting the timestamp
 *                        when the signal was received (PC-Timestamp (ms).
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalArrayWithTimestamp(BL_HANDLE handle,
                                                 int signalNr,
                                                 unsigned char* array,
                                                 unsigned long long* timestamp);

/** @brief Returns the current signal value (for array signals).
 *
 * @attention The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *  @param[in] handle     Handle representing the channel to get the signal value from (see @ref
 *                        BLC_getChannelHandle )
 *  @param[in] signalName Name of the Signal as declared in LDF.
 *  @param[out] array     Pointer to an 8 byte array getting the value. It must always have the size
 *                        of 8 bytes, even for smaller array signals!
 *  @return               Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                        return values for error, or for textual representation (for return values
 *                        < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalArrayByName(BL_HANDLE handle,
                                          const char* signalName,
                                          unsigned char* array);

/** @brief Returns the type of a signal
 *
 *  @param[in] handle Handle representing the channel to which the signal belongs (see @ref
 *                    BLC_getChannelHandle )
 *  @param idx        Zero based index of requested signal entry.
 *  @return           Status of operation; Signal is Array == 1; Signal is scalar Value == 0. Values
 *                    <0 on error. See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_isSignalArray(BL_HANDLE handle, int idx);

/** @brief Encodes the signal's value as defined in the corresponding Signal Encoding tables of
 * LDF/SDF.
 *
 *  If no SignalEncoding is specified for this signal, the value itself is written into destination
 * buffer 'description'. If one of the required pointers is NULL or the buffer size is too small,
 * the function returns the needed minimum buffer length in 'length'. It's possible to use two
 * variants to get encoded signal: 1) pointer 'encUnit' and 'buffLen1' set to NULL: then encoded
 * signal saved inclusive unit in buffer 'encSignal' 2) pointer 'encUnit' and 'buffLen1' != NULL:
 * unit of signal saved separately in buffer 'encUnit'
 *  @param[in] handle       Handle representing the channel to which the signal belongs (see @ref
 *                          BLC_getChannelHandle )
 *  @param signalNr         Number (Index) of the signal accordng to SDF.
 *  @param value            Value to be encoded
 *  @param[out] encSignal   Points to save location of encoded signal value (inclusive 'unit', if
 *                          'encUnit' not used)
 *  @param[in,out] buffLen0 Input the allocated length of 'encSignal' buffer. Output the length of
 *                          the written data.
 *  @param[out] encUnit     Optional: points to save location of signal unit (if this pointer is
 *                          NULL then 'unit' saved in 'encSignal' buffer also)
 *  @param[in,out] buffLen1 Optional: Input the allocated length of 'encUnit' buffer (if this
 *                          pointer is NULL then 'unit' saved in 'encSignal' buffer also). Output
 *                          the length of the written data.
 *  @return                 Status of operation; '=0' means successful, '!=0' otherwise. See
 *                          standard return values for error, or for textual representation (for
 *                          return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_encodeSignal(BL_HANDLE handle,
                                  int signalNr,
                                  unsigned long long value,
                                  char* encSignal,
                                  size_t* buffLen0,
                                  char* encUnit,
                                  size_t* buffLen1);

/**
 * @brief BLC_decodeSignal takes an encoded Signal value and tries to compute it back to its Signal
 * value. Rounding errors might occur for large signals or encoding scales and offsets.
 *
 * @param[in] handle      The Channel handle the Signal does come from.
 * @param signalNr        The number of the Signal that has the encodings.
 * @param[out] encSignal  The encoded signal value as a c-string(zero terminated).
 * @param[out] value      The reverted value. rounding errors might occur.
 * @return                @ref BL_OK if the value could be converted, != 0 otherwise.
 */
int BL_DLLIMPORT BLC_decodeSignal(BL_HANDLE handle, int signalNr, char* encSignal, int64_t* value);

/** @brief Get values of all signals mapped to a frame
 *
 * @param[in] handle      Handle representing the channel to which the frame belongs (see @ref
 *                        BLC_getChannelHandle )
 * @param frameNr         Frame number (according to SDF) to get the signal data from
 * @param[out] signalList Pre-allocated array of @ref BLC_SIGNAL structures to store the signal data
 *                        to
 * @param signalListLen   Length of the pre-allocated array of @ref BLC_SIGNAL structures
 * @return                The number of signals stored to signalList. Values <0 on error. See
 *                        standard return values for error, or for textual representation (for
 *                        return values < -1000) @ref BLC_getLastError.
 * */
int BL_DLLIMPORT BLC_getSignalsInFrame(BL_HANDLE handle,
                                       int frameNr,
                                       BLC_SIGNAL* signalList,
                                       int signalListLen);

/**
 * @brief Returns some details for given frame entry.
 *
 * @param[in] handle      Handle representing the channel to which the frame belongs (see @ref
 *                        BLC_getChannelHandle )
 * @param idx             Zero based index of requested frame entry (sdf number).
 * @param[out] pbusid     Pointer to int, which gets filled with BUS ID (without parity bits on
 *                        LIN-Bus)
 * @param[out] psize      Pointer to int, which gets filled with size of frame in bytes
 * @param[out] pnodenum   Pointer to int, which gets filled with nodeindex of publishing node for
 *                        this frame
 * @param[out] pframetype Pointer to int, which gets filled with LIN version of this frame (LIN
 *                        channel only)
 */
int BL_DLLIMPORT BLC_getFrameDetails(
    BL_HANDLE handle, int idx, int* pbusid, int* psize, int* pnodenum, int* pframetype);

/**
 * @brief Returns some details for given frame entry.
 *
 * @param[in] handle  Handle representing the channel to which the signal belongs (see @ref
 *                    BLC_getChannelHandle )
 * @param signalNr    Zero based index of the signal entry (sdf number).
 * @return            The number of the node the signal is published by. -1 if signal is virtual.
 *                    Values <-1 on error. See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getNodeForSignal(BL_HANDLE handle, int signalNr);
/** @}*/

/** @addtogroup direct_mode
 *  @brief List of functions to access the LIN-BUS directly
 *
 *  @{
 */

/** @brief Starts direct mode on channel with given baudrate, bitwidth, stopbits and parity
 * settings. If the direct mode is already active on the channel, it will be restarted. The command
 * prepares the channel with @ref BLC_dmReportConfig settings of 5ms and 8 bytes
 *
 * @param[in] handle  Handle representing the channel to which the frame belongs (see @ref
 *                    BLC_getChannelHandle )
 * @param baudrate    The baudrate to configure while in direct mode.
 * @param bitwidth    This parameter is not yet used and has to be set to 0. The bitwidth will be 8.
 * @param stopbits    This parameter is not yet used and has to be set to 0. It will be 1 stopbit.
 * @param parity      This parameter is not yet used and has to be set to 0. Parity bit is
 *                    deactivated.
 * @return            @ref BL_OK on success, errorcode otherwise
 */
int BL_DLLIMPORT
BLC_dmStart(BL_HANDLE handle, int baudrate, int bitwidth, int stopbits, int parity);

/** @brief Configure the reporting policy of the device in respect to a timeout and/or a block of
 * bytes. The device will report any data read from the bus if the read data exceeds the given byte
 * count or after [timeout] milliseconds idle time.
 *
 * direct mode has to be active
 *
 * @param[in] handle  Handle representing the channel to which the frame belongs (see @ref
 *                    BLC_getChannelHandle )
 * @param[in] timeout The time in milliseconds until the bus is determined as idle resulting in a
 *                    report of data even thou less then [bytes] data was received.
 * @param bytes       The amount of data after wich a report is generated.
 * @return            @ref BL_OK on success, errorcode otherwise
 */
int BL_DLLIMPORT BLC_dmReportConfig(BL_HANDLE handle, int timeout, int bytes);

/** @brief Writes data in directmode to the bus
 *
 * direct mode has to be active
 *
 * if no bus power is available, the data will be queued to be sent when bus power is available
 *
 * @param[in] handle  Handle representing the channel to which the frame belongs (see @ref
 *                    BLC_getChannelHandle )
 * @param[in] data    The buffer containing the data to send.
 * @param dataSize    The amount of data in the buffer. only 1023 bytes can be send to the device in
 *                    one call.
 * @return            Number of bytes written, values <0 indicate error code.
 */
int BL_DLLIMPORT BLC_dmWrite(BL_HANDLE handle, const char* data, unsigned int dataSize);

/**
 * @brief Read data in direct mode.
 *
 * reads maximum bufferSize bytes to buffer. Will wait for data for infinite  amount of time. If the
 * DirectMode is active this function or @ref BLC_dmReadTimeout have to be called to prevent the
 * internal buffer from allocating all system memory.
 *
 * @param[in] handle  Handle representing the channel to which the frame belongs (see @ref
 *                    BLC_getChannelHandle )
 * @param[out] buffer The buffer having at least [bufferSize] space to store received data.
 * @param bufferSize  The amount of data to read.
 * @return            Number of bytes read, values <0 indicate error code
 */
int BL_DLLIMPORT BLC_dmRead(BL_HANDLE handle, char* buffer, unsigned int bufferSize);

/**
 * @brief Same as @ref BLC_dmRead with waiting timeout in ms
 *
 * If the DirectMode is active this function or @ref BLC_dmRead have to be called to prevent the
 * internal buffer from allocating all system memory.
 *
 * @param[in] handle  Handle representing the channel to which the frame belongs (see @ref
 *                    BLC_getChannelHandle )
 * @param[out] buffer The buffer having at least [bufferSize] space to store received data.
 * @param bufferSize  The amount of data to read.
 * @param timeout_ms  The timeout in milliseconds after which the function returns with less then
 *                    bufferSize data read.
 * @return            Number of bytes read, values <0 indicate error code
 */
int BL_DLLIMPORT BLC_dmReadTimeout(BL_HANDLE handle,
                                   char* buffer,
                                   unsigned int bufferSize,
                                   unsigned int timeout_ms);

/**
 * @brief Issue a pulse on the bus
 *
 * with a duration of lowtime_us in us. After the pulse, any further action will be delayed
 * paddingtime_us if no bus power is available, the pulse will be queued to be sent when bus power
 * is available
 *
 * @param[in] handle      Handle representing the channel to which the frame belongs (see @ref
 *                        BLC_getChannelHandle )
 * @param lowtime_us      The time in micro seconds to hold the output on dominant level.
 * @param paddingtime_us  The time in mico seconds to idle before taking the next  action.
 * @return                @ref BL_OK on success, errocode otherwise
 */
int BL_DLLIMPORT BLC_dmPulse(BL_HANDLE handle,
                             unsigned int lowtime_us,
                             unsigned int paddingtime_us);

/**
 * @brief Delay the next operation by the given time.
 *
 * this function is an alias for "@ref BLC_dmPulse(channel, 0, paddingtime_us)". If no bus power is
 * available, the delay will be queued to be sent when bus power is available.
 *
 * @param[in] channel     A handle representing the channel to which the frame belongs
 * @param paddingtime_us  The time in mico seconds to idle before taking the next action.
 * @return                @ref BL_OK on success, errocode otherwise
 * @see                   @ref BLC_getChannelHandle
 */
int BL_DLLIMPORT BLC_dmDelay(BL_HANDLE channel, unsigned int paddingtime_us);

/**
 * @brief Stop direct mode
 *
 * @param[in] handle  Handle representing the channel to which the frame belongs
 * @return            @ref BL_OK on success, errorcode otherwise
 * @see               @ref BLC_getChannelHandle
 */
int BL_DLLIMPORT BLC_dmStop(BL_HANDLE handle);

/**
 * @brief BLC_dmPrepare enters or exits the preparation state.
 *
 * @param[in] channel The channel handle to work on.
 * @param mode        The preparation mode to set. 1 for entering preparation mode, 0 to exit it and
 *                    2 to clear the preparation buffer.
 * @return            @ref BL_OK on success, errorcode otherwise
 */
int BL_DLLIMPORT BLC_dmPrepare(BL_HANDLE channel, unsigned char mode);
/** @}*/

/** @addtogroup command_functions
 *  @brief List of functions to access the LIN-BUS directly
 *
 *  @{
 */

/**
 * @brief BLC_loggingStart enables the standard logging feature for a specific device or channel.
 *
 * @param[in] handle      Handle representing the channel or device handle whose data should be
 *                        logged. If one want to log a single channel (e.g. the first LIN) use the
 *                        channel handle and get one logfile. If one want to log all device channels
 *                        use the connection handle and get one logfile for each channel and one for
 *                        the device channel.
 * @param[in] configFile  The config file to load (can be created with the SimpleMenu). Setting
 *                        "configFile" to a nullptr will load these default settings: ASCII mode,
 *                        logging of frames, debug and error messages limit file size to 100MB and
 *                        max. 2 files per channel. Output path is "User/Documents/Lipowsky
 *                        Industrie-Elektronik GmbH/logs"
 * @return                @ref BL_OK on success, errorcode otherwise
 * @see                   @ref BLC_getChannelHandle and @ref BLC_open
 */
int BL_DLLIMPORT BLC_loggingStart(BL_HANDLE handle, const char* configFile);

/**
 * @brief BLC_loggingAddComment Added a string to the logfile
 *
 * @param[in] handle  Handle representing the channel or device handle whose data should be logged.
 *                    If one want to log a single channel (e.g. the first LIN) use the channel
 *                    handle and get one logfile. If one want to log all device channels use the
 *                    connection handle and get one logfile for each channel and one for the device
 *                    channel.
 * @param[in] comment The comment string which would be added to the logfile which is linked to
 *                    the handle.
 * @return            @ref BL_OK on success, errorcode otherwise
 * @see               @ref BLC_getChannelHandle and @ref BLC_open
 */
int BL_DLLIMPORT BLC_loggingAddComment(BL_HANDLE handle, const char* comment);

/**
 * @brief BLC_loggingStop stop and close all active logfiles which were started via @ref
 * BLC_loggingStart and linked to the handle. This function did not stop the logging via a SDF file
 * if used.
 *
 *@param[in] handle The handle of the device or channel to stop. If this is a device handle all
 *                  corresponding channels will be stopped, if this is a channel handle, only the
 *                  logging of this channel will be stopped.
 * @return          @ref BL_OK on success, errorcode otherwise
 */
int BL_DLLIMPORT BLC_loggingStop(BL_HANDLE handle);

/**
 * @brief BLC_loggingStopGlobal stop and close all active logfiles which were started via @ref
 * BLC_loggingStart. This function did not stop the logging via a SDF file if used.
 *
 * @return @ref BL_OK on success, errorcode otherwise
 */
int BL_DLLIMPORT BLC_loggingStopGlobal();
/** @}*/

/**
 *  Incomplete features. Do not use.
 */

/** @addtogroup legacy
 *  @brief List of functions to access the LIN-BUS directly
 *
 *  @{
 */

#ifdef WIN32
#define BL_EXCEPTION_FILTER_ATTR __stdcall
#else
#define BL_EXCEPTION_FILTER_ATTR
#endif
typedef long(BL_EXCEPTION_FILTER_ATTR* exception_filter)(struct _EXCEPTION_POINTERS* ExceptionInfo);
void BL_DLLIMPORT BLC_overwriteCrashHandler(exception_filter function,
                                            const char* application_name,
                                            int dump_external_code,
                                            int show_msgbox_on_crash);

int BL_DLLIMPORT BLC_runLuaCode(BL_HANDLE handle, const char* lua_code);

/** @}*/

#if defined(__cplusplus)
}  // extern "C"
#endif

#endif  // BABYLIN_H
