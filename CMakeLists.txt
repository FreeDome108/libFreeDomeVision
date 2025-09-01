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

# Настройка компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()
endif()

# Поиск зависимостей
find_package(Threads REQUIRED)

# Основная библиотека
add_library(anantadigital_core
    src/anantadigital_core.cpp
    src/quantum_feedback_system.cpp
    src/consciousness_hybrid.cpp
    src/consciousness_integration.cpp
)

# Настройка свойств библиотеки
set_target_properties(anantadigital_core PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "src/anantadigital_core.hpp;src/quantum_feedback_system.hpp"
)

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
