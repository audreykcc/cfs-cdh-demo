###########################################################
#
# CDH_APP mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the CDH_APP configuration
set(CDH_APP_MISSION_CONFIG_FILE_LIST
  cdh_app_fcncode_values.h
  cdh_app_interface_cfg_values.h
  cdh_app_mission_cfg.h
  cdh_app_perfids.h
  cdh_app_msg.h
  cdh_app_msgdefs.h
  cdh_app_msgstruct.h
  cdh_app_tbl.h
  cdh_app_tbldefs.h
  cdh_app_tblstruct.h
  cdh_app_topicid_values.h
)

generate_configfile_set(${CDH_APP_MISSION_CONFIG_FILE_LIST})

