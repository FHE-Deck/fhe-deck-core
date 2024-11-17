file(GLOB EXAMPLES *.cpp)
 
set(CMAKE_C_FLAGS_INIT "-Wall")

foreach(EXAMPLE_SRC ${EXAMPLES}) 
 
	get_filename_component(EXAMPLE_NAME ${EXAMPLE_SRC} NAME_WE)
	add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC}) 
	
	target_link_libraries(${EXAMPLE_NAME} PRIVATE fhe_deck)

endforeach()
