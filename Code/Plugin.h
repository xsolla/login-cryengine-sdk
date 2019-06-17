// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#pragma once

#include "Worker.h"

#include <Xsolla/Login/IXsollaLoginSDK.h>

#include <CrySystem/ICryPlugin.h>

namespace Xsolla
{
	namespace Login
	{
		class CXsollaLoginPlugin : public IXsollaLoginPlugin, public ISystemEventListener
		{
		public:
			CRYINTERFACE_BEGIN()
			CRYINTERFACE_ADD(IXsollaLoginPlugin)
			CRYINTERFACE_ADD(Cry::IEnginePlugin)
			CRYINTERFACE_END()
			CRYGENERATE_SINGLETONCLASS_GUID(CXsollaLoginPlugin, "XsollaLogin", "64125DBE-5C9E-4C30-B7B5-27F1E574C80C"_cry_guid);

			PLUGIN_FLOWNODE_REGISTER;
			PLUGIN_FLOWNODE_UNREGISTER;
		public:
			virtual ~CXsollaLoginPlugin();

			// Cry::IEnginePlugin
			virtual bool                       Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;
			// ~Cry::IEnginePlugin
		public:
			// ISystemEventListener
			virtual void                       OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
			// ~ISystemEventListener
		public:
			// IXsollaLoginPlugin
			virtual void                       RegisterListener(IXsollaLoginListener* pListener) override;
			virtual void                       RemoveListener(IXsollaLoginListener* pListener) override;
						                       
			virtual void                       Request_Authorization(const char* username, const char* password, bool rememberMe) override;
			virtual void                       Request_Registration(const char* username, const char* password, const char* email) override;
			virtual void                       Request_PasswordRecovery(const char* username) override;

			virtual bool                       ValidateToken(const char * token, const char* key) override;
			// ~IXsollaLoginPlugin
		public:
			void                               Notify_AuthorizationSuccess(const char* token);
			void                               Notify_AuthorizationError(const char* errorStr, uint16 errorCode, bool isRawError);

			void                               Notify_RegistrationSuccess();
			void                               Notify_RegistrationError(const char* errorStr, uint16 errorCode, bool isRawError);

			void                               Notify_RecoveryPasswordSuccess();
			void                               Notify_RecoveryPasswordError(const char* errorStr, uint16 errorCode, bool isRawError);
		private:
			void                               Shutdown();
		private:
			std::vector<IXsollaLoginListener*> m_listeners;
			std::unique_ptr<CHttpWorker>       m_pHttpWorker = nullptr;
			bool                               isShutdown = false;
		};
	}
}