# Description
**XsollaLogin** - CRYENGINE V plugin for integration Xsolla Login API

# Building on Windows
## Before compiling
* Unpack `SDKs.7z` archive in root folder
* Setup CRYENGINE 5.5 +  (if it not setuped)
## Compiling
* Use XsollaLogin.cryproject for generation solution
* Open solution with Visual Studio and build it

# Using on Windows
* After compiling plugin go to `bin/win_x64` folder and copy `XsollaLogin.dll` to you project bin folder
* Copy `cpprest140_2_9.dll` from `SDKs/cpprestsdk/lib/Release` folder to `CRYENGINE/bin/win_x64` folder (you need add this dll also in project bin folder when you releasing game)
* Add XsollaLogin plugin to you .cryproject file

```bash
{
    "type": "EPluginType::Native",
    "path": "bin/win_x64/XsollaLogin.dll"
}
```
* That's all. Plugin ready for using
