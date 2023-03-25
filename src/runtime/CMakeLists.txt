# Runtime library CMakeLists.txt

include(Runtime)

# add_subdirectory(core)

add_library(bismuth_runtime OBJECT
  ${RUNTIME_SOURCES}
  ${CORE_SOURCES}
)

include_directories(bismuth_runtime_archive 
  ${CORE_INCLUDE}
)

add_library(bismuth_runtime_archive STATIC
  ${RUNTIME_SOURCES}
  ${CORE_SOURCES}
)

include_directories(bismuth_runtime 
  ${CORE_INCLUDE}
)

