set(ARROW_DOWNLOAD_BINARY_DIR ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/thirdparty/arrow-download/)

# Download and unpack arrow at configure time
configure_file(${CMAKE_SOURCE_DIR}/cmake/Templates/Arrow.CMakeLists.txt.cmake ${ARROW_DOWNLOAD_BINARY_DIR}/CMakeLists.txt COPYONLY)

execute_process(
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${ARROW_DOWNLOAD_BINARY_DIR}
)

if(result)
    message(FATAL_ERROR "CMake step for arrow failed: ${result}")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${ARROW_DOWNLOAD_BINARY_DIR}
)

if(result)
    message(FATAL_ERROR "Build step for arrow failed: ${result}")
endif()

# Locate the Arrow package.
# Requires that you build with:
#   -DARROW_ROOT:PATH=/path/to/arrow_install_dir
set(ARROW_ROOT ${ARROW_DOWNLOAD_BINARY_DIR}/arrow-prefix/src/arrow-install/usr/local/)
message(STATUS "ARROW_ROOT: " ${ARROW_ROOT})

# Copy the arrow-format flatbuffer headers to include/ipc using configure_file (will sync if input file changes)
set(ARROW_GENERATED_IPC_DIR ${ARROW_DOWNLOAD_BINARY_DIR}/arrow-prefix/src/arrow/cpp/src/arrow/ipc/)

configure_file(${ARROW_GENERATED_IPC_DIR}/File_generated.h ${CMAKE_SOURCE_DIR}/include/gdf/ipc/File_generated.h COPYONLY)
configure_file(${ARROW_GENERATED_IPC_DIR}/Message_generated.h ${CMAKE_SOURCE_DIR}/include/gdf/ipc/Message_generated.h COPYONLY)
configure_file(${ARROW_GENERATED_IPC_DIR}/Schema_generated.h ${CMAKE_SOURCE_DIR}/include/gdf/ipc/Schema_generated.h COPYONLY)
configure_file(${ARROW_GENERATED_IPC_DIR}/Tensor_generated.h ${CMAKE_SOURCE_DIR}/include/gdf/ipc/Tensor_generated.h COPYONLY)
