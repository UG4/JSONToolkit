-- ugshell -ex ../../plugins/JSONToolkit/test/test.lua --path $UG4_ROOT/plugins/JSONToolkit/test/basic-01-person/

ug_load_script("ug_util.lua")
local path = util.GetParam("--path", "")

print("Create validator...")
v0=JSONSchemaValidator();

-- A) Init schema
print("Init schema...")
local jschema=JSON(); 
JSON_load_from_file(jschema, path.."schema.json");
print(JSON_dump(jschema))
v0:init(jschema)

-- B) Validate JSON from file. 
print("Validating documents...")
local jdocument=JSON(); 
JSON_load_from_file(jdocument, path.."instance.json"); 
print("|"..JSON_dump(jdocument).."|")
v0:validate_document(jdocument)


-- C) Validate JSON from LUA table. 
print("\nValidating LUA table...")
local mypersons = {
    {name="Petra Mueller", age=43},  -- correct
    {vorname="Oskar Alt", age=73},   -- incorrect (name is missing)
    {name="Helene Jung", age=0}      -- incorrect (age<2)
}

for i,luaperson in ipairs(mypersons) do
    JSON_parse(jdocument, util.json.encode(luaperson))
    print("|"..JSON_dump(jdocument).."|")
    v0:validate_document(jdocument)
end



