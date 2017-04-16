set(DATA_FILES DataGenerator.cpp)

add_executable(generarData ${DATA_FILES})
target_link_libraries (generarData algo3-tp1-base)