#pragma once

#include "cinder/app/App.h"

extern "C" {
	#include "lauxlib.h"
	#include "lua.h"
	#include "lualib.h"
}
#include "LuaBridge/LuaBridge.h"

namespace xui {

class XNode;
    
class XScript 
{
public:
	XScript();
	~XScript();
        
	void bindNode(XNode* node);
	void loadString( const std::string& script );
	void loadFile( ci::DataSourceRef source );
	std::string getLastErrors();
    void gc();
	bool functionExists( const std::string& function );
	static void LuaGlobalBindAllChildren(XNode* node);

	// call lua functions
	void call( const std::string& function );
	template<typename T> T call( const std::string& function )
	{
		T result;
            
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return result;
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			result = functionRef();
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
		return result;
	}   
	template<typename T, typename Arg> T call( const std::string& function, const Arg& arg )
	{
		T result;
            
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;     
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			result = functionRef(arg);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
		return result;
	}
	template<typename Arg> void call( const std::string& function, const Arg& arg )
	{
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			functionRef(arg);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
	}
	template<typename T, typename Arg1, typename Arg2> T call( const std::string& function, const Arg1& arg1, const Arg2& arg2 )
	{
		T result;
            
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;     
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			result = functionRef(arg1, arg2);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
		return result;
	}
	template<typename Arg1, typename Arg2> void call( const std::string& function, const Arg1& arg1, const Arg2& arg2 )
	{
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			functionRef(arg1, arg2);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
	}
	template<typename T, typename Arg1, typename Arg2, typename Arg3> T call( const std::string& function, const Arg1& arg1, const Arg2& arg2, const Arg3& arg3 )
	{
		T result;
            
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;     
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			result = functionRef(arg1, arg2, arg3);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
		return result;
	}
	template<typename Arg1, typename Arg2, typename Arg3> void call( const std::string& function, const Arg1& arg1, const Arg2& arg2, const Arg3& arg3 )
	{
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			functionRef(arg1, arg2, arg3);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
	}
	template<typename T, typename Arg1, typename Arg2, typename Arg3, typename Arg4> T call( const std::string& function, const Arg1& arg1, const Arg2& arg2, const Arg3& arg3, const Arg4& arg4 )
	{
		T result;
            
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;     
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			result = functionRef(arg1, arg2, arg3, arg4);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
		return result;
	}
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4> void call( const std::string& function, const Arg1& arg1, const Arg2& arg2, const Arg3& arg3, const Arg4& arg4 )
	{
		if( !functionExists( function ) || ( mStopOnErrors && mErrors ) )
			return;
		try
		{
			luabridge::LuaRef functionRef = luabridge::getGlobal(mState, function.c_str());
			functionRef(arg1, arg2, arg3, arg4);
			mErrors = false;
		}
		catch (luabridge::LuaException const& e) 
		{
			mErrors = true;
			mLastErrorString = e.what();
			ci::app::console() << "Lua Error trying to call " << function << " : " << std::endl << e.what() << std::endl;
		}
	}

        
    lua_State* getState(){ return mState; }

private:
    static int panic( lua_State* L );
	void addClassSupport();
        
    std::string getErrorMessage();
        
	lua_State*					mState;

	std::string                 mLastErrorString;
	bool                        mStopOnErrors;
	bool                        mErrors;
};

}