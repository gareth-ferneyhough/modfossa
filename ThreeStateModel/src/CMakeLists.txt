#include_directories ("${PROJECT_SOURCE_DIR}/src/svm")
#link_directories ("${PROJECT_SOURCE_DIR}/src/lib")

file(GLOB_RECURSE Ion3_src
  "*.c*"
)

set (EXTRA_LIBS ${EXTRA_LIBS} sundials_cvode sundials_nvecserial)

add_executable (Ion3 ${Ion3_src})

target_link_libraries (Ion3 ${EXTRA_LIBS})

install (TARGETS Ion3 DESTINATION .)
