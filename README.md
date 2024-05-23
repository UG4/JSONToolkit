# JSONToolkit plugin

**UG4-Plugin** implementing an interface for JSON

Copyright 2024 Goethe University Frankfurt

## Install
Please install/clone this repository through UG4's package manager[ughub](https://github.com/UG4/ughub).


 ```
 cmake -DJSONToolkit=ON ..
 ```

## Functionality

This plugin provides:
a) a class **JSON** representing 'nlohmann::json' and functions
 ```
void JSON_parse(nlohmann::json& j, std::string s);
bool JSON_load_from_file(nlohmann::json& j, std::string filename);
std::string JSON_dump(const nlohmann::json& j);
 ```
b) a class **JSONSchemaValidator** for validating JSON:
 ```
JSONSchemaValidator::JSONSchemaValidator()
void JSONSchemaValidator::init(nlohmann::json& schema)
JSONSchemaValidator::validate_document(nlohmann::json& document)
 ```



## Dependency
* [nlohmann](https://github.com/nlohmann/json) is included as a submodule.
* [json-schema-validator](https://github.com/pboettch/json-schema-validator) is included as a submodule.


## License
TBD
