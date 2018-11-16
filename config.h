/*
 * ------------------------------------------------------------
**  FileName:   config.h
**  Desc:       DWM Config File 
**  LastChange: 2016-04-06 20:27:03
------------------------------------------------------------*/
#include <X11/XF86keysym.h>
#include "gaplessgrid.c"
#include "selfrestart.c"
#include "zoomswap.c"
#include "moveresize.c"


/* mbp-mappings */
/* appearance */
/*static const char *fonts[] = {
	"Input Mono Condensed:size=10",
	"i3fonticon:size=10"
};
*/
static const char *fonts[] = {
	/*"termsynu:size=12",*/

	"ProFontWindows Nerd Font Mono:size=10",
  	"Wucon Siji:size=10"
	
/*  	"ProFontWindows Nerd Font Mono:size=9",  */
};




static const unsigned int borderpx 			= 1;	/* border pixel of windows */
static const unsigned int snap 				= 10;	/* snap pixel */
static const unsigned int tagpadding 		= 5;	
static const unsigned int tagspacing 		= 10;	
static const unsigned int gappx				= 20;	/* gap pixel between windows */
static const unsigned int systraypinning 	= 0;	/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing 	= 0;	/* systray spacing */
static const int systraypinningfailfirst 	= 1;	/* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray 				= 1;	/* 0 means no systray */
static const int showbar 					= 1;	/* 0 means no bar */
static const int topbar 					= 1;	/* 0 means bottom bar */

#define NUMCOLORS 9
static const char colors[NUMCOLORS][MAXCOLORS][9] = {
	// border	 foreground	background
	{ "#f9f9f9", "#c49b7c", "#1a2f20" }, // 0 = normal
	{ "#000000", "#c49b7c", "#843a6d" }, // 1 = selected
	{ "#b43030", "#c49b7c", "#b23450" }, // 2 = red / urgent
	{ "#212121", "#c49b7c", "#14161A" }, // 3 = green / occupied
	{ "#212121", "#ab7438", "#0b0606" }, // 4 = yellow
	{ "#212121", "#475971", "#0b0606" }, // 5 = blue
	{ "#212121", "#694255", "#0b0606" }, // 6 = cyan
	{ "#212121", "#3e6868", "#0b0606" }, // 7 = magenta
	{ "#212121", "#f5f5f5", "#843a6d" }, // 8 = rojo sangre
};

/* tagging */
static const char *tags[] = {
/*		"web",
		"term",
		"code",
		"media",
		"game",
		"misc" 
*/
		"    ",
		"    ",
		"    ",
		"    ",
		"    ",
		"    ",
/*
		"1",
		"2",
		"3",
		"4",
		"5",
		"6"
*/
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class			instance	title		tags mask	isfloating		monitor */
	{ "Gimp",			NULL,		NULL,		0,				0,			-1 },
	{ "Firefox",		NULL,		NULL,		2 << 0,			0,			-1 },
	{ "Steam",			NULL,		NULL,		1 << 4,			1,			-1 },
	{ "Nitrogen",		NULL,		NULL,		0,			  	1,			-1 },
	{ "Lxappearance",	NULL,		NULL,		0,				1,			-1 },
	{ "XCalc",			NULL,		NULL,		0,				1,			-1 },
	{ "Xgrabcolor",		NULL,		NULL,		0,				1,			-1 },
};

/* layout(s) */
static const float mfact 		= 0.55;	/* factor of master area size [0.05..0.95] */
static const int nmaster 		= 1;	/* number of clients in master area */
static const int resizehints 	= 0;	/* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|=",      tile },    /* first entry is default */
	{ "Null",      NULL },    /* no layout function means floating behavior */
	{ "Monocle",      monocle },
	{ "htile",      htile },
	{ "gap",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] 			= "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "run", "-bw", "0", "-sidebar-mode", "-terminal sakura", NULL };
static const char *termcmd[] 		= { "urxvt", NULL };
static const char *screenshot[] 	= { "screenshot", NULL};
static const char *volupcmd[]      = { "amixer", "-c", "1", "-q", "set", "Master", "5%+", NULL };
static const char *voldncmd[]      = { "amixer", "-c", "1", "-q", "set", "Master", "5%-", NULL };
static const char *mpctog[]        = { "mpc", "toggle", NULL };
static const char *mpcprev[]       = { "mpc", "prev", NULL };
static const char *mpcnext[]       = { "mpc", "next", NULL };
static const char *mute[]       = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *brightupcmd[] = { "xbacklight", "+", "10", NULL };
static const char *brightdowncmd[] = { "xbacklight", "-", "10", NULL };
static const char *printscreen[] = { "scrotc", NULL};


