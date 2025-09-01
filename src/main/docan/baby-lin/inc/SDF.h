#ifndef SDF_H
#define SDF_H

#include "BabyLINReturncodes.h"

typedef struct {
  int sectionNr;
  // ! Sectiontype (i.e. 0 = LIN, 1 = CAN, 99 = DEVICE)
  int type;
  char name[64];
  char description[4096];
} SDF_SECTIONINFO;

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup sdf_functions
 * @brief List of SDF functions
 *
 * The following structures are used to load and retrieve data from a SDF. The API allows to load
 * and retrieve SDF informations without an existing BabyLIN-Device connection and is particulaly
 * useful for SDF preloading or SDF loading to download to multiple BabyLIN devices. Functions
 * prefixed with BLC_ require an existing connection to a BabyLIN with a loaded SDF on the
 * corresponding channel.
 *
 * @{
 */

#define SDF_OK 0
#define SDF_HANDLE_INVALID -100024
#define SDF_IN_USE -100025

typedef void* SDF_HANDLE;

/**
 * @brief Loads a SDFile to memory and returns a @ref SDF_HANDLE
 *
 * @param[in] filename  The filename to load, can be absolute or relative to the current working
 *                      directory
 * @return              To the loaded SDFile or 0 on error
 */
SDF_HANDLE BL_DLLIMPORT SDF_open(const char* filename);

/**
 * @brief Loads a LDFFile to memory, creates a temporary SDF and returns a @ref SDF_HANDLE
 *
 * @param[in] filename  The filename to load, can be absolute or relative to the current working
 *                      directory
 * @return              To the loaded SDFile or 0 on error
 */
SDF_HANDLE BL_DLLIMPORT SDF_openLDF(const char* filename);

/** @brief Closes a SDFile opened using @ref SDF_open
 *
 * @param[in] handle    The SDFile handle to close
 * @return              0 on success
 */
int BL_DLLIMPORT SDF_close(SDF_HANDLE handle);

/**
 * @brief Returns whether the command overwriting feature for macro names is enabled
 *
 * @param[in] sdfhandle The SDFile from @ref SDF_open
 * @return              0 = feature disabled for this SDF, 1 = feature enabled, commands will be
 *                      interpreted as macro names first, if that fails, it will execute the normal
 *                      command e.g "reboot", if it exists.
 */
int BL_DLLIMPORT SDF_hasMacroCommandOverwriteEnabled(SDF_HANDLE sdfhandle);

/**
 * @brief Download a SDFile to a BabyLIN device
 *
 * @param[in] sdfhandle The SDFile from @ref SDF_open to download
 * @param[in] blhandle  The BabyLIN connection handle from @ref BLC_open to download to
 * @param[in] mode      See @ref BLC_loadSDF modes
 * @return              See @ref BLC_loadSDF returncodes (0 = success)
 */
int BL_DLLIMPORT SDF_downloadToDevice(SDF_HANDLE sdfhandle, BL_HANDLE blhandle, int mode);

/**
 * @brief Download a SDFile to a BabyLIN device
 *
 * @param[in] sectionhandle The SDFile from @ref SDF_open to download
 * @param[in] channelhandle The BabyLIN channel handle from @ref BLC_getChannelHandle to download to
 * @return                  See @ref BLC_loadSDF returncodes (0 = success)
 */
int BL_DLLIMPORT SDF_downloadSectionToChannel(SDF_HANDLE sectionhandle, BL_HANDLE channelhandle);

/**
 * @brief Get number of sections in SDF
 *
 * @param[in] sdfhandle The SDFile from @ref SDF_open
 * @return              Number of sections ( negative value on error )
 */
int BL_DLLIMPORT SDF_getSectionCount(SDF_HANDLE sdfhandle);

/**
 * @brief Get handle to a section of a sdf
 * @param[in] handle    The handle of the sdf to get the section handle from
 * @param[in] sectionNr The section number to get the handle for
 * @return              Handle to the section ( 0 on error )
 */
SDF_HANDLE BL_DLLIMPORT SDF_getSectionHandle(SDF_HANDLE handle, int sectionNr);

/**
 * @brief Get information about a section
 * @param[in] handle    The section handle to retrieve informations about
 * @param[out] info     Pointer to pre-allocated @ref SDF_SECTIONINFO structure to fill
 * @return              0 on success
 */
int BL_DLLIMPORT SDF_getSectionInfo(SDF_HANDLE handle, SDF_SECTIONINFO* info);
/** @} */

#if defined(__cplusplus)
}  // extern "C"
#endif

#endif  // SDF_H
