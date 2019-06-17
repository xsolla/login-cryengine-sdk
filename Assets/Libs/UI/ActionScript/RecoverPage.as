// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

var isRecoverPageHide = true;

function HideRecoverPage(_hide:Boolean) : Void
{
	_root.RecoverRoot._visible = !_hide;
	isRegPageHide = !_hide;

	_root.PageSwitcher._visible = _hide;
	
	HideErrorBox(); 
	HideSuccessBox();
}

function IsRecoverPageHidden() : Boolean
{
	return isRecoverPageHide;
}

function RecoverPageInitialize() : Void
{
	HideRecoverPage(true);
	_root.RecoverRoot.RecoverButton.button_text.text = "@ui_RecoverPassword";
}

RecoverPageInitialize();

function GetRecoverUsername() : String
{
	var value = _root.RecoverRoot.usernameField.enter_text.text;
	return value;
}

RecoverRoot.CreateAccountButton.onRelease = function()
{
	//fscommand("OnCreateAccountButton");
	HideRecoverPage(true);
	HideRegisterPage(false);
}

RecoverRoot.BackButton.onRelease = function()
{
	//fscommand("OnBackButton", "RecoverPage");
	HideRecoverPage(true);
	HideLoginPage(false);
}

RecoverRoot.RecoverButton.onRelease = function()
{
	HideErrorBox(); 
	HideSuccessBox();

	var args:Array = new Array();
	args.push(GetRecoverUsername());
	
	fscommand("OnRecoverButton", args);
}

RecoverRoot.RecoverButton.onRollOver = function()
{
	this.gotoAndPlay("start");
}

RecoverRoot.RecoverButton.onRollOut = function()
{
	this.gotoAndPlay("end");
}