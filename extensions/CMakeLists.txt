
find_package(Qt5 REQUIRED Qml Quick)

set(cachedimg_SRCS
    cachedimg.cpp
    cachedimg_plugin.cpp
    )

add_library(cachedimgplugin SHARED ${cachedimg_SRCS})
target_link_libraries(cachedimgplugin Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

install(TARGETS cachedimgplugin DESTINATION ${KDE_INSTALL_QMLDIR}/pl/rlalik/cachedimg)

install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/pl/rlalik/cachedimg)
