# Runtime library CMakeLists.txt

include(Runtime)

add_library(wpl_runtime OBJECT
  ${RUNTIME_SOURCES}
)

add_library(wpl_runtime_archive STATIC
  ${RUNTIME_SOURCES}
)

