// Copyright (C) 2006 — 2020 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#pragma once

#define NOT_USE_CRY_MEMORY_MANAGER

#include <CryCore/Project/CryModuleDefs.h>
#define eCryModule eCryM_EnginePlugin

#include <CryCore/Platform/platform.h>
#include <CrySystem/ISystem.h>
#include <Cry3DEngine/I3DEngine.h>
#include <CryNetwork/ISerialize.h>

#include "CVars.h"

#define TITLE "[Xsolla-Login] "
#define SDK_VERSION "0.1"

#if !defined (_RELEASE) && !defined (CRY_IS_MONOLITHIC_BUILD)
#define DEBUG_LOGGING 1 
#else
#define DEBUG_LOGGING 0
#endif

//! Logging system
#define Log(...) do {  CryLog (TITLE __VA_ARGS__); } while(0)
#define LogAlways(...) do { CryLogAlways (TITLE __VA_ARGS__); } while(0)
#define LogWarning(...) do { CryWarning(VALIDATOR_MODULE_ONLINE, VALIDATOR_WARNING, TITLE __VA_ARGS__); } while(0)
#define LogError(...) do { CryWarning(VALIDATOR_MODULE_ONLINE, VALIDATOR_ERROR, TITLE __VA_ARGS__); } while(0)

#if DEBUG_LOGGING
#define LogDebug(...) do {  CryLog (TITLE __FUNCTION__ "() " __VA_ARGS__); } while(0)
#else
#define LogDebug(...) {}
#endif

//! Useful macros
#ifdef TODO
#undef TODO
#define TODO(msg) __pragma(message("[TODO] " __FUNCTION__ "() " msg))
#else
#define TODO(msg) __pragma(message("[TODO] " __FUNCTION__ "() " msg))
#endif 

#ifdef DEPRECATED
#undef DEPRECATED
#define DEPRECATED(msg) __pragma(message("[DEPRECATED] " msg))
#else
#define DEPRECATED(msg) __pragma(message("[DEPRECATED] " msg))
#endif

namespace Xsolla
{
	namespace Login
	{
		class CXsollaLoginPlugin;

		extern CXsollaLoginPlugin* g_pPlugin;
		extern CCvars* g_pCVars;
	}
}