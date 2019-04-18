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