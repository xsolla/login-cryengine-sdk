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

# JWT validation setup
option(OPTION_JWT_VALIDATION "Enable jwt validation" OFF)

if(OPTION_JWT_VALIDATION)
	add_definitions(-DJWT_VALIDATION_ENABLED)
	
	# OpenSSL - Requered by Jwt-Cpp
	target_link_libraries(${THIS_PROJECT} PRIVATE ${SDKS}/openssl/lib/VC/libcrypto64MD.lib) 
	set(OPENSSL_INCLUDES ${SDKS}/openssl/include)
	# ~OpenSSL
	
	# JWT-CPP
	set(JWTCPP_INCLUDES ${SDKS}/jwt-cpp/includes)
	# ~JWT-CPP
	
	include_directories(
	${JWTCPP_INCLUDES}
	${OPENSSL_INCLUDES})
endif()

set_solution_startup_target(${THIS_PROJECT})
#END-CUSTOM