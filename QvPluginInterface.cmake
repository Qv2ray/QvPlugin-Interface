cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(PluginInterfaceDir
    ${CMAKE_CURRENT_LIST_DIR})

set(QVGUIPLUGIN_INTERFACE_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/gui)
set(QVGUIPLUGIN_INTERFACE_HEADERS
    ${QVGUIPLUGIN_INTERFACE_INCLUDE_PATH}/QvGUIPluginInterface.hpp)


set(QVPLUGIN_INTERFACE_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR})
set(QVPLUGIN_INTERFACE_HEADERS
    ${QVPLUGIN_INTERFACE_INCLUDE_PATH}/QvPluginBase.hpp
    ${QVPLUGIN_INTERFACE_INCLUDE_PATH}/QvPluginInterface.hpp
    ${QVPLUGIN_INTERFACE_INCLUDE_PATH}/handlers/EventHandler.hpp
    ${QVPLUGIN_INTERFACE_INCLUDE_PATH}/handlers/KernelHandler.hpp
    ${QVPLUGIN_INTERFACE_INCLUDE_PATH}/handlers/OutboundHandler.hpp
    ${QVPLUGIN_INTERFACE_INCLUDE_PATH}/handlers/SubscriptionHandler.hpp)

set(QVPLUGIN_HTTP_TO_SOCKS_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/socks2http)
set(QVPLUGIN_HTTP_TO_SOCKS_HEADERS
    ${QVPLUGIN_HTTP_TO_SOCKS_INCLUDE_PATH}/HttpProxy.hpp
    ${QVPLUGIN_HTTP_TO_SOCKS_INCLUDE_PATH}/SocketStream.hpp)

