cmake_minimum_required(VERSION 3.13.0)

project(ChessCpp LANGUAGES CXX) # This sets CMAKE_PROJECT_NAME, but nested

# calls changes PROJECT_NAME, CMAKE_PROJECT_NAME

# Ensure minimum C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
	# set(COMPILER_WARNINGS -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wmissing-declarations -Werror=missing-include-dirs -Werror=undef)
	set(COMPILER_WARNINGS -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wmissing-declarations -Werror=missing-include-dirs -Werror=undef -Wno-sign-conversion)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(COMPILER_WARNINGS "/W4 /WX")
endif()

# Add source files of application
set(SOURCES
	${CMAKE_SOURCE_DIR}/src/ChessGame.cpp
	${CMAKE_SOURCE_DIR}/src/Boards/Board.cpp
	${CMAKE_SOURCE_DIR}/src/Boards/ChessBoard.cpp

	# ${CMAKE_SOURCE_DIR}/src/Pieces/Bishop.cpp
	# ${CMAKE_SOURCE_DIR}/src/Pieces/Champion.cpp
	# ${CMAKE_SOURCE_DIR}/src/Pieces/King.cpp
	# ${CMAKE_SOURCE_DIR}/src/Pieces/Knight.cpp
	# ${CMAKE_SOURCE_DIR}/src/Pieces/Magician.cpp
	# ${CMAKE_SOURCE_DIR}/src/Pieces/Pawn.cpp
	# ${CMAKE_SOURCE_DIR}/src/Pieces/Queen.cpp
	# ${CMAKE_SOURCE_DIR}/src/Pieces/Rook.cpp
	${CMAKE_SOURCE_DIR}/src/Players/Player.cpp
	${CMAKE_SOURCE_DIR}/src/Players/RealPlayer.cpp
	${CMAKE_SOURCE_DIR}/src/Positions/Position.cpp

	# Agrega aquí todos los archivos fuente que compartan `chess_main` y `${TEST_NAME}`
)

# Create executable
add_executable(chess_main)
target_compile_options(chess_main PRIVATE ${COMPILER_WARNINGS})

# source files
target_sources(chess_main PRIVATE main.cpp ${SOURCES})

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
message(STATUS "Include path: ${INCLUDE_DIR}")

# set include directory
target_include_directories(
	chess_main PRIVATE
	"${INCLUDE_DIR}"
)

# add_subdirectory("src")

# TODO: use variable to activate tests
enable_testing()
add_subdirectory(test)