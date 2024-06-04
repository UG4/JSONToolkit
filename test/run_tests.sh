#!/bin/sh
ugshell -ex ../../plugins/JSONToolkit/test/test-validation.lua --path $UG4_ROOT/plugins/JSONToolkit/test/basic-01-person/

ugshell -ex ../../plugins/JSONToolkit/test/test-validation.lua --path $UG4_ROOT/plugins/JSONToolkit/test/basic-02-rectangle/

ugshell -ex ../../plugins/JSONToolkit/test/test-json-validation.lua --path $UG4_ROOT/plugins/JSONToolkit/test/basic-03-convcheck/solver.convcheck.

