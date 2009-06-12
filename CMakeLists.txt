cmake_minimum_required(VERSION 2.6)

project(unfolder)

find_package(GTK)

add_definitions(-Wall -g -fomit-frame-pointer)

include_directories(/usr/include/glib-2.0 /usr/lib64/glib-2.0/include
	/usr/lib/glib-2.0/include)

add_executable(unfolder unfold.c common.c main.c marking.c netconv.c nodelist.c readlib.c
	readpep.c order.c pe.c array.c dot.c)

target_link_libraries(unfolder glib-2.0)

add_subdirectory(test)