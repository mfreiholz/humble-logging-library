cmake_minimum_required(VERSION 2.8)
project(humblelogging_tests)

set(sources
	main.cpp
	common_tests.cpp
)

include_directories(
	../include
	../../googletest/googletest/include
)

# Compile
add_executable(
	${PROJECT_NAME}
	${sources}
)

# Link
target_link_libraries(
	${PROJECT_NAME}
	humblelogging
	optimized C:/Source/GitHub/googletest/googletest/mybuild/Release/gtest.lib
	optimized C:/Source/GitHub/googletest/googletest/mybuild/Release/gtest_main.lib
	debug C:/Source/GitHub/googletest/googletest/mybuild/Debug/gtest.lib
	debug C:/Source/GitHub/googletest/googletest/mybuild/Debug/gtest_main.lib
)