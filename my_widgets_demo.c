# Demo code for three different TAB graphics with help of LVGL example widgets

void lv_my_widgets_demo(void)
{
	tv = lv_tabview_create(lv_scr_act(), NULL);
#if LV_USE_THEME_MATERIAL
    if(LV_THEME_DEFAULT_INIT == lv_theme_material_init) {
        lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
        if(disp_size >= LV_DISP_SIZE_MEDIUM) {
            lv_obj_set_style_local_pad_left(tv, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, LV_HOR_RES / 2);
            lv_obj_t * sw = lv_switch_create(lv_scr_act(), NULL);
            if(lv_theme_get_flags() & LV_THEME_MATERIAL_FLAG_DARK)
                lv_switch_on(sw, LV_ANIM_OFF);
            lv_obj_set_event_cb(sw, color_chg_event_cb);
            lv_obj_set_pos(sw, LV_DPX(10), LV_DPX(10));
            lv_obj_set_style_local_value_str(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, "Dark Theme");
            lv_obj_set_style_local_value_align(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_ALIGN_OUT_RIGHT_MID);
            lv_obj_set_style_local_value_ofs_x(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_DPI/35);
        }
    }
#endif//#if LV_USE_THEME_MATERIAL

    t1 = lv_tabview_add_tab(tv, "TAB 1");
    t2 = lv_tabview_add_tab(tv, "TAB 2");
    t3 = lv_tabview_add_tab(tv, "TAB 3");

    lv_style_init(&style_box);
    lv_style_set_value_align(&style_box, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_LEFT);
    lv_style_set_value_ofs_y(&style_box, LV_STATE_DEFAULT, - LV_DPX(10));
    lv_style_set_margin_top(&style_box, LV_STATE_DEFAULT, LV_DPX(30));

    tab1_create(t1);
    tab2_create(t2);
    tab3_create(t3);


}

static void tab1_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    //lv_coord_t grid_w = lv_page_get_width_grid(parent, disp_size <= LV_DISP_SIZE_SMALL ? 1 : 2, 1);

    lv_obj_t * cont;

    cont = lv_cont_create(parent, NULL);
    lv_obj_set_auto_realign(cont, true);                    /*Auto realign when the size changes*/
    lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0);  /*This parametrs will be sued when realigned*/
    lv_cont_set_fit(cont, LV_FIT_TIGHT);
    lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_MID);

    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(cont, NULL);
    lv_obj_set_event_cb(btn1, event_handler_btn);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t * btn2 = lv_btn_create(cont, NULL);
    lv_obj_set_event_cb(btn2, event_handler_btn);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Toggled");

#if LV_USE_BTNMATRIX
    //Button Matrix
    lv_obj_t * btnm1 = lv_btnmatrix_create(cont, NULL);
    lv_btnmatrix_set_map(btnm1, btnm_map);
    lv_btnmatrix_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
    lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECK_STATE);
    lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(btnm1, event_handler_btnmatrix);
#endif//#if LV_USE_BTNMATRIX

}

static void tab2_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    //lv_coord_t grid_w = lv_page_get_width_grid(parent, disp_size <= LV_DISP_SIZE_SMALL ? 1 : 2, 1);

    lv_obj_t * cont2;

    cont2 = lv_cont_create(parent, NULL);
    lv_obj_set_auto_realign(cont2, true);                    /*Auto realign when the size changes*/
    lv_obj_align_origo(cont2, NULL, LV_ALIGN_CENTER, 0, 0);  /*This parametrs will be sued when realigned*/
    lv_cont_set_fit(cont2, LV_FIT_TIGHT);
    lv_cont_set_layout(cont2, LV_LAYOUT_COLUMN_MID);

    //Calendar
    lv_obj_t  * calendar = lv_calendar_create(cont2, NULL);
    lv_obj_set_size(calendar, 235, 235);
    lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(calendar, event_handler_calendar);

    /*Make the date number smaller to be sure they fit into their area*/
    lv_obj_set_style_local_text_font(calendar, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, lv_theme_get_font_small());

    /*Set today's date*/
    lv_calendar_date_t today;
    today.year = 2021;
    today.month = 02;
    today.day = 03;

    lv_calendar_set_today_date(calendar, &today);
    lv_calendar_set_showed_date(calendar, &today);
}

static void tab3_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    //lv_coord_t grid_w = lv_page_get_width_grid(parent, disp_size <= LV_DISP_SIZE_SMALL ? 1 : 2, 1);

    lv_obj_t * cont3;

    cont3 = lv_cont_create(parent, NULL);
    lv_obj_set_auto_realign(cont3, true);                    /*Auto realign when the size changes*/
    lv_obj_align_origo(cont3, NULL, LV_ALIGN_CENTER, 0, 0);  /*This parametrs will be sued when realigned*/
    lv_cont_set_fit(cont3, LV_FIT_TIGHT);
    lv_cont_set_layout(cont3, LV_LAYOUT_COLUMN_MID);

    //Image include
    LV_IMG_DECLARE(LVGL);

    lv_obj_t * img1 = lv_img_create(cont3, NULL);
    lv_img_set_src(img1, &LVGL);
    lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -20);

    lv_obj_t * img2 = lv_img_create(cont3, NULL);
    lv_img_set_src(img2, LV_SYMBOL_IMAGE "External Image");
    lv_obj_align(img2, img1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

}