static Key keys[] = {
	/* modifier			key				function			argument */
	        { 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = volupcmd } },
        { 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = voldncmd } },
        { 0,                            XF86XK_AudioPlay,           spawn,          {.v = mpctog } },
        { 0,                            XF86XK_AudioPrev,           spawn,          {.v = mpcprev } },
        { 0,                            XF86XK_AudioNext,           spawn,          {.v = mpcnext } },
        { 0,                            XF86XK_AudioMute,           spawn,        { .v = mute } },
        { 0,                            XF86XK_MonBrightnessUp,     spawn,        { .v = brightupcmd } },
        { 0,                            XF86XK_MonBrightnessDown,   spawn,        { .v = brightdowncmd } },
        { 0,                            0xff61,                     spawn,        { .v = printscreen } },
	{ MODKEY,			XK_p,				spawn,				{.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_Return,			spawn,				{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_b,				togglebar,			{0} },
	{ MODKEY,			XK_j,				focusstack,			{.i = +1 } },
	{ MODKEY,			XK_k,				focusstack,			{.i = -1 } },
	{ MODKEY,			XK_i,				incnmaster,			{.i = +1 } },
	{ MODKEY,			XK_d,				incnmaster,			{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_j,				setmfact,			{.f = -0.05} },
	{ MODKEY|ShiftMask,		XK_l,				setmfact,			{.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_j,				setcfact,			{.f = +0.25} },
	{ MODKEY|ShiftMask,		XK_k,				setcfact,			{.f = -0.25} },
	{ MODKEY|ShiftMask,		XK_o,				setcfact,			{.f =  0.00} },
	{ MODKEY,			XK_n,				pushdown,			{0} },
        { MODKEY,			XK_m,				pushup,				{0} },
	{ MODKEY,			XK_Return,			zoom,				{0} },
	{ MODKEY,			XK_Tab,				view,				{0} },
	{ MODKEY|ShiftMask,		XK_c,				killclient,			{0} },
	{ MODKEY,			XK_q,				setlayout,			{.v = &layouts[0]} },
	{ MODKEY,			XK_w,				setlayout,			{.v = &layouts[1]} },
	{ MODKEY,			XK_e,				setlayout,			{.v = &layouts[2]} },
	{ MODKEY,			XK_r,				setlayout,			{.v = &layouts[3]} },
	{ MODKEY,			XK_t,				setlayout,			{.v = &layouts[4]} },
	{ MODKEY,			XK_space,			setlayout,			{0} },
        { MODKEY,			XK_f,				togglefullscreen,		{0} },
	{ MODKEY|ShiftMask,		XK_space,			togglefloating,			{0} },
	{ MODKEY,			XK_0,				view,				{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,				tag,				{.ui = ~0 } },
	{ MODKEY,			XK_comma,			focusmon,			{.i = -1 } },
	{ MODKEY,			XK_period,			focusmon,			{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_comma,			tagmon,				{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_period,			tagmon,				{.i = +1 } },
	{ MODKEY,                       XK_Down,       			 moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
        { MODKEY,                       XK_Up,    			 moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
        { MODKEY,                       XK_Right, 			 moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
        { MODKEY,                       XK_Left,  			 moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},
        { MODKEY|ShiftMask,             XK_Down,  			 moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
        { MODKEY|ShiftMask,             XK_Up,    			 moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
        { MODKEY|ShiftMask,             XK_Right, 			 moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
        { MODKEY|ShiftMask,             XK_Left,  			 moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},



	TAGKEYS(					XK_1,					0)
	TAGKEYS(					XK_2,					1)
	TAGKEYS(					XK_3,					2)
	TAGKEYS(					XK_4,					3)
	TAGKEYS(					XK_5,					4)
	TAGKEYS(					XK_6,					5)
	TAGKEYS(					XK_7,					6)
	TAGKEYS(					XK_8,					7)
	TAGKEYS(					XK_9,					8)
	{ MODKEY|ShiftMask,			XK_q,					quit,			{0} },
	{ MODKEY|ShiftMask,			XK_r,					self_restart,		{0} },
};
	/*  
    { 0,					XK_Print,				spawn,			{.v = screenshot } },
	{ 0,					XF86AudioRaiseVolume,	  		spawn,			{.v = volup } },
    { 0,					XF86AudioLowerVolume,			spawn,			{.v = voldown } },
    { 0,					XF86AudioMute,				spawn,			{.v = voltoggle } },
    { 0,					XF86TouchpadToggle,			spawn,			{.v = togtouchpad } },
*/
/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click					event mask		button			function			argument */
	{ ClkLtSymbol,					0,			Button1,		setlayout,			{0} },
	{ ClkLtSymbol,					0,			Button3,		setlayout,			{.v = &layouts[2]} },
	{ ClkStatusText,				0,			Button2,		spawn,				{.v = termcmd } },
	{ ClkClientWin,					MODKEY,		Button1,		movemouse,			{0} },
	{ ClkClientWin,					MODKEY,		Button2,		togglefloating,		{0} },
	{ ClkClientWin,					MODKEY,		Button3,		resizemouse,		{0} },
	{ ClkTagBar,					0,			Button1,		view,				{0} },
	{ ClkTagBar,					0,			Button3,		toggleview,			{0} },
	{ ClkTagBar,					MODKEY,		Button1,		tag,				{0} },
	{ ClkTagBar,					MODKEY,		Button3,		toggletag,			{0} },
};
