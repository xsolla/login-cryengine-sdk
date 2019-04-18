// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

#pragma once

namespace Xsolla
{
	namespace Login
	{
		class CCvars
		{
		public:
			CCvars() {}
			~CCvars() {}
		public:
			void Register();
			void Unregister();
		public:
			ICVar* m_pProjectID = nullptr;
			ICVar* m_pCallbackURL = nullptr;
			int    m_http_timeout = 0;
			int    m_log_level = 0;
			int    m_storageType = 0;
		};
	}
}