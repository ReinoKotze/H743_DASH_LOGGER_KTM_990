SET(SOURCES screens/ui_Normal.c
    screens/ui_RAWsensor.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_rear_wheel_png.c
    images/ui_img_front_wheel_png.c
    images/ui_img_ecu_warning__1_png.c
    images/ui_img_fi_orange_png.c
    images/ui_img_1414997601.c
    images/ui_img_pngegg_png.c)

add_library(ui ${SOURCES})
