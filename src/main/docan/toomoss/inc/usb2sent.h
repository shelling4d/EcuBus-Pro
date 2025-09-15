/**
 * @file usb2sent.h
 * @brief  USB转SENT相关函数
 * @author wdluo(wdluo@toomoss.com)
 * @version 1.0
 * @date 2022-10-04
 * @copyright Copyright (c) 2022 重庆图莫斯电子科技有限公司
 */
#ifndef __USB2SENT_H_
#define __USB2SENT_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif
 /**
  *@defgroup USB转SENT
  * @{
  * @brief USB转SENT接口函数和数据类型定义
 */

 /**
  *@name 函数返回错误值宏定义
  *@brief 函数调用出错后返回值定义
  *@{
 */
#define SENT_SUCCESS             (0)   ///<函数执行成功
#define SENT_ERR_NOT_SUPPORT     (-1)  ///<适配器不支持该函数
#define SENT_ERR_USB_WRITE_FAIL  (-2)  ///<USB写数据失败
#define SENT_ERR_USB_READ_FAIL   (-3)  ///<USB读数据失败
#define SENT_ERR_CMD_FAIL        (-4)  ///<命令执行失败
#define SENT_ERR_PARAMETER       (-5)  ///<函数参数传入有误
#define SENT_ERR_MSG_TYPE        (-6)  ///<当前函数不支持该消息类型
 /** @} */

/**
 *@name SENT主从模式
 *@brief SENT主从模式宏定义
 *@{
*/
#define SENT_MASTER         1   ///<主机模式，用于模拟主节点发送数据
#define SENT_SLAVE          0   ///<从机模式，用于监控SENT主机发送出来的数据
#define SENT_SPC            0x80///<使能SPC模式
#define SENT_SPC_SLAVE_TX   0x40///<使能SPC从机模式发送数据
/** @} */


/**
 *@name SENT消息类型
 *@brief SENT消息类型定义，该值在MsgType里面体现
 *@{
*/
#define SENT_MSGTYPE_ERROR          0       ///<错误帧，比如CRC错误，数据不完整等
#define SENT_MSGTYPE_FAST           1       ///<快速通道数据,数据存放在Data[0]~Data[7]里面，Status的高4位代表数据有效半字节数
#define SENT_MSGTYPE_SLOW_SHORT     2       ///<慢速通道，简短型串行信息,8位数据+4位ID,Data[0]为ID,Data[1]为数据
#define SENT_MSGTYPE_SLOW_ENH1      3       ///<慢速通道，增强型串行信息,12位数据+8位ID,Data[0]为ID，Data[1]为高4位数据,Data[2]为低8位数据
#define SENT_MSGTYPE_SLOW_ENH2      4       ///<慢速通道，增强型串行信息,16位数据+4位ID,Data[0]为ID，Data[1]为高8位数据,Data[2]为低8位数据
#define SENT_MSGTYPE_TX             0x80    ///<当前帧为发送数据帧
#define SENT_MSGTYPE_SPC            0x08    ///<当前帧为SPC模式帧
/** @} */

/**
 *@name SENT总线空闲电平
 *@brief SENT空闲模式下总线电平
 *@{
*/
#define SENT_IDLE_HIGH     1 ///<总线空闲时为高电平，数据输出低电平脉冲
#define SENT_IDLE_LOW      0 ///<总线空闲时为低电平，数据输出高电平脉冲
/** @} */

/**
 *@name SENT初始化结构体
 *@brief  SENT初始化结构定义
 */
