// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

var isRegPageHide = true;
var agreeBox = false;

function SetRegisterCheckBox(_value:Boolean) : Void
{
	agreeBox = _value;
	
	if(agreeBox)
	{
		RegisterRoot.AgreeBox.gotoAndStop("true");
	}
	else
	{
		RegisterRoot.AgreeBox.gotoAndStop("false");
	}
}

function GetRegisterCheckBox() : Boolean
{
	return agreeBox;
}

function HideRegisterPage(_hide:Boolean) : Void
{
	HideErrorBox(); 
	HideSuccessBox();

	_root.RegisterRoot._visible = !_hide;
	isRegPageHide = !_hide;
}

function IsRegisterPageHidden() : Boolean
{
	return isRegPageHide;
}

function RegisterPageInitialize() : Void
{
	HideRegisterPage(true);
	_root.RegisterRoot.RegisterButton.button_text.text = "@ui_CreateAccount";
}

function GetRegisterUsername() : String
{
	var value = _root.RegisterRoot.username_enter_text.text;
	return value;
}

function GetRegisterEmail() : String
{
	var value = _root.RegisterRoot.email_enter_text.text;
	return value;
}

function GetRegisterPassword() : String
{
	var value = _root.RegisterRoot.password_enter_text.text;
	return value;
}

RegisterPageInitialize();

RegisterRoot.AlreadyHaveAccountButton.onRelease = function()
{
	//fscommand("OnAlreadyHaveAccount");
	HideRegisterPage(true);
	HideLoginPage(false);
}

RegisterRoot.BackButton.onRelease = function()
{
	//fscommand("OnBackButton", "RegisterPage");

	HideRegisterPage(true);
	HideLoginPage(false);
}

RegisterRoot.AgreeBox.onRelease = function()
{
	if(GetRegisterCheckBox())
	{
		SetRegisterCheckBox(false);
	}
	else
	{
		SetRegisterCheckBox(true);
	}
}

RegisterRoot.RegisterButton.onRelease = function()
{
	if(GetRegisterCheckBox())
	{
		HideErrorBox(); 
		HideSuccessBox();
	
		var args:Array = new Array();
		args.push(GetRegisterUsername());
		args.push(GetRegisterPassword());
		args.push(GetRegisterEmail());
	
		fscommand("OnCreateButton", args);
	}
	else
	{
		ShowErrorBox("@ui_not_accept_privacy");
	}	
}

RegisterRoot.RegisterButton.onRollOver = function()
{
	this.gotoAndPlay("start");
}

RegisterRoot.RegisterButton.onRollOut = function()
{
	this.gotoAndPlay("end");
}