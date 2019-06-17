// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#include "StdAfx.h"
#include "CVars.h"

namespace Xsolla
{
	namespace Login
	{
		void CCvars::Register()
		{
			m_pProjectID = REGISTER_STRING("xl_login_project_id", "", VF_CHEAT | VF_INVISIBLE, "Project ID");
			m_pCallbackURL = REGISTER_STRING("xl_login_callback_url", "https://login.xsolla.com/api/blank", VF_CHEAT | VF_INVISIBLE, "Callback url");

			REGISTER_CVAR2("xl_login_http_timeout", &m_http_timeout, 5, VF_NULL, "Http timeout in seconds");
			REGISTER_CVAR2("xl_login_log_level", &m_log_level, 0, VF_CHEAT | VF_INVISIBLE, "Log level (0-2)");
			REGISTER_CVAR2("xl_login_storage_type", &m_storageType, 0, VF_CHEAT | VF_INVISIBLE, "Storage type (0 - Xsolla, 1 - Custom)");
		}

		void CCvars::Unregister()
		{
			gEnv->pConsole->UnregisterVariable("xl_login_project_id", true);
			gEnv->pConsole->UnregisterVariable("xl_login_callback_url", true);

			gEnv->pConsole->UnregisterVariable("xl_login_http_timeout", true);
			gEnv->pConsole->UnregisterVariable("xl_login_log_level", true);
			gEnv->pConsole->UnregisterVariable("xl_login_storage_type", true);
		}
	}
}