#ifndef BABYLINCAN_TYPES_H
#define BABYLINCAN_TYPES_H

#include "BabyLINReturncodes.h"

/** @addtogroup structures
 *  @brief List of BabyLIN structures
 *
 *  The following structures are used to retrieve data from a running BabyLIN device like frame- and
 * signal-reports or error and debug information
 *  @{
 */

/** @brief Information about a BabyLIN port on the host operating system
 *
 * The structure holds information about a BabyLIN device connected to the PC Use @ref
 * BLC_getBabyLinPorts to retrieve a list of connected BabyLIN-Devices
 *
 * */
typedef struct _BLC_PORTINFO {
  /** @brief The COM-port number the device is connected to (windows only), use this value for
   * BLC_open. For Network devices this is the TCP port to connect to.
   */
  int portNr;
  /** @brief The type of interface of the connected device (0=USBSerial, 1=Not Connectable(Network
   * UDP), 2=Network TCP).
   *
   * Devices of type 1 can not be Connected to via BLC_open...(...).
   */
  int type;
  /** @brief The name of the connected device (f.ex. BabyLIN RM-II). For Network devices this is the
   * hostname of the device.
   */
  char name[256];
  /** @brief The linux device file the BabyLIN is connected to (linux only) For Network devices this
   * is the ip in dot notation.
   */
  char device[256];
} BLC_PORTINFO;

/** @brief Information about a connected BabyLIN device
 *
 * The structure holds information about a connected BabyLIN device retreive informations using
 * @ref BLC_getTargetID or request by using @ref BLC_sendCommand with command "targetid"
 *
 */
typedef struct _BLC_TARGETID {
  /** @brief Type of the hardware
   *
   * | Value | Device |
   * |------:|--------|
   * |0x100  |Baby-LIN|
   * |0x102  |Baby-LIN-RC |
   * |0x103  |Baby-LIN-KS01 |
   * |0x200  |Baby-LIN-RM |
   * |0x510  |Baby-LIN-MB |
   * |0x300  |HARP |
   * |0x503  |Baby-LIN-II |
   * |0x501  |Baby-LIN-RC-II |
   * |0x500  |Baby-LIN-RM-II |
   * |0x700  |Baby-LIN-MB-II |
   * |0x502  |HARP-4 |
   * |0x511  |HARP-5 |
   * |0x508  |Baby-LIN-RM-III |
   * |0x509  |Baby-LIN-RC-II-B |
   * |0x504  |MIF_LIN-II |
   * |0x507  |MIF_CAN_FD |
   * |0x600  |Virtual_CAN |
   * */
  unsigned short type;

  // ! Firmware version of the device
  unsigned short version;

  // ! Firmware build number
  unsigned short build;

  /** @brief Software related flags
   *
   * |Value|Description|
   * |----:|:----------|
   * |0x01 |Testversion|
   * */
  unsigned short flags;

  // ! Device's serial number
  long serial;

  // ! Remaining heap size on device (memory available for SDF dowload)
  long heapsize;

  // ! number of channels
  long numofchannels;

  // ! Textual name of the device (zero-terminated C-string)
  char name[128];
} BLC_TARGETID;

/**
 * @brief Information about a channel on a BabyLIN device
 *
 * Return data of the command '@ref BLC_getChannelInfo' providing information about a channel
 * (BUS-type, speed etc.)
 */
typedef struct _BLC_CHANNELINFO {
  /// Channel-id(i.e. 0 = device channel)
  unsigned short id;

  /// Channel-Type(i.e. 0 = LIN, 1 = CAN, 99 = DEVICE)
  unsigned short type;

  /// Textual name of the Channel (zero-terminated C-string)
  char name[128];

  /// Maximum Baudrate of Channel
  long maxbaudrate;

  /**
   * @brief Flags describing the State of the Channel.
   *
   * Bit0 : Indicates, whether the channel is disabled, due to missing licences.<br>
   * Bit1 : Indicates, that SDFs of version 3 may be uploaded onto this Channel.<br>
   * Bit2 : Deprecated: ignore the state of this bit.<br>
   * Bit3 : Indicates, that the Channel is initialized (SDF/Section was loaded or Monitor Mode is
   * active).<br>
   * Bit4 : Indicates, that the channel has the ability and license to send and receive
   * CAN FD frames.<br>
   * Bit5 : Indicates, that the channel has the ability and license to send and
   * receive CAN HS frames.<br>
   * Bit6 : Indicates, that the channel has the ability and license to
   * send and receive CAN LS frames.
   *
   * @remark Some bits may not be set by older firmware version.<br>Please consider a firmware
   * update.
   */
  long reserved1;

  /// Reserved value (ignore for now)
  long reserved2;

  /// Reserved value (ignore for now)
  long reserved3;

  /// the number of the section of the loaded sdf associated with this channel >= 0 means valid
  /// section number, -1: no mapping or no sdf loaded
  int associatedWithSectionNr;
} BLC_CHANNELINFO;

