cmake_minimum_required(VERSION 3.18)
# 1.create a Project
set(PROJECT_NAME "ode_test")
PROJECT(${PROJECT_NAME})
# set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
# 2. add subdirectory and include directory
# add_subdirectory(dll)
# add_subdirectory(lib)
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/main)
set(ODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ode)
message(STATUS "MAIN_DIR This is SOURCE dir " ${MAIN_DIR})
message(STATUS "ODE_DIR This is SOURCE dir " ${ODE_DIR})
# set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# set(MC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mc)

include_directories(${ODE_DIR}/inc)
# include_directories(${DLL_DIR}/inc)
# include_directories(${LIB_DIR}/inc)
# include_directories(${MC_DIR}/inc)

file(GLOB main_inc CONFIGURE_DEPENDS ${MAIN_DIR}/inc/*.h)
file(GLOB ode_inc CONFIGURE_DEPENDS  ${ODE_DIR}/inc/*.h)
message(STATUS "main_inc This is SOURCE dir " ${main_inc})
message(STATUS "ode_inc This is SOURCE dir " ${ode_inc})
# file(GLOB lib_inc CONFIGURE_DEPENDS  ${LIB_DIR}/inc/*.h)
# file(GLOB mc_inc CONFIGURE_DEPENDS  ${MC_DIR}/inc/*.h)


# 2. to get all source files
aux_source_directory(${MAIN_DIR} main_src)
aux_source_directory(${ODE_DIR}/src ode_src)
message(STATUS "main_src This is SOURCE dir " ${main_src})
message(STATUS "ode_src This is SOURCE dir " ${ode_src})
# aux_source_directory(${LIB_DIR}/src lib_src)
# aux_source_directory(${MC_DIR}/src mc_src)

# 3. create a executable file
add_executable(${PROJECT_NAME} 
							${main_src}
							${ode_src}
							${main_inc}
							${ode_inc})
# 4. Set Project Properties
target_include_directories(${PROJECT_NAME} PUBLIC 
											${MAIN_DIR}/inc
											${ODE_DIR}/inc)
# target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_DIR}/lib/libmc.a)
# message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${PROJECT_SOURCE_DIR})
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR This is SOURCE dir " ${CMAKE_CURRENT_SOURCE_DIR})
# 5. link library, include directory
