-- ugshell -ex ../../plugins/JSONToolkit/test/test.lua --path $UG$_ROOT/plugins/JSONToolkit/test/basic-01/

ug_load_script("ug_util.lua")
local path = util.GetParam("--path", "")

print("Create validator...")
v0=JSONSchemaValidator();

print("Init schema...")
local jschema=JSON(); 
JSON_load_from_file(jschema, path.."schema.json");
print(JSON_dump(jschema))
v0:init(jschema)

print("Validate document...")
local jdocument=JSON(); 
JSON_load_from_file(jdocument, path.."instance.json"); 
print(JSON_dump(jdocument))
v0:validate_document(jdocument)