// ! Return data of the command @ref BLC_getSDFInfo
typedef struct _BLC_SDFINFO {
  // ! Filename of the loaded sdf
  char filename[256];

  // ! number of sections in the SDF. A file consists of at least one Section (LIN, CAN or DEVICE)
  short sectionCount;

  // ! SDF-version
  short version_major, version_minor;
} BLC_SDFINFO;

// ! Return data of the command @ref BLC_getSectionInfo
typedef struct _BLC_SECTIONINFO {
  // ! Textual name of the Section (zero-terminated C-string) as defined using SessionConf
  char name[128];

  // ! Channel-Type(i.e. 0 = LIN, 1 = CAN, 99 = DEVICE)
  int type;

  // ! Number of the section within the SDF ( zero-based index )
  short nr;
} BLC_SECTIONINFO;

// ! Carries information about one frame, is used as API interface
typedef struct _BLC_FRAME {
  // ! Id of the channel within the device
  unsigned long chId;

  // ! Global time index of frame transmission start (in us). Received from target, represents the
  // time since the Target was powered on.
  unsigned long timestamp;

  // ! Timestamp with pc time, used to calculate age of framedata, to allow timeout functions (ms)
  long intime;

  // ! FrameID of Frame ( as appeared on the BUS. On LIN BUS without parity bits )
  unsigned long frameId;

  // ! Length of frameData
  unsigned char lenOfData;

  // ! Databytes of the frame
  unsigned char frameData[8];

  // clang-format off
  /** @brief Additional, informational frame flags
   *
   * Used as a bitfield, multiple flags possible
   * | Value | Description |
   * |------:|:------------|
   * | 0x01  | Frame has error|
   * | 0x02  | Frame is selfsent (sent by the BabyLIN-Device, because it simulates the corresponding node)|
   * | 0x04  | Timebase, if set, the unit of @ref timestamp is ms, otherwise us|
   * | 0x08  | The frame was a SDF specified frame |
   * | 0x10  | The frame was an injected frame |
   * | 0x20  | The frame was a protocol frame |
   **/
  // clang-format on
  short frameFlags;

  // clang-format off
  /** @brief Bus specific flags
   *
   * for LIN-BUS:
   * Used as a bitfield, multiple flags possible
   * | Value | Description |
   * |------:|:------------|
   * | 0x01  |Valid CLASSIC checksum (V1)|
   * | 0x02  |Valid EXTENDED checksum (V2)|
   * | 0x04  |incomplete frame without checksum, not an error|
   * | 0x08  |Errorframe (f.ex: no data)|
   * | 0x10  |Frame is slave response to a master request. If set, the upper 3 bits of flags denote a master request id|
   * | 0x20  |Event triggered frame (only if 0x10 is not set )|
   * | 0x1C0 |Master request ID|
   * | 0x600 |Frame Type: 0: regular LIN, 1: KLine Raw, 2: KLine Webasto
   *
   * for CAN-BUS:
   * Used as a bitfield, multiple flags possible
   * | Value | Description |
   * |------:|:------------|
   * | 0x01 |29 bit frame identifier|
   * | 0x06 |Frame Type: 0: regular CAN, 1: CAN-FD, 2: CAN-FD with bitrate switching|
   * */
  // clang-format on
  short busFlags;

  /** @brief Checksum of the frame
   * stores a checksum V1 or V2 ( refer to busFlags which checksum type applies )
   */
  unsigned char checksum;
} BLC_FRAME;

