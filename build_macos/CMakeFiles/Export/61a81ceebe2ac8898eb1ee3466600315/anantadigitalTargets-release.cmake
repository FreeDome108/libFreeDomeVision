#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "anantadigital::anantadigital_core" for configuration "Release"
set_property(TARGET anantadigital::anantadigital_core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(anantadigital::anantadigital_core PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libanantadigital_core.2.1.0.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libanantadigital_core.2.dylib"
  )

list(APPEND _cmake_import_check_targets anantadigital::anantadigital_core )
list(APPEND _cmake_import_check_files_for_anantadigital::anantadigital_core "${_IMPORT_PREFIX}/lib/libanantadigital_core.2.1.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