typedef struct _SENT_CONFIG
{
    unsigned char   TicksTimeUs;    ///<Ticks时间，单位为us，一般为3
    unsigned char   MasterMode;     ///<0-从机模式，用于监控SENT总线数据，1-主机模式，用于发送SENT总线数据，bit[7]-使能SPC模式，bit[6]-使能SPC从机响应数据模式
    unsigned char   LowTicks;       ///<低电平输出Ticks数，低电平输出时间=TicksTimeUs*LowTicks，推荐设置为5
    unsigned char   PausePulseTicks;///<暂停脉冲数，0-不输出，1~64对应12Ticks~768Ticks,0xFF-自动长度，但是最小为12Ticks
    unsigned char   NibbleNum;      ///<快速通道半字节数，不包含CRC，从机模式若是0则自动匹配，主机模式Status高4位代表要发送的有效半字节数
    unsigned char   IdleLevel;      ///<总线空闲状态，0-空闲低电平，1-空闲高电平
    unsigned char   DataFormat;     ///<数据格式
    unsigned char   SensorType;     ///<传感器类型
}SENT_CONFIG;
/** @} */

/**
 *@name SENT帧结构体
 *@brief SENT帧结构体定义
 */
typedef struct _SENT_MSG
{
    unsigned int    Timestamp;      ///<接收到信息帧时的时间标识，从SENT控制器初始化开始计时,单位为100us。发送数据时为帧间隔时间，单位为ms
    unsigned char   TimestampHigh;  ///<时间戳高位
    unsigned char   MsgType;///<bit[2..0]:\n
    ///<0-错误帧，比如CRC错误，数据不完整等\n
    ///<1-快速通道数据\n
    ///<2-慢速通道，简短型串行信息,8位数据+4位ID\n
    ///<3-慢速通道，增强型串行信息,12位数据+8位ID\n
    ///<4-慢速通道，增强型串行信息,16位数据+4位ID\n
    ///<bit[3]:1-SPC帧标志,0-普通SENT帧\n
    ///<bit[6..4]:通道号标志\n
    ///<bit[7]:TXD标志
    unsigned char   Status;         ///<低4位代表Status，高4位代表DLC
    unsigned char   Data[8];        ///<若MsgType为1，里面为半字节数据；若MsgType为2，Data[0]为ID,Data[1]为数据；若MsgType为3或4，Data[0]为ID，Data[1]为高4位或者高8位数据，Data[2]为低8位数据
    unsigned char   crc;            ///<MsgType若为3或者4，则是6bit有效CRC，其他的为4bit有效CRC
    unsigned short  Tmtr;           ///<Total trigger time，单位为0.01tick
    unsigned short  Tmlow;          ///<触发字段,SPC模式时用到,Master low time，单位为0.01tick
}SENT_MSG;
/** @} */
/**
 *@name SENT帧数据格式
 *@brief SENT帧数据格式定义
 */
