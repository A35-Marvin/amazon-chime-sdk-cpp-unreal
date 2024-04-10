cmake_minimum_required(VERSION 3.17...3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_NAME amazon-chime-signaling-sdk-cpp-lib)

set(SIGNALING_LANGUAGES C CXX)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND SIGNALING_LANGUAGES OBJC)
endif()

project(
        AmazonChimeSignalingSdkCpp
        VERSION 0.1.0
        DESCRIPTION "Library for Amazon Chime's C++ Signaling SDK"
        LANGUAGES ${SIGNALING_LANGUAGES})

# list of options available
# Enable Address Sanitizer
option(ENABLE_ASAN "Enable Address Sanitizer" OFF)
# Build test
option(BUILD_TEST "Build tests" ON)

if(ENABLE_ASAN)
    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined"
            )
    set(CMAKE_LINKER_FLAGS_DEBUG
            "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address,undefined")
    set(CMAKE_C_FLAGS_DEBUG
            "${CMAKE_C_FLAGS_DEBUG} -O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined"
            )
endif()

configure_file (
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_SOURCE_DIR}/src/version.h"
)

# set flag to build in different env. Default to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release ... FORCE)
endif()

message(
        STATUS
        "CMakeLists.txt - Current variables:\nCURRENT_BUILD_TYPE: ${CMAKE_BUILD_TYPE}"
        "\nENABLE_ASAN: ${ENABLE_ASAN}"
        "\nBUILD_TEST: ${BUILD_TEST}"
)

set(SDK_HEADERS
        src/audio_video/local_audio_configuration.h
        src/audio_video/remote_video_source_info.h
        src/transport/signaling_transport.h
        src/signaling/default_signaling_client.h
        src/transport/signaling_transport_configuration.h
        src/transport/websocket_signaling_transport.h
        src/session/turn_credentials.h
        src/signaling/signaling_client.h
        src/signaling/signaling_client_observer.h
        src/signaling/signaling_client_configuration.h
        src/signaling/signaling_client_status.h
        src/signaling/signaling_client_status.h
        src/utils/attendee.h)

set(SDK_SRC
        src/websocket/certs/trusted.cc
        src/audio_video/default_audio_frame_adapter.cc
        src/transport/default_signaling_transport_factory.cc
        src/transport/websocket_signaling_transport.cc
        src/signaling/default_signaling_client.cc
        src/signaling/default_signaling_client_factory.cc
        src/utils/logging.cc
        src/websocket/libwebsockets_websocket.cc
        src/websocket/default_websocket_factory.cc
        src/proto/video_control.pb.cc)