// ! Carries information about one frame, is used as API interface
typedef struct _BLC_JUMBO_FRAME {
  // ! Id of the channel within the device
  unsigned long chId;

  // ! Global time index of frame transmission start (in us). Received from target, represents the
  // time since the Target was powered on.
  unsigned long timestamp;

  // ! Timestamp with pc time, used to calculate age of framedata, to allow timeout functions (ms)
  long intime;

  // ! FrameID of Frame ( as appeared on the BUS. On LIN BUS without parity bits )
  unsigned long frameId;

  // ! Length of frameData
  unsigned int lenOfData;

  // ! Databytes of the frame
  unsigned char frameData[1024];

  // clang-format off
  /** @brief Additional, informational frame flags
   *
   * Used as a bitfield, multiple flags possible
   * | Value | Description |
   * |------:|:------------|
   * | 0x01  | Frame has error|
   * | 0x02  | Frame is selfsent (sent by the BabyLIN-Device, because it simulates the corresponding node)|
   * | 0x04  | Timebase, if set, the unit of @ref timestamp is ms, otherwise us|
   * | 0x08  | The frame was a SDF specified frame |
   * | 0x10  | The frame was an injected frame |
   * | 0x20  | The frame was a protocol frame |
   * | 0x40  | The frame was not actually on the bus, only been mapped as its a SDF like inject |
   **/
  // clang-format on
  short frameFlags;

  // clang-format off
  /** @brief Bus specific flags
   *
   * for LIN-BUS:
   * Used as a bitfield, multiple flags possible
   * | Value | Description |
   * |------:|:------------|
   * | 0x01  |Valid CLASSIC checksum (V1)|
   * | 0x02  |Valid EXTENDED checksum (V2)|
   * | 0x04  |incomplete frame without checksum, not an error|
   * | 0x08  |Errorframe (f.ex: no data)|
   * | 0x10  |Frame is slave response to a master request. If set, the upper 3 bits of flags denote a master request id|
   * | 0x20  |Event triggered frame ( only if 0x10 is not set )|
   * | 0x1C0 |Master request ID|
   * | 0x600 |Frame Type: 0: regular LIN, 1: KLine Raw, 2: KLine Webasto|
   *
   * for CAN-BUS:
   * Used as a bitfield, multiple flags possible
   * | Value | Description |
   * |------:|:------------|
   * | 0x01 |29 bit frame identifier|
   * | 0x06 |Frame Type: 0: regular LIN, 1: CAN-FD, 2: CAN-FD with bitrate switching|
   **/
  // clang-format on
  short busFlags;

  /** @brief checksum of the frame
   * stores a checksum V1 or V2 ( refer to busFlags which checksum type applies )
   */
  unsigned char checksum;
} BLC_JUMBO_FRAME;

/**
 * @brief status of a macro
 *
 * Information about a macro, used as parameter of a callback function registered by @ref
 * BLC_registerMacroStateCallback
 * */
typedef struct _BLC_MACROSTATE {
  // ! channel number this information belongs to
  int channelid;

  /** @brief Macro-number the information is about
   * */
  int macronr;

  /** @brief The macro command number currently executed
   *
   * denotes the command-number in the macro @ref macronr which is currently executed
   *
   * valid if @ref state denotes a running macro
   * */
  int cmdnr;

  /**
   * @brief state of the macro execution
   *
   * |Value|Description|
   * |----:|:----------|
   * |0x00 |Macro execution ended|
   * |0x01 |Macro execution started|
   * |0x02 |Macro execution running|
   * |0x03 |Macro execution error|
   */
  int state;

  /**
   * @brief Timestamp of the macro state
   * @remark Previous BabyLIN DLL v10.22.0 this value was long!
   *         We recommend to recompile your app using BabyLIN library if you have linked against a
   * version previous v10.22.0.
   */
  unsigned long timestamp;
} BLC_MACROSTATE;

// ! Carries information about one signal.
typedef struct _BLC_SIGNAL {
  // ! Index number of signal; see the SDF for the adequate number
  int index;
  // ! Defines whether this signal is a normal, value-based one (0) or LIN2.0 array signal (1).
  int isArray;
  // ! Value of the signal.
  unsigned long long value;
  // ! Length of the array.
  int arrayLength;
  // ! Value(s) of the signal, if isArray == 1.
  unsigned char array[8];
  // ! Global time index of frame transmission start (in usec).
  unsigned long timestamp;
  // ! Current Channelid
  unsigned short chId;
} BLC_SIGNAL;

