project(MilkyPlayer C CXX ASM)

set(SOURCES
		main.cpp
		PlayerMaster.cpp
		PlayerController.cpp
		#PlayerLogic.cpp
		ResamplerHelper.cpp
		)

set(HEADERS
		PlayerMaster.h
		PlayerController.h
		#PlayerLogic.h
		ResamplerHelper.h
		amigaversion.h
		project.h
		BasicTypes.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
		PRIVATE
		${PROJECT_SOURCE_DIR}
		# Include the CMake-generated version header from the build directory
		${PROJECT_BINARY_DIR}
		${SDL_INCLUDE_DIR}
		)

find_package(SDL REQUIRED)

target_link_libraries(${PROJECT_NAME}
		milkyplay
		${SDL_LIBRARY}
		)

# Version number in format X.YY.ZZ
set(VER_X  0)
set(VER_YY 01)
set(VER_ZZ 00)
set(VER_FULL "${VER_X}.${VER_YY}.${VER_ZZ}")


configure_file(
		${PROJECT_SOURCE_DIR}/amigaversion.h.in
		${PROJECT_BINARY_DIR}/amigaversion.h
)