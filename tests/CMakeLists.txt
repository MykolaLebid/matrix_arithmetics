add_executable(test_matrix "")
target_sources(test_matrix 
	PRIVATE
	MainTest.cpp
        MatrixTest.cpp	
	)

target_include_directories(test_matrix 
	                   PUBLIC 
			   ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(test_matrix
 	PRIVATE
	#gmock_main
	GMock::main
 )
enable_testing()
 
add_test(
 	NAME google_test
 	COMMAND $<TARGET_FILE:test_matrix>
)
	
