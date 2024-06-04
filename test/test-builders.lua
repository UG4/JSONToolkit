-- Example: Create object via factory 
-- Note: This requires feature-json-schema branch.

ug_load_script("ug_util.lua")

-- Option 1: defaults.
local builder = JacobiBuilderCPU1()
desc1 = builder:get_default()
print(desc1) 

-- Option 2: LUA table => JSON object
desc2 = util.json.encode({damp=0.75, bBlock=true})
print(desc2) -- or: print(JSON_dump(jdesc))

-- Create JSON object.
jdesc2=JSON()
JSON_parse(jdesc2, desc2)

-- Create UG4 object.
jac=JacobiBuilderCPU1(jdesc2):build()
print(jac:config_string())