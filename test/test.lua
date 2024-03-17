
ug_load_script("ug_util.lua")
local path = util.GetParam("--path", "")

local jschema=JSON(); 
JSON_load_from_file(jschema, path.."schema.json");

local jdocument=JSON(); 
JSON_load_from_file(jdocument, path.."instance.json"); 

v0=JSONSchemaValidator();
v0:init(jschema)
v0:validate_document(jdocument)