set(hdrs rtcConfSet.h
    PARENT_SCOPE
    rtcconfSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

