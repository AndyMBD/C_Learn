cmake_minimum_required(VERSION 3.18)
# 1.create a Project
set(PROJECT_NAME "C_001")
PROJECT(${PROJECT_NAME})
# set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
# 2. add subdirectory and include directory
add_subdirectory(dll)
add_subdirectory(lib)
# include_directories(${PROJECT_SOURCE_DIR}/dll/inc)
# include_directories(${PROJECT_SOURCE_DIR}/lib/inc)
include_directories(${PROJECT_SOURCE_DIR}/main/inc)
# 2. to get all source files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/main/src demo_src)

# 3. create a executable file
add_executable(${PROJECT_NAME} ${demo_src})
# 4. Set Project Properties

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
										RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# 4. Set Project Properties
target_include_directories(${PROJECT_NAME} PUBLIC 
											${PROJECT_SOURCE_DIR}/dll/inc)
target_link_libraries(${PROJECT_NAME} PUBLIC 
										C_001_dll)
target_include_directories(${PROJECT_NAME} PUBLIC 
											${PROJECT_SOURCE_DIR}/lib/inc)
target_link_libraries(${PROJECT_NAME} PUBLIC 
											C_001_lib)

message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${PROJECT_SOURCE_DIR})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR This is SOURCE dir " ${CMAKE_CURRENT_SOURCE_DIR})
# 5. link library, include directory
