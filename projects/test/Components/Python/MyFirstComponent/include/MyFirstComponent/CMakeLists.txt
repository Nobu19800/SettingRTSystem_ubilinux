set(hdrs MyFirstComponent.h
    PARENT_SCOPE
    MoveServiceSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

