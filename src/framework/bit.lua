--[[
    Description: Encapsulate bit operations.
    Author: M.Wan
    Date: 04/26/2014
]]

bit = {}

bit.data32 = {
    2147483648,
    1073741824,
    536870912,
    268435456,
    134217728,
    67108864,
    33554432,
    16777216,
    8388608,
    4194304,
    2097152,
    1048576,
    524288,
    262144,
    131072,
    65536,
    32768,
    16384,
    8192,
    4096,
    2048,
    1024,
    512,
    256,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    1
}

--[[
    Convert to binary.
    @param arg Number
    @return Bits array (32 bits)
]]
function bit:d2b(arg)
    assert(type(arg) == "number", "Invalid params.")
    local tr = {}
    for i = 1, 32 do
        if arg >= self.data32[i] then
            tr[i] = 1
            arg = arg - self.data32[i]
        else
            tr[i] = 0
        end
    end
    return tr
end

--[[
    Convert to integer.
    @param arg Bits array (32 bits)
    @return Number
]]
function bit:b2d(arg)
    assert(type(arg) == "table" and #arg == 32, "Invalid params.")
    local nr = 0
    for i = 1, 32 do
        if arg[i] == 1 then
            nr = nr + 2 ^ (32 - i)
        end
    end
    return nr
end

--[[
    Bit xor operation.
]]
function bit:op_xor(a, b)
    assert(type(a) == "number" and type(b) == "number", "Invalid params.")
    local op1 = self:d2b(a)
    local op2 = self:d2b(b)
    local r = {}

    for i = 1, 32 do
        if op1[i] == op2[i] then
            r[i] = 0
        else
            r[i] = 1
        end
    end
    return self:b2d(r)
end

--[[
    Bit and operation.
]]
function bit:op_and(a, b)
    assert(type(a) == "number" and type(b) == "number", "Invalid params.")
    local op1 = self:d2b(a)
    local op2 = self:d2b(b)
    local r = {}
    
    for i = 1, 32 do
        if op1[i] == 1 and op2[i] == 1 then
            r[i] = 1
        else
            r[i] = 0
        end
    end
    return self:b2d(r)
    
end

--[[
    Bit or operation.
]]
function bit:op_or(a, b)
    assert(type(a) == "number" and type(b) == "number", "Invalid params.")
    local op1 = self:d2b(a)
    local op2 = self:d2b(b)
    local r = {}
    
    for i = 1, 32 do
        if op1[i] == 1 or op2[i] == 1 then
            r[i] = 1
        else
            r[i] = 0
        end
    end
    return self:b2d(r)
end

--[[
    Bit not operation.
]]
function bit:op_not(a)
    assert(type(a) == "number", "Invalid params.")
    local op1 = self:d2b(a)
    local r = {}

    for i = 1, 32 do
        if op1[i] == 1 then
            r[i] = 0
        else
            r[i] = 1
        end
    end
    return self:b2d(r)
end

--[[
    Bit right shift operation.
]]
function bit:rshift(a, n)
    assert(type(a) == "number" and type(n) == "number", "Invalid params.")
    local op1 = self:d2b(a)
    local r = self:d2b(0)
    
    if n < 32 and n > 0 then
        for i = 1, n do
            for i = 31, 1, -1 do
                op1[i + 1] = op1[i]
            end
            op1[1] = 0
        end
        r = op1
    end
    return self:b2d(r)
end

--[[
    Bit left shift operation.
]]
function bit:lshift(a, n)
    assert(type(a) == "number" and type(n) == "number", "Invalid params.")
    local op1 = self:d2b(a)
    local r = self:d2b(0)
    
    if n < 32 and n > 0 then
        for i = 1, n do
            for i = 1, 31 do
                op1[i] = op1[i + 1]
            end
            op1[32] = 0
        end
        r = op1
    end
    return self:b2d(r)
end