# Runtime library CMakeLists.txt

include(Runtime)

# add_subdirectory(core)

add_library(wpl_runtime OBJECT
  ${RUNTIME_SOURCES}
  ${CORE_SOURCES}
)

include_directories(wpl_runtime_archive 
  ${CORE_INCLUDE}
)

add_library(wpl_runtime_archive STATIC
  ${RUNTIME_SOURCES}
  ${CORE_SOURCES}
)

include_directories(wpl_runtime 
  ${CORE_INCLUDE}
)

