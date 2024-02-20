# Copyright (c) 2023 Nordic Semiconductor ASA
# Copyright 2023-2024 NXP
# SPDX-License-Identifier: Apache-2.0

if("${SB_CONFIG_REMOTE_BOARD}" STREQUAL "")
	message(FATAL_ERROR
	"Target ${BOARD} not supported for this sample. "
	"There is no remote board selected in Kconfig.sysbuild")
endif()

set(REMOTE_APP remote)

ExternalZephyrProject_Add(
	APPLICATION ${REMOTE_APP}
	SOURCE_DIR  ${APP_DIR}/${REMOTE_APP}
	BOARD       ${SB_CONFIG_REMOTE_BOARD}
)

native_simulator_set_child_images(${DEFAULT_IMAGE} ${REMOTE_APP})

native_simulator_set_final_executable(${DEFAULT_IMAGE})

if ("${BOARD}" STREQUAL "mimxrt1170_evkb_cm7" OR
	"${BOARD}" STREQUAL "mimxrt1170_evk_cm7"  OR
	"${BOARD}" STREQUAL "mimxrt1160_evk_cm7" OR
	"${BOARD}" STREQUAL "lpcxpresso55s69_cpu0"
	)
	# For these NXP boards the main core application is dependent on
	# 'zephyr_image_info.h' generated by remote application.

	# Let's build the remote application first
	add_dependencies(${DEFAULT_IMAGE} ${REMOTE_APP})
endif()
