// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#include "StdAfx.h"
#include "Worker.h"

#pragma warning( disable : 4266 ) // Json warning disable
#include <cpprest/http_client.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

namespace Xsolla
{
	namespace Login
	{
		void CHttpWorker::Request_Authorization(const char * username, const char * password, bool rememberMe)
		{
			string_t apiUrlStr;

			if (g_pCVars->m_storageType == EStorageType::EStorage_Xsolla)
			{
				apiUrlStr = U("https://login.xsolla.com/api/login");
			}
			else
			{
				apiUrlStr = U("https://login.xsolla.com/api/proxy/login");
			}

			uri_builder builder(apiUrlStr);
			builder.append_query(U("projectId"), conversions::to_string_t(g_pCVars->m_pProjectID->GetString()));
			builder.append_query(U("login_url"), conversions::to_string_t(g_pCVars->m_pCallbackURL->GetString()));

			http_client_config config;
			config.set_timeout(std::chrono::seconds(g_pCVars->m_http_timeout));

			http_client client(builder.to_uri(), config);

			char sProductVersion[128];
			gEnv->pSystem->GetProductVersion().ToString(sProductVersion);

			json::value postData;
			postData[U("username")] = json::value::string(conversions::to_string_t(username));
			postData[U("password")] = json::value::string(conversions::to_string_t(password));
			postData[U("remember_me")] = json::value::boolean(rememberMe);
			// Not best way, but used now. Need be replaced by headers later.
			postData[U("engine")] = json::value::string(U("cryengine"));
			postData[U("engine_v")] = json::value::string(conversions::to_string_t(sProductVersion));
			postData[U("sdk")] = json::value::string(U("login"));
			postData[U("sdk_v")] = json::value::string(conversions::to_string_t(SDK_VERSION));

			http_request msg(methods::POST);
			msg.set_request_uri(conversions::to_string_t(U("")));
			msg.set_body(postData.serialize().c_str(), U("application/json"));
			// Not used now, but can be used later
			//msg.headers().add(U("engine"), U("cryengine"));
			//msg.headers().add(U("engine_v"), conversions::to_string_t(sProductVersion));
			//msg.headers().add(U("sdk"), U("login"));
			//msg.headers().add(U("sdk_v"), conversions::to_string_t(SDK_VERSION));

			auto task = client.request(msg).then([=](http_response response)
			{
				Callback_Authorization(response);	
			});
		}

		void CHttpWorker::Request_Registration(const char * username, const char * password, const char* email)
		{
			string_t apiUrlStr;

			if (g_pCVars->m_storageType == EStorageType::EStorage_Xsolla)
			{
				apiUrlStr = U("https://login.xsolla.com/api/user");
			}
			else
			{
				apiUrlStr = U("https://login.xsolla.com/api/proxy/registration");
			}

			uri_builder builder(apiUrlStr);
			builder.append_query(U("projectId"), conversions::to_string_t(g_pCVars->m_pProjectID->GetString()));
			builder.append_query(U("login_url"), conversions::to_string_t(g_pCVars->m_pCallbackURL->GetString()));

			http_client_config config;
			config.set_timeout(std::chrono::seconds(g_pCVars->m_http_timeout));

			http_client client(builder.to_uri(), config);

			char sProductVersion[128];
			gEnv->pSystem->GetProductVersion().ToString(sProductVersion);

			json::value postData;
			postData[U("username")] = json::value::string(conversions::to_string_t(username));
			postData[U("password")] = json::value::string(conversions::to_string_t(password));
			postData[U("email")] = json::value::string(conversions::to_string_t(email));

			postData[U("engine")] = json::value::string(U("cryengine"));
			postData[U("engine_v")] = json::value::string(conversions::to_string_t(sProductVersion));
			postData[U("sdk")] = json::value::string(U("login"));
			postData[U("sdk_v")] = json::value::string(conversions::to_string_t(SDK_VERSION));

			http_request msg(methods::POST);
			msg.set_request_uri(conversions::to_string_t(U("")));
			msg.set_body(postData.serialize().c_str(), U("application/json"));
			//msg.headers().add(U("engine"), U("cryengine"));
			//msg.headers().add(U("engine_v"), conversions::to_string_t(sProductVersion));
			//msg.headers().add(U("sdk"), U("login"));
			//msg.headers().add(U("sdk_v"), conversions::to_string_t(SDK_VERSION));

			auto task = client.request(msg).then([=](http_response response)
			{
				Callback_Registration(response);
			});
		}

