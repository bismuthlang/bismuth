# SPDX-License-Identifier: MIT
#
# SPDX-FileCopyrightText: Copyright (c) 2019-2023 Lars Melchior and contributors

# Lines 5--21 are from the below link (see their license); 
# This heuristic allows us to pull CPM from nix locally or 
# download it when we don't have CPM installed and are thus outside of a
# nix build. 
# https://github.com/OlivierLDff/QOlm/blob/4aad491596987c2acf7be06e880173c27bab8a51/cmake/CPM.cmake
message(STATUS "Looking for local CPM.cmake")
find_file(CPM_LOCAL_FILE
  CPM.cmake
  PATH_SUFFIXES share/cpm/
)

if(EXISTS ${CPM_LOCAL_FILE})
  message(STATUS "Using local CPM.cmake: ${CPM_LOCAL_FILE}")
  include(${CPM_LOCAL_FILE})
  return()
endif()

set(CPM_DOWNLOAD_VERSION 0.40.4)
set(CPM_HASH_SUM "67dcc1deb6e12a2f0705647ccc5f7023e3d15746b944e14352b82373e09b8a0a")

if(CPM_SOURCE_CACHE)
  set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
  set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
  set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

# Expand relative path. This is important if the provided path contains a tilde (~)
get_filename_component(CPM_DOWNLOAD_LOCATION ${CPM_DOWNLOAD_LOCATION} ABSOLUTE)

file(DOWNLOAD
     https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
     ${CPM_DOWNLOAD_LOCATION} EXPECTED_HASH SHA256=${CPM_HASH_SUM}
)

include(${CPM_DOWNLOAD_LOCATION})
