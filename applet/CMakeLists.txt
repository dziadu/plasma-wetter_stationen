# add_definitions(-DTRANSLATION_DOMAIN=\"plasma_applet_org.kde.plasma.wetter_stationen_\")

# include_directories(
#     ${CMAKE_SOURCE_DIR}/libs
# )

set(wetterstationenapplet_SRCS
    wetterstationenapplet.cpp
    plasma_applet_wetter_stationen_export.h)

include(GenerateExportHeader)

add_library(plasma_applet_wetter_stationen MODULE ${wetterstationenapplet_SRCS})
generate_export_header(plasma_applet_wetter_stationen)

# kcoreaddons_desktop_to_json(plasma_applet_wetter_stationen package/metadata.desktop SERVICE_TYPES plasma-applet.desktop)

target_link_libraries(plasma_applet_wetter_stationen
    KF5::Plasma
)

install(TARGETS plasma_applet_wetter_stationen DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/applets)

# install(FILES wind-arrows.svgz DESTINATION ${PLASMA_DATA_INSTALL_DIR}/desktoptheme/default/wetter_stationen/)

# plasma_install_package(package org.kde.plasma.wetter_stationen)

# 
# set(wetter_stationen_SRCS
#     plugin/plugin.cpp
#     plugin/abstractunitlistmodel.cpp
#     plugin/locationlistmodel.cpp
# )
# 
# add_library(wetter_stationen_plugin SHARED ${wetter_stationen_SRCS})
# 
# target_link_libraries(wetter_stationen_plugin
#     Qt5::Qml
# )
# 
# install(TARGETS wetter_stationen_plugin DESTINATION ${QML_INSTALL_DIR}/org/kde/plasma/private/wetter_stationen)
# install(FILES plugin/qmldir DESTINATION ${QML_INSTALL_DIR}/org/kde/plasma/private/wetter_stationen)
