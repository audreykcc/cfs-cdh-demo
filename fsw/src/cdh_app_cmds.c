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
 * \file
 *   This file contains the source code for the CDH App Ground Command-handling functions
 */

/*
** Include Files:
*/
#include "cdh_app.h"
#include "cdh_app_cmds.h"
#include "cdh_app_msgids.h"
#include "cdh_app_eventids.h"
#include "cdh_app_version.h"
#include "cdh_app_tbl.h"
#include "cdh_app_utils.h"
#include "cdh_app_msg.h"

/* The sample_lib module provides the SAMPLE_Function() prototype */
#include "sample_lib.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t CDH_APP_SendHkCmd(const CDH_APP_SendHkCmd_t *Msg)
{
    int i;

    /*
    ** Get command execution counters...
    */
    CDH_APP_Data.HkTlm.Payload.CommandErrorCounter = CDH_APP_Data.CommandErrorCounter;
    CDH_APP_Data.HkTlm.Payload.CommandCounter      = CDH_APP_Data.CommandCounter;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(CDH_APP_Data.HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(CDH_APP_Data.HkTlm.TelemetryHeader), true);

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (i = 0; i < CDH_APP_PLATFORM_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(CDH_APP_Data.TblHandles[i]);
    }

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE NOOP commands                                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t CDH_APP_NoopCmd(const CDH_APP_NoopCmd_t *Msg)
{
    CDH_APP_Data.CommandCounter++;

    CFE_EVS_SendEvent(CDH_APP_NOOP_INF_EID,
                      CFE_EVS_EventType_INFORMATION,
                      "CDH: NOOP command %s",
                      CDH_APP_VERSION);

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t CDH_APP_ResetCountersCmd(const CDH_APP_ResetCountersCmd_t *Msg)
{
    CDH_APP_Data.CommandCounter      = 0;
    CDH_APP_Data.CommandErrorCounter = 0;

    CFE_EVS_SendEvent(CDH_APP_RESET_INF_EID, CFE_EVS_EventType_INFORMATION, "CDH: RESET command");

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function Process Ground Station Command                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t CDH_APP_ProcessCmd(const CDH_APP_ProcessCmd_t *Msg)
{
    CFE_Status_t               Status;
    void                      *TblAddr;
    CDH_APP_ExampleTable_t *TblPtr;
    const char                *TableName = "CDH_APP.ExampleTable";

    /* Sample Use of Example Table */
    CDH_APP_Data.CommandCounter++;
    Status = CFE_TBL_GetAddress(&TblAddr, CDH_APP_Data.TblHandles[0]);
    if (Status < CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CDH App: Fail to get table address: 0x%08lx", (unsigned long)Status);
    }
    else
    {
        TblPtr = TblAddr;
        CFE_ES_WriteToSysLog("CDH App: Example Table Value 1: %d  Value 2: %d", TblPtr->Int1, TblPtr->Int2);

        CDH_APP_GetCrc(TableName);

        Status = CFE_TBL_ReleaseAddress(CDH_APP_Data.TblHandles[0]);
        if (Status != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("CDH App: Fail to release table address: 0x%08lx", (unsigned long)Status);
        }
        else
        {
            /* Invoke a function provided by CDH_APP_LIB */
            SAMPLE_LIB_Function();
        }
    }

    return Status;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* A simple example command that displays a passed-in value                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t CDH_APP_DisplayParamCmd(const CDH_APP_DisplayParamCmd_t *Msg)
{
    CDH_APP_Data.CommandCounter++;
    CFE_EVS_SendEvent(CDH_APP_VALUE_INF_EID,
                      CFE_EVS_EventType_INFORMATION,
                      "CDH_APP: ValU32=%lu, ValI16=%d, ValStr=%s",
                      (unsigned long)Msg->Payload.ValU32,
                      (int)Msg->Payload.ValI16,
                      Msg->Payload.ValStr);

    return CFE_SUCCESS;
}

/* set the recording threshold from a ground command */
CFE_Status_t CDH_APP_SetThresholdCmd(const CDH_APP_SetThresholdCmd_t *Msg) {
    CDH_APP_Data.Threshold = Msg->Payload.Threshold;
    CDH_APP_Data.CommandCounter++;

    CFE_EVS_SendEvent(CDH_APP_THRESHOLD_INF_EID,
                      CFE_EVS_EventType_INFORMATION,
                      "CDH_APP: Threshold set to %ld",
                      (long)CDH_APP_Data.Threshold);

    return CFE_SUCCESS;
}

/* Simulate one sensor reading. Store it only if it crosses the threshold (CDH-001) */
CFE_Status_t CDH_APP_SimSampleCmd(const CDH_APP_SimSampleCmd_t *Msg)
{
    int32 Value = Msg->Payload.Value;

    CDH_APP_Data.CommandCounter++;

    if (Value <= CDH_APP_Data.Threshold)
    {
        CFE_EVS_SendEvent(CDH_APP_SKIP_INF_EID, CFE_EVS_EventType_INFORMATION,
                          "CDH: Value %ld below threshold %ld, not stored",
                          (long)Value, (long)CDH_APP_Data.Threshold);
        return CFE_SUCCESS;
    }

    if (CDH_APP_Data.StoreCount >= CDH_APP_STORE_CAPACITY)
    {
        CFE_EVS_SendEvent(CDH_APP_STORE_FULL_ERR_EID, CFE_EVS_EventType_ERROR,
                          "CDH: Store full (%u records), value %ld dropped",
                          (unsigned int)CDH_APP_Data.StoreCount, (long)Value);
        return CFE_SUCCESS;
    }

    CDH_APP_Data.NextSeq++;
    CDH_APP_Data.Store[CDH_APP_Data.StoreCount].Seq   = CDH_APP_Data.NextSeq;
    CDH_APP_Data.Store[CDH_APP_Data.StoreCount].Value = Value;
    CDH_APP_Data.StoreCount++;

    CFE_EVS_SendEvent(CDH_APP_RECORD_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "CDH: Stored record seq=%lu value=%ld (%u stored)",
                      (unsigned long)CDH_APP_Data.NextSeq, (long)Value,
                      (unsigned int)CDH_APP_Data.StoreCount);

    return CFE_SUCCESS;
}