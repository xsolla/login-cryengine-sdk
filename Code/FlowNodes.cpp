// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#include "StdAfx.h"
#include "Plugin.h"
#include <Xsolla/Login/IXsollaLoginSDK.h>
#include <CryFlowGraph/IFlowBaseNode.h>
#include <FlashUI/FlashUI.h>


namespace Xsolla
{
	namespace Login
	{
		//! Authorization flownode
		class CFlowNode_XsollaAuthorization
			: public CFlowBaseNode<eNCT_Singleton>
			, public IXsollaLoginListener
		{
		private:
			enum EInputPorts
			{
				eIP_Auth = 0,
				eIP_Username,
				eIP_Password,
				eIP_RememberMe,
			};

			enum EOutputPorts
			{
				eOP_AuthComplete,
				eOP_AuthError,
				eOP_ErrorCode,
				eOP_IsRawError,
			};

		public:
			CFlowNode_XsollaAuthorization(SActivationInfo* pActInfo) {}
			~CFlowNode_XsollaAuthorization() {}

			virtual void GetConfiguration(SFlowNodeConfig& config)
			{
				static const SInputPortConfig in_config[] =
				{
					InputPortConfig_Void("Auth"),
					InputPortConfig<string>("Username"),
					InputPortConfig<string>("Password"),
					InputPortConfig<bool>("RememberMe", false),
					{ 0 }
				};
				static const SOutputPortConfig out_config[] =
				{
					OutputPortConfig_AnyType("AuthComplete"),
					OutputPortConfig<string>("AuthError"),
					OutputPortConfig<int>("ErrorCode"),
					OutputPortConfig<bool>("IsRawError"),
					{ 0 }
				};

				config.pInputPorts = in_config;
				config.pOutputPorts = out_config;
				config.SetCategory(EFLN_APPROVED);
			}
			virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
			{
				if (event == eFE_Activate)
				{
					m_pActInfo = *pActInfo;

					if (IsPortActive(pActInfo, eIP_Auth))
					{
						string username = GetPortString(pActInfo, eIP_Username);
						string password = GetPortString(pActInfo, eIP_Password);
						bool rememberMe = GetPortBool(pActInfo, eIP_RememberMe);
						
						g_pPlugin->RegisterListener(this);
						g_pPlugin->Request_Authorization(username.c_str(), password.c_str(), rememberMe);
					}
				}
			}

			virtual void GetMemoryUsage(ICrySizer* s) const
			{
				s->Add(*this);
			}
		public:
			// IXsollaLoginListener
			virtual void AuthorizationSuccess(const char* token) override
			{
				ActivateOutput(&m_pActInfo, eOP_AuthComplete, true);
			}

			virtual void AuthorizationError(const char* errorStr, uint16 errorCode, bool isRawError) override
			{
				ActivateOutput(&m_pActInfo, eOP_IsRawError, isRawError);
				ActivateOutput(&m_pActInfo, eOP_AuthError, (string)errorStr);
				ActivateOutput(&m_pActInfo, eOP_ErrorCode, (int)errorCode);
			}

			virtual void RegistrationSuccess() override {}
			virtual void RegistrationError(const char* errorStr, uint16 errorCode, bool isRawError) override {}
			virtual void RecoveryPasswordSuccess() override {}
			virtual void RecoveryPasswordError(const char* errorStr, uint16 errorCode, bool isRawError) override {}
			// ~IXsollaLoginListener
		private:
			SActivationInfo m_pActInfo;
		};

