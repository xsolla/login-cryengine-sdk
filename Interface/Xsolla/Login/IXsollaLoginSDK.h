// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#pragma once

#include <CrySystem/ICryPlugin.h>

namespace Xsolla
{
	namespace Login
	{
		struct IXsollaLoginListener
		{
			virtual ~IXsollaLoginListener() {}

			virtual void AuthorizationSuccess(const char* token) = 0;
			virtual void AuthorizationError(const char* errorStr, uint16 errorCode, bool isRawError) = 0;

			virtual void RegistrationSuccess() = 0;
			virtual void RegistrationError(const char* errorStr, uint16 errorCode, bool isRawError) = 0;

			virtual void RecoveryPasswordSuccess() = 0;
			virtual void RecoveryPasswordError(const char* errorStr, uint16 errorCode, bool isRawError) = 0;
		};

		struct IXsollaLoginPlugin : public Cry::IEnginePlugin
		{
		public:
			CRYINTERFACE_DECLARE_GUID(IXsollaLoginPlugin, "DF83B9CC-4386-400F-8731-74834713ACBE"_cry_guid);
		public:
			virtual void RegisterListener(IXsollaLoginListener* pListener) = 0;
			virtual void RemoveListener(IXsollaLoginListener* pListener) = 0;

			virtual void Request_Authorization(const char* username, const char* password, bool rememberMe) = 0;
			virtual void Request_Registration(const char* username, const char* password, const char* email) = 0;
			virtual void Request_PasswordRecovery(const char* username) = 0;

			virtual bool ValidateToken(const char * token, const char* key) = 0;
		};
	}
}