/* clang-format off */
// ! Represents a BUS error message
typedef struct _BLC_ERROR{
  /** @brief Time of occurence.
   * The timestamp when the error occurred.
   *
   * device-timstamp in us if error @ref type is a device error (1-16)
   *
   * pc timestamp in ms if error @ref type is dll error (65535)
   * */
  unsigned long timestamp;
  /** @brief Error type
   *
   * | Value | Name | Description | Status |
   * |------:|:-----|:------------|:-------|
   * |1|ERRTYPE_ID|Parity error in ID||
   * |2|ERRTYPE_DATA|Read data from BUS does not match send data|Frame-ID|
   * |3|ERRTYPE_FRAMING|Framing error in data reception|Frame-ID|
   * |4|ERRTYPE_CHECKSUM|Checksum failed|Frame-ID|
   * |5|ERRTYPE_DATATO|Data timed out (incomplete msg reception)|Frame-ID|
   * |6|ERRTYPE_SEQ|Unexpected state sequencing|internal status|
   * |8|ERRTYPE_MACRO|Error in macro execution|internal status|
   * |9|ERRTYPE_BUSBUSY|Bus is already used|internal status|
   * |10|ERRTYPE_BUSOFF|Bus is offline (no bus power) |internal status|
   * |11|ERRTYPE_BUSSPEED_DIFFERS|Actual bus-speed differs from LDF bus speed (Warning) |actual speed|
   * |12|ERRTYPE_RX_FRAME_LEN|Frame length error|Frame-ID|
   * |13|ERRTYPE_RX_INCOMPLETE|Incomplete frame received|Frame-ID|
   * |14|ERRTYPE_RESP_LOST|Response send buffer overflow occured|unused|
   * |15|ERRTYPE_CAN_NOERR|CAN error disappeared|unused|
   * |16|ERRTYPE_CAN_ERR|CAN error| bitmap 0x01 noAck<br>bitmap 0x02 stuffing error<br>bitmap 0x04 framing error<br>bitmap 0x08 recessive bit error<br>bitmap 0x10 dominant bit error<br>bitmap 0x20 checksum error|
   * |17|ERRTYPE_FRAME_ERR|A received Frame does not match its definition in the SDF|The Frame number in the SDF|
   * |18|ERRTYPE_LIN_SHORT_GND|LIN master Bus Low level too lang (master pull-up destroying danger)|unused|
   * |19|ERRTYPE_INTERNAL_OVERFLOW|Queue overflow of an internal buffer/queue|internal status|
   * |20|ERRTYPE_FLASH_SDF_LOAD|Error while loading SDF from persistent memory|internal status|
   * |21|ERRTYPE_TX_HEADER_FAIL|An error occurred during the sending of a frame header|Frame-ID|
   * |22|ERRTYPE_NO_CANPHY_SELECT|Bus was started without an activated CAN-Transceiver||
   * |23|ERRTYPE_SLAVE_PROTOCOL_TIMEOUT|Slave protocol timeout||
   * |24|ERRTYPE_CAN_STUFFERR|A CAN stuff error occurred||
   * |25|ERRTYPE_CAN_FORMERR|A CAN form error occurred||
   * |26|ERRTYPE_CAN_ACKERR|A CAN ack error occurred||
   * |27|ERRTYPE_CAN_RECESSIVEBITERR|A CAN bit recessive error occurred||
   * |28|ERRTYPE_CAN_DOMINANTBITERR|A CAN bit dominant error occurred||
   * |29|ERRTYPE_CAN_CRCERR|A CAN CRC error occurred||
   * |30|ERRTYPE_CAN_SETBYSWERR|A CAN frame can't be send on the bus||
   * |31|ERRTYPE_CAN_BUSOFF|The CAN Bus is off||
   * |32|ERRTYPE_SDF_LOG_COMMAND|Log file error|0=An internal error occurred<br>1=The log command is unknown<br>2=The log command has too few parameters<br>3=The log command has too many parameters<br>4=The log file handle is invalid<br>10=A parameter is invalid<br>11=The first parameter is mandatory<br>12=The first parameter is no unsigned integer<br>13=The first parameter is no handle<br>14=The first parameter is no valid handle<br>21=The second parameter is mandatory<br>22=The second parameter is no unsigned integer<br>23=The second parameter is no handle<br>24=The second parameter is no valid handle<br>31=The third parameter is mandatory<br>32=The third parameter is no unsigned integer<br>33=The third parameter is no handle<br>34=The third parameter is no valid handle<br>100=Could not create log file<br>101=Could not close log file<br>102=Could not start log file<br>103=Could not stop log file<br>104=Could not pause log file<br>105=Could not resume log file<br>106=Could not write to file|
   * |33|ERRTYPE_SD_SDF_LOAD|The SDF could not be loaded from the SD card||
   * |34|ERRTYPE_PROTOCOL_DEFINITION|Error on protocol definition|0=Error on CAN ID size<br>1=CAN flags mismatch<br>2=frame size too large|
   * |35|ERRTYPE_PROTOCOL_SLAVE|Error on slave protocol||
   * |36|ERRTYPE_PROTOCOL_MASTER|Error on master protocol|See macro error codes|
   * |256|ERRTYPE_WARN_CANFD_FRAME|Warning: CAN-FD baudrate and flags are inconsistent||
   * |257|ERRTYPE_WARN_MISSING_SYSCFG204|Warning: SYSCFG204 not defined||
   * |258|ERRTYPE_WARN_CANID_MULTIPLE_USE|CAN ID used in more than one frame definitions||
   * |512|ERRTYPE_SLAVE_PROTOCOL_SKIPPED_MIXED_PROTOCOLTYPES|Skipped execution of slave protocol||
   * |513|ERRTYPE_SLAVE_PROTOCOL_USE_FIRST|The first of multiple possible services is executed||
   * |514|ERRTYPE_LOGGER|A logging error occurred|0=No SD Card in device or no SD Card license<br>1=Log file number 99999 reached, please empty log directory<br>2=No free space on SD card<br>3=Can not open log file|
   * |999|ERRTYPE_RUNTIME_SDFCODES|A runtime error occurred in the SDF||
   * |61166|ERRTYPE_RUNTIME_DLLCONMBII|MB-II DLL-Connector error|1=Connection lost<br>2=Message lost<br>3=Message dropped|
   * |65535|ERRTYPE_RUNTIME_LIBRARY|Error in DLL occurred|1=Connection lost<br>2=Message lost<br>3=Message dropped<br>4=Message was no report and not an answer to a transaction<br>5=The Baby-LIN library was not active for more than 2s<br>6=The Baby-LIN library was not active for more than 3s<br>7=The Baby-LIN library was not active for more than 4s<br>8=The Baby-LIN library was not active for more than 5s|
   **/
  unsigned short type;
  /** @brief Additional error information
   *
   * Depends on @ref type descriptions.
   * for "dll status code":
   * |status|description|
   * |-----:|:----------|
   * |1|Lost connection to device|
   **/
  unsigned short status;
} BLC_ERROR;
/* clang-format on */

