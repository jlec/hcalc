cmake_minimum_required (VERSION 2.6) 
project (hcalc C)

find_package(X11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${X11_X11_INCLUDE_PATH}")

add_executable(hcalc
							draw.c
							hcalc.c
							images.c
							input.c
							setupx.c)
target_link_libraries(hcalc ${X11_X11_LIB} ${X11_Xpm_LIB})

install (TARGETS hcalc DESTINATION bin)