typedef enum
{
    H0 = 0,
    H1,///<CH1=(byte[0]<<8)|(byte[1]<<4)|byte[2],CH2=(byte[5]<<8)|(byte[4]<<4)|byte[3]
    H2,///<CH1=(byte[0]<<8)|(byte[1]<<4)|byte[2]
    H3,///<CH1=(byte[0]<<9)|(byte[1]<<6)|(byte[2]<<3)|byte[3]
    H4,///<CH1=(byte[0]<<8)|(byte[1]<<4)|byte[2],CH2(Counter)=(byte[3]<<4)|byte[4]
    H5,///<CH1=(byte[0]<<8)|(byte[1]<<4)|byte[2],CH2=0
    H6,///<CH1=(byte[0]<<10)|(byte[1]<<6)|(byte[2]<<2)|(byte[3]>>2),CH2=(byte[5]<<6)|(byte[4]<<2)|(byte[3]&0x03)
    H7,///<CH1=(byte[0]<<12)|(byte[1]<<8)|(byte[2]<<4)|byte[3],CH2==(byte[5]<<4)|byte[4]
    //F.6.1 Data Frames with One Multiplexed Fast Channel and 12-bit Sensor Data
    F1_1,///<FC=byte[0],CH1=(byte[1]<<8)|(byte[2]<<4)|byte[3]
    F1_2,///<FC=byte[0],CH1=(byte[1]<<8)|(byte[2]<<4)|byte[3]
    F1_3,///<FC=byte[0],CH1=(byte[1]<<8)|(byte[2]<<4)|byte[3]
    F1_4,///<FC=byte[0],DCC=byte[1],CH1=(byte[2]<<8)|(byte[3]<<4)|byte[4]
    F1_5,///<FC=byte[0],DCC=byte[1],CH1=(byte[2]<<8)|(byte[3]<<4)|byte[4]
    F1_6,///<FC=byte[0],DCC=byte[1],CH1=(byte[2]<<8)|(byte[3]<<4)|byte[4]
    //F.6.2 Data Frames with One Multiplexed Fast Channel and 16-bit Sensor Data
    F2_1,///<FC=byte[0],CH1=(byte[1]<<12)|(byte[2]<<8)|(byte[3]<<4)|byte[4]
    F2_2,///<FC=byte[0],CH1=(byte[1]<<12)|(byte[2]<<8)|(byte[3]<<4)|byte[4]
    F2_3,///<FC=byte[0],CH1=(byte[1]<<12)|(byte[2]<<8)|(byte[3]<<4)|byte[4]
    F2_4,///<FC=byte[0],DCC=byte[1],CH1=(byte[2]<<12)|(byte[3]<<8)|(byte[4]<<4)|byte[5]
    //F.6.3 Data Frames with Two Multiplexed Fast Channels with Sensor Data
    F3_1,///<FC=byte[0],CH1=(byte[1]<<8)|(byte[2]<<4)|byte[3],CH2=(byte[5]<<4)|byte[4]
    F3_2,///<FC=byte[0],CH1=(byte[1]<<6)|(byte[2]<<2)|(byte[3]>>2),CH2=(byte[5]<<6)|(byte[4]<<2)|(byte[3]&0x03)
    F3_3,///<FC=byte[0],CH1=(byte[1]<<12)|(byte[2]<<8)|(byte[3]<<4)|byte[4],CH2=(byte[7]<<8)|(byte[6]<<4)|byte[5]
    F3_4,///<FC=byte[0],CH1=(byte[1]<<10)|(byte[2]<<6)|(byte[3]<<2)|(byte[4]>>2),CH2=(byte[7]<<10)|(byte[6]<<6)|(byte[5]<<2)|(byte[4]&0x03)
    F3_5,///<FC=byte[0],DCC=byte[1],CH1=(byte[2]<<8)|(byte[3]<<4)|byte[4],CH2=(byte[7]<<8)|(byte[6]<<4)|byte[5]
    //F.6.4 Data Frames with Free to Use Data
    F4_1,///<FC=byte[0]
    F4_2,///<FC=byte[0]
    F4_3,///<FC=byte[0]
    F4_4,///<FC=byte[0]
    F4_5,///<FC=byte[0]
    F4_6,///<FC=byte[0],DCC=byte[1]
    F4_7,///<FC=byte[0],DCC=byte[1]
    F4_8,///<FC=byte[0],DCC=byte[1]
    F4_9///<FC=byte[0],DCC=byte[1]
}SENT_DATA_FORMATS;//参考Table H-1 – Basic SENT frame formats, data channels and nibble orders
/** @} */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief 初始化配置SENT总线，必须调用，否则无法正常工作
 * @param DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param[in] pConfig 初始化结构体，可以参考 @ref SENT初始化结构定义 查看参数详情
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_Init(int DevHandle,unsigned char Channel, SENT_CONFIG* pConfig);

