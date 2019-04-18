// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

function ShowErrorBox(_errorStr:String) : Void
{
	_root.ErrorRoot._visible = true;
	_root.ErrorRoot.error_text.text = _errorStr;
}

function HideErrorBox() : Void
{
	_root.ErrorRoot._visible = false;
	_root.ErrorRoot.error_text.text = "";
}

function ShowSuccessBox(_successStr:String) : Void
{
	_root.SuccessRoot._visible = true;
	_root.SuccessRoot.success_text.text = _successStr;
}

function HideSuccessBox() : Void
{
	_root.SuccessRoot._visible = false;
	_root.SuccessRoot.success_text.text = "";
}

// Default
HideErrorBox(); 
HideSuccessBox();