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
 *
 * Main header file for the Sample application
 */

#ifndef CDH_APP_H
#define CDH_APP_H

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_config.h"

#include "cdh_app_mission_cfg.h"
#include "cdh_app_platform_cfg.h"

#include "cdh_app_perfids.h"
#include "cdh_app_msgids.h"
#include "cdh_app_msg.h"

/************************************************************************
** Type Definitions
*************************************************************************/

/*
** Global Data
*/

/* Maximum number of stored records */
#define CDH_APP_STORE_CAPACITY 16

/* One stored science record */
typedef struct
{
    uint32 Seq;   /* unique sequence number */
    int32  Value; /* sensor reading that crossed the threshold */
} CDH_APP_Record_t;

typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8 CommandCounter;
    uint8 CommandErrorCounter;
    int32 Threshold; /* set by SET_THRESHOLD command */

        /* Record store (CDH-001): records stay here until the ground acknowledges them */
    CDH_APP_Record_t Store[CDH_APP_STORE_CAPACITY];
    uint16           StoreCount; /* how many records are stored right now */
    uint32           NextSeq;    /* sequence number for the next record */

    /*
    ** Housekeeping telemetry packet...
    */
    CDH_APP_HkTlm_t HkTlm;

    /*
    ** Run Status variable used in the main processing loop
    */
    uint32 RunStatus;

    /*
    ** Operational data (not reported in housekeeping)...
    */
    CFE_SB_PipeId_t CommandPipe;

    CFE_TBL_Handle_t TblHandles[CDH_APP_PLATFORM_NUMBER_OF_TABLES];
} CDH_APP_Data_t;

/*
** Global data structure
*/
extern CDH_APP_Data_t CDH_APP_Data;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (CDH_APP_Main), these
**       functions are not called from any other source module.
*/
void         CDH_APP_Main(void);
CFE_Status_t CDH_APP_Init(void);

#endif /* CDH_APP_H */
