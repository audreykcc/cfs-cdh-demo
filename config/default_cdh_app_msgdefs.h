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
 *   message payload and constant definitions.
 */
#ifndef DEFAULT_CDH_APP_MSGDEFS_H
#define DEFAULT_CDH_APP_MSGDEFS_H

#include "common_types.h"
#include "cdh_app_fcncodes.h"

typedef struct CDH_APP_DisplayParam_Payload
{
    uint32 ValU32;                                    /**< 32 bit unsigned integer value */
    int16  ValI16;                                    /**< 16 bit signed integer value */
    char   ValStr[CDH_APP_MISSION_STRING_VAL_LEN]; /**< An example string */
} CDH_APP_DisplayParam_Payload_t;

typedef struct CDH_APP_SetThreshold_Payload
{
    uint32 Threshold; /**< new recording threshold value */
} CDH_APP_SetThreshold_Payload_t;

/*************************************************************************/
/*
** Type definition (CDH App housekeeping)
*/

typedef struct CDH_APP_HkTlm_Payload
{
    uint8 CommandCounter;
    uint8 CommandErrorCounter;
} CDH_APP_HkTlm_Payload_t;

typedef struct CDH_APP_SimSample_Payload
{
    int32 Value; /**< Simulated sensor reading */
} CDH_APP_SimSample_Payload_t;

#endif
