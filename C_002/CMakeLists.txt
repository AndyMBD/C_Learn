cmake_minimum_required(VERSION 3.29)
# 1.create a Project
set(PROJECT_NAME "C_002")
PROJECT(${PROJECT_NAME})
# set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
# 2. add subdirectory and include directory
# add_subdirectory(dll)
# add_subdirectory(lib)
find_package(GSL REQUIRED)
message(STATUS "GSL_INCLUDE_DIRS: " ${GSL_INCLUDE_DIRS})
message(STATUS "GSL_LIBRARIES: " ${GSL_LIBRARIES})
message(STATUS "GSL_LIBRARY_DIRS: " ${GSL_LIBRARY_DIRS})

set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/main)
set(DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dll)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${MAIN_DIR}/inc)
include_directories(${DLL_DIR}/inc)
include_directories(${LIB_DIR}/inc)

file(GLOB main_inc CONFIGURE_DEPENDS ${MAIN_DIR}/inc/*.h)
file(GLOB dll_inc CONFIGURE_DEPENDS  ${DLL_DIR}/inc/*.h)
file(GLOB lib_inc CONFIGURE_DEPENDS  ${LIB_DIR}/inc/*.h)


# 2. to get all source files
aux_source_directory(${MAIN_DIR}/src demo_src)
aux_source_directory(${DLL_DIR}/src dll_src)
aux_source_directory(${LIB_DIR}/src lib_src)

# 3. create a executable file
add_executable(${PROJECT_NAME} 
							${demo_src}
							${dll_src}
							${lib_src}
							${demo_inc}
							${dll_inc}
							${lib_inc})
# 4. Set Project Properties
target_include_directories(${PROJECT_NAME} PUBLIC 
											${MAIN_DIR}/inc
											${DLL_DIR}/inc
											${LIB_DIR}/inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${GSL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GSL_LIBRARIES})
# message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${GSL})
# message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${PROJECT_SOURCE_DIR})
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR This is SOURCE dir " ${CMAKE_CURRENT_SOURCE_DIR})
# 5. link library, include directory
