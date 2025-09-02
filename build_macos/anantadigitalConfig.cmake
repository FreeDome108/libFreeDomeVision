
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was anantadigitalConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include(CMakeFindDependencyMacro)

# Find dependencies
find_dependency(Threads)

# Include the targets file
include("${CMAKE_CURRENT_LIST_DIR}/anantadigitalTargets.cmake")

# Set variables
set(anantadigital_VERSION "2.1.0")
set(anantadigital_VERSION_MAJOR "2")
set(anantadigital_VERSION_MINOR "1")
set(anantadigital_VERSION_PATCH "0")

# Platform-specific variables
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(anantadigital_PLATFORM "Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    if(CMAKE_OSX_DEPLOYMENT_TARGET)
        set(anantadigital_PLATFORM "macOS")
    else()
        set(anantadigital_PLATFORM "iOS")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(anantadigital_PLATFORM "Android")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(anantadigital_PLATFORM "Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Avrora")
    set(anantadigital_PLATFORM "Avrora")
endif()

check_required_components(anantadigital)
