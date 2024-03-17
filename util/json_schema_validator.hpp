/*
 * JSON schema validator for JSON for modern C++
 *
 * Copyright (c) 2016-2019 Patrick Boettcher <p@yai.se>.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef __H__UG__JSON_SCHEMA_VALIDATOR_HPP__
#define __H__UG__JSON_SCHEMA_VALIDATOR_HPP__

#include <nlohmann/json-schema.hpp>

#include <fstream>
#include <iostream>

#include "ug.h"
#include "common/error.h"
#include "common/log.h"
#include "common/util/smart_pointer.h"







namespace ug
{
    namespace JSONToolkit
    {

    	struct JSONSchemaValidator : public nlohmann::json_schema::json_validator
		{
    		JSONSchemaValidator();

    		~JSONSchemaValidator(){};

    		//! Set root.
    		void init(nlohmann::json& schema);

    		//! Do the actual validation of the document
    		bool validate_document(nlohmann::json& document);

		};

   } // namespace JSONToolkit

} // namespace ug

#endif // __H__UG__JSON_SCHEMA_VALIDATOR_HPP__
