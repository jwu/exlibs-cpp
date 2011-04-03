-- ======================================================================================
-- File         : test_module.lua
-- Author       : Wu Jie 
-- Last Change  : 08/31/2010 | 16:43:47 PM | Tuesday,August
-- Description  : 
-- ======================================================================================


local test = require("package.foo")
test.test_01.test()

require("package.module_see_all")
package.module_see_all.test()

local mm = require("package.module_see_all")
mm.test()

-- DISABLE: can't use this tech in sub module { 
-- require("package.module_with_local")
-- package.module_with_local.test()

-- local mm = require("package.module_with_local")
-- mm.test()
-- } DISABLE end 

-- NOTE: this will load module_with_local in current directory, not in directory package/ { 
require("module_with_local")
module_with_local.test()

local mm = require("module_with_local")
mm.test()
-- } NOTE end 

require("package.no_module")
test()

local mm = require("package.no_module")
if mm ~= nil then
    print ("no_module returns nil")
end

