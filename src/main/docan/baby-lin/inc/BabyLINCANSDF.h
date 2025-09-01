#ifndef BABYLINCANSDF_H
#define BABYLINCANSDF_H

#include "BabyLINReturncodes.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** @addtogroup sdf_functions
 *  @{
 */

/**
 *  @brief Get the SDF's number for node by name.
 *
 *  @param handle   Handle representing the connection; returned previously by getChannelHandle().
 *  @param name     Name of the node.
 *  @return         Returns the node's number or -1 if there's no signal with specified name. Even
 *                  smaller numbers designate error codes as defined in BabyLIN.h.
 */
int BL_DLLIMPORT BLC_SDF_getNodeNr(BL_HANDLE handle, const char* name);

/**
 *  @brief Get the SDF's number for signal by name.
 *
 *  @param handle   Handle representing the connection; returned previously by getChannelHandle().
 *  @param name     Name of the signal.
 *  @return         Returns the signal's number or -1 if there's no signal with specified name. Even
 *                  smaller numbers designate error codes as defined in BabyLIN.h.
 */
int BL_DLLIMPORT BLC_SDF_getSignalNr(BL_HANDLE handle, const char* name);

/**
 *  @brief Get the SDF's number for frame by name.
 *
 *  @param handle   Handle representing the connection; returned previously by getChannelHandle().
 *  @param name     Name of the frame.
 *  @return         Returns the frame's number or -1 if there's no frame with specified name. Even
 *                  smaller numbers designate error codes as defined in BabyLIN.h.
 */
int BL_DLLIMPORT BLC_SDF_getFrameNr(BL_HANDLE handle, const char* name);

/**
 *  @brief Get the SDF's number for schedule by name.
 *
 *  @param handle   Handle representing the connection; returned previously by getChannelHandle().
 *  @param name     Name of the schedule.
 *  @return         Returns the schedule's number or -1 if there's no schedule with specified name.
 *                  Even smaller numbers designate error codes as defined in BabyLIN.h.
 */
int BL_DLLIMPORT BLC_SDF_getScheduleNr(BL_HANDLE handle, const char* name);

/**
 *  @brief Get the number of schedule tables in the SDF.
 *
 *  @param handle   Handle representing the connection; returned previously by getChannelHandle().
 *  @return         Returns the number of schedule tablesname or 0 if there's no schedule defined.
 */
int BL_DLLIMPORT BLC_SDF_getNumSchedules(BL_HANDLE handle);

/**
 *  @brief Get the SDF's name of schedule by number.
 *
 *  @param handle       Handle representing the connection; returned previously by
 *                      getChannelHandle().
 *  @param schedule_nr  Index of the schedule.
 *  @return             Returns the schedule's name or empty string if there's no schedule with
 *                      specified index.
 */
CPCHAR BL_DLLIMPORT BLC_SDF_getScheduleName(BL_HANDLE handle, int schedule_nr);

/**
 *  @brief Get the SDF's number for macro by name.
 *
 *  @param handle   Handle representing the connection; returned previously by getChannelHandle().
 *  @param name     Name of the macro.
 *  @return         Returns the macro's number or -1 if there's no macro with specified name. Even
 *                  smaller numbers designate error codes as defined in BabyLIN.h.
 */
int BL_DLLIMPORT BLC_SDF_getMacroNr(BL_HANDLE handle, const char* name);
/** @} */

#if defined(__cplusplus)
}  // extern "C"
#endif

#endif  // BABYLINCANSDF_H
