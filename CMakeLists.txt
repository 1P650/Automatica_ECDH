cmake_minimum_required(VERSION 3.5)

project(elliptic_curves LANGUAGES C)

add_executable(elliptic_curves main.c
    arifm.h
    arifm.c
    multinv.c
    hexutil.h
    multinv.h
    montgomery.h
    elliptic.h
    elliptic.c)

include(GNUInstallDirs)
install(TARGETS elliptic_curves
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
