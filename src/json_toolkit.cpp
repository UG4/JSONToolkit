/*
 * JSON schema validator for JSON for modern C++
 *
 * Copyright (c) 2016-2019 Patrick Boettcher <p@yai.se>.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "json_schema_validator.hpp"


#include <fstream>
#include <iostream>


#include <boost/optional.hpp>
#include <boost/exception/diagnostic_information.hpp>


#include "parameter_set.h"

#include "json_toolkit.hpp"

namespace ug
{
    namespace JSONToolkit
	{

    using nlohmann::json;

    /*static*/
    SmartPtr<void> JSONTool::create_object(const nlohmann::json& jsonobject)
    {
    	boost::optional<ParameterValue> obj = CreateParameterValue(jsonobject);
    	if (!obj) return SPNULL;

    	UG_LOG(obj.get().name);
    	return obj.get().objValue;
    }


    bool JSONTool::load_from_file(nlohmann::json& j, std::string filename)
    {
    	UG_LOG("JSONTool::load_from_file: " + filename + "\n");
    	std::ifstream file(filename);

    	if (!file.good())
    	{
    		UG_LOG ("JSONTool::load_from_file: could not open " << filename << " for reading\n");
    		return false;
    	}
    	try {
    		file >> j;
    	} UG_CATCH_THROW("JSONTool::load_from_file: failure at "<<
    			file.tellg() << " - while parsing document.");

    	return true;
    }



    void JSONTool::parse(nlohmann::json& j, std::string s)
    { j=nlohmann::json::parse(s); }

    /*static*/  std::string JSONTool::dump(const json& j)
    { return j.dump();}




    SmartPtr<nlohmann::json> JSONTool::create(const std::string &s)
    {
       	auto jobj = make_sp<nlohmann::json> (new nlohmann::json());
       	parse(*jobj, s);
       	return jobj;
    }

    /*static*/  SmartPtr<nlohmann::json> JSONTool::create_from_file(const std::string &s)
    {
    	auto jobj = make_sp<nlohmann::json> (new nlohmann::json());
    	load_from_file(*jobj, s);
    	return jobj;
    }






} // namespace JSONToolkit
} // namespace ug
