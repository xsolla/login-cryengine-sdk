
# Description
**XsollaLogin** - CRYENGINE V plugin for integration Xsolla Login API

# Building on Windows
## Before compiling
* Unpack `SDKs.7z` archive in root folder
* Setup CRYENGINE 5.6   (if it not setuped)
## Compiling
* Use XsollaLogin.cryproject for generation solution
* Open solution with Visual Studio and build it

# Using on Windows
* After compiling plugin go to `bin/win_x64` folder and copy `XsollaLogin.dll` to you project bin folder
* Copy `cpprest_2_10.dll` from `SDKs/cpprestsdk/lib/Release` folder to `CRYENGINE/bin/win_x64` folder (you need add this dll also in project bin folder when you releasing game)
* Add XsollaLogin plugin to you .cryproject file

```bash
{
    "type": "EPluginType::Native",
    "path": "bin/win_x64/XsollaLogin.dll"
}
```
* Set `xl_login_project_id` console variable (Read more on [WIKI](https://github.com/xsolla/login-cryengine-sdk/wiki))
* That's all. Plugin ready for using

# WIKI
* For more instructions - please read our [WIKI](https://github.com/xsolla/login-cryengine-sdk/wiki)