# Copyright (c) 2011-2020:  G-CSC, Goethe University Frankfurt
# Author: Tim Schön
# 
# This file is part of UG4.
# 
# UG4 is free software: you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License version 3 (as published by the
# Free Software Foundation) with the following additional attribution
# requirements (according to LGPL/GPL v3 §7):
# 
# (1) The following notice must be displayed in the Appropriate Legal Notices
# of covered and combined works: "Based on UG4 (www.ug4.org/license)".
# 
# (2) The following notice must be displayed at a prominent place in the
# terminal output of covered works: "Based on UG4 (www.ug4.org/license)".
# 
# (3) The following bibliography is recommended for citation and must be
# preserved in all covered files:
# "Reiter, S., Vogel, A., Heppner, I., Rupp, M., and Wittum, G. A massively
#   parallel geometric multigrid solver on hierarchically distributed grids.
#   Computing and visualization in science 16, 4 (2013), 151-164"
# "Vogel, A., Reiter, S., Rupp, M., Nägel, A., and Wittum, G. UG4 -- a novel
#   flexible software system for simulating pde based models on high performance
#   computers. Computing and visualization in science 16, 4 (2013), 165-179"
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.

# Name of your plugin and sources.
set(pluginName	JSONToolkit)
set(SOURCES		util/json_plugin.cpp
				util/parameter_set.cpp
				util/json_toolkit.cpp	
				util/json_schema_validator.cpp	
				# json-schema-validator
				external/json-schema-validator/src/smtp-address-validator.cpp
        		external/json-schema-validator/src/json-schema-draft7.json.cpp
        		external/json-schema-validator/src/json-uri.cpp
        		external/json-schema-validator/src/json-validator.cpp
        		external/json-schema-validator/src/json-patch.cpp
        		external/json-schema-validator/src/string-format-check.cpp	
				)

# 

# External libs (JSON).
include_directories(AFTER ${UG_ROOT_PATH}/externals/JSONForUG4/json-cxx/single_include)  # JSON
include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/external/json-schema-validator/src)



# Add json-schema-validator
add_subdirectory(external/json-schema-validator)

# Requires C++ 11.
set (CMAKE_CXX_STANDARD 11)

################################################################################
# The code below doesn't have to be changed (usually)
################################################################################
cmake_minimum_required(VERSION 2.8.12)

project(UG_PLUGIN_${pluginName})



# Include the definitions and dependencies for ug-plugins.
include(${UG_ROOT_CMAKE_PATH}/ug_plugin_includes.cmake)

if(buildEmbeddedPlugins)
	# add the sources to ug4's sources
	EXPORTSOURCES(${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES})
else(buildEmbeddedPlugins)
	# create a shared library from the sources and link it against ug4.
	add_library(${pluginName} SHARED ${SOURCES})
	target_link_libraries (${pluginName} ug4)
endif(buildEmbeddedPlugins)
