-- Example: Create object via factory 
-- Note: This requires feature-json-schema branch.

ug_load_script("ug_util.lua")

-- Option 1: defaults.
desc1 = JSON_GetDefault_JacobiCPU1()
print(desc1) 

-- Option 2: LUA table => JSON object
desc2 = util.json.encode({damp=0.75, bBlock=true})
print(desc2) -- or: print(JSON_dump(jdesc))

-- Create JSON object.
jdesc=JSON()
JSON_parse(jdesc, desc2)

-- Create UG4 object.
jac=JSONFactory_Smart_JacobiCPU1(jdesc)
print(jac:config_string())