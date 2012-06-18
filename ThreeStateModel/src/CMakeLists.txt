file(GLOB_RECURSE ModFossa_src
  "*.c*"
)

set (EXTRA_LIBS ${EXTRA_LIBS} sundials_cvode sundials_nvecserial)

add_library(ModFossa SHARED ${ModFossa_src})
#add_executable(ModFossa ${ModFossa_src})
target_link_libraries (ModFossa ${EXTRA_LIBS} ${Boost_LIBRARIES})

install (TARGETS ModFossa DESTINATION .)
