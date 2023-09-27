project(emiso_engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} emiso_engine.cpp emiso_webserver.cpp)

target_link_libraries(${PROJECT_NAME} httpserver jsoncpp)

#set(INSTALL_PATH ${CMAKE_BINARY_DIR}/root)
#install(FILES ${PROJECT_NAME} DESTINATION ${INSTALL_PATH})
