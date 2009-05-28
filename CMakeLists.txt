cmake_minimum_required(VERSION 2.6)

project(unfolder)

FIND_PATH( GTK_glibconfig_INCLUDE_PATH NAMES glibconfig.h
	PATHS
		/usr/openwin/share/include
		/usr/local/include/glib12
		/usr/lib/glib/include
		/usr/lib64/glib/include
		/usr/local/lib/glib/include
		/opt/gnome/include
		/opt/gnome/lib/glib/include
)

FIND_PATH( GTK_glib_INCLUDE_PATH NAMES glib.h
	PATH_SUFFIXES gtk-1.2 glib-1.2 glib12
	PATHS
		/usr/openwin/share/include
		/usr/lib/glib/include
		/opt/gnome/include
)

FIND_LIBRARY( GTK_glib_LIBRARY
	NAMES  glib glib12
	PATHS  /usr/openwin/lib
		/opt/gnome/lib
)

include_directories(${GTK_glibconfig_INCLUDE_PATH} ${GTK_glib_INCLUDE_PATH})

add_executable(unfolder common.c main.c marking.c netconv.c nodelist.c order.c pe.c readlib.c readpep.c unfold.c)

target_link_libraries(unfolder ${GTK_glib_LIBRARY})
