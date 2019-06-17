// Copyright (C) 2006 — 2019 Xsolla Inc. All rights reserved.
// Created by AfroStalin

LogIn.SwitcherText.TXT.text = "@ui_LogIn";
SignUp.SwitcherText.TXT.text = "@ui_SignUp";

var login_active = false;
var signup_active = false;

LogIn.onRollOver = function()
{
    if(!login_active)
        this.gotoAndPlay("end");
}

LogIn.onRollOut = function()
{
    if(!login_active)
        this.gotoAndPlay("start");
}

SignUp.onRollOver = function()
{
    if(!signup_active)
        this.gotoAndPlay("end");
}

SignUp.onRollOut = function()
{
    if(!signup_active)
        this.gotoAndPlay("start");
}

LogIn.onRelease = function()
{
    if(login_active)
        return;

    login_active = true;
    signup_active = false;

    SetSwitcherActivity();

    _root.LoginRoot._visible = true;
    _root.RegisterRoot._visible = false;
}

SignUp.onRelease = function()
{
    if(signup_active)
        return;

    login_active = false;
    signup_active = true;

    SetSwitcherActivity();

    _root.LoginRoot._visible = false;
    _root.RegisterRoot._visible = true;
}

function SetSwitcherActivity()
{
    if(signup_active == true)
    {
        SignUp.gotoAndStop("Active");
    }
    else
    {
        SignUp.gotoAndStop("None");
    }

    if(login_active == true)
    {
        LogIn.gotoAndStop("Active");
    }
    else
    {
        LogIn.gotoAndStop("None");
    }
}

function StartActive()
{
    login_active = true;
    SetSwitcherActivity();
}

StartActive();