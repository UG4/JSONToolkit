/*
 * JSON schema validator for JSON for modern C++
 *
 * Copyright (c) 2016-2019 Patrick Boettcher <p@yai.se>.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __H__UG__JSON_TOOLKIT_HPP__
#define __H__UG__JSON_TOOLKIT_HPP__

#include <nlohmann/json-schema.hpp>

#include <fstream>
#include <iostream>

#include "ug.h"
#include "common/error.h"
#include "common/log.h"

#include "common/ug_config.h"
#include "common/util/smart_pointer.h"


namespace ug
{
    namespace JSONToolkit
    {

    	// TODO: Move into separate class.
    	struct JSONTool {
    		JSONTool(){}

    		static SmartPtr<void> create_object(const nlohmann::json& j);

    		static SmartPtr<nlohmann::json> create(const std::string &s);
    		static SmartPtr<nlohmann::json> create_from_file(const std::string &s);

    		static void parse(nlohmann::json& j, std::string s);
    		static bool load_from_file(nlohmann::json& j, std::string filename);
    		static std::string dump(const nlohmann::json& j);
     };


   } // namespace JSONToolkit

} // namespace ug

#endif // __H__UG__JSON_TOOLKIT_HPP__
