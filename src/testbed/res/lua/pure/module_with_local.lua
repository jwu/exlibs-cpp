-- ======================================================================================
-- File         : module_with_local.lua
-- Author       : Wu Jie 
-- Last Change  : 08/31/2010 | 16:47:20 PM | Tuesday,August
-- Description  : 
-- ======================================================================================

-- module setup
local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M

-- Import Section:

-- Method 1:
-- DISABLE { 
-- setmetatable(M, {__index = _G})
-- } DISABLE end 

-- Method 2:
-- DISABLE { 
-- -- Now you must prefix any global-variable name with _G. 
-- -- but the access is a little faster, because there is no metamethod involved.
-- local _G = _G
-- } DISABLE end 

-- Method 3:
-- declare everything this module needs from outside
local print = print

-- no more external access after this point
setfenv(1, M)

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function test()
    print("module_with_local.test() invoked!")
end
