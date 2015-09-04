add_subdirectory(GyroSensor_L3GD20_I2C)

MAP_ADD_STR(hdrs "${PROJECT_NAME}/" headers)
set(headers ${headers} PARENT_SCOPE)
