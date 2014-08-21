/*
 * settings.h
 *
 *  Created on: 2012/12/25
 *      Author: Tonsuke
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_


#include <string.h>
#include <stdint.h>

#include "icon.h"

#include "sd.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 4

#define SETTING_TYPE_DIR   0
#define SETTING_TYPE_ITEM  1

#define MAX_SETTING_NAME_LEN 13
#define MAX_SETTING_STACK_LEVEL 4
#define MAX_SETTING_ITEMS 8


extern int my_sprintf(char *a, const char *b, ...);

#define SPRINTF sprintf

typedef struct{
	uint32_t freq;
}cpu_conf_typedef;

typedef struct{
	uint8_t busWidth;
}card_conf_typedef;

typedef struct{
	int baudrate;
}debug_conf_typedef;

typedef struct{
	char fontEnabled, sort, photo_frame_td;
}filer_conf_typedef;

typedef struct{
	uint8_t brightness, time2sleep;
}disp_conf_typedef;

typedef union
{
	uint8_t d8;
	struct
	{
		uint8_t fft : 1;
		uint8_t fft_bar_type: 2;
		uint8_t fft_bar_color_idx : 3;
		uint8_t musicinfo : 1;
		uint8_t prehalve : 1;
	}b;
}music_conf_typedef;

typedef struct{
//	cpu_conf_typedef cpu_conf;
//	card_conf_typedef card_conf;
//	debug_conf_typedef debug_conf;
	filer_conf_typedef filer_conf;
	disp_conf_typedef disp_conf;
	music_conf_typedef music_conf;
}settings_group_typedef;

extern settings_group_typedef settings_group;


typedef struct{
	const uint16_t *data;
	const uint8_t *alpha;
}icon_ptr_typedef;


typedef struct  __attribute__ ((packed)) {
	unsigned char selected_id;
	unsigned char item_count;
	const unsigned int *item_array;
	void *(*func)(void *arg);
}settings_item_typedef;

typedef struct  __attribute__ ((packed)) settings_list_struct {
	const char name[MAX_SETTING_NAME_LEN];
	const icon_ptr_typedef *icon;
	const short itemCnt;
	struct settings_list_struct *next;
	void *(*func)(void *arg);
	const char type;
	settings_item_typedef *item;
}settings_list_typedef;


typedef struct  __attribute__ ((packed)) {
	uint8_t pos[MAX_SETTING_ITEMS], \
			items[MAX_SETTING_ITEMS], \
			idx;
	char name[MAX_SETTING_STACK_LEVEL][MAX_SETTING_NAME_LEN];
}settings_stack_typedef;

#define NEXT_LIST(list) ((settings_list_typedef*)list)

extern const uint8_t settings_save_128[]; extern const size_t _sizeof_settings_save_128[];

extern char settings_mode;
extern unsigned char settings_root_list_fileCnt;
extern settings_list_typedef *settings_p, *settings_parent;
extern settings_stack_typedef settings_stack;

extern const settings_list_typedef settings_root_list[];
extern const settings_list_typedef settings_card_list[];
extern const settings_list_typedef settings_card_buswidth_list[];
extern const settings_list_typedef settings_back_to_cardlist[];
extern const settings_list_typedef settings_back_to_cpulist[];


extern const settings_list_typedef settings_usb_msc_list[], settings_usb_msc_select_list[];
extern const settings_list_typedef settings_about_motionplayer_list[];

extern const settings_list_typedef settings_cpu_list[];
extern const settings_list_typedef settings_cpufreq_list[];

extern const settings_list_typedef settings_debug_list[];
extern const settings_list_typedef settings_baudrate_list[];

extern const settings_list_typedef settings_photo_list[];
extern const settings_list_typedef settings_font_list[];
extern const settings_list_typedef settings_sort_list[];
extern const settings_list_typedef settings_photo_frame_td_list[];

extern const settings_list_typedef settings_display_list[];
extern const settings_list_typedef settings_brightness_list[];
extern const settings_list_typedef settings_sleeptime_list[];

extern const settings_list_typedef settings_music_list[];
extern const settings_list_typedef settings_musicinfo_list[];
extern const settings_list_typedef settings_fft_list[];
extern const settings_list_typedef settings_fft_display_list[];
extern const settings_list_typedef settings_fft_bar_type_list[];
extern const settings_list_typedef settings_fft_bar_color_list[];
extern const settings_list_typedef settings_prehalve_list[];


extern void SETTINGS_Init(void);
extern void SETTINGS_Save(void);
void *SETTING_ABOUT_MOTIONPLAYER(void *arg);
void *SETTINGS_PHOTO_FRAME_TD(void *arg);
void *SETTINGS_DISPLAY_BRIGHTNESS(void *arg);
void *SETTINGS_DISPLAY_SLEEP(void *arg);
void *SETTINGS_FFT(void *arg);
void *SETTINGS_FFT_BAR_TYPE(void *arg);
void *SETTINGS_FFT_BAR_COLOR(void *arg);
void *SETTINGS_MUSICINFO(void *arg);

#endif /* SETTINGS_H_ */