// ! Carries information about DTL protocol (both requests and responses).
typedef struct _BLC_DTL {
  // ! Status of protocol frame
  BL_DTL_STATUS status;

  // ! NAD of protocol frame
  unsigned char nad;

  // ! Length of the data-array.
  int length;
  // ! frame data, beginning with the (R)SID.
  unsigned char data[4 * 1024];
} BLC_DTL;

// ! Events from a device
typedef struct _BLC_EVENT {
  /** @brief Time of occurence.
   * The timestamp (of the device (us)) when the error occurred.
   * */
  unsigned int timestamp;
  /** @brief Time of occurence.
   * The timestamp (of the PC (ms)) when the error occurred.
   * */
  unsigned int pc_timestamp;
  /* clang-format off */
  /** @brief The event that occured
   *
   * | Value | Name | Description | data |
   * |------:|:-----|:------------|:-------|
   * |0|EVENTID_REBOOT|The device was rebootet.| |
   * |1|EVENTID_HWSTATE|The state of the LIN bus voltage has changed|0: LIN bus voltage missing.\n: LIN bus voltage detected.|
   * |3|EVENTID_DIRECT_MODE|||
   * |4|EVENTID_BOOTLOADER_START|The bootloader is starting after a reboot.|The second parameter contains the hardware type.|
   * |5|EVENTID_FIRMWARE_START|The firmware is starting after a reboot.|The second parameter contains the hardware type.|
   * |6|EVENTID_BUSSPEED_CHANGE|The bus speed has changed.|The second parameter is the bus speed.|
   * |7|EVENTID_ENLARGE_TIMEOUT_REQ|The firmware requests a change of the default timeout.|For internal use only.|
   * |8|EVENTID_REBOOT_TO_FOLLOW|Is sent before the device executes a reboot.||
   * |9|EVENTID_INJECTREJECT_BY_FRAMEID|An inject command was rejected.|A protocol with the same RX ID was actually executed.|
   * |10|EVENTID_DISCONNECT|Device disconnected from host.|The parameter contains the reason: 0: No command was received from the host and triggered a timeout. 1: A channel crashed and was reset.|
   * |999|EVENTID_RUNTIME_ERROR|A runtime error occurred.|The second parameter contains the error code.|
   */
  int event;
  /* clang-format on */
  /** @brief Additional information of an event
   */
  long long data;
} BLC_EVENT;

/**
 * @brief Type of an ad hoc protocol
 */
typedef enum {
  TYPE_RAW = 0,
  TYPE_DTL_ISOTP = 1,
  TYPE_ISOTP_WITHOUT_NAD = 2,
  TYPE_WEBASTO_UHW2 = 3,
  TYPE_WEBASTO_STD = 5,
  TYPE_KLINE_RAW = 6,
} ADHOC_PROTOCOL_TYPE;

