/* See LICENSE file for copyright and license details. */

// theme
#include "themes/onedark.h"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */

static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 14;        /* 2 is the default spacing around the bar's font */

static const char *fonts[]          = { "FuraCode Nerd Font:style:Regular:size=11",
					"Material Design Icons-Regular:size=11" };

static const char dmenufont[]       = "JetBrainsMono Nerd Font:style:medium:size=11";

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { gray3, black, gray2 },
	[SchemeSel]  = { gray4, blue,  blue },
	/* Layout indicator's color  */
	[SchemeLayout]     = { green,   black,  black },

};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static char *tags[] = { "", "", "", "" , "" };

static const char* chrome[] = { "nyxt", NULL };

static const Launcher launchers[] = {
    /* command     name to display */
    { chrome,         "爵" },
};

static const unsigned int ulinepad	= 7;	/* Underline position in X axe, increase the value move the uline to right side */
static const unsigned int ulinewidth	= 10;	/* Width of underline */
static const unsigned int ulinestroke	= 3;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 3;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const int horizpadbar        = 8;        /* horizontal padding for statusbar */
static const int vertpadbar         = 14;        /* vertical padding for statusbar */

static const char *tagsel[][2] = {
  { blue,    black, },
  { red,     black, },
  { orange,  black, },
  { green,   black, },
  { pink,    black, },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance           title       tags mask     isfloating   monitor */
	{ "Gimp",       NULL,              NULL,       0,            1,           -1 },
	{ "Firefox",    NULL,              NULL,       1 << 8,       0,           -1 },
	{ "KeePassXC",  "keepassxc",       NULL,       1 << 4,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
/* Using rofi instead of dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "rofi", "-show", "drun" };
static const char *termcmd[]  = { "alacritty", NULL };
/* dmenu script for retrieving passwords from pass */
static const char *passmenu[]  = { "passmenu", NULL };
static const char *editor[]    = {"/usr/bin/sh", "-c", "if systemctl --user is-active --quiet emacs; then /usr/bin/emacsclient -c; else /usr/bin/emacs; fi", NULL };

/* Using 0 to indicate there is no MODKEY key to be pressed */
#define NONE 0

/* Sound */
static const char *vol_mute[]  = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *vol_down[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *vol_up[]    = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
        /* Specifing keysym 0x1008ff12 without using the <X11/keysym.h>  */
	{ NONE,                         0x1008ff12,      spawn,          {.v = vol_mute } }, 
	{ NONE,                         0x1008ff11,      spawn,          {.v = vol_down } },
	{ NONE,                         0x1008ff13,      spawn,          {.v = vol_up   } },		
	{ MODKEY,                       XK_p,            spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,       spawn,          {.v = termcmd  } },
  	{ MODKEY,                       XK_o,            spawn,          {.v = passmenu } },
	{ MODKEY,                       XK_e,            spawn,          {.v = editor   } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        TAGKEYS(                        XK_ampersand,                         0)
	TAGKEYS(                        XK_eacute,                            1)
	TAGKEYS(                        XK_quotedbl,                          2)
	TAGKEYS(                        XK_quoteright,                        3)
	TAGKEYS(                        XK_parenleft,                         4)
	TAGKEYS(                        XK_minus,                             5)
	TAGKEYS(                        XK_egrave,                            6)
	TAGKEYS(                        XK_underscore,                        7)
	TAGKEYS(                        XK_ccedilla,                          8)
        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

