

#file(GLOB_RECURSE sr5test_SOURCES "*.test.cpp")

set(sr5test_SOURCES test.cpp 
	test.test.cpp 
	load.test.cpp 
	rng.test.cpp
	dmg.test.cpp
	battle.test.cpp
	sim.test.cpp
)
set(TARGET_NAME sr5test)

add_executable(${TARGET_NAME}
  test.cpp
  ${sr5test_SOURCES})
  
target_link_libraries(${TARGET_NAME}
  PUBLIC sr5lib)
  
target_include_directories(${TARGET_NAME}
  PUBLIC ../externals/catch/)
  
target_include_directories(${TARGET_NAME}
  PUBLIC ../externals/rapidxml/)
