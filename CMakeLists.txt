cmake_minimum_required(VERSION 3.5)

project(FirstCproj LANGUAGES C)

add_executable(FirstCproj ddaemon.c)

include(GNUInstallDirs)
install(TARGETS FirstCproj
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
