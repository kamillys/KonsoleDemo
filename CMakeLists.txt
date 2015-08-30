project("KonsoleDemo")

FIND_PACKAGE(KDE4 REQUIRED)
set(CMAKE_BUILD_TYPE "Debug")
INCLUDE_DIRECTORIES( ${KDE4_INCLUDES} . )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC_LIST src/main.cpp
             src/mainwindow.cpp
             src/mainwindow.h
             src/splitterm.cpp
             src/splitterm.h
             src/konsolewidget.cpp
             src/konsolewidget.h
	     )

kde4_add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${KDE4_KPARTS_LIBS})


## Install files
install(TARGETS ${PROJECT_NAME} DESTINATION ${BIN_INSTALL_DIR} )