/**
 * @brief 配置SENT总线Tick时间
 * @param DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param TickTimeUs Tick时间，单位为us
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_SetTickTime(int DevHandle, unsigned char Channel, double TickTimeUs);

/**
 * @brief  主机模式下手动发送SENT消息
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param[in]  pSentMsg SENT消息帧指针
 * @param  MsgNum 发送的SENT消息帧数，不能大于64帧
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_SendMsg(int DevHandle, unsigned char Channel, SENT_MSG* pSentMsg, unsigned int MsgNum);

/**
 * @brief  设置并启动SENT快速通道帧发送列表
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param  pSentMsg SENT快速通道消息帧指针
 * @param  MsgNum 发送的SENT消息帧数，不能大于64帧
 * @param  SendTimes 列表循环发送次数，若设置为0xFFFFFFFF则一直循环发送列表，直到调用 @ref SENT_StopFastMsgTable 函数为止
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_StartFastMsgTable(int DevHandle, unsigned char Channel, SENT_MSG* pSentMsg, unsigned int MsgNum, unsigned int SendTimes);

/**
 * @brief   更新SENT快速通道发送列表中的帧
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param  StartMsgIndex 需要开始更新的起始帧索引，如果该索引大于原来列表大小，则将更新的帧添加到列表后面
 * @param  pSentMsg SENT快速通道消息帧指针
 * @param  MsgNum 更新的SENT消息帧数，不能大于64帧
 * @return 
 */
int WINAPI  SENT_UpdateFastMsgTable(int DevHandle, unsigned char Channel, unsigned char StartMsgIndex,SENT_MSG* pSentMsg, unsigned int MsgNum);

/**
 * @brief  停止正在发送的SENT帧列表
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_StopFastMsgTable(int DevHandle, unsigned char Channel);

/**
 * @brief  设置并启动SENT SPC帧发送列表
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param  pSentMsg SENT快速通道消息帧指针
 * @param  MsgNum 发送的SENT消息帧数，不能大于64帧
 * @param  SendTimes 列表循环发送次数，若设置为0xFFFFFFFF则一直循环发送列表，直到调用 @ref SENT_StopSPCMsgTable 函数为止
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_StartSPCMsgTable(int DevHandle, unsigned char Channel, SENT_MSG* pSentMsg, unsigned int MsgNum, unsigned int SendTimes);

/**
 * @brief   更新SENT SPC快速通道发送列表中的帧
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param  StartMsgIndex 需要开始更新的起始帧索引，如果该索引大于原来列表大小，则将更新的帧添加到列表后面
 * @param  pSentMsg SENT快速通道消息帧指针
 * @param  MsgNum 更新的SENT消息帧数，不能大于64帧
 * @return 
 */
int WINAPI  SENT_UpdateSPCMsgTable(int DevHandle, unsigned char Channel, unsigned char StartMsgIndex,SENT_MSG* pSentMsg, unsigned int MsgNum);

/**
 * @brief  停止正在发送的SENT帧列表
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_StopSPCMsgTable(int DevHandle, unsigned char Channel);

/**
 * @brief  设置并启动SENT慢速通道帧发送列表，调用该函数后数据不会立即发送，它是在发送快速数据的时候才通过Status域发送，所以需要发送慢速通道帧数据，需要同时启动快速帧发送列表
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param  pSentMsg SENT慢速通道消息帧指针
 * @param  MsgNum 发送的SENT消息帧数，不能大于64帧
 * @param  SendTimes 列表循环发送次数，若设置为0xFFFFFFFF则一直循环发送列表，直到调用 @ref SENT_StopSlowMsgTable 函数为止
 * @return 
 */
int WINAPI  SENT_StartSlowMsgTable(int DevHandle, unsigned char Channel, SENT_MSG* pSentMsg, unsigned int MsgNum, unsigned int SendTimes);

/**
 * @brief   更新慢速通道发送列表中的帧
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param  StartMsgIndex 需要开始更新的起始帧索引，如果该索引大于原来列表大小，则将更新的帧添加到列表后面
 * @param  pSentMsg SENT慢速通道消息帧指针
 * @param  MsgNum 更新的SENT消息帧数，不能大于64帧
 * @return 
 */
int WINAPI  SENT_UpdateSlowMsgTable(int DevHandle, unsigned char Channel, unsigned char StartMsgIndex,SENT_MSG* pSentMsg, unsigned int MsgNum);

/**
 * @brief  停止正在发送的SENT帧列表
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @return 函数执行状态
 * @retval =0 函数执行成功
 * @retval !=0 函数执行失败
 */
