cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(PLUGIN_INTERFACE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})

if(QVPLUGIN_HAS_HTTP_TO_SOCKS_HELPER)
    find_package(Qt6 COMPONENTS Network REQUIRED)
    set(QVPLUGIN_HTTP_TO_SOCKS_FILES
        ${CMAKE_CURRENT_LIST_DIR}/utils/HttpProxy.hpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/SocketStream.hpp
        )
endif()

set(QVPLUGIN_INTERFACE_HEADERS
    ${QVPLUGIN_HTTP_TO_SOCKS_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/QvPluginBase.hpp
    ${CMAKE_CURRENT_LIST_DIR}/QvPluginInterface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/QvPluginInterfaceModels.hpp
    ${CMAKE_CURRENT_LIST_DIR}/QvPluginProcessor.hpp)

function(qv2ray_configure_plugin TARGET_NAME)
    target_link_libraries(${TARGET_NAME} Qt::Core)
    if(QVPLUGIN_HAS_HTTP_TO_SOCKS_HELPER)
        target_link_libraries(${TARGET_NAME} Qt::Network)
    endif()
    target_include_directories(${TARGET_NAME} PUBLIC ${PLUGIN_INTERFACE_INCLUDE_DIR})
    if(UNIX AND NOT APPLE AND NOT WIN32 AND NOT ANDROID)
        install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION lib/qv2ray/plugins)
    elseif(WIN32)
        install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION plugins)
    elseif(APPLE)
        add_custom_command(TARGET ${TARGET_NAME}
            POST_BUILD
            COMMAND ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/" $<TARGET_FILE:${TARGET_NAME}>)
        install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/qv2ray.app/Contents/Resources/plugins)
    elseif(ANDROID)
        set(deployment_tool "${QT_HOST_PATH}/${QT6_HOST_INFO_BINDIR}/androiddeployqt")
        set(apk_dir "$<TARGET_PROPERTY:${TARGET_NAME},BINARY_DIR>/android-build")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND
            ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
            "${apk_dir}/libs/${CMAKE_ANDROID_ARCH_ABI}/$<TARGET_FILE_NAME:${TARGET_NAME}>"
            )
    else()
        message(FATAL_ERROR "The platform is not supported yet.")
    endif()
endfunction()
