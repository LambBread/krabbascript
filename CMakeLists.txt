cmake_minimum_required(VERSION 3.15)
project(krabbascript VERSION 2.2.3 LANGUAGES C)

option(KRS_FORMAT "Run clang-format on source files" OFF)

file(GLOB_RECURSE KRS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
add_executable(kscript "${KRS_SRCS}")

target_include_directories(kscript PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(kscript PUBLIC KSCRIPT_VENDOR="KrabbaTek")
install(TARGETS kscript DESTINATION bin)

if(KRS_FORMAT)
    find_program(CLANG_FORMAT_EXE NAMES clang-format)
    if(CLANG_FORMAT_EXE)
        add_custom_target(format COMMAND ${CLANG_FORMAT_EXE} -i ${KRS_SRCS} COMMENT "Running clang-format on source files...")
    else()
        message(WARNING "krabbascript ---- cannot find clang-format. Target 'format' will not be available.")
    endif()
endif()
