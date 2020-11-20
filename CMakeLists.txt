cmake_minimum_required(VERSION 3.17)
project(DownloadExecuteReport C)

set(CMAKE_C_STANDARD 11)

configure_file(resources.rc resources.rc)
add_executable(DownloadExecuteReport main.c resources.rc)