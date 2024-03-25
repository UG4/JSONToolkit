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

    	SmartPtr<void> JSON_create_object(const nlohmann::json& j);
    	void JSON_parse(nlohmann::json& j, std::string s);
    	bool JSON_load_from_file(nlohmann::json& j, std::string filename);
    	std::string JSON_dump(const nlohmann::json& j);


   } // namespace JSONToolkit

} // namespace ug

#endif // __H__UG__JSON_TOOLKIT_HPP__
