// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#pragma once

namespace web
{
	namespace http
	{
		class http_response;
	}
}

namespace Xsolla
{
	namespace Login
	{
		class CHttpWorker
		{
		public:
			CHttpWorker() {};
			~CHttpWorker() {};
		public:
			void Request_Authorization(const char* username, const char* password, bool rememberMe);
			void Request_Registration(const char* username, const char* password, const char* email);
			void Request_RecoveryPassword(const char* username);
		private:
			void Callback_Authorization(web::http::http_response &response);
			void Callback_Registration(web::http::http_response &response);
			void Callback_RecoveryPassword(web::http::http_response &response);
		private:
			enum EStorageType
			{
				EStorage_Xsolla = 0,
				EStorage_Custom,
			};
		};
	}
}