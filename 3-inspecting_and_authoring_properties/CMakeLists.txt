# 1. Requirements
cmake_minimum_required(VERSION 3.22)
project(inspecting_and_authoring_properties)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2.Configuration
add_compile_options(-Wno-deprecated)  # This is just to avoid some spammy warnings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # This line is optional. It's just for certain IDEs to use

# 3. Boilerplate
set(USD_INSTALL_ROOT /usr/local/USD)
set(USD_LIBRARY_DIRECTORY ${USD_INSTALL_ROOT}/lib)
set(USD_INCLUDE_DIRECTORY ${USD_INSTALL_ROOT}/include)
message(STATUS "Found USD library dir: ${USD_LIBRARY_DIRECTORY}")
message(STATUS "Found USD include dir: ${USD_INCLUDE_DIRECTORY}")

# boost_python38 rely on which version your python used for compling usd
# make sure it matches the version you used
find_library(USD_BOOST_PYTHON boost_python38 HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_KIND usd_kind HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_SDF usd_sdf HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_TF usd_tf HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_GF usd_gf HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_VT usd_vt HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_USD usd_usd HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_USDGEOM usd_usdGeom HINTS ${USD_LIBRARY_DIRECTORY})

find_package(PythonLibs REQUIRED)

# 4. Include/Link Everything
add_executable(run_it
	main.cpp
)

target_include_directories(run_it
PUBLIC
	${PYTHON_INCLUDE_PATH}
	${USD_INCLUDE_DIRECTORY}
)

target_link_libraries(
run_it
	${PYTHON_LIBRARY}
	${USD_BOOST_PYTHON}
	${USD_SDF}
	${USD_TF}
		${USD_GF}
		${USD_VT}
	${USD_USDGEOM}
	${USD_USD}
    ${USD_KIND}
)
