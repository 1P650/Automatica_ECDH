cmake_minimum_required(VERSION 3.5)

project(inverse_modulo LANGUAGES C)

add_executable(inverse_modulo arifm.h arifm.c multinv.h multinv.c main.c
    hexutil.h
    montgomery.h
    benchmark.h
)

include(GNUInstallDirs)
install(TARGETS inverse_modulo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