typedef union {
  struct {
    // any value of PROTOCOL_TYPE
    // 0: Raw
    // 1: DTL/ISO-TP with NAD
    // 2: ISO-TP without NAD (CAN only)
    // 3: Webasto KLine UHW V2 (LIN only)
    // 4: Raw Jumbo (LIN only)
    // 5: Webasto KLine Standard (LIN only)
    //
    int protocoltype : 6;
    unsigned int unused_1 : 5;
    // shorten sf (single frame) on transmission
    unsigned int tx_shortensf : 1;
    // shorten last consecutive frame on transmission
    unsigned int tx_shortenlcf : 1;
    unsigned int unused_2 : 3;
    // if set a pos response has to fulfil RSID = SID | 0x40 rule other wise everything with
    // matching length is positive signals are mapped on positive Response only
    unsigned int use_std_posresp : 1;
    // interpret neg. response as 0x7f sid errorcode
    unsigned int use_std_negresp : 1;
    // this bit is set for a slave protocol definition
    unsigned int slaveprotocol : 1;
    // 0: no (Only full frames are accepted) Default bei V0
    // 1: yes (Only shortened frames are accepted)
    // 2: ignore, accept both (Full and shortened frames are accepted)
    unsigned int expect_shortenedsf : 2;
    // 0: no (Only full frames are accepted)
    // 1: yes (Only shortened frames are accepted)
    // 2: ignore, accept both (Full and shortened frames are accepted)  Default bei V0
    unsigned int expect_shortenedlcf : 2;
    unsigned int unused_3 : 5;
    // accept any containersize on reception
    unsigned int accept_any_csize : 1;
    // send shortened FloawCtrl frame (for CAN only)
    unsigned int xmit_shortenflowctrl : 1;
  } generic;

  struct {
    // See generic definition above.
    unsigned int protocoltype : 6;
    unsigned int unused_1 : 2;
    // classic or enhanced checksum
    unsigned int xmit_chksumtype : 1;
    // classic or enhanced checksum or both
    unsigned int expect_chksumtype : 2;
    // See generic definition above.
    unsigned int xmit_shortensf : 1;
    // See generic definition above.
    unsigned int xmit_shortenlcf : 1;
    unsigned int unused_2 : 3;
    // See generic definition above.
    unsigned int use_std_posresp : 1;
    // See generic definition above.
    unsigned int use_std_negresp : 1;
    // See generic definition above.
    unsigned int slaveprotocol : 1;
    // See generic definition above.
    unsigned int expect_shortenedsf : 2;
    // See generic definition above.
    unsigned int expect_shortenedlcf : 2;
    unsigned int unused_3 : 5;
    // See generic definition above.
    unsigned int accept_any_csize : 1;
    // See generic definition above.
    unsigned int xmit_shortenflowctrl : 1;
  } lin;
  struct {
    // See generic definition above.
    unsigned int protocoltype : 6;
    // use can FD baudswitch on transmission
    unsigned int xmit_canfd_switch : 1;
    // use can FD frame on transmission
    unsigned int xmit_canfd_frame : 1;
    // use can 29 bit frame id if set on transmission
    unsigned int xmit_can_11_29bit : 1;
    // expect can 29 bit frame id if set on reception
    unsigned int expect_can_11_29bit : 2;
    // shorten sf (single frame) on transmission
    unsigned int xmit_shortensf : 1;
    // shorten last consecutive frame on transmission
    unsigned int xmit_shortenlcf : 1;
    unsigned int unused_1 : 3;
    // See generic definition above.
    unsigned int use_std_posresp : 1;
    // See generic definition above.
    unsigned int use_std_negresp : 1;
    // See generic definition above.
    unsigned int slaveprotocol : 1;
    // See generic definition above.
    unsigned int expect_shortenedsf : 2;
    // 0: no (Only full frames are accepted)
    // 1: yes (Only shortened frames are accepted)
    // 2: ignore, accept both (Full and shortened frames are accepted)
    unsigned int expect_shortenedlcf : 2;
    // 0: no (Only CAN-FD frames without baudswitch are accepted)
    // 1: yes (Only CAN-FD frames with baudswitch are accepted)
    // 2: ignore, accept both (All CAN-FD frames are accepted)
    unsigned int expect_canfd_switch : 2;
    // 0: no (Only normal CAN frames are accepted)
    // 1: yes (Only CAN-FD frames are accepted)
    // 2: ignore, accept both (All CAN frames are accepted)
    unsigned int expect_canfd_frame : 2;
    // 1: don't wait for FlowControl on IsoTp transmissions
    unsigned int xmit_no_flowctrl_wait : 1;
    // See generic definition above.
    unsigned int accept_any_csize : 1;
    // See generic definition above.
    unsigned int xmit_shortenflowctrl : 1;

  } can;
} ADHOC_PROTOCOL_FLAGS;