function(qv2ray_configure_plugin TARGET_NAME)
    set(options GUI Quick Widgets NO_INSTALL NO_RPATH HTTP_TO_SOCKS)
    set(oneValueArgs
        INSTALL_PREFIX_LINUX
        INSTALL_PREFIX_WINDOWS
        INSTALL_PREFIX_MACOS
        INSTALL_PREFIX_ANDROID)
    set(multiValueArgs)

    cmake_parse_arguments(QVPLUGIN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # ====================================== BEGIN PARSING ARGUMENTS
    if(NOT DEFINED QVPLUGIN_Widgets)
        set(QVPLUGIN_Widgets FALSE)
    elseif(QVPLUGIN_Widgets)
        set(QVPLUGIN_GUI TRUE)
    endif()

    if(NOT DEFINED QVPLUGIN_Quick)
        set(QVPLUGIN_Quick FALSE)
    elseif(QVPLUGIN_Quick)
        set(QVPLUGIN_GUI TRUE)
    endif()

    if(NOT DEFINED QVPLUGIN_GUI)
        set(QVPLUGIN_GUI FALSE)
    endif()

    if(NOT DEFINED QVPLUGIN_NO_INSTALL)
        set(QVPLUGIN_NO_INSTALL FALSE)
    endif()

    if(NOT DEFINED QVPLUGIN_HTTP_TO_SOCKS)
        set(QVPLUGIN_HTTP_TO_SOCKS FALSE)
    endif()

    if(NOT DEFINED QVPLUGIN_NO_RPATH)
        set(QVPLUGIN_NO_RPATH FALSE)
    endif()

    if((NOT DEFINED QVPLUGIN_INSTALL_PREFIX_LINUX) OR (QVPLUGIN_INSTALL_PREFIX_LINUX STREQUAL ""))
        set(QVPLUGIN_INSTALL_PREFIX_LINUX "lib/qv2ray/plugins")
    endif()

    if((NOT DEFINED QVPLUGIN_INSTALL_PREFIX_WINDOWS) OR (QVPLUGIN_INSTALL_PREFIX_WINDOWS STREQUAL ""))
        set(QVPLUGIN_INSTALL_PREFIX_WINDOWS "plugins")
    endif()

    if((NOT DEFINED QVPLUGIN_INSTALL_PREFIX_MACOS) OR (QVPLUGIN_INSTALL_PREFIX_MACOS STREQUAL ""))
        set(QVPLUGIN_INSTALL_PREFIX_MACOS "qv2ray.app/Contents/Resources/plugins")
    endif()

    if(DEFINED QVPLUGIN_INSTALL_PREFIX_ANDROID)
        message("INSTALL_PREFIX_ANDROID is not used")
    endif()
    # ====================================== END PARSING ARGUMENTS

    find_package(Qt6 COMPONENTS Core REQUIRED)
    target_sources(${TARGET_NAME} PRIVATE ${QVPLUGIN_INTERFACE_HEADERS})
    target_link_libraries(${TARGET_NAME} Qt::Core)
    target_include_directories(${TARGET_NAME} PRIVATE ${QVPLUGIN_INTERFACE_INCLUDE_PATH})

    if(QVPLUGIN_HTTP_TO_SOCKS)
        find_package(Qt6 COMPONENTS Network REQUIRED)
        target_sources(${TARGET_NAME} ${QVPLUGIN_HTTP_TO_SOCKS_HEADERS})
        target_link_libraries(${TARGET_NAME} Qt::Network)
        target_include_directories(${TARGET_NAME} PRIVATE ${QVPLUGIN_HTTP_TO_SOCKS_INCLUDE_PATH})
    endif()

    if(QVPLUGIN_GUI)
        find_package(Qt6 COMPONENTS Gui REQUIRED)
        target_link_libraries(${TARGET_NAME} Qt::Gui)
        target_include_directories(${TARGET_NAME} PRIVATE ${QVGUIPLUGIN_INTERFACE_INCLUDE_PATH})
        target_sources(${TARGET_NAME} PRIVATE ${QVGUIPLUGIN_INTERFACE_HEADERS})
    endif()

    if(QVPLUGIN_Quick)
        find_package(Qt6 COMPONENTS Quick REQUIRED)
        target_link_libraries(${TARGET_NAME} Qt::Quick)
    endif()

    if(QVPLUGIN_Widgets)
        find_package(Qt6 COMPONENTS Widgets REQUIRED)
        target_link_libraries(${TARGET_NAME} Qt::Widgets)
    endif()

    target_include_directories(${TARGET_NAME} PRIVATE ${PluginInterfaceDir})

    if(APPLE AND NOT QVPLUGIN_MACOS_ADD_RPATH)
        add_custom_command(TARGET ${TARGET_NAME}
            POST_BUILD
            COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/" $<TARGET_FILE:${TARGET_NAME}>)
    endif()

    if(NOT QVPLUGIN_NO_INSTALL)
        if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
            install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${QVPLUGIN_INSTALL_PREFIX_LINUX})
        elseif(WIN32)
            install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${QVPLUGIN_INSTALL_PREFIX_WINDOWS})
        elseif(APPLE)
            install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${QVPLUGIN_INSTALL_PREFIX_MACOS})
        elseif(ANDROID)
            set(apk_dir "$<TARGET_PROPERTY:${TARGET_NAME},BINARY_DIR>/android-build")
            add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                COMMAND
                ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
                "${apk_dir}/libs/${CMAKE_ANDROID_ARCH_ABI}/$<TARGET_FILE_NAME:${TARGET_NAME}>"
                )
        else()
            message(FATAL_ERROR "The platform is not supported yet.")
        endif()
    endif()

    message(STATUS "Configured Qv2ray Plugin: ${TARGET_NAME}")
    message(STATUS "==========================================================")
    message(STATUS "-- Plugin Components")
    message(STATUS "      QWidgets: ${QVPLUGIN_Widgets}")
    message(STATUS "       QtQuick: ${QVPLUGIN_Quick}")
    message(STATUS "         QtGui: ${QVPLUGIN_GUI}")
    message(STATUS "    HTTP2SOCKS: ${QVPLUGIN_HTTP_TO_SOCKS}")
    message(STATUS "-- Installation Options")
    message(STATUS "     NoInstall: ${QVPLUGIN_NO_INSTALL}")
    message(STATUS "       NoRPath: ${QVPLUGIN_NO_RPATH}")
    message(STATUS "-- Installation Prefixes")
    message(STATUS "        Global: ${CMAKE_INSTALL_PREFIX}")
    message(STATUS "         Linux: ${QVPLUGIN_INSTALL_PREFIX_LINUX}")
    message(STATUS "         macOS: ${QVPLUGIN_INSTALL_PREFIX_MACOS}")
    message(STATUS "       Windows: ${QVPLUGIN_INSTALL_PREFIX_WINDOWS}")
    message(STATUS "       Android: ${QVPLUGIN_INSTALL_PREFIX_ANDROID}")
    message(STATUS "==========================================================")
    message("")
endfunction()