		void CHttpWorker::Request_RecoveryPassword(const char * username)
		{
			string_t apiUrlStr;

			if (g_pCVars->m_storageType == EStorageType::EStorage_Xsolla)
			{
				apiUrlStr = U("https://login.xsolla.com/api/password/reset/request");
			}
			else
			{
				apiUrlStr = U("https://login.xsolla.com/api/proxy/registration/password/reset");
			}

			uri_builder builder(apiUrlStr);
			builder.append_query(U("projectId"), conversions::to_string_t(g_pCVars->m_pProjectID->GetString()));
			builder.append_query(U("login_url"), conversions::to_string_t(g_pCVars->m_pCallbackURL->GetString()));

			char sProductVersion[128];
			gEnv->pSystem->GetProductVersion().ToString(sProductVersion);

			http_client_config config;
			config.set_timeout(std::chrono::seconds(g_pCVars->m_http_timeout));

			http_client client(builder.to_uri(), config);

			json::value postData;
			postData[U("username")] = json::value::string(conversions::to_string_t(username));

			postData[U("engine")] = json::value::string(U("cryengine"));
			postData[U("engine_v")] = json::value::string(conversions::to_string_t(sProductVersion));
			postData[U("sdk")] = json::value::string(U("login"));
			postData[U("sdk_v")] = json::value::string(conversions::to_string_t(SDK_VERSION));

			http_request msg(methods::POST);
			msg.set_request_uri(conversions::to_string_t(U("")));
			msg.set_body(postData.serialize().c_str(), U("application/json"));
			//msg.headers().add(U("engine"), U("cryengine"));
			//msg.headers().add(U("engine_v"), conversions::to_string_t(sProductVersion));
			//msg.headers().add(U("sdk"), U("login"));
			//msg.headers().add(U("sdk_v"), conversions::to_string_t(SDK_VERSION));

			auto task = client.request(msg).then([=](http_response response)
			{
				Callback_RecoveryPassword(response);
			});
		}

		void CHttpWorker::Callback_Authorization(http_response &response)
		{
			http::status_code code = response.status_code();
#ifndef RELEASE
			string_t rawResponseStr = response.to_string();
#endif
			if (code == 200)
			{
				auto jsonTask = response.extract_json().then([=](json::value json)
				{
					json::value tokenValue = json[U("login_url")];

					if (!tokenValue.is_null())
					{
						string_t tokenRawString = tokenValue.as_string();
						size_t start = tokenRawString.find(U("token="));
						start += 6;
						size_t end = tokenRawString.find('&');

						string_t clearTokenT = tokenRawString.substr(start, end - start);
						std::string clearToken = std::string(clearTokenT.begin(), clearTokenT.end()).c_str();

						g_pPlugin->Notify_AuthorizationSuccess(clearToken.c_str());
					}

				}).wait();
			}
			else
			{
				auto jsonTask = response.extract_json().then([=](json::value json)
				{
					json::value errorValue = json[U("error")];

					string errorStr;
					bool isRawError = false;

					if (!errorValue.is_null())
					{
						json::value errorCodeValue = errorValue[U("code")];

						if (!errorCodeValue.is_null() && errorCodeValue.is_string())
						{
							string_t rawErrorStr = errorCodeValue.as_string();
							std::string stdRawErrorStr = std::string(rawErrorStr.begin(), rawErrorStr.end());

							if (stdRawErrorStr == "003-001")
							{
								errorStr = "@ui_error_wrong_user_or_pass";
							}
							else if (stdRawErrorStr == "003-007")
							{
								errorStr = "@ui_error_acc_not_active";
							}
							else if (stdRawErrorStr == "002-040")
							{
								errorStr = "@ui_error_acc_banned";
							}
							else
							{
								errorStr.Format("@ui_error_%s", stdRawErrorStr.c_str());
							}
						}
						else if (!errorCodeValue.is_null() && errorCodeValue.is_integer())
						{
							json::value errorDescriptionValue = errorValue[U("description")];

							if (!errorDescriptionValue.is_null() && errorDescriptionValue.is_string())
							{
								string_t rawDescStr = errorDescriptionValue.as_string();
								errorStr = std::string(rawDescStr.begin(), rawDescStr.end()).c_str();
								isRawError = true;
							}
						}
					}

					g_pPlugin->Notify_AuthorizationError(errorStr.c_str(), code, isRawError);
				}).wait();
			}

#ifndef RELEASE
			if (g_pCVars->m_log_level > 0)
			{
				LogDebug("Response status code : %u", code);
				LogDebug("Response raw : %s ", std::string(rawResponseStr.begin(), rawResponseStr.end()).c_str());
			}
#endif
		}