// ! Ad-Hoc protocol
typedef struct _BLC_ADHOC_PROTOCOL {
  const char* name;

  ADHOC_PROTOCOL_FLAGS flags;

  unsigned char active;
  int req_slot_time;
  int rsp_slot_time;
  int rsp_delay;
  unsigned char fill_byte;
} BLC_ADHOC_PROTOCOL;

typedef union {
  struct {
    unsigned int unused_1 : 2;
    unsigned int unused_2 : 2;
    // shorten sf (single frame) on transmission
    // 0: no
    // 1: yes
    // 2: default from protocol
    unsigned int shortensf_txd : 2;
    // expect shorten sf (single frame) on reception
    // 0: no
    // 1: yes
    // 2: ignore
    unsigned int shortensf_rcv : 2;
    // shorten last consecutive frame on transmission
    // 0: no
    // 1: yes
    // 2: default from protocol
    unsigned int shortenlcf_txd : 2;
    // shorten last consecutive frame on reception
    // 0: no
    // 1: yes
    // 2: ignore
    unsigned int shortenlcf_rcv : 2;
    unsigned int unused_3 : 8;
    // if set a pos response has to fulfil RSID = SID | 0x40 rule other wise everything with
    // matching length is positive signals are mapped on positive Response only
    unsigned int use_std_posresp : 2;
    // interpret neg. response as 0x7f sid errorcode
    unsigned int use_std_negresp : 2;
    // Service does not expect a answer, if set
    unsigned int requestonly : 1;
    unsigned int unused_4 : 2;
    // accept any containersize on reception
    unsigned int accept_any_csize : 2;
    unsigned int unused_5 : 3;
  } generic;

  struct {
    // Checksum type for transmission
    // 0: classic
    // 1: enhanced
    // 2: protocol default
    unsigned int checksum_txd : 2;
    // Checksum type for reception
    // 0: classic
    // 1: enhanced
    // 2: ignore
    unsigned int checksum_rcv : 2;
    // See generic definition above.
    unsigned int shortensf_txd : 2;
    // See generic definition above.
    unsigned int shortensf_rcv : 2;
    // See generic definition above.
    unsigned int shortenlcf_txd : 2;
    // See generic definition above.
    unsigned int shortenlcf_rcv : 2;
    unsigned int unused_1 : 8;
    // See generic definition above.
    unsigned int use_std_posresp : 2;
    // See generic definition above.
    unsigned int use_std_negresp : 2;
    // See generic definition above.
    unsigned int requestonly : 1;
    unsigned int unused_2 : 2;
    // See generic definition above.
    unsigned int accept_any_csize : 2;
    unsigned int unused_3 : 3;
  } lin;
  struct {
    // CAN frame id type for transmission
    // 0: 11 Bit
    // 1: 29 Bit
    // 2: Protocol default
    unsigned int id_11_29_txd : 2;
    // CAN frame id type for reception
    // 0: 11 Bit
    // 1: 29 Bit
    // 2: ignore
    unsigned int id_11_29_rcv : 2;
    // See generic definition above.
    unsigned int shortensf_txd : 2;
    // See generic definition above.
    unsigned int shortensf_rcv : 2;
    // See generic definition above.
    unsigned int shortenlcf_txd : 2;
    // See generic definition above.
    unsigned int shortenlcf_rcv : 2;
    // CAN FD baudrate switching for transmission
    // 0: off
    // 1: on
    // 2: protocol default
    unsigned int fdbaudswitch_txd : 2;
    // CAN FD baudrate switching for reception
    // 0: off
    // 1: on
    // 2: ignore
    unsigned int fdbaudswitch_rcv : 2;
    // CAN FD frame for transmission
    // 0: off
    // 1: on
    // 2: protocol default
    unsigned int fdframe_txd : 2;
    // CAN FD frame for transmission
    // 0: off
    // 1: on
    // 2: ignore
    unsigned int fdframe_rcv : 2;
    // See generic definition above.
    unsigned int use_std_posresp : 2;
    // See generic definition above.
    unsigned int use_std_negresp : 2;
    // See generic definition above.
    unsigned int requestonly : 1;
    unsigned int no_flowctrl_wait : 2;

    // See generic definition above.
    unsigned int accept_any_csize : 2;
    unsigned int unused_1 : 3;
  } can;
} ADHOC_SERVICE_FLAGS;

// ! Ad-Hoc service
typedef struct {
  const char* name;
  ADHOC_SERVICE_FLAGS flags;

  int req_frame_id;
  long long req_container_size;
  long long req_payload_size;
  int req_slot_time;

  int rsp_frame_id;
  long long rsp_container_size;
  long long rsp_payload_size;
  int rsp_slot_time;
  int rsp_delay;
} BLC_ADHOC_SERVICE;

