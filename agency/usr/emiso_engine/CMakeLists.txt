
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(emiso_engine emiso_engine.cpp emiso_webserver.cpp)

target_link_libraries(emiso_engine httpserver)

#set(INSTALL_PATH ${CMAKE_BINARY_DIR}/root)
#install(FILES emiso_engine DESTINATION ${INSTALL_PATH})
