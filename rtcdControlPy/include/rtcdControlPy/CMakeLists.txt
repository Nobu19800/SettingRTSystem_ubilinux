set(hdrs rtcdControlPy.h
    PARENT_SCOPE
    rtcControlSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

