/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef UINT64METHODS_H
#define UINT64METHODS_H

/***
 * Lua can not represent uint64 values so we created support for it through our class system.
 *
 * Almost all metamethods including concat, tostring, comparing and math metamethods are implemented.
 * To convert an uint64 value back to a number you must call `tonumber(tostring(myuint64))` which returns nil if conversion failed.
 */
namespace Luauint64
{
    // Template by Mud from http://stackoverflow.com/questions/4484437/lua-integer-type/4485511#4485511
    int __add(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) + Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __sub(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) - Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __mul(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) * Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __div(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) / Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __mod(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) % Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __pow(lua_State* L, uint64* u)
    {
        Eluna::Push(L, static_cast<uint64>(powl(static_cast<long double>(*u), static_cast<long double>(Eluna::CHECKVAL<uint64>(L, 2)))));
        return 1;
    }
    int __eq(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) == Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __lt(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) < Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __le(lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) <= Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __tostring(lua_State* L, uint64* u)
    {
        Eluna::Push(L, std::to_string(*u));
        return 1;
    }
    int gc(lua_State* L, uint64* u)
    {
        Eluna::GetEluna(L)->storeduints.erase(*u);
        return ElunaTemplate<uint64>::CollectGarbage(L);
    }

    /**
     * Returns true if the value can be safely casted to a lua integer
     *
     * @return bool fits
     */
    int fitsint(lua_State* L, uint64* u)
    {
        if (*u <= static_cast<uint64>(std::numeric_limits<lua_Integer>::max()))
            Eluna::Push(L, true);
        else
            Eluna::Push(L, false);
        return 1;
    }

    /**
     * Casts the uint64 number into a lua integer and returns it
     *
     * @return int64 value
     */
    int toint(lua_State* L, uint64* u)
    {
        Eluna::Push(L, static_cast<lua_Integer>(*u));
        return 1;
    }

    /**
     * Casts the uint64 number into a lua number and returns it
     *
     * @return double value
     */
    int tonumber(lua_State* L, uint64* u)
    {
        Eluna::Push(L, static_cast<lua_Number>(*u));
        return 1;
    }

    /**
     * Returns the uint64 as a hex string
     *
     * @return int64 value
     */
    int tohex(lua_State* L, uint64* u)
    {
        std::ostringstream oss;
        oss << std::hex << *u;
        Eluna::Push(L, oss.str().c_str());
        return 1;
    }
};
#endif
