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

namespace ug
{
    namespace JSONToolkit
	{

    SmartPtr<void> JSON_create_object(const json& jsonobject)
    {
    	boost::optional<ParameterValue> obj = CreateParameterValue(jsonobject);
    	if (!obj) return SPNULL;

    	UG_LOG(obj.get().name);
    	return obj.get().objValue;
    }

    bool JSON_load_from_file(nlohmann::json& j, std::string filename)
    {
    	UG_LOG("JSON_load_from_file: from file " + filename + "\n");
    	std::ifstream file(filename);

    	if (!file.good())
    	{
    		UG_LOG ("JSON_load_from_file: could not open " << filename << " for reading\n");
    		return false;
    	}
    	try {
    		file >> j;
    	} UG_CATCH_THROW("JSON_load_from_file: failure  at "<<
    			file.tellg() << " - while parsing document.");

    	return true;
    }

    void JSON_parse(nlohmann::json& j, std::string s)
    { j=nlohmann::json::parse(s); }

    std::string JSON_dump(const json& j)
    { return j.dump();}




} // namespace JSONToolkit
} // namespace ug
