/*
 * Copyright (c) 2011-2015:  G-CSC, Goethe University Frankfurt
 * Author: Tim Schön
 * 
 * This file is part of UG4.
 * 
 * UG4 is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License version 3 (as published by the
 * Free Software Foundation) with the following additional attribution
 * requirements (according to LGPL/GPL v3 §7):
 * 
 * (1) The following notice must be displayed in the Appropriate Legal Notices
 * of covered and combined works: "Based on UG4 (www.ug4.org/license)".
 * 
 * (2) The following notice must be displayed at a prominent place in the
 * terminal output of covered works: "Based on UG4 (www.ug4.org/license)".
 * 
 * (3) The following bibliography is recommended for citation and must be
 * preserved in all covered files:
 * "Reiter, S., Vogel, A., Heppner, I., Rupp, M., and Wittum, G. A massively
 *   parallel geometric multigrid solver on hierarchically distributed grids.
 *   Computing and visualization in science 16, 4 (2013), 151-164"
 * "Vogel, A., Reiter, S., Rupp, M., Nägel, A., and Wittum, G. UG4 -- a novel
 *   flexible software system for simulating pde based models on high performance
 *   computers. Computing and visualization in science 16, 4 (2013), 165-179"
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 */

#ifndef __H__UG__parameter_set__
#define __H__UG__parameter_set__



#include <nlohmann/json.hpp>
using namespace nlohmann;


#include <fstream>
#include <map>
#include <string>
#include <stdexcept>

#include <boost/optional.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include "common/ug_config.h"
#include "common/util/smart_pointer.h"

#include <registry/registry.h>
#include <registry/class.h>
#include <registry/function_traits.h>
#include <bridge/bridge.h>
#include <bindings/lua/lua_util.h>
#include <bindings/lua/bindings_lua.h>
#include <bindings/lua/lua_parsing.h>

namespace ug
{
    namespace JSONToolkit
    {
        struct ParameterValue
        {

                ParameterValue() {}

                ParameterValue(std::string name, SmartPtr<void> objValue)
                {
                    this->name = name;
                    this->objValue = objValue;
                }
            
                std::string name;
                SmartPtr<void> objValue = SPNULL;
        };    

        
        class ParameterSet
        {
            public:
                ParameterSet();
                ParameterSet(const char*  json);
                void loadJSON(const char* json);
                void loadJSONFile(const char* file);
                void loadFromJSONObject(const json jsonobject);
                bridge::CustomReturn get(const char* name);

            private:           
                std::map<std::string, ParameterValue> parameters;

        };


        //! This function creates a 'ParameterValue' from JSON.
        boost::optional<ParameterValue> CreateParameterValue(const json& jsonobject);
    

    } // end of namespace JSONToolkit

}//	end of namespace ug

#endif
