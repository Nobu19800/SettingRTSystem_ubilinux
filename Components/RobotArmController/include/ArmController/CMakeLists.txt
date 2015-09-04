set(hdrs ArmController.h
    ManipulatorCommonInterface_CommonSVC_impl.h
    ManipulatorCommonInterface_MiddleLevelSVC_impl.h
    PARENT_SCOPE
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

