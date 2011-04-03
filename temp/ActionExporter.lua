-- ======================================================================================
-- File         : ActionExporter.lua
-- Author       : Wu Jie 
-- Last Change  : 09/10/2010 | 14:06:25 PM | Friday,September
-- Description  : 
-- ======================================================================================

require("lxp.dom")

print("start load action.xml...")
local f = assert( io.open("./action.xml", "r") )
local t = f:read("*all")
f:close()
local dom = lxp.dom.parse(t)
for k,v in pairs(dom[1].attr) do
    print ( "key = " .. tostring(k) .. ", value = " .. tostring(v) )
end

