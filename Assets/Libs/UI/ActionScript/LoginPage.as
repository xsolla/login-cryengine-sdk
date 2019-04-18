// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

var isLoginPageHide = true;
var rememberBox = false;

function SetRememberCheckBox(_value:Boolean) : Void
{
	rememberBox = _value;
	
	if(rememberBox)
	{
		LoginRoot.RememberBox.gotoAndStop("true");
	}
	else
	{
		LoginRoot.RememberBox.gotoAndStop("false");
	}
}

function GetRememberCheckBox() : Boolean
{
	return rememberBox;
}

function HideLoginPage(_hide:Boolean) : Void
{
	_root.LoginRoot._visible = !_hide;
	isLoginPageHide = !_hide;
	
	HideErrorBox(); 
	HideSuccessBox();
}

function IsLoginPageHidden() : Boolean
{
	return isLoginPageHide;
}

function LoginPageInitialize() : Void
{
	HideLoginPage(false);
	_root.LoginRoot.LoginButton.button_text.text = "@ui_SignIn";
}

function GetLoginEmail() : String
{
	var value = _root.LoginRoot.email_enter_text.text;
	return value;
}

function SetLoginEmail(_value:String) : Void
{
	_root.LoginRoot.email_enter_text.text = _value;
}

function GetLoginPassword() : String
{
	var value = _root.LoginRoot.password_enter_text.text;
	return value;
}

function SetLoginPassword(_value:String) : Void
{
	_root.LoginRoot.password_enter_text.text = _value;
}


LoginPageInitialize();


LoginRoot.ForgotButton.onRelease = function()
{
	//fscommand("OnForgotPasswordButton");

	HideLoginPage(true);
	HideRecoverPage(false);
}

LoginRoot.CreateAccount.onRelease = function()
{
	//fscommand("OnCreateAccountButton");

	HideLoginPage(true);
	HideRegisterPage(false);
}


LoginRoot.LoginButton.onRelease = function()
{
	HideErrorBox(); 
	HideSuccessBox();

	var args:Array = new Array();
	args.push(GetLoginEmail());
	args.push(GetLoginPassword());
	args.push(GetRememberCheckBox());
	
	fscommand("OnLoginButton", args);
}

LoginRoot.RememberBox.onRelease = function()
{
	if(GetRememberCheckBox())
	{
		SetRememberCheckBox(false);
	}
	else
	{
		SetRememberCheckBox(true);
	}
}


LoginRoot.LoginButton.onRollOver = function()
{
	this.gotoAndPlay("start");
}

LoginRoot.LoginButton.onRollOut = function()
{
	this.gotoAndPlay("end");
}