add_library(${LIBRARY_NAME} "${SDK_HEADERS}" "${SDK_SRC}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Libwebsocket dependency
#find_package(LibWebsockets REQUIRED)
include(FetchContent)
FetchContent_Declare(
        libwebsockets
        GIT_REPOSITORY https://github.com/A35-Marvin/aws-libwebsockets.git
        GIT_TAG        9560724395ec581020818715086eb0d73e1e719b
)

# Use open ssl static lib
set(OPENSSL_USE_STATIC_LIBS TRUE)

set(LWS_CTEST_INTERNET_AVAILABLE OFF CACHE BOOL "enable tests for proto" FORCE)
set(LWS_WITHOUT_TESTAPPS ON CACHE BOOL "Don't build the libwebsocket-test-apps" FORCE)
set(LWS_WITHOUT_TEST_SERVER ON CACHE BOOL "Don't build the libwebsocket-test-apps" FORCE)
set(LWS_WITHOUT_TEST_SERVER_EXTPOLL ON CACHE BOOL "Don't build the libwebsocket-test-apps" FORCE)
set(LWS_WITHOUT_TEST_PING ON CACHE BOOL "Don't build the libwebsocket-test-apps" FORCE)
set(LWS_WITHOUT_TEST_CLIENT ON CACHE BOOL "Don't build the libwebsocket-test-apps" FORCE)

set(LWS_ROLE_H1 ON CACHE BOOL "" FORCE)
set(LWS_ROLE_WS ON CACHE BOOL "" FORCE)
set(LWS_ROLE_RAW ON CACHE BOOL "" FORCE)
set(LWS_OPENSSL_SUPPORT ON CACHE BOOL "" FORCE)
set(LWS_WITH_TLS ON CACHE BOOL "" FORCE)
set(LWS_SSL_CLIENT_USE_OS_CA_CERTS ON CACHE BOOL "" FORCE)
set(LWS_WITHOUT_EXTENSIONS ON CACHE BOOL "" FORCE)
set(LWS_WITH_POLL ON CACHE BOOL "" FORCE)
set(LWS_WITH_IPV6 ON CACHE BOOL "" FORCE)
set(LWS_NO_DAEMONIZE ON CACHE BOOL "" FORCE)
set(LWS_BUILTIN_GETIFADDRS ON CACHE BOOL "" FORCE)
set(LWS_HAVE_SSL_CTX_set1_param ON CACHE BOOL "" FORCE)
set(LWS_HAVE_X509_VERIFY_PARAM_set1_host ON CACHE BOOL "" FORCE)
set(LWS_HAVE_RSA_SET0_KEY ON CACHE BOOL "" FORCE)
set(LWS_HAVE_X509_get_key_usage ON CACHE BOOL "" FORCE)
set(LWS_HAVE_SSL_CTX_get0_certificate ON CACHE BOOL "" FORCE)
set(LWS_HAVE_OPENSSL_ECDH_H ON CACHE BOOL "" FORCE)
set(LWS_HAVE_STDINT_H ON CACHE BOOL "" FORCE)
set(LWS_HAVE_ATOLL ON CACHE BOOL "" FORCE)
set(LWS_HAVE__ATOI64 ON CACHE BOOL "" FORCE)
set(LWS_HAVE__STAT32I64 ON CACHE BOOL "" FORCE)
set(LWS_HAVE_MALLOC_H ON CACHE BOOL "" FORCE)
set(LWS_HAVE_TLS_CLIENT_METHOD ON CACHE BOOL "" FORCE)
set(LWS_HAVE_TLSV1_2_CLIENT_METHOD ON CACHE BOOL "" FORCE)
set(LWS_HAVE_SSL_SET_INFO_CALLBACK ON CACHE BOOL "" FORCE)
set(LWS_HAVE_SSL_EXTRA_CHAIN_CERTS ON CACHE BOOL "" FORCE)
set(LWS_HAVE_SSL_get0_alpn_selected ON CACHE BOOL "" FORCE)
set(LWS_HAVE_SSL_set_alpn_protos ON CACHE BOOL "" FORCE)
set(LWS_HAS_INTPTR_T ON CACHE BOOL "" FORCE)

set(LWS_ROLE_H2 OFF CACHE BOOL "" FORCE)
set(LWS_ROLE_CGI OFF CACHE BOOL "" FORCE)
set(USE_WOLFSSL OFF CACHE BOOL "" FORCE)
set(USE_OLD_CYASSL OFF CACHE BOOL "" FORCE)
set(LWS_WITH_BORINGSSL OFF CACHE BOOL "" FORCE)
set(LWS_WITH_MBEDTLS OFF CACHE BOOL "" FORCE)
set(LWS_WITH_POLARSSL OFF CACHE BOOL "" FORCE)
set(LWS_WITH_ESP32 OFF CACHE BOOL "" FORCE)
set(LWS_WITH_PLUGINS OFF CACHE BOOL "" FORCE)
set(LWS_WITH_NO_LOGS OFF CACHE BOOL "" FORCE)
set(LWS_BUILD_HASH OFF CACHE BOOL "" FORCE)
set(LWS_WITHOUT_SERVER OFF CACHE BOOL "" FORCE)
set(LWS_WITHOUT_CLIENT OFF CACHE BOOL "" FORCE)
set(LWS_WITH_LIBEV OFF CACHE BOOL "" FORCE)
set(LWS_WITH_LIBUV OFF CACHE BOOL "" FORCE)
set(LWS_WITH_LIBEVENT OFF CACHE BOOL "" FORCE)
set(LWS_WITH_UNIX_SOCK OFF CACHE BOOL "" FORCE)
set(LWS_WITH_HTTP2 OFF CACHE BOOL "" FORCE)
set(LWS_LATENCY OFF CACHE BOOL "" FORCE)
set(LWS_NO_SERVER OFF CACHE BOOL "" FORCE)
set(LWS_NO_CLIENT OFF CACHE BOOL "" FORCE)
set(LWS_MINGW_SUPPORT OFF CACHE BOOL "" FORCE)
set(LWS_SHA1_USE_OPENSSL_NAME OFF CACHE BOOL "" FORCE)
set(LWS_SSL_SERVER_WITH_ECDH_CERT OFF CACHE BOOL "" FORCE)
set(LWS_HAVE_UV_VERSION_H OFF CACHE BOOL "" FORCE)
set(LWS_HAVE_NEW_UV_VERSION_H OFF CACHE BOOL "" FORCE)
set(LWS_HAVE_PTHREAD_H OFF CACHE BOOL "" FORCE)
set(LWS_WITH_CGI OFF CACHE BOOL "" FORCE)
set(LWS_WITH_HTTP_PROXY OFF CACHE BOOL "" FORCE)
set(LWS_WITH_RANGES OFF CACHE BOOL "" FORCE)
set(LWS_WITH_ACCESS_LOG OFF CACHE BOOL "" FORCE)
set(LWS_WITH_SERVER_STATUS OFF CACHE BOOL "" FORCE)
set(LWS_WITH_STATEFUL_URLDECODE OFF CACHE BOOL "" FORCE)
set(LWS_WITH_PEER_LIMITS OFF CACHE BOOL "" FORCE)
set(LWS_WITH_LEJP OFF CACHE BOOL "" FORCE)
set(LWS_WITH_SMTP OFF CACHE BOOL "" FORCE)
set(LWS_PLAT_OPTEE OFF CACHE BOOL "" FORCE)
set(LWS_WITH_ZIP_FOPS OFF CACHE BOOL "" FORCE)
set(LWS_AVOID_SIGPIPE_IGN OFF CACHE BOOL "" FORCE)
set(LWS_FALLBACK_GETHOSTBYNAME OFF CACHE BOOL "" FORCE)
set(LWS_WITH_STATS OFF CACHE BOOL "" FORCE)
set(LWS_WITH_SOCKS5 OFF CACHE BOOL "" FORCE)
set(LWS_HAVE_SYS_CAPABILITY_H OFF CACHE BOOL "" FORCE)
set(LWS_HAVE_LIBCAP OFF CACHE BOOL "" FORCE)
set(LWS_WITH_JWS OFF CACHE BOOL "" FORCE)
set(LWS_WITH_ACME OFF CACHE BOOL "" FORCE)
set(LWS_WITH_SELFTESTS OFF CACHE BOOL "" FORCE)
set(LWS_HAVE_PIPE2 OFF CACHE BOOL "" FORCE)

set(LWS_HAVE_HMAC_CTX_new ON CACHE BOOL "" FORCE)
set(LWS_HAVE_EVP_MD_CTX_free ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(libwebsockets)

target_link_libraries(${LIBRARY_NAME} PRIVATE websockets)

# Protobuf
FetchContent_Declare(
	protobuf
	GIT_REPOSITORY https://github.com/A35-Marvin/aws-protobuf.git
	GIT_TAG        a6d84d0b0b246a0abb99a97e5ad20094b395b504
	SOURCE_SUBDIR  cmake
	)

set(protobuf_BUILD_TESTS OFF CACHE BOOL "enable tests for proto" FORCE)
FetchContent_MakeAvailable(protobuf)

target_link_libraries(${LIBRARY_NAME} PRIVATE protobuf::libprotobuf)

# Include src directory so that we can avoid .. in the header includes
target_include_directories(${LIBRARY_NAME}
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Expose include paths for upstream projects
target_include_directories(
        ${LIBRARY_NAME} INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_14)
# set flag as c++11 instead of gnu++11 for some compilers
set_target_properties(${LIBRARY_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# Add stack smashing protection. MSVC uses /GS which is enabled by default. See
# https://docs.microsoft.com/en-us/cpp/build/reference/gs-buffer-security-check?view=msvc-160
if(NOT MSVC)
    target_compile_options(${LIBRARY_NAME} PRIVATE "-fstack-protector")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SDK_BINARY_NAME "${LIBRARY_NAME}.a")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SDK_BINARY_NAME "${LIBRARY_NAME}.lib")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_options(${LIBRARY_NAME} PUBLIC "-ObjC")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Set Runtime Library as MT to use static library
    set_property(
            TARGET ${LIBRARY_NAME} PROPERTY MSVC_RUNTIME_LIBRARY
            "MultiThreadedDLL")
	set_property(TARGET ${LIBRARY_NAME} PROPERTY C_STANDARD 11)
endif()

# Combine binaries
# Currently supporting Mac and Linux

set(SDK_BINARY_LIB_NAME "libamazon_chime_signaling_sdk")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SDK_BINARY_NAME "${SDK_BINARY_LIB_NAME}.a")

    # TODO @hokyungh: might be better to use mri script
    add_custom_command(
            TARGET ${LIBRARY_NAME}
            POST_BUILD
            COMMAND ar -x $<TARGET_FILE:${LIBRARY_NAME}>
	    COMMAND ar -x $<TARGET_FILE:protobuf::libprotobuf>
            COMMAND ar -x $<TARGET_FILE:websockets>
            COMMAND ar -qc ${SDK_BINARY_NAME} *.o
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SDK_BINARY_NAME "${SDK_BINARY_LIB_NAME}.a")
    add_custom_command(
            TARGET ${LIBRARY_NAME}
            POST_BUILD
            COMMAND
            libtool -static -o ${SDK_BINARY_NAME}
            $<TARGET_FILE:${LIBRARY_NAME}>
            $<TARGET_FILE:protobuf::libprotobuf>
            $<TARGET_FILE:websockets>
            $<TARGET_FILE:websockets_shared>
    )
endif()

# Run unit test
if (BUILD_TEST)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()
