/*
 * framework/core/l-stage.c
 *
 * Copyright(c) 2007-2018 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <framework/core/l-stage.h>

static const char stage_lua[] = X(
local Display = require "graphic.display"

local M = Class(DisplayObject)

function M:init()
	self.exiting = false
	self.display = Display.new()
	self.super:init(self.display:getSize())
end

function M:getSize()
	return self.display:getSize()
end

function M:getPhysicalSize()
	return self.display:getPhysicalSize()
end

function M:getBpp()
	return self.display:getBpp()
end

function M:setBacklight(brightness)
	return self.display:setBacklight(brightness)
end

function M:getBacklight()
	return self.display:getBacklight()
end

function M:showfps(value)
	self.display:showfps(value)
	return self
end

function M:exit()
	self.exiting = true
	return self
end

function M:loop()
	local Event = Event
	local display = self.display

	while not self.exiting do
		self:render(Event.new(Event.ENTER_FRAME))
		display:present()
	end
end

return M
);

int luaopen_stage(lua_State * L)
{
	if(luaL_loadbuffer(L, stage_lua, sizeof(stage_lua) - 1, "Stage.lua") == LUA_OK)
		lua_call(L, 0, 1);
	return 1;
}
