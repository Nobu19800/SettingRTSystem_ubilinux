add_subdirectory(AccAndMagnSensor_LSM303DLHC)

MAP_ADD_STR(hdrs "${PROJECT_NAME}/" headers)
set(headers ${headers} PARENT_SCOPE)
