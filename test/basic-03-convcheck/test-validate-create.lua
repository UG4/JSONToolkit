-- Load util (for util.json)
ug_load_script("ug_util.lua")

------------------------------------------------------------
-- First version: Configuration using defaults.
------------------------------------------------------------
local convCheck = ConvCheckBuilderCPU1():build()
print("\n#1:"..convCheck:config_string())
print("build on defaults: "..ConvCheckBuilder(jdesc):get_defaults():dump())

------------------------------------------------------------
-- Second version: Configuration via descriptor.
------------------------------------------------------------
local luadesc = {					
	type = "standard",
	iterations = 25,
	reduction = 1e-6,
	absolute = 1e-12
}

local jdesc=JSON_create(util.json.encode(luadesc)) 
convCheck = ConvCheckBuilderCPU1(jdesc):build()

print("\n#2:"..convCheck:config_string())
print("\n built from "..JSON_dump(jdesc).."\n")

------------------------------------------------------------
-- Third version: Validate object before creating object:
------------------------------------------------------------
-- Create validator
local v0=JSONSchemaValidator();
local jschema=JSON_create_from_file("solver.convcheck.schema.json");
v0:init(jschema)


-- Create object, if descriptor is valid
InitUG(2, AlgebraType("CPU",2))
if (v0:validate_document(jdesc)) then
	convCheck = ConvCheckBuilder(jdesc):build()
	print("\n#3:"..convCheck:config_string())
end




