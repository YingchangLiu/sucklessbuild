/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx          = 2;        /* border pixel of windows */
static const unsigned int gappx             = 6;        /* gaps between windows */
static const unsigned int snap              = 32;       /* snap pixel */
static const int showbar                    = 1;        /* 0 means no bar */
static const int topbar                     = 0;        /* 0 means bottom bar */
static const unsigned int systraypinning    = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing    = 2;   /* systray spacing */
static const int systraypinningfailfirst    = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray                = 1;   /* 0 means no systray */
static const Bool viewontag                 = True;     /* Switch view on tag switch */
static const char *fonts[]                  = { "DejaVu Sans Mono:size=11","WenQuanYi Zen Hei Mono:size=11" };
static const char dmenufont[]               = "monospace:size=11";
static const char col_gray1[]               = "#222222";
static const char col_gray2[]               = "#444444";
static const char col_gray3[]               = "#bbbbbb";
static const char col_gray4[]               = "#eeeeee";
static const char col_cyan[]                = "#005577";
static const char col_cyan2[]               = "#37474F";
static const char col_border[]              = "#42A5F5";
static const unsigned int baralpha          = 0xd0;
static const unsigned int borderalpha       = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan2, col_border},
    [SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
//	"st", NULL,
	"sh", "-c", "/home/kelen/dotfile/config/autostart.sh",  NULL,
	NULL /* terminate */
};

typedef struct {
   const char *name;
   const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
const char *spcmd4[] = {"thunar", NULL };
static Sp scratchpads[] = {
   /* name          cmd  */
   {"spterm",      spcmd1},
   {"spranger",    spcmd2},
   {"keepassxc",   spcmd3},
   {"pavucontrol", spcmd4},
};


/* tagging */
//static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 1; /* 1 means alttags will show only when key is held down*/

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     switchtotag     isfloating   monitor */
     { "Tor Browser",   NULL,       NULL,       1 << 1,       2,             0,           -1 },
     { "firefox",       NULL,       NULL,       1 << 1,       2,             0,           -1 },
     { "icalingua",     NULL,       NULL,       1 << 2,       3,             0,           -1 },
     { "weixin",        NULL,       NULL,       1 << 2,       3,             0,           -1 },
     { "thunderbird",   NULL,       NULL,       1 << 3,       4,             0,           -1 },
     { "Zotero",        NULL,       NULL,       1 << 4,       5,             0,           -1 },
     { "qqmusic",       NULL,       NULL,       1 << 6,       7,             0,           -1 },
     { "Steam",         NULL,       NULL,       1 << 8,       9,             1,           -1 },
     { "Lutris",        NULL,       NULL,       1 << 8,       9,             1,           -1 },
     { "wegame.exe",    NULL,       NULL,       1 << 8,       9,             1,           -1 },
     { "Gimp",          NULL,       NULL,       0,            0,             1,           -1 },
     { "Pavucontrol",   NULL,       NULL,       0,            0,             1,           -1 },
     { "Thunar",        NULL,       NULL,       0,            0,             1,           -1 },
     { NULL,            "spterm",   NULL,       SPTAG(0),     0,             1,           -1 },
     { NULL,            "spfm",     NULL,       SPTAG(1),     0,             1,           -1 },
     { NULL,            "keepassxc",NULL,       SPTAG(2),     0,             1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "HHH",      gaplessgrid },
};

/* key definitions */
#include <X11/XF86keysym.h>
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
static const char *dmenucmd[] 		= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  		= { "st", NULL };
static const char *trayercmd[]      = { "/home/kelen/dotfile/script/systray-toggle.sh", NULL};
static const char *killprocesscmd[] = { "/home/kelen/dotfile/config/bin/killprocess", NULL};
static const char *backgroundcmd[]  = { "/home/kelen/dotfile/config/bin/xorg-background-changer", NULL};
static const char *wallenginecmd[]  = { "/home/kelen/dotfile/config/bin/xorg-wallpaperengine-changer", NULL};
static const char *screenshotcmd[]  = { "flameshot", "gui", NULL};


static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_o,      spawn,          {.v = trayercmd } },
    { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = killprocesscmd } },
    { MODKEY,                       XK_c,      spawn,          {.v = backgroundcmd } },
    { MODKEY,                       XK_x,      spawn,          {.v = wallenginecmd } },
    { Mod1Mask|ShiftMask,           XK_s,      spawn,          {.v = screenshotcmd } },
    { ControlMask|Mod1Mask,         XK_l,      spawn,          SHCMD("slock") },
    { MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
//  { 0, XF86XK_AudioMute,                     spawn,          SHCMD("sh /home/kelen/dotfile/script/voltoggle.sh") },
//  { 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("sh /home/kelen/dotfile/script/volup.sh") },
//  { 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("sh /home/kelen/dotfile/script/voldown.sh") },
    { Mod1Mask,                     XK_Left,   spawn,          SHCMD("pavucontrol") },
    { 0, XF86XK_AudioMute,                     spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
    { 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
    { 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
    { 0, XF86XK_MonBrightnessUp,               spawn,          SHCMD("light -A 5") },
    { 0, XF86XK_MonBrightnessDown,             spawn,          SHCMD("light -U 5") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_grave,  togglescratch,  {.ui = 0 } },
    { MODKEY,                       XK_v,      togglescratch,  {.ui = 1 } },
    { MODKEY,                       XK_z,      togglescratch,  {.ui = 2 } },
    { MODKEY,                       XK_e,      togglescratch,  {.ui = 3 } },
    { MODKEY,                       XK_n,      togglealttag,   {0} },
    { MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

