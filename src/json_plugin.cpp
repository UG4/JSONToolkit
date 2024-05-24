/*
 * Copyright (c) 2016:  G-CSC, Goethe University Frankfurt
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


#include <string>

#ifdef UG_JSON
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>
#endif

#include "bridge/bridge.h"
#include "bridge/util.h"
#include "bridge/suffix_tag.h"
#include "parameter_set.h"

#include "json_toolkit.hpp"
#include "json_schema_validator.hpp"


using namespace std;
using namespace ug::bridge;

namespace ug{
	namespace JSONToolkit{

		struct Functionality
		{

			static void Common(Registry& reg, string grp)
			{

				{
					string name = "ParameterSet";
					typedef ParameterSet T;

					reg.add_class_<T>(name, grp)
						.add_constructor<void (*)()>()
						.add_constructor<void (*)(const char*)>("json-string containing the parameters")
						.add_method("loadJSON", &T::loadJSON, "", "json-string containing the parameters", "Loads all Parameters given in the string.")
						.add_method("loadJSONFile", &T::loadJSONFile,	"", "string containing the filename", "Loads all parameters in the file given.")
						.add_method("get", &T::get, "object", "name of the parameter", "gets the parameter by the name", "")
						.set_construct_as_smart_pointer(true);

					reg.add_class_to_group(name, grp);

				}
				
#ifdef UG_JSON
				{
					string name = "JSON";
					typedef nlohmann::json J;
					reg.add_class_<J>(name, grp)
						.add_constructor<void (*)()>();
						//.add_method("to_string", &J::to_string, "object", "name of the parameter", "gets the parameter by the name", "");
					reg.add_class_to_group(name, grp);

					reg.add_function("JSON_load_from_file", &JSON_load_from_file);
					reg.add_function("JSON_parse", &JSON_parse);
					reg.add_function("JSON_dump", &JSON_dump);
				}
				{
					string name = "JSONSchemaValidator";
					typedef JSONSchemaValidator J;
					reg.add_class_<J>(name, grp)
					.add_constructor<void (*)()>()
					.add_method("init", &J::init, "object", "name of the parameter", "gets the parameter by the name", "")
					.add_method("validate_document", &J::validate_document, "object", "name of the parameter", "gets the parameter by the name", "");
					reg.add_class_to_group(name, grp);

				}
#endif
				// New
				{
					string name = "ParameterValue";
					typedef ParameterValue T;
					reg.add_class_<T>(name, grp);

					reg.add_function("JSON_create_object", &JSON_create_object);
				}

			}
		};

	}//	end of namespace JSONToolkit

	// Template auxiliary.
	template <typename TRegistry=ug::bridge::Registry>
	void InitUGPlugin_JSONToolkit_(TRegistry* reg, string grp)
	{
		grp.append("/JSONToolkit");
		typedef JSONToolkit::Functionality Functionality;

		try{
			RegisterCommon<Functionality>(*reg,grp);
		}
		UG_REGISTRY_CATCH_THROW(grp);
	}


	// Classic expose.
	extern "C" UG_API void
	InitUGPlugin_JSONToolkit(ug::bridge::Registry* reg, string grp)
	{ InitUGPlugin_JSONToolkit_<ug::bridge::Registry>(reg, grp); }

	extern "C" UG_API void
	FinalizeUGPlugin_JSONToolkit()
	{}


#ifdef UG_USE_PYBIND11
	// Expose for pybind11.
	namespace JSONToolkit{
		void InitUGPlugin(ug::pybind::Registry* reg, string grp)
		{ InitUGPlugin_Limex_<ug::pybind::Registry>(reg, grp); }
	}
#endif



}//	end of namespace ug
