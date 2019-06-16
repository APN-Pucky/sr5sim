


#file(GLOB_RECURSE sr5sim_SOURCES "*.cpp")
#list(REMOVE_ITEM sr5sim_SOURCES "main.cpp")

set(sr5sim_SOURCES character.cpp 
	load.cpp debug.cpp 
	utils.cpp rng.cpp
	sim.cpp
)


add_library(sr5lib ${sr5sim_SOURCES})

target_include_directories(sr5lib PUBLIC ../externals/rapidxml/)

add_executable(sr5sim main.cpp)



target_link_libraries(sr5sim sr5lib)


#install(TARGETS sr5sim DESTINATION bin)
#install(TARGETS sr5lib DESTINATION lib)
