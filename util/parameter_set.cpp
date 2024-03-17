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

#include "parameter_set.h"
#include "json_toolkit.hpp"

using namespace nlohmann;

namespace ug
{

    namespace JSONToolkit
    {

        ParameterSet::ParameterSet()
        {
        }

        ParameterSet::ParameterSet(const char* json)
        {
            this->loadJSON(json);
        }

        void ParameterSet::loadJSON(const char* jsonstring)
        {
            json j = json::parse(jsonstring);
            this->loadFromJSONObject(j);
        }

        void ParameterSet::loadJSONFile(const char* filename)
        {
            UG_LOG("Loading parameters from file " + std::string(filename) + "\n");
            std::ifstream file(filename);
            json j;
            file >> j;
            this->loadFromJSONObject(j);
        }

        void ParameterSet::loadFromJSONObject(const json j)
        {
            for(const auto& item : j.items())
            {
                auto value = CreateParameterValue(item.value());

                if(!value)
                {                
                    continue;
                }

                parameters[item.key()] = value.get();
            }
        }

        bridge::CustomReturn ParameterSet::get(const char* name)
        {
            std::string strname = std::string(name);
            auto search = parameters.find(strname);
            //UG_LOG("Getting parameter " + strname + "\n");
            if(search == parameters.end())
            {
                throw std::range_error("Parameter " + strname + " is not defined.");
            }

            ParameterValue val = search->second;

            lua_State* L = script::GetDefaultLuaState();

            if(val.name == "number")
            {            
                void* p = val.objValue.get();
                double* doublep = (double*)p;
                lua_pushnumber(L, *doublep);
            }
            else
            {
                bridge::lua::CreateNewUserData(L, val.objValue, val.name.c_str());
            }       

            return bridge::CustomReturn(); 
        }


        boost::optional<ParameterValue> CreateParameterValue(const json& j)
        {
            std::string type = j["type"];

            if (type == "number")
            {
                double* paramvalue = new double;
                *paramvalue = j["value"];
                //UG_LOG("Created Parameter with type " + type + " and value " + std::to_string(*paramvalue) + ".\n");
                auto value = ParameterValue(type, make_sp(paramvalue));            
                return value;
            }

            bridge::Registry& reg = bridge::GetUGRegistry();
    
            if(!reg.classname_registered(type))
            {
                UG_LOG("Could not create Parameter with type " + type + ". Type needs to be registered in the UG Registry.\n");
                return boost::none;  
            }

            auto valueclass = reg.get_class(type);
            
            bridge::ExportedClassBaseImpl* exportedclass = dynamic_cast<bridge::ExportedClassBaseImpl*>(valueclass);
        
            boost::optional<bridge::ExportedConstructor&> constructor_maybe = exportedclass->get_json_constructor();

            if(!constructor_maybe)
            {
                UG_LOG("No suitable constructor for type " + type + " found!");
                return boost::none; 
            }

            bridge::ExportedConstructor constructor = constructor_maybe.get();

            bridge::ParameterStack params;

            params.push<std::string>(j.dump());
            SmartPtr<void> parametervalue;
            // UG_LOG("param stack size: " + std::to_string(params.size()) + "\n");
            // UG_LOG("param top element: " + std::string(params.to<std::string>(0)) + "\n");

            try
            {
                parametervalue = SmartPtr<void>(constructor.create(params), exportedclass->get_delete_function());
            }
            catch(...)
            {
                UG_LOG("Exception while creating parameter object of type " + type + ": " + boost::current_exception_diagnostic_information());
                return boost::none;
            }

            //UG_LOG("Created Parameter with type " + type + ".\n");
            return ParameterValue(type, parametervalue);
        }
    }
}
