// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

var isRegPageHide = true;
var agreeBox = false;
var passwordShow = false;


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
	_root.PageSwitcher._visible = true;
	_root.RegisterRoot.RegisterButton.button_text.text = "@ui_CreateAccount";
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

RegisterRoot.AgreeBox.onRollOver = function()
{
    if(GetRegisterCheckBox() == false)
	{
	    this.gotoAndStop("rollover");
	}
}

RegisterRoot.AgreeBox.onRollOut = function()
{
	if(GetRegisterCheckBox() == false)
	{
		SetRegisterCheckBox(false);
	}
}

RegisterRoot.RegisterButton.onRelease = function()
{
	if(GetRegisterCheckBox())
	{
		HideErrorBox(); 
		HideSuccessBox();
	
		var args:Array = new Array();
		args.push(_root.RegisterRoot.userNameField.enter_text.text);
		args.push(_root.RegisterRoot.passwordField.enter_text.text);
		args.push(_root.RegisterRoot.emailField.enter_text.text);

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

RegisterRoot.ShowPasswordBtn.onRelease = function()
{
    if(passwordShow)
	{
		_root.RegisterRoot.passwordField.enter_text.password = true;
		passwordShow = false;
	}
	else
	{
	    _root.RegisterRoot.passwordField.enter_text.password = false;
		passwordShow = true;
	}
}

SetRegisterCheckBox(false);