int WINAPI  SENT_StopSlowMsgTable(int DevHandle, unsigned char Channel);

/**
 * @brief 主机模式获取已发成功发送出去的帧，从机模式获取监控到的帧
 * @param DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param pSentMsg 存储SENT帧缓冲区指针，该缓冲区不能小于64，否则可能会出现缓冲区溢出导致程序异常闪退
 * @return 成功获取到的SENT消息帧数
 * @retval <0 函数执行失败
 */
int WINAPI  SENT_GetMsg(int DevHandle, unsigned char Channel, SENT_MSG* pSentMsg);

/**
 * @brief 主机模式获取已发成功发送出去的帧，从机模式获取监控到的帧
 * @param DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4，SENT总线在硬件上是跟LIN总线共用的
 * @param pSentMsg 存储SENT帧缓冲区指针
 * @param BufSize 存储数据的缓存区大小
 * @return 成功获取到的SENT消息帧数
 * @retval <0 函数执行失败
 */
int WINAPI  SENT_GetMsgWithSize(int DevHandle, unsigned char Channel, SENT_MSG* pSentMsg, unsigned int BufSize);

/**
 * @brief  获取SENT起始时间戳，该时间戳可以转换成实际的时间
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4
 * @return SENT起始时间戳
 * @retval <0 函数调用失败
 */
long long WINAPI SENT_GetStartTime(int DevHandle, unsigned char Channel);

/**
 * @brief  复位时间戳，复位后起始时间戳为当前时间
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4
 * @return 函数执行状态
 * @retval <0 函数调用失败
 */
int WINAPI SENT_ResetStartTime(int DevHandle, unsigned char Channel);

/**
 * @brief  停止SENT总线功能
 * @param  DevHandle 设备号，通过调用 @ref USB_ScanDevice 获取
 * @param  Channel SENT通道号，0-SENT1，1-SENT2，2-SENT3，3-SENT4
 * @return 函数执行状态
 * @retval <0 函数调用失败
 */
int WINAPI  SENT_Stop(int DevHandle, unsigned char Channel);

/**
 * @brief  将快速通道原始SENT数据解析成实际数据，注意只解析快速通道帧数据
 * @param  DataFormat 数据格式定义，只支持H1到H7格式数据
 * @param  pSentMsg SENT帧缓冲区首地址
 * @param  MsgNum 需要进行解析的帧数
 * @param  pDataCh1 解析出的快速通道1数据
 * @param  pDataCh2 解析出的快速通道2数据
 * @return 函数执行状态
 * @retval >=0 成功解析到的快速通道数据帧数
 * @retval <0 函数调用失败
 */
int WINAPI  SENT_MsgDecode(unsigned char DataFormat,SENT_MSG* pSentMsg,int MsgNum,unsigned int *pDataCh1, unsigned int* pDataCh2);

/**
 * @brief  将快速通道原始SENT数据解析成实际数据，注意只解析快速通道帧数据
 * @param  DataFormat 数据格式定义，支持所有格式数据
 * @param  pSentMsg SENT帧缓冲区首地址
 * @param  MsgNum 需要进行解析的帧数
 * @param  pDataCh1 解析出的快速通道1数据
 * @param  pDataCh2 解析出的快速通道2数据
 * @param  pFC 数据格式为F1_1及以上时输出的对应FC(Frame Control)数据
 * @param  pDCC 数据格式为F1_1及以上时输出的对应DCC(Data Consistency Counter)数据
 * @return 函数执行状态
 * @retval >=0 成功解析到的快速通道数据帧数
 * @retval <0 函数调用失败
 */
int WINAPI  SENT_MsgDecodeEx(unsigned char DataFormat, SENT_MSG* pSentMsg, int MsgNum, unsigned int* pDataCh1, unsigned int* pDataCh2, unsigned char* pFC, unsigned char* pDCC);

#ifdef __cplusplus
}
#endif
/** @} USB转SENT*/
#endif
