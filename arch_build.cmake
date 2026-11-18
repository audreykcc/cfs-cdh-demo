###########################################################
#
# CDH_APP platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the CDH_APP configuration
set(CDH_APP_PLATFORM_CONFIG_FILE_LIST
  cdh_app_internal_cfg_values.h
  cdh_app_platform_cfg.h
  cdh_app_perfids.h
  cdh_app_msgids.h
  cdh_app_msgid_values.h
)

generate_configfile_set(${CDH_APP_PLATFORM_CONFIG_FILE_LIST})