		void CHttpWorker::Callback_Registration(web::http::http_response &response)
		{
			http::status_code code = response.status_code();
#ifndef RELEASE
			string_t rawResponseStr = response.to_string();
#endif

			if (code == 204)
			{
				g_pPlugin->Notify_RegistrationSuccess();
			}
			else
			{
				auto jsonTask = response.extract_json().then([=](json::value json)
				{
					json::value errorValue = json[U("error")];

					string errorStr;
					bool isRawError = false;

					if (!errorValue.is_null())
					{
						json::value errorCodeValue = errorValue[U("code")];
		
						if (!errorCodeValue.is_null() && errorCodeValue.is_string())
						{
							string_t rawErrorStr = errorCodeValue.as_string();
							std::string stdRawErrorStr = std::string(rawErrorStr.begin(), rawErrorStr.end());

							if (stdRawErrorStr == "003-003")
							{
								errorStr = "@ui_error_username_alredy_taken";
							}
							else if (stdRawErrorStr == "003-004")
							{
								errorStr = "@ui_error_email_alredy_taken";
							}
							else
							{
								errorStr.Format("@ui_error_%s", stdRawErrorStr.c_str());
							}
						}
						else if (!errorCodeValue.is_null() && errorCodeValue.is_integer())
						{
							json::value errorDescriptionValue = errorValue[U("description")];

							if (!errorDescriptionValue.is_null() && errorDescriptionValue.is_string())
							{
								string_t rawDescStr = errorDescriptionValue.as_string();
								errorStr = std::string(rawDescStr.begin(), rawDescStr.end()).c_str();
								isRawError = true;
							}
						}
					}

					g_pPlugin->Notify_RegistrationError(errorStr.c_str(), code, isRawError);
				}).wait();
			}

#ifndef RELEASE
			if (g_pCVars->m_log_level > 0)
			{
				LogDebug("Response status code : %u", code);
				LogDebug("Response raw : %s ", std::string(rawResponseStr.begin(), rawResponseStr.end()).c_str());
			}
#endif
		}

		void CHttpWorker::Callback_RecoveryPassword(web::http::http_response & response)
		{
			http::status_code code = response.status_code();
#ifndef RELEASE
			string_t rawResponseStr = response.to_string();
#endif

			if (code == 204)
			{
				g_pPlugin->Notify_RecoveryPasswordSuccess();
			}
			else
			{
				auto jsonTask = response.extract_json().then([=](json::value json)
				{
					json::value errorValue = json[U("error")];

					string errorStr;
					bool isRawError = false;

					if (!errorValue.is_null())
					{
						json::value errorCodeValue = errorValue[U("code")];

						if (!errorCodeValue.is_null() && errorCodeValue.is_string())
						{
							string_t rawErrorStr = errorCodeValue.as_string();
							errorStr.Format("@ui_error_%s", std::string(rawErrorStr.begin(), rawErrorStr.end()).c_str());
						}
						else if (!errorCodeValue.is_null() && errorCodeValue.is_integer())
						{
							json::value errorDescriptionValue = errorValue[U("description")];

							if (!errorDescriptionValue.is_null() && errorDescriptionValue.is_string())
							{
								string_t rawDescStr = errorDescriptionValue.as_string();
								errorStr = std::string(rawDescStr.begin(), rawDescStr.end()).c_str();
								isRawError = true;
							}
						}
					}

					g_pPlugin->Notify_RecoveryPasswordError(errorStr.c_str(), code, isRawError);
				}).wait();

			}

#ifndef RELEASE
			if (g_pCVars->m_log_level > 0)
			{
				LogDebug("Response status code : %u", code);
				LogDebug("Response raw : %s ", std::string(rawResponseStr.begin(), rawResponseStr.end()).c_str());
			}
#endif
		}
	}
}