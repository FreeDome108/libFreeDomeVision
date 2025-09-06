cmake_minimum_required(VERSION 3.16)
project(anAntaDigital VERSION 2.1.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции сборки
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(ENABLE_QUANTUM_FEEDBACK "Enable quantum feedback system" ON)

# Platform detection
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_LINUX TRUE)
    message(STATUS "Building for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    if(CMAKE_OSX_DEPLOYMENT_TARGET)
        set(PLATFORM_MACOS TRUE)
        message(STATUS "Building for macOS")
    else()
        set(PLATFORM_IOS TRUE)
        message(STATUS "Building for iOS")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(PLATFORM_ANDROID TRUE)
    message(STATUS "Building for Android")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_WINDOWS TRUE)
    message(STATUS "Building for Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Avrora")
    set(PLATFORM_AVRORA TRUE)
    message(STATUS "Building for Avrora")
endif()

# Platform-specific compiler flags
if(PLATFORM_LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -fPIC")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()
elseif(PLATFORM_MACOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -fPIC")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14")
    # Отключаем std::filesystem для macOS 10.14
    add_definitions(-D_LIBCPP_DISABLE_AVAILABILITY)
elseif(PLATFORM_IOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -fPIC")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0")
elseif(PLATFORM_ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -fPIC")
    set(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION "clang")
elseif(PLATFORM_WINDOWS)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /O2")
        add_definitions(-D_WIN32_WINNT=0x0601)
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")
    endif()
elseif(PLATFORM_AVRORA)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -fPIC")
endif()

# Поиск зависимостей
find_package(Threads REQUIRED)

# Основная библиотека
add_library(anantadigital_core
    src/anantadigital_core.cpp
    src/quantum_feedback_system.cpp
    src/consciousness_hybrid.cpp
    src/consciousness_integration.cpp
    src/lubomir_understanding.cpp
    src/interference_field.cpp
    src/dome_acoustic_resonator.cpp
)

# Настройка свойств библиотеки
set_target_properties(anantadigital_core PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "src/anantadigital_core.hpp;src/quantum_feedback_system.hpp;src/consciousness_hybrid.hpp;src/consciousness_integration.hpp;src/lubomir_understanding.hpp;src/interference_field.hpp;src/dome_acoustic_resonator.hpp"
)

# Platform-specific library properties
if(PLATFORM_IOS)
    set_target_properties(anantadigital_core PROPERTIES
        XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH NO
        XCODE_ATTRIBUTE_ENABLE_BITCODE NO
        XCODE_ATTRIBUTE_VALIDATE_PRODUCT YES
    )
elseif(PLATFORM_ANDROID)
    set_target_properties(anantadigital_core PROPERTIES
        ANDROID_NATIVE_API_LEVEL 21
    )
endif()

# Подключение зависимостей
target_link_libraries(anantadigital_core
    PUBLIC Threads::Threads
)

# Включение директорий
target_include_directories(anantadigital_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Компиляционные определения
target_compile_definitions(anantadigital_core
    PRIVATE
        ANANTADIGITAL_VERSION="${PROJECT_VERSION}"
        $<$<BOOL:${ENABLE_QUANTUM_FEEDBACK}>:ENABLE_QUANTUM_FEEDBACK>
        $<$<BOOL:${PLATFORM_LINUX}>:PLATFORM_LINUX>
        $<$<BOOL:${PLATFORM_MACOS}>:PLATFORM_MACOS>
        $<$<BOOL:${PLATFORM_IOS}>:PLATFORM_IOS>
        $<$<BOOL:${PLATFORM_ANDROID}>:PLATFORM_ANDROID>
        $<$<BOOL:${PLATFORM_WINDOWS}>:PLATFORM_WINDOWS>
        $<$<BOOL:${PLATFORM_AVRORA}>:PLATFORM_AVRORA>
)

# Демонстрационные приложения
if(BUILD_EXAMPLES)
    add_executable(anantadigital_demo
        examples/anantadigital_demo.cpp
    )
    target_link_libraries(anantadigital_demo PRIVATE anantadigital_core)
    
    add_executable(quantum_acoustic_demo
        examples/quantum_acoustic_demo.cpp
    )
    target_link_libraries(quantum_acoustic_demo PRIVATE anantadigital_core)
    
    add_executable(audio_playback_demo
        examples/audio_playback_demo.cpp
    )
    target_link_libraries(audio_playback_demo PRIVATE anantadigital_core)
    
    add_executable(lubomir_understanding_demo
        examples/lubomir_understanding_demo.cpp
    )
    target_link_libraries(lubomir_understanding_demo PRIVATE anantadigital_core)
    
    # Поиск и подключение аудио библиотек
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)
    pkg_check_modules(SNDFILE REQUIRED sndfile)
    
    target_include_directories(audio_playback_demo PRIVATE ${PORTAUDIO_INCLUDE_DIRS} ${SNDFILE_INCLUDE_DIRS})
    target_link_libraries(audio_playback_demo PRIVATE ${PORTAUDIO_LIBRARIES} ${SNDFILE_LIBRARIES})
    target_compile_options(audio_playback_demo PRIVATE ${PORTAUDIO_CFLAGS_OTHER} ${SNDFILE_CFLAGS_OTHER})
    
    # Дополнительные пути для macOS
    if(PLATFORM_MACOS)
        target_include_directories(audio_playback_demo PRIVATE 
            /opt/homebrew/include
            /usr/local/include
        )
        target_link_directories(audio_playback_demo PRIVATE 
            /opt/homebrew/lib
            /usr/local/lib
        )
    endif()
endif()

# Тесты
if(BUILD_TESTS)
    enable_testing()
    
    add_executable(anantadigital_tests
        tests/test_anantadigital_core.cpp
        tests/test_quantum_feedback.cpp
        tests/test_consciousness.cpp
    )
    target_link_libraries(anantadigital_tests PRIVATE anantadigital_core)
    
    add_test(NAME anantadigital_tests COMMAND anantadigital_tests)
endif()

# Установка
install(TARGETS anantadigital_core
    EXPORT anantadigitalTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/anantadigital
)

# Установка заголовочных файлов
install(DIRECTORY src/
    DESTINATION include/anantadigital
    FILES_MATCHING PATTERN "*.hpp"
)

# Экспорт целей
install(EXPORT anantadigitalTargets
    FILE anantadigitalTargets.cmake
    NAMESPACE anantadigital::
    DESTINATION lib/cmake/anantadigital
)

# Конфигурационный файл
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    anantadigitalConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/anantadigitalConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/anantadigitalConfig.cmake"
    INSTALL_DESTINATION lib/cmake/anantadigital
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/anantadigitalConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/anantadigitalConfigVersion.cmake"
    DESTINATION lib/cmake/anantadigital
)