		//! Registration flownode
		class CFlowNode_XsollaRegistration
			: public CFlowBaseNode<eNCT_Singleton>
			, public IXsollaLoginListener
		{
		private:
			enum EInputPorts
			{
				eIP_Registration = 0,
				eIP_Username,
				eIP_Password,
				eIP_Email,
			};

			enum EOutputPorts
			{
				eOP_RegComplete,
				eOP_RegError,
				eOP_ErrorCode,
				eOP_IsRawError,
			};

		public:
			CFlowNode_XsollaRegistration(SActivationInfo* pActInfo) {}
			~CFlowNode_XsollaRegistration() {}

			virtual void GetConfiguration(SFlowNodeConfig& config)
			{
				static const SInputPortConfig in_config[] =
				{
					InputPortConfig_Void("Registration"),
					InputPortConfig<string>("Username"),
					InputPortConfig<string>("Password"),
					InputPortConfig<string>("EMail"),
					{ 0 }
				};
				static const SOutputPortConfig out_config[] =
				{
					OutputPortConfig_AnyType("RegComplete"),
					OutputPortConfig<string>("RegError"),
					OutputPortConfig<int>("ErrorCode"),
					OutputPortConfig<bool>("IsRawError"),
					{ 0 }
				};

				config.pInputPorts = in_config;
				config.pOutputPorts = out_config;
				config.SetCategory(EFLN_APPROVED);
			}
			virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
			{
				if (event == eFE_Activate)
				{
					m_pActInfo = *pActInfo;

					if (IsPortActive(pActInfo, eIP_Registration))
					{
						string username = GetPortString(pActInfo, eIP_Username);
						string password = GetPortString(pActInfo, eIP_Password);
						string email = GetPortString(pActInfo, eIP_Email);

						g_pPlugin->RegisterListener(this);
						g_pPlugin->Request_Registration(username.c_str(), password.c_str(), email.c_str());
					}
				}
			}

			virtual void GetMemoryUsage(ICrySizer* s) const
			{
				s->Add(*this);
			}
		public:
			// IXsollaLoginListener
			virtual void AuthorizationSuccess(const char* token) override {}
			virtual void AuthorizationError(const char* errorStr, uint16 errorCode, bool isRawError) override {}

			virtual void RegistrationSuccess() override
			{
				ActivateOutput(&m_pActInfo, eOP_RegComplete, true);
			};

			virtual void RegistrationError(const char* errorStr, uint16 errorCode, bool isRawError) override
			{
				ActivateOutput(&m_pActInfo, eOP_IsRawError, isRawError);
				ActivateOutput(&m_pActInfo, eOP_RegError, (string)errorStr);
				ActivateOutput(&m_pActInfo, eOP_ErrorCode, (int)errorCode);
			};

			virtual void RecoveryPasswordSuccess() override {}
			virtual void RecoveryPasswordError(const char* errorStr, uint16 errorCode, bool isRawError) override {}
			// ~IXsollaLoginListener
		private:
			SActivationInfo m_pActInfo;
		};

		//! Registration flownode
		class CFlowNode_XsollaRecoveryPassword
			: public CFlowBaseNode<eNCT_Singleton>
			, public IXsollaLoginListener
		{
		private:
			enum EInputPorts
			{
				eIP_Recovery = 0,
				eIP_Username,
			};

			enum EOutputPorts
			{
				eOP_RecoveryComplete,
				eOP_RecoveryError,
				eOP_ErrorCode,
				eOP_IsRawError,
			};

		public:
			CFlowNode_XsollaRecoveryPassword(SActivationInfo* pActInfo) {}
			~CFlowNode_XsollaRecoveryPassword() {}

			virtual void GetConfiguration(SFlowNodeConfig& config)
			{
				static const SInputPortConfig in_config[] =
				{
					InputPortConfig_Void("Recovery"),
					InputPortConfig<string>("Username"),
					{ 0 }
				};
				static const SOutputPortConfig out_config[] =
				{
					OutputPortConfig_AnyType("RecoveryComplete"),
					OutputPortConfig<string>("RecoveryError"),
					OutputPortConfig<int>("ErrorCode"),
					OutputPortConfig<bool>("IsRawError"),
					{ 0 }
				};

				config.pInputPorts = in_config;
				config.pOutputPorts = out_config;
				config.SetCategory(EFLN_APPROVED);
			}
			virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
			{
				if (event == eFE_Activate)
				{
					m_pActInfo = *pActInfo;

					if (IsPortActive(pActInfo, eIP_Recovery))
					{
						string username = GetPortString(pActInfo, eIP_Username);

						g_pPlugin->RegisterListener(this);
						g_pPlugin->Request_PasswordRecovery(username.c_str());
					}
				}
			}

			virtual void GetMemoryUsage(ICrySizer* s) const
			{
				s->Add(*this);
			}
		public:
			// IXsollaLoginListener
			virtual void AuthorizationSuccess(const char* token) override {}
			virtual void AuthorizationError(const char* errorStr, uint16 errorCode, bool isRawError) override {}
			virtual void RegistrationSuccess() override {}
			virtual void RegistrationError(const char* errorStr, uint16 errorCode, bool isRawError) override {}

			virtual void RecoveryPasswordSuccess() override 
			{
				ActivateOutput(&m_pActInfo, eOP_RecoveryComplete, true);
			}

			virtual void RecoveryPasswordError(const char* errorStr, uint16 errorCode, bool isRawError) override
			{
				ActivateOutput(&m_pActInfo, eOP_IsRawError, isRawError);
				ActivateOutput(&m_pActInfo, eOP_RecoveryError, (string)errorStr);
				ActivateOutput(&m_pActInfo, eOP_ErrorCode, (int)errorCode);
			}
			// ~IXsollaLoginListener
		private:
			SActivationInfo m_pActInfo;
		};
	}
}

REGISTER_FLOW_NODE_EX("Xsolla:Login:Authorization", Xsolla::Login::CFlowNode_XsollaAuthorization, CFlowNode_XsollaAuthorization);
REGISTER_FLOW_NODE_EX("Xsolla:Login:Registration", Xsolla::Login::CFlowNode_XsollaRegistration, CFlowNode_XsollaRegistration);
REGISTER_FLOW_NODE_EX("Xsolla:Login:RecoveryPassword", Xsolla::Login::CFlowNode_XsollaRecoveryPassword, CFlowNode_XsollaRecoveryPassword);