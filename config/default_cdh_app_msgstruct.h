/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * @file
 *   Specification for the CDH_APP command and telemetry
 *   message data types.
 *
 * @note
 *   Constants and enumerated types related to these message structures
 *   are defined in cdh_app_msgdefs.h.
 */
#ifndef DEFAULT_CDH_APP_MSGSTRUCT_H
#define DEFAULT_CDH_APP_MSGSTRUCT_H

/************************************************************************
 * Includes
 ************************************************************************/

#include "cdh_app_mission_cfg.h"
#include "cdh_app_msgdefs.h"
#include "cfe_msg_hdr.h"

/*************************************************************************/

/*
** The following commands all share the "NoArgs" format
**
** They are each given their own type name matching the command name, which
** allows them to change independently in the future without changing the prototype
** of the handler function
*/
typedef struct
{
    CFE_MSG_CommandHeader_t CommandHeader; /**< \brief Command header */
} CDH_APP_NoopCmd_t;

typedef struct
{
    CFE_MSG_CommandHeader_t CommandHeader; /**< \brief Command header */
} CDH_APP_ResetCountersCmd_t;

typedef struct
{
    CFE_MSG_CommandHeader_t CommandHeader; /**< \brief Command header */
} CDH_APP_ProcessCmd_t;

typedef struct
{
    CFE_MSG_CommandHeader_t           CommandHeader; /**< \brief Command header */
    CDH_APP_DisplayParam_Payload_t Payload;
} CDH_APP_DisplayParamCmd_t;

typedef struct
{
    CFE_MSG_CommandHeader_t            CommandHeader; /**< \brief Command header */
    CDH_APP_SetThreshold_Payload_t Payload;
} CDH_APP_SetThresholdCmd_t;

typedef struct
{
    CFE_MSG_CommandHeader_t     CommandHeader; /**< \brief Command header */
    CDH_APP_SimSample_Payload_t Payload;
} CDH_APP_SimSampleCmd_t;

/*************************************************************************/
/*
** Type definition (CDH App housekeeping)
*/

typedef struct
{
    CFE_MSG_CommandHeader_t CommandHeader; /**< \brief Command header */
} CDH_APP_SendHkCmd_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t  TelemetryHeader; /**< \brief Telemetry header */
    CDH_APP_HkTlm_Payload_t Payload;         /**< \brief Telemetry payload */
} CDH_APP_HkTlm_t;

#endif /* CDH_APP_MSGSTRUCT_H */
