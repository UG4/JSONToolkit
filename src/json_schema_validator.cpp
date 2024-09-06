/*
 * JSON schema validator for JSON for modern C++
 *
 * Copyright (c) 2016-2019 Patrick Boettcher <p@yai.se>.
 *
 * SPDX-License-Identifier: MIT
 *
 */


// Standard lib.
#include <fstream>
#include <iostream>

// UG4 core.
#include "common/util/smart_pointer.h"
#include "common/util/path_provider.h"

// My lib.
#include "json_toolkit.hpp"
#include "json_schema_validator.hpp"


using nlohmann::json_uri;
using nlohmann::json;

namespace ug
{
    namespace JSONToolkit
	{

    static void loader(const json_uri &uri, json &schema)
    {
    	std::string filename =  ug::PathProvider::get_path(ROOT_PATH) + uri.path();
    	JSONTool::load_from_file(schema, filename);
    }

    class custom_error_handler : public nlohmann::json_schema::basic_error_handler
	{
    	void error(const nlohmann::json::json_pointer &ptr, const json &instance, const std::string &message) override
    	{
    		nlohmann::json_schema::basic_error_handler::error(ptr, instance, message);
    		std::cerr << "ERROR: '" << ptr << "' - '" << instance << "': " << message << "\n";
    	}
	};


    JSONSchemaValidator::JSONSchemaValidator()
    : json_validator(loader, nlohmann::json_schema::default_string_format_check)
    {}


    void JSONSchemaValidator::init(json& schema)
    {
    	try {
    		// insert this schema as the root to the validator
    		// this resolves remote-schemas, sub-schemas and references via the given loader-function
    		this->set_root_schema(schema);
    	} 
    	UG_CATCH_THROW("JSONSchemaValidator: setting root schema failed."); 
    	/*catch (const std::exception &e) {
    		std::cerr <<"JSONSchemaValidator: setting root schema failed - : " << e.what();
    		throw e;
    	}*/
    }

    //! Do the actual validation of the document
    bool JSONSchemaValidator::validate_document(json& document)
    {
        custom_error_handler err;
    	this->validate(document, err);

    	return (err) ? false : true;

    }



} // namespace JSONToolkit
} // namespace ug
