/**
 * @file demo.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "demo.h"

#if LV_USE_DEMO

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_keyboard(void);
static void kb_event_cb(lv_obj_t * keyboard, lv_event_t e);
static void kb_create(void);
static void ta_event_cb(lv_obj_t * ta_local, lv_event_t e);
static void wp_event_cb(lv_obj_t* wp_local, lv_event_t e);
static void demo_create2(void);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t* lb;
static lv_obj_t* wp;
static lv_obj_t* kb;
static lv_obj_t* ta;

LV_IMG_DECLARE(img_raccoon_pattern)
LV_IMG_DECLARE(img_embadity_pattern)

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a demo application
 */
void demo_create(void)
{
    wp = lv_img_create(lv_disp_get_scr_act(NULL), NULL);
    lv_img_set_auto_size(wp, true);
    lv_obj_set_click(wp, true);
    lv_img_set_src(wp, &img_embadity_pattern);
    lv_obj_align(wp, NULL, LV_ALIGN_CENTER, 0, 0);

    lb = lv_label_create(lv_scr_act(), NULL);
    lv_obj_align(lb, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_label_set_align(lb, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(lb, "LVGL v7.11");

    lv_obj_set_event_cb(wp, wp_event_cb);
}

static void demo_create2(void)
{
    wp = lv_img_create(lv_disp_get_scr_act(NULL), NULL);
    lv_img_set_auto_size(wp, true);
    lv_obj_set_click(wp, true);
    lv_img_set_src(wp, &img_raccoon_pattern);
    lv_obj_align(wp, NULL, LV_ALIGN_CENTER, 0, 0);

    lb = lv_label_create(lv_scr_act(), NULL);
    lv_obj_align(lb, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_label_set_align(lb, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(lb, "LVGL v7.11");

    lv_obj_set_event_cb(wp, wp_event_cb);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_keyboard(void)
{
    /*Create a text area. The keyboard will write here*/
    ta  = lv_textarea_create(lv_scr_act(), NULL);
    lv_obj_align(ta, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 16);
    lv_obj_set_event_cb(ta, ta_event_cb);
    lv_textarea_set_text(ta, "Remove this text and enter the command: \"rotate on\" or \"rotate off\"");
    lv_coord_t max_h = LV_VER_RES / 2 - LV_DPI / 8;
    if(lv_obj_get_height(ta) > max_h) lv_obj_set_height(ta, max_h);

    kb_create();
}

static void kb_event_cb(lv_obj_t * keyboard, lv_event_t e)
{
    lv_keyboard_def_event_cb(kb, e);

    if(e == LV_EVENT_CANCEL)
    {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_del(kb);
        lv_obj_del(ta);
        kb = NULL;
        ta = NULL;
    }
}

static void kb_create(void)
{
    kb = lv_keyboard_create(lv_scr_act(), NULL);
    lv_keyboard_set_cursor_manage(kb, true);
    lv_obj_set_event_cb(kb, kb_event_cb);
    lv_keyboard_set_textarea(kb, ta);
}

static void ta_event_cb(lv_obj_t * ta_local, lv_event_t e)
{
    if((e == LV_EVENT_VALUE_CHANGED) && (kb != NULL))
    {
    	if(strcmp(lv_textarea_get_text(ta), "rotate on") == 0)
    	{
    		lv_disp_set_rotation(NULL, LV_DISP_ROT_180);
    		lv_obj_del(wp);
    		lv_obj_del(lb);
            lv_obj_del(kb);
            lv_obj_del(ta);
            wp = NULL;
            lb = NULL;
            kb = NULL;
            ta = NULL;
            demo_create2();
    	}
    	else if(strcmp(lv_textarea_get_text(ta), "rotate off") == 0)
    	{
    		lv_disp_set_rotation(NULL, LV_DISP_ROT_90);
    		lv_obj_del(wp);
    		lv_obj_del(lb);
            lv_obj_del(kb);
            lv_obj_del(ta);
            wp = NULL;
            lb = NULL;
            kb = NULL;
            ta = NULL;
    		demo_create();
    	}
    }
}

static void wp_event_cb(lv_obj_t* wp_local, lv_event_t e)
{
    if(e == LV_EVENT_CLICKED)
    {
    	lv_keyboard();
    }
}

#endif  /*LV_USE_DEMO*/
