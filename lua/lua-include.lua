-- Copyright (c) 2020:  G-CSC, Goethe University Frankfurt
-- Author: Tim Schön
-- 
-- This file is part of UG4.
-- 
-- UG4 is free software: you can redistribute it and/or modify it under the
-- terms of the GNU Lesser General Public License version 3 (as published by the
-- Free Software Foundation) with the following additional attribution
-- requirements (according to LGPL/GPL v3 §7):
-- 
-- (1) The following notice must be displayed in the Appropriate Legal Notices
-- of covered and combined works: "Based on UG4 (www.ug4.org/license)".
-- 
-- (2) The following notice must be displayed at a prominent place in the
-- terminal output of covered works: "Based on UG4 (www.ug4.org/license)".
-- 
-- (3) The following bibliography is recommended for citation and must be
-- preserved in all covered files:
-- "Reiter, S., Vogel, A., Heppner, I., Rupp, M., and Wittum, G. A massively
--   parallel geometric multigrid solver on hierarchically distributed grids.
--   Computing and visualization in science 16, 4 (2013), 151-164"
-- "Vogel, A., Reiter, S., Rupp, M., Nägel, A., and Wittum, G. UG4 -- a novel
--   flexible software system for simulating pde based models on high performance
--   computers. Computing and visualization in science 16, 4 (2013), 165-179"
-- 
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
-- GNU Lesser General Public License for more details.

--------------------------------------------------------------------------------
--[[!
Provides the necessary Lua parts for usage of the ParameterSet-class 
from common/until/parameter_set.h.

Allows to easily read in parameters from JSON-files, creating complex C++
parameter objects and using them as for example as follows

params = {
	permeability = { type="number",	value= 1.0e-11 },
	porosity = { type="number",	value= 0.1 },

    silt = {
      type = "VanGenuchtenModel",
      thetaS = 0.396, thetaR = 0.350,
	  alpha = 0.423, n = 3.06, Ksat= 1.0
	}
}

local p = util.Parameters:fromtable(params)

p.porosity    ----- will output 0.1 and can be used anywhere in the problem
p.silt		--- will represent a VanGenuchtenModel-C++-Object and can be used anywhere in the problem

To use C++ classes in this way, they need to have a constructor with one "const char*" argument, which needs to be registered
with "jsonConstructor=true". The constructor argument will contain a json representation of the parameters for this parameter, in
the example above "{ thetaS = 0.396, thetaR = 0.350, alpha = 0.423, n = 3.06, Ksat= 1.0 }".

]]--
--------------------------------------------------------------------------------

print ("Loading JSONToolkit...")
util = util or {}

if util.Parameters == nil then

	util.Parameters = {}

	if (not util.json) then
		print("ERROR: JSONToolkit requires USE_JSON in ugcore. ")
		-- exit();
	end

	-- Use util.json (from ugcore) -- ug_load_script("json.lua")
	local json = util.json 

	-- Provides an constructor that will create an empty parameter object
	function util.Parameters:new()
		local Tmp = {}
		setmetatable(Tmp,util.Parameters)
		Tmp.cppobject = ParameterSet()
		return Tmp
	end

	-- Provides an constructor that will read in the values for the parameters 
	-- from a LuaTable. To do so, the LuaTable will be converted to json and parsed in C++.
	function util.Parameters:fromtable(params)
		local Tmp = util.Parameters:new()
		Tmp.cppobject:loadJSON(json.encode(params))
		return Tmp
	end

	-- Provides an constructor that will read in the parameter values from a JSON-file.
	-- The file will be parsed in C++.
	function util.Parameters:fromfile(filename)
		local Tmp = util.Parameters:new()
		Tmp.cppobject:loadJSONFile(filename)
		return Tmp
	end

	-- Overriding the __index-Function to provide easy access to the parameters;
	-- the parameter values are accessible as if they were members of the lua table.
	function util.Parameters.__index(self,index)	
		if index == "loadfile" or index == "loadjson" or index == "loadtable" then
			return rawget(util.Parameters,index)
		end		
		paramvalue = self.cppobject:get(index)	
		return paramvalue
	end 

	function util.Parameters.loadfile(self,filename)		
		self.cppobject:loadJSONFile(filename)
	end

	function util.Parameters.loadjson(self,jsonstring)	
		self.cppobject:loadJSON(jsonstring)
	end

	function util.Parameters.loadtable(self, table)	
		self.cppobject:loadJSON(json.encode(table))
	end
end

-- util.ParametersLua = {}
-- function util.ParametersLua.CreateParameter(param)
-- 	if (param.type == "const") then
-- 		print("added const param")
-- 		return param.value
-- 	elseif _G[param.type] ~= nil then
-- 		return _G[param.type](json.encode(param))
-- 	end
-- end

-- function util.ParametersLua.__index(self,index)	
-- 	print(index)
-- 	return self.parameters[index]	
-- end 

-- function util.ParametersLua:new()
-- 	local Tmp = { }
-- 	Tmp.parameters = {}
-- 	setmetatable(Tmp,util.ParametersLua)
	
-- 	Tmp.loadJSONFile = function(filename)	
-- 		file = io.open(filename, "r")
-- 		fileparameters = file:read("*all")	
-- 		fileparametertable = json.decode(fileparameters)
	
-- 		for index,value in ipairs(fileparametertable) do
-- 			Tmp.parameters[index] = util.ParametersLua.CreateParameter(value)
-- 		end	
-- 	end 
	
-- 	Tmp.loadLUATable = function(params)
-- 		for index,value in pairs(params) do
-- 			Tmp.parameters[index] = util.ParametersLua.CreateParameter(value)
-- 		end
-- 	end

--     return Tmp
-- end

-- function util.ParametersLua:load(params)
--     local Tmp = util.ParametersLua:new()
	
-- 	Tmp.loadLUATable(params)

--     return Tmp
-- end

-- function util.ParametersLua:fromfile(filename)
--     local Tmp = util.ParametersLua:new()
	
-- 	Tmp.loadJSONFile(filename)

--     return Tmp
-- end