typedef struct {
  int nad;
  int p2_extended;
  int flow_control_st_min;
  int flow_control_block_size;
} BLC_ADHOC_EXECUTE;

// ! Carries information about one signal.
typedef struct _BLC_LOG {
  // ! Index number of signal; see the SDF for the adequate number
  int format_version;
  // ! (0) channel source: channel.id / channel.signal_index, (1) group source: group.id / group.sub_index 
  unsigned int source_type;
  // ! Information about the source of the log
  union {
    struct {
      // ! the channel id
      int id;
      // ! the signal id 
      int signal_index;
    } channel;
    struct {
      // ! the group id
      int id;
      // ! the sub index 
      int sub_index;
    } group;
  } source;

  // ! unix time index of the log (in sec).
  unsigned long long timestamp_unix;
  // ! Global time index of the log (in usec).
  unsigned long timestamp_usec;

  // ! Value type of the value content 0x0 unsigned, 0x1 signed
  unsigned int value_signed;
  // ! byte size of one element (possible values are one of {1, 2, 4, 8})
  unsigned int value_element_size;
  // ! array size of the value (is always greater then 0)
  unsigned int value_array_size;
  // ! values as single value if value_array_size == 1 or as array of values for value_array_size > 1 
  unsigned char value_data[4 * 1024];
} BLC_LOG;

/** @}*/

/** @addtogroup callback_handling Callback Handling
 *  @brief List of functions to manage callback functions
 *
 *  The following functions are used to register callback functions for a BabyLIN connection.
 *  A callback will be called whenever a corresponding message is received on the connection it is
 * registered to ( push method ). If you want to use a pull method to retrieve the data, have a look
 * at the @ref pull_handling section of the documentation
 *
 * The device, that generated the callback must not be closed from within the callback.
 *  @{
 */

// !these Callbacks will tell you the data(as done with old callbacks) AND the Channel which send
// the Data !to find out which Device send the data use => !BL_HANDLE hConnection =
// BLC_getConnectionOfChannel(BLC_CHANNEL hChannel);
typedef void(BLC_frame_callback_func)(BL_HANDLE, BLC_FRAME frame);
typedef void(BLC_jumboframe_callback_func)(BL_HANDLE, BLC_JUMBO_FRAME jumbo_frame);
typedef void(BLC_signal_callback_func)(BL_HANDLE, BLC_SIGNAL signal);
typedef void(BLC_macrostate_callback_func)(BL_HANDLE, BLC_MACROSTATE macroState);
typedef void(BLC_error_callback_func)(BL_HANDLE, BLC_ERROR error);
typedef void(BLC_debug_callback_func)(BL_HANDLE, const char* text);
typedef void(BLC_dtl_request_callback_func)(BL_HANDLE, BLC_DTL dtl_request);
typedef void(BLC_dtl_response_callback_func)(BL_HANDLE, BLC_DTL dtl_response);
typedef void(BLC_event_callback_func)(BL_HANDLE, BLC_EVENT event);

// !these Callbacks will tell you the data(as done with old callbacks), plus the Channel which send
// the Data and a user data pointer !added when registering the function !to find out which Device
// send the data use => !BL_HANDLE hConnection = BLC_getConnectionOfChannel(BLC_CHANNEL hChannel);
typedef void(BLC_frame_callback_func_ptr)(BL_HANDLE, BLC_FRAME frame, void*);
typedef void(BLC_jumboframe_callback_func_ptr)(BL_HANDLE, BLC_JUMBO_FRAME jumbo_frame, void*);
typedef void(BLC_signal_callback_func_ptr)(BL_HANDLE, BLC_SIGNAL signal, void*);
typedef void(BLC_macrostate_callback_func_ptr)(BL_HANDLE, BLC_MACROSTATE macroState, void*);
typedef void(BLC_error_callback_func_ptr)(BL_HANDLE, BLC_ERROR error, void*);
typedef void(BLC_debug_callback_func_ptr)(BL_HANDLE, const char* text, void*);
typedef void(BLC_dtl_request_callback_func_ptr)(BL_HANDLE, BLC_DTL dtl_request, void*);
typedef void(BLC_dtl_response_callback_func_ptr)(BL_HANDLE, BLC_DTL dtl_response, void*);
typedef void(BLC_event_callback_func_ptr)(BL_HANDLE, BLC_EVENT event, void*);
typedef void(BLC_log_callback_func_ptr)(BL_HANDLE, BLC_LOG log, void*);

typedef void(BLC_lua_print_func_ptr)(const char* msg, void* userdata);

#endif  // BABYLINCAN_TYPES_H
