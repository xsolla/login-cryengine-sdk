cmake_minimum_required (VERSION 3.6.2)
set(CRYENGINE_DIR "D:/Program Files/Crytek/CRYENGINE Launcher/Crytek/CRYENGINE_5.5")
set(TOOLS_CMAKE_DIR "${CRYENGINE_DIR}/Tools/CMake")

set(PROJECT_BUILD 1)
set(PROJECT_DIR "${CMAKE_SOURCE_DIR}/../")

include("${TOOLS_CMAKE_DIR}/CommonOptions.cmake")

add_subdirectory("${CRYENGINE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/CRYENGINE")

include("${TOOLS_CMAKE_DIR}/Configure.cmake")
start_sources()

sources_platform(ALL)
add_sources("Code_uber.cpp"
    PROJECTS XsollaLogin
    SOURCE_GROUP "Root"
		"CVars.cpp"
		"FlowNodes.cpp"
		"Plugin.cpp"
		"StdAfx.cpp"
		"Worker.cpp"
		"CVars.h"
		"Plugin.h"
		"StdAfx.h"
		"Worker.h"
)

end_sources()

CryEngineModule(XsollaLogin FORCE_SHARED PCH "StdAfx.cpp" SOLUTION_FOLDER "Project")

target_include_directories(${THIS_PROJECT}
PRIVATE
    "${CRYENGINE_DIR}/Code/CryEngine/CryCommon"
    "${CRYENGINE_DIR}/Code/CryEngine/CryAction"
    "${CRYENGINE_DIR}/Code/CryEngine/CrySchematyc/Core/Interface"
    "${CRYENGINE_DIR}/Code/CryPlugins/CryDefaultEntities/Module"
)


if(OPTION_ENGINE)
    if(NOT EXISTS "${CRYENGINE_DIR}/Code/Sandbox/EditorQt")
		add_library(Editor STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
		set_target_properties(Editor PROPERTIES LINKER_LANGUAGE CXX)
		if (WIN32)
			set_visual_studio_debugger_command(Editor "${CRYENGINE_DIR}/bin/win_x64/Sandbox.exe" "-project \"${PROJECT_DIR}XsollaLogin.cryproject\"")
		endif()
	endif()
else()
	add_library(GameLauncher STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
	set_target_properties(GameLauncher PROPERTIES LINKER_LANGUAGE CXX)
	if (WIN32)
		set_visual_studio_debugger_command(GameLauncher "${CRYENGINE_DIR}/bin/win_x64/GameLauncher.exe" "-project \"${PROJECT_DIR}XsollaLogin.cryproject\"")
	endif()

    add_library(Editor STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
    set_target_properties(Editor PROPERTIES LINKER_LANGUAGE CXX)
    if (WIN32)
        set_visual_studio_debugger_command(Editor "${CRYENGINE_DIR}/bin/win_x64/Sandbox.exe" "-project \"${PROJECT_DIR}XsollaLogin.cryproject\"")
    endif()

	add_library(GameServer STATIC "${CRYENGINE_DIR}/Code/CryEngine/CryCommon/CryCore/Platform/platform.h")
	set_target_properties(GameServer PROPERTIES LINKER_LANGUAGE CXX)
	if (WIN32)
		set_visual_studio_debugger_command(GameServer "${CRYENGINE_DIR}/bin/win_x64/Game_Server.exe" "-project \"${PROJECT_DIR}XsollaLogin.cryproject\"")
	endif()
endif()

# Set StartUp project in Visual Studio
set_solution_startup_target(GameLauncher)

if (WIN32)
    set_visual_studio_debugger_command( ${THIS_PROJECT} "${CRYENGINE_DIR}/bin/win_x64/GameLauncher.exe" "-project \"${PROJECT_DIR}XsollaLogin.cryproject\"" )
endif()

#BEGIN-CUSTOM
set(CMAKE_CONFIGURATION_TYPES "Profile;Release" CACHE STRING "" FORCE) 
set(SDKS ${CMAKE_CURRENT_SOURCE_DIR}/../SDKs)
set(INTERFACE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../Interface)

# CPPRESTSDK
set(CPPRESTSDK_INCLUDES ${SDKS}/cpprestsdk/include)
set(CPPRESTSDK_LIBS ${SDKS}/cpprestsdk/lib)
add_definitions("/EHsc")
# ~CPPRESTSDK

include_directories(
${INTERFACE_INCLUDES}
${CPPRESTSDK_INCLUDES})

# CPPRESTSDK
target_link_libraries(${THIS_PROJECT} PRIVATE ${CPPRESTSDK_LIBS}/Release/cpprest140_2_9.lib)
# ~CPPRESTSDK

set_solution_startup_target(${THIS_PROJECT})
#END-CUSTOM