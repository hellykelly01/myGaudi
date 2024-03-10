# Find quietly if already found before
if(DEFINED CACHE{PYTHIA8_INCLUDE_DIRS})
  set(${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY YES)
endif()

find_path(PYTHIA8_INCLUDE_DIR Pythia8/Pythia.h
          HINTS $ENV{PYTHIA8_ROOT_DIR}/include ${PYTHIA8_ROOT_DIR}/include)

find_path(PYTHIA8_PLUGINS_INCLUDE_DIR Pythia8Plugins/HepMC3.h
          HINTS $ENV{PYTHIA8_ROOT_DIR}/include ${PYTHIA8_ROOT_DIR}/include)

find_library(PYTHIA8_LIBRARY NAMES pythia8
          HINTS $ENV{PYTHIA8_ROOT_DIR}/lib ${PYTHIA8_ROOT_DIR}/lib)

set(PYTHIA8_INCLUDE_DIRS ${PYTHIA8_INCLUDE_DIR} ${PYTHIA8_PLUGINS_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set Pythia8_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia8 DEFAULT_MSG PYTHIA8_INCLUDE_DIRS PYTHIA8_LIBRARY)

mark_as_advanced(Pythia8_FOUND PYTHIA8_INCLUDE_DIR PYTHIA8_INCLUDE_DIRS
                 PYTHIA8_PLUGINS_INCLUDE_DIR PYTHIA8_LIBRARY)

# Modernisation: create an interface target to link against
if(TARGET Pythia8)
    return()
endif()
if(Pythia8_FOUND)
  add_library(Pythia8 IMPORTED INTERFACE)
  target_include_directories(Pythia8 SYSTEM INTERFACE "${PYTHIA8_INCLUDE_DIRS}")
  target_link_libraries(Pythia8 INTERFACE "${PYTHIA8_LIBRARY}")
  # Display the imported target for the user to know
  if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
    message(STATUS "  Import target: Pythia8")
  endif()
endif()

if(COMMAND __deprecate_var_for_target)
  foreach(v IN ITEMS PYTHIA8_INCLUDE_DIR PYTHIA8_PLUGINS_INCLUDE_DIR PYTHIA8_INCLUDE_DIRS PYTHIA8_LIBRARY)
    variable_watch(${v} __deprecate_var_for_target)
  endforeach()
endif()