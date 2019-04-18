// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#include "StdAfx.h"
#include "Plugin.h"


#include <CryCore/Platform/platform_impl.inl>

namespace Xsolla
{
	namespace Login 
	{
		CXsollaLoginPlugin::~CXsollaLoginPlugin()
		{
			if (!isShutdown)
			{
				Shutdown();
			}
		}

		void CXsollaLoginPlugin::Shutdown()
		{
			g_pPlugin = nullptr;

			m_listeners.clear();

			gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);

			m_pHttpWorker.reset();

			g_pCVars->Unregister();
			SAFE_DELETE(g_pCVars);
		}

		bool CXsollaLoginPlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
		{
			gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this, "CXsollaLoginPlugin");

			m_pHttpWorker.reset(new CHttpWorker());

			g_pPlugin = this;

			return true;
		}

		void CXsollaLoginPlugin::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
		{
			switch (event)
			{
			case ESYSTEM_EVENT_GAME_FRAMEWORK_INIT_DONE:
			{
				g_pCVars->Register();
				break;
			}
			case ESYSTEM_EVENT_FULL_SHUTDOWN:
			case ESYSTEM_EVENT_FAST_SHUTDOWN:
			{
				isShutdown = true;
				Shutdown();
				break;
			}
			default:
				break;
			}
		}

		void CXsollaLoginPlugin::RegisterListener(IXsollaLoginListener * pListener)
		{
			if (!stl::find(m_listeners, pListener) && pListener != nullptr)
				m_listeners.push_back(pListener);
		}

		void CXsollaLoginPlugin::RemoveListener(IXsollaLoginListener * pListener)
		{
			stl::find_and_erase(m_listeners, pListener);
		}

		void CXsollaLoginPlugin::Request_Authorization(const char * username, const char * password, bool rememberMe)
		{
			if (string(password).size() < 6)
			{
				Notify_AuthorizationError("@ui_error_short_password", 0, false);
			}
			else
			{
				m_pHttpWorker->Request_Authorization(username, password, rememberMe);
			}		
		}

		void CXsollaLoginPlugin::Request_Registration(const char * username, const char * password, const char* email)
		{
			if (string(password).size() < 6)
			{
				Notify_RegistrationError("@ui_error_short_password", 0, false);
			}
			else
			{
				m_pHttpWorker->Request_Registration(username, password, email);
			}
		}

		void CXsollaLoginPlugin::Request_PasswordRecovery(const char * username)
		{
			m_pHttpWorker->Request_RecoveryPassword(username);
		}

		void CXsollaLoginPlugin::Notify_AuthorizationSuccess(const char* token)
		{
			for (const auto &it : m_listeners)
			{
				it->AuthorizationSuccess(token);
			}
		}

		void CXsollaLoginPlugin::Notify_AuthorizationError(const char * errorStr, uint16 errorCode, bool isRawError)
		{
			for (const auto &it : m_listeners)
			{
				it->AuthorizationError(errorStr, errorCode, isRawError);
			}
		}

		void CXsollaLoginPlugin::Notify_RegistrationSuccess()
		{
			for (const auto &it : m_listeners)
			{
				it->RegistrationSuccess();
			}
		}

		void CXsollaLoginPlugin::Notify_RegistrationError(const char * errorStr, uint16 errorCode, bool isRawError)
		{
			for (const auto &it : m_listeners)
			{
				it->RegistrationError(errorStr, errorCode, isRawError);
			}
		}

		void CXsollaLoginPlugin::Notify_RecoveryPasswordSuccess()
		{
			for (const auto &it : m_listeners)
			{
				it->RecoveryPasswordSuccess();
			}
		}

		void CXsollaLoginPlugin::Notify_RecoveryPasswordError(const char * errorStr, uint16 errorCode, bool isRawError)
		{
			for (const auto &it : m_listeners)
			{
				it->RecoveryPasswordError(errorStr, errorCode, isRawError);
			}
		}

		CRYREGISTER_SINGLETON_CLASS(CXsollaLoginPlugin)
	}
}