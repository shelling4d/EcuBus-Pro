#ifndef BABYLINCAN_NOSTRUCT_H
#define BABYLINCAN_NOSTRUCT_H

#include "BabyLINCAN.h"

#if defined(__cplusplus)
#include <cstddef>  // get "size_t", used by function BL_encodeSignal())
#include <cstdint>
extern "C" {
#else
#include <stddef.h>  // get "size_t", used by function BL_encodeSignal())
#include <stdint.h>
#endif

/** @brief Open a connection to a BabyLIN device using BLC_PORTINFO information.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 *  This function tries to open the BabyLIN device of the BLC_PORTINFO information, i.e. works as a
 * wrapper for @ref BLC_open and @ref BLC_openNet which automatically decides which connection to
 * establish.
 *
 * \note Platform independent way of connecting to BabyLIN-devices found by @ref BLC_getBabyLinPorts
 * or @ref BLC_getBabyLinPortsTimout.
 *
 * \note the BLC_PORTINFO-structure of the BabyLIN to connect to ( see @ref BLC_getBabyLinPorts ) is
 * divided in its members here.
 *
 * @param portNr    The Comport number on Windows for serial devices or the TCP port for network
 *                  devices.
 * @param type      The type of the connection to establish refer to @ref BLC_PORTINFO 's type field
 *                  for value descriptions.
 * @param name      A 256 character array. name is not yet used and has to have a '\0' as first
 *                  character.
 * @param device    A 256 character array. device is the path to the serial connection under Linux
 *                  (e.g. /dev/ttyUSB0) or the TCP IP address of the device to connect to.
 * @return          Returns an handle for the BabyLIN-connection or NULL if the connection could not
 *                  be established. You may fetch the corresponding (textual) error with @ref
 *                  BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT BLCns_openPort(int portNr, int type, char* name, char* device);

/** @brief Open a connection to a BabyLIN device using BLC_PORTINFO information.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 *  This function tries to open the BabyLIN device specified by the BLC_PORTINFO derived from the
 * given URL.
 *
 * @param url   The device URL to convert might be a system path (/dev/ttyUSB1) for Unix based
 *              systems, a comport (COM1) as is used for windows or a network address
 *              (tcp://127.0.0.1:2048) to connect to a network device.
 *
 * @return      Returns an handle for the BabyLIN-connection or NULL if the connection could not be
 *              established or the given URL is malformed. You may fetch the corresponding (textual)
 *              error with @ref BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT BLCns_openURL(char* url);

/**
 * @brief Requests the information about the target
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 * @param handle        Handle representing the connection (see @ref BLC_open )
 * @param type          The target type refer to @ref BLC_TARGETID for value description.
 * @param version       The firmware version of the device.
 * @param flags         The flags as described in @ref BLC_TARGETID.
 * @param serial        Devices serial number.
 * @param heapsize      The devices heap size.
 * @param numofchannels The number of channels as described in @ref BLC_TARGETID.
 * @param name          The product name, has to be preallocated.
 * @param nameLength    Length of the product name array.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getTargetID(BL_HANDLE handle,
                                   unsigned short* type,
                                   unsigned short* version,
                                   unsigned short* flags,
                                   long* serial,
                                   long* heapsize,
                                   long* numofchannels,
                                   char* name,
                                   int nameLength);

/** @brief Retrieve informations about the Channel
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 * @param handle        Channel-handle representing the Channel. (see @ref BLC_getChannelHandle)
 * @param id            The channel id.
 * @param type          The channel type as described in @ref BLC_CHANNELINFO.
 * @param name          The channel name, has to be preallocated.
 * @param nameLength    The size of the name array.
 * @param maxbaudrate   The maximal baud-rate as described in @ref BLC_CHANNELINFO.
 * @param reserved1     Reserved for future use.
 * @param reserved2     Reserved for future use.
 * @param reserved3     Reserved for future use.
 * @param associatedWithSectionNr The index of the section as described in @ref BLC_CHANNELINFO.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getChannelInfo(BL_HANDLE handle,
                                      unsigned short* id,
                                      unsigned short* type,
                                      char* name,
                                      int nameLength,
                                      long* maxbaudrate,
                                      long* reserved1,
                                      long* reserved2,
                                      long* reserved3,
                                      int* associatedWithSectionNr);

/** @brief Get the version string of the library
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 *  This function returns the version string of the library.
 *
 * @param buffer    A preallocated buffer to store the version string in.
 * @param bufferlen The length of the preallocated buffer.
 * @return          Returns a C-string with the version information.
 */
int BL_DLLIMPORT BLCns_getVersionString(char* buffer, int bufferlen);

/** @brief Retrieve the last framedata available for a frame
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Baby-LIN fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before ( see @ref babylin_commands )
 *
 * @param handle    Is the Handle representing the channel to get the frame data from (see @ref
 *                  BLC_getChannelHandle )
 * @param frameNr   Zero based index of requested frame entry.
 * @param chId      The channel id, the frame came in at.
 * @param timestamp The timestamp given the frame from the device as described in the @ref BLC_FRAME
 *                  struct.
 * @param intime    The PC time when the frame came in as described in the @ref BLC_FRAME struct.
 * @param frameId   The frame id as described in the @ref BLC_FRAME struct.
 * @param lenOfData The length of the frame data array.
 * @param frameData Pointer to a preallocated array to be filled with the frames data.
 * @param frameFlags The frame flags as described in the @ref BLC_FRAME struct.
 * @param busFlags  The bus specific flags as described in the @ref BLC_FRAME struct.
 * @param checksum  Only valid for LIN channels the frames checksum byte.
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getLastFrame(BL_HANDLE handle,
                                    int frameNr,
                                    unsigned long* chId,
                                    unsigned long* timestamp,
                                    long* intime,
                                    unsigned long* frameId,
                                    unsigned char* lenOfData,
                                    unsigned char* frameData,
                                    short* frameFlags,
                                    short* busFlags,
                                    unsigned char* checksum);

/** @brief Fetches the next frame on Channel from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * @param handle    Handle representing the channel to get the frame data from (see @ref
 *                  BLC_getChannelHandle )
 * @param chId      The channel id, the frame came in at.
 * @param timestamp The timestamp given the frame from the device as described in the @ref BLC_FRAME
 *                  struct.
 * @param intime    The PC time when the frame came in as described in the @ref BLC_FRAME struct.
 * @param frameId   The frame id as described in the @ref BLC_FRAME struct.
 * @param lenOfData The length of the frame data array.
 * @param frameData Pointer to a preallocated array to be filled witht he frame data.
 * @param frameFlags The frame flags as described in the @ref BLC_FRAME struct.
 * @param busFlags  The bus specific flags as described in the @ref BLC_FRAME struct.
 * @param checksum  Only valid for LIN channels the frames checksum byte.
 *
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextFrame(BL_HANDLE handle,
                                    unsigned long* chId,
                                    unsigned long* timestamp,
                                    long* intime,
                                    unsigned long* frameId,
                                    unsigned char* lenOfData,
                                    unsigned char* frameData,
                                    short* frameFlags,
                                    short* busFlags,
                                    unsigned char* checksum);

/** @brief Fetches the next frames on Channel from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * @param handle        Handle representing the channel to get the frame data from (see @ref
 *                      BLC_getChannelHandle )
 * @param chId          Array of channel identifiers for the corresponding fetched frames.
 * @param timestamp     Array of timestamps for the corresponding fetched frames.
 * @param intime        Array of arrival timestamps for the corresponding fetched frames.
 * @param frameId       Array of frame identifiers for the corresponding fetched frames.
 * @param lenOfData     Array of data lengths for the data of of the corresponding fetched frames.
 * @param frameData     Array of frame data arrays for the corresponding fetched frames.
 * @param frameFlags    Array of frame flags for the corresponding fetched frames.
 * @param busFlags      Array of bus flags for the corresponding fetched frames.
 * @param checksum      Array of checksums for the corresponding fetched frames.
 * @param size          Input/Output parameter. On input, number of BLC_FRAMEs to be fetched, which
 *                      must be a positive value.
 * @return              The actual number of retrieved BLC_FRAMEs, which might be less than *size on
 *                      input. Status of operation; '=0' means successful, '!=0' otherwise. See
 *                      standard return values for error, or for textual representation (for return
 *                      values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextFrames(BL_HANDLE handle,
                                     unsigned long chId[],
                                     unsigned long timestamp[],
                                     long intime[],
                                     unsigned long frameId[],
                                     unsigned char lenOfData[],
                                     unsigned char frameData[],
                                     short frameFlags[],
                                     short busFlags[],
                                     unsigned char checksum[],
                                     int* size);

/** @brief Fetches the next frame on Channel from the receiver queue with wait-timeout
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * Retrieves the next frame received from the BabyLIN. If no frame-data is available, the function
 * will wait _up to_ timeout_ms milliseconds for new data before it returns with a BL_TIMEOUT return
 * code.
 *
 * @param handle    Handle representing the channel to get the frame data from (see @ref
 *                  BLC_getChannelHandle )
 * @param chId      The channel id, the frame came in at.
 * @param timestamp The timestamp given the frame from the device as described in the @ref BLC_FRAME
 *                  struct.
 * @param intime    The PC time when the frame came in as described in the @ref BLC_FRAME struct.
 * @param frameId   The frame id as described in the @ref BLC_FRAME struct.
 * @param lenOfData The length of the frame data array.
 * @param frameData Pointer to a preallocated array that will be filled with the frame data.
 * @param frameFlags The frame flags as described in the @ref BLC_FRAME struct.
 * @param busFlags  The bus specific flags as described in the @ref BLC_FRAME struct.
 * @param checksum only valid for LIN channels the frames checksum byte.
 * @param timeout_ms Timeout to wait for new framedata.
 *
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextFrameTimeout(BL_HANDLE handle,
                                           unsigned long* chId,
                                           unsigned long* timestamp,
                                           long* intime,
                                           unsigned long* frameId,
                                           unsigned char* lenOfData,
                                           unsigned char* frameData,
                                           short* frameFlags,
                                           short* busFlags,
                                           unsigned char* checksum,
                                           int timeout_ms);

/** @brief Fetches the next frames on Channel from the receiver queue with wait-timeout
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * Retrieves the next frame received from the BabyLIN. If no frame-data is available, the function
 * will wait _up to_ timeout_ms milliseconds before new data before it returns with a BL_TIMEOUT
 * return code.
 *
 * @param handle        Handle representing the channel to get the frame data from (see @ref
 *                      BLC_getChannelHandle )
 * @param chId          Array of channel identifiers for the corresponding fetched frames.
 * @param timestamp     Array of timestamps for the corresponding fetched frames.
 * @param intime        Array of arrival timestamps for the corresponding fetched frames.
 * @param frameId       Array of frame identifiers for the corresponding fetched frames.
 * @param lenOfData     Array of data lengths for the data of of the corresponding fetched frames.
 * @param frameData     Array of frame data arrays for the corresponding fetched frames.
 * @param frameFlags    Array of frame flags for the corresponding fetched frames.
 * @param busFlags      Array of bus flags for the corresponding fetched frames.
 * @param checksum      Array of checksums for the corresponding fetched frames.
 * @param timeout_ms    Timeout to wait for new framedata
 * @param size          Input/Output parameter. On input, number of BLC_FRAMEs to be fetched, which
 *                      must be a positive value. On output, the actual number of retrieved
 *                      BLC_FRAMEs, which might be less than *size on input.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextFramesTimeout(BL_HANDLE handle,
                                            unsigned long chId[],
                                            unsigned long timestamp[],
                                            long intime[],
                                            unsigned long frameId[],
                                            unsigned char lenOfData[],
                                            unsigned char frameData[],
                                            short frameFlags[],
                                            short busFlags[],
                                            unsigned char checksum[],
                                            int timeout_ms,
                                            int* size);

/** @brief Fetches the next jumbp frame on Channel from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * @param handle    Handle representing the channel to get the frame data from (see @ref
 *                  BLC_getChannelHandle )
 * @param chId      The channel id, the frame came in at.
 * @param timestamp The timestamp given the frame from the device as described in the @ref BLC_FRAME
 *                  struct.
 * @param intime    The PC time when the frame came in as described in the @ref BLC_JUMBO_FRAME
 *                  struct.
 * @param frameId   The frame id as described in the @ref BLC_JUMBO_FRAME struct.
 * @param lenOfData The length of the frame data array.
 * @param frameData Pointer to a preallocated array to be filled witht he frame data.
 * @param frameFlags The frame flags as described in the @ref BLC_JUMBO_FRAME struct.
 * @param busFlags  The bus specific flags as described in the @ref BLC_JUMBO_FRAME struct.
 * @param checksum  Only valid for LIN channels the frames checksum byte.
 * @return Status   of operation; '=0' means successful, '!=0' otherwise. See standard return values
 *                  for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */

int BL_DLLIMPORT BLCns_getNextJumboFrame(BL_HANDLE handle,
                                         unsigned long* chId,
                                         unsigned long* timestamp,
                                         long* intime,
                                         unsigned long* frameId,
                                         unsigned int* lenOfData,
                                         unsigned char* frameData,
                                         short* frameFlags,
                                         short* busFlags,
                                         unsigned char* checksum);

/** @brief Fetches the next jumbo frames on Channel from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * @param handle        Handle representing the channel to get the frame data from (see @ref
 *                      BLC_getChannelHandle )
 * @param chId          Array of channel identifiers for the corresponding fetched frames.
 * @param timestamp     Array of timestamps for the corresponding fetched frames.
 * @param intime        Array of arrival timestamps for the corresponding fetched frames.
 * @param frameId       Array of frame identifiers for the corresponding fetched frames.
 * @param lenOfData     Array of data lengths for the data of of the corresponding fetched frames.
 * @param frameData     Array of frame data arrays for the corresponding fetched frames.
 * @param frameFlags    Array of frame flags for the corresponding fetched frames.
 * @param busFlags      Array of bus flags for the corresponding fetched frames.
 * @param checksum      Array of checksums for the corresponding fetched frames.
 * @param size          Input/Output parameter. On input, number of  BLC_JUMBO_FRAME to be fetched,
 *                      which must be a positive value.
 * @return              The actual number of retrieved BLC_JUMBO_FRAMEs, which might be less than
 *                      *size on input. Status of operation; '=0' means successful, '!=0' otherwise.
 *                      See standard return values for error, or for textual representation (for
 *                      return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextJumboFrames(BL_HANDLE handle,
                                          unsigned long chId[],
                                          unsigned long timestamp[],
                                          long intime[],
                                          unsigned long frameId[],
                                          unsigned int lenOfData[],
                                          unsigned char frameData[],
                                          short frameFlags[],
                                          short busFlags[],
                                          unsigned char checksum[],
                                          int* size);

/** @brief Fetches the next jumbo frame on Channel from the receiver queue with wait-timeout
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * Retrieves the next jumbo frame received from the BabyLIN. If no frame-data is available, the
 * function will wait _up to_ timeout_ms milliseconds for new data before it returns with a
 * BL_TIMEOUT return code.
 *
 * @param handle    Handle representing the channel to get the frame data from (see @ref
 *                  BLC_getChannelHandle )
 * @param chId      The channel id, the frame came in at.
 * @param timestamp The timestamp given the frame from the device as described in the @ref BLC_FRAME
 *                  struct.
 * @param intime    The PC time when the frame came in as described in the @ref BLC_JUMBO_FRAME
 *                  struct.
 * @param frameId   The frame id as described in the @ref BLC_JUMBO_FRAME struct.
 * @param lenOfData The length of the frame data array.
 * @param frameData Pointer to a preallocated array that will be filled with the frame data.
 * @param frameFlags The frame flags as described in the @ref BLC_JUMBO_FRAME struct.
 * @param busFlags  The bus specific flags as described in the @ref BLC_JUMBO_FRAME struct.
 * @param checksum  Only valid for LIN channels the frames checksum byte.
 * @param timeout_ms Timeout to wait for new framedata.
 *
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextJumboFrameTimeout(BL_HANDLE handle,
                                                unsigned long* chId,
                                                unsigned long* timestamp,
                                                long* intime,
                                                unsigned long* frameId,
                                                unsigned int* lenOfData,
                                                unsigned char* frameData,
                                                short* frameFlags,
                                                short* busFlags,
                                                unsigned char* checksum,
                                                int timeout_ms);

/** @brief Fetches the next jumbo frames on Channel from the receiver queue with wait-timeout
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Device fills the receiver queue only if command "disframe" or "mon_on" is sent
 * before.
 *
 * Retrieves the next frame received from the BabyLIN. If no frame-data is available, the function
 * will wait _up to_ timeout_ms milliseconds before new data before it returns with a BL_TIMEOUT
 * return code.
 *
 * @param handle     Handle representing the channel to get the frame data from (see @ref
 *                   BLC_getChannelHandle )
 * @param chId       Array of channel identifiers for the corresponding fetched frames.
 * @param timestamp  Array of timestamps for the corresponding fetched frames.
 * @param intime     Array of arrival timestamps for the corresponding fetched frames.
 * @param frameId    Array of frame identifiers for the corresponding fetched frames.
 * @param lenOfData  Array of data lengths for the data of of the corresponding fetched frames.
 * @param frameData  Array of frame data arrays for the corresponding fetched frames.
 * @param frameFlags Array of frame flags for the corresponding fetched frames.
 * @param busFlags   Array of bus flags for the corresponding fetched frames.
 * @param checksum   Array of checksums for the corresponding fetched frames.
 * @param timeout_ms Timeout to wait for new framedata
 * @param size       Input/Output parameter. On input, number of BLC_JUMBO_FRAMEs to be fetched,
 *                   which must be a positive value. On output, the actual number of retrieved
 *                   BLC_JUMBO_FRAMEEs, which might be less than *size on input.
 *
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextJumboFramesTimeout(BL_HANDLE handle,
                                                 unsigned long chId[],
                                                 unsigned long timestamp[],
                                                 long intime[],
                                                 unsigned long frameId[],
                                                 unsigned int lenOfData[],
                                                 unsigned char frameData[],
                                                 short frameFlags[],
                                                 short busFlags[],
                                                 unsigned char checksum[],
                                                 int timeout_ms,
                                                 int* size);

/** @brief Fetches the next signal from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 * @param handle    Handle representing the channel to get the signal data from (see @ref
 *                  BLC_getChannelHandle )
 * @param index     The signal number of the received signal.
 * @param isArray   != 0 if the signal is marked as array signal.
 * @param value     The signal value for non array signals only.
 * @param arrayLength The length of the given array and the amount of bytes copied into it.
 * @param array     The signal data of array signals.
 * @param timestamp The timestamp given the signal report by the device.
 * @param chId      The id of the channel that did report the signal value.
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextSignal(BL_HANDLE handle,
                                     int* index,
                                     int* isArray,
                                     unsigned long long* value,
                                     int* arrayLength,
                                     unsigned char* array,
                                     unsigned long* timestamp,
                                     unsigned short* chId);

/** @brief Fetches the next signals from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 * @param handle        Handle representing the channel to get the signal data from (see @ref
 *                      BLC_getChannelHandle )
 * @param index         Output parameter: array of indices of the corresponding retrieved signals.
 * @param isArray       Output parameter: array of boolean values, indicating if the corresponding
 *                      retrieved signal is an array.
 * @param value         Output parameter: array of signal values for the corresponding retrieved
 *                      signals.
 * @param arrayLength   Output parameter: array of array lengths for the data arrays contained in
 *                      the retrieved signals.
 * @param array         Output parameter: array of 8*(*size) bytes, containing for each retrieved
 *                      signal an 8-byte data array if the resp. array length is greater 0.
 * @param timestamp     Output parameter: array of timestamps for the corresponding retrieved
 *                      signals.
 * @param chId          Output parameter: array of channel identifiers for the corresponding
 *                      retreived signals.
 * @param size          Input/Output parameter. On input, number of BLC_SIGNAL to  be fetched, which
 *                      must be a positive value. On output, the actual number of retrieved
 *                      BLC_SIGNALs, which might be less than *size on input.
 *
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextSignals(BL_HANDLE handle,
                                      int index[],
                                      int isArray[],
                                      unsigned long long value[],
                                      int arrayLength[],
                                      unsigned char array[],
                                      unsigned long timestamp[],
                                      unsigned short chId[],
                                      int* size);

/** @brief Fetches the next signals for a signal number from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 * @attention The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 *  @param handle       Handle representing the channel to get the signal data from (see @ref
 *                      BLC_getChannelHandle )
 *  @param index        Output parameter: array of indices of the corresponding retrieved signals.
 *  @param isArray      Output parameter: array of boolean values, indicating if the corresponding
 *                      retrieved signal is an array.
 *  @param value        Output parameter: array of signal values for the corresponding retrieved
 *                      signals.
 *  @param arrayLength  Output parameter: array of array lengths for the data arrays contained in
 *                      the retrieved signals.
 *  @param array        Output parameter: array of 8*(*size) bytes, containing for each retrieved
 *                      signal an 8-byte data array if the resp. array length is greater 0.
 *  @param timestamp    Output parameter: array of timestamps for the corresponding retrieved
 *                      signals.
 *  @param chId         Output parameter: array of channel identifiers for the corresponding
 *                      retrieved signals.
 *  @param size         Input/Output parameter. On input, number of BLC_SIGNAL to be fetched, which
 *                      must be a positive value. On output, the actual number of retrieved
 *                      BLC_SIGNALs, which might be less than *size on input.
 *  @param signalNumber The signal number to return signals for
 *  @return             Status of operation; '=0' means successful, '!=0' otherwise.
 *                      See standard return values for error, or for textual
 *                      representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextSignalsForNumber(BL_HANDLE handle,
                                               int index[],
                                               int isArray[],
                                               unsigned long long value[],
                                               int arrayLength[],
                                               unsigned char array[],
                                               unsigned long timestamp[],
                                               unsigned short chId[],
                                               int size,
                                               int signalNumber);

/** @brief Fetches the next Bus error from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 * @param handle    Handle representing the channel to get the error data from (see @ref
 *                  BLC_getChannelHandle )
 * @param timestamp The timestamp when the error was recorded by the device.
 * @param type      The error type.
 * @param status    The error status.
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextBusError(BL_HANDLE handle,
                                       unsigned long* timestamp,
                                       unsigned short* type,
                                       unsigned short* status);

/** @brief Fetches the next complete DTL request from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 * @param handle    Handle representing the channel to get the DTL data from (see @ref
 *                  BLC_getChannelHandle )
 * @param status    The DTL status.
 * @param nad       The NAD of that DTL request.
 * @param length    The length of the DTL data, has to hold the length of the preallocated data
 *                  buffer.
 * @param data      The DTL data, has to be preallocated.
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextDTLRequest(
    BL_HANDLE handle, BL_DTL_STATUS* status, unsigned char* nad, int* length, unsigned char* data);

/** @brief Fetches the next complete DTL response from the receiver queue.
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 *  @param handle   Handle representing the channel to get the DTL data from (see @ref
 *                  BLC_getChannelHandle )
 * @param status    The DTL status.
 * @param nad       The NAD of that DTL response.
 * @param length    The length of the DTL data, has to hold the length of the  preallocated data
 *                  buffer.
 * @param data      The DTL data, has to be preallocated.
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getNextDTLResponse(
    BL_HANDLE handle, BL_DTL_STATUS* status, unsigned char* nad, int* length, unsigned char* data);

/** @brief Retrieve further Information about a loaded SDF
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 * Need a loaded SDF (see @ref BLC_loadSDF or @ref BLC_loadLDF )
 * @param handle        Handle to a valid connection
 * @param filename      The loaded SDFs file name.
 * @param sectionCount  The amount of sections in that SDF.
 * @param version_major The SDFs major version.
 * @param version_minor The SDFs minor version.
 * @return              Status of operation; '=0' means successful, '!=0' otherwise. See standard
 *                      return values for error, or for textual representation (for return values <
 *                      -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLCns_getSDFInfo(BL_HANDLE handle,
                                  char* filename,
                                  short* sectionCount,
                                  short* version_major,
                                  short* version_minor);

/** @brief Retrieve informations about a SDF-Section from a loaded SDF
 *
 * @attention This function is required by certain BabyLIN Wrappers.
 * @attention It is strongly recommended, that it is not used in C/C++ applications.
 *
 * @param handle    handle of a valid connection
 * @param infoAboutSectionNr The section number to retrieve information of. Ranges from 0 to the
 *                  number of sections in the loaded SDF (see @ref BLC_getSDFInfo and @ref
 *                  BLC_SDFINFO.sectionCount )
 * @param name      The sections name.
 * @param type      The section type e.g. LIN.
 * @param nr        The section number.
 * @return          Status of operation; '=0' means successful, '!=0' otherwise. See standard return
 *                  values for error, or for textual representation (for return values < -1000) @ref
 *                  BLC_getLastError.
 */
int BL_DLLIMPORT
BLCns_getSectionInfo(BL_HANDLE handle, int infoAboutSectionNr, char* name, int* type, short* nr);

#if defined(__cplusplus)
}  // extern "C"
#endif
#endif  // BABYLINCAN_NOSTRUCT_H
