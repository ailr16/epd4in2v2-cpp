include_directories(
    ${CMAKE_SOURCE_DIR}/inc/clib/Config
    ${CMAKE_SOURCE_DIR}/inc/clib/e-Paper
    ${CMAKE_SOURCE_DIR}/inc/clib/Fonts
    ${CMAKE_SOURCE_DIR}/inc/clib/GUI
    # Cpp wrappers
    ${CMAKE_SOURCE_DIR}/inc/
)

# clib source files for Config
add_library(lib__config__dev_config clib/Config/DEV_Config.c)
add_library(lib__config__dev_hardware_spi clib/Config/dev_hardware_SPI.c)
add_library(lib__config__rpi_gpiod clib/Config/RPI_gpiod.c)
add_library(lib__config__sysfs_gpio clib/Config/sysfs_gpio.c)
add_library(lib__config__sysfs_software_spi clib/Config/sysfs_software_spi.c)

set(clib_config
    lib__config__dev_config
    lib__config__dev_hardware_spi
    lib__config__rpi_gpiod
    lib__config__sysfs_gpio
    lib__config__sysfs_software_spi
)


# clib for the display specific model
add_library(lib__epaper__epd_4in2_v2 clib/e-Paper/EPD_4in2_V2.c)

set(clib_epaper
    lib__epaper__epd_4in2_v2
)


# clib for fonts
add_library(lib__fonts__font8 clib/Fonts/font8.c)
add_library(lib__fonts__font12 clib/Fonts/font12.c)
add_library(lib__fonts__font12cn clib/Fonts/font12CN.c)
add_library(lib__fonts__font16 clib/Fonts/font16.c)
add_library(lib__fonts__font20 clib/Fonts/font20.c)
add_library(lib__fonts__font24 clib/Fonts/font24.c)
add_library(lib__fonts__font24cn clib/Fonts/font24CN.c)

set(clib_fonts
    lib__fonts__font8
    lib__fonts__font12
    lib__fonts__font12cn
    lib__fonts__font16
    lib__fonts__font20
    lib__fonts__font24
    lib__fonts__font24cn
)

# clib for GUI handling
add_library(lib__gui__gui_bmpfile clib/GUI/GUI_BMPfile.c)
add_library(lib__gui__gui_paint clib/GUI/GUI_Paint.c)

set(clib_gui
    lib__gui__gui_bmpfile
    lib__gui__gui_paint
)


foreach(lib IN LISTS clib_config clib_epaper clib_fonts clib_gui)
    target_compile_definitions(${lib}
        PRIVATE
            USE_LGPIO_LIB
            RPI
            DEBUG
    )
    target_compile_options(${lib}
        PRIVATE
            -g
            -O
            -ffunction-sections
            -fdata-sections
            -Wall
    )
endforeach()

add_library(lib_Gui Gui.cpp)
target_link_libraries(lib_Gui
    clib_gui
)

add_executable(main main.cpp)

target_link_libraries(main
    PRIVATE
        ${clib_config}
        ${clib_epaper}
        ${clib_fonts}
        ${clib_gui}
        lgpio
        m
)

target_compile_definitions(main
    PRIVATE
        USE_LGPIO_LIB
        RPI
        DEBUG
)

target_compile_options(main
    PRIVATE
        -g
        -O
        -ffunction-sections
        -fdata-sections
        -Wall
)