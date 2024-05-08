/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int arrowpx   = 18;       /* arrow size in px */
static const unsigned int s_arrowpx = 18;  
static       unsigned int borderpx  = 4;        /* border pixel of windows */
static       unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
 
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static       int showbar            = 1;        /* 0 means no bar */
static       int topbar             = 1;        /* 0 means bottom bar */

static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char font[]            = "monospace Bold 11";
static const char dmenufont[]       = "monospace:size=11";
/*
static const char col_gray1[]       = "#1d2021";
static const char col_gray2[]       = "#504945";
static const char col_gray3[]       = "#bdae93";
static const char col_gray4[]       = "#ebdbb2";
static const char col_cyan[]        = "#cc241d";
*/
//static const char *colors[][3]      = {
	/*               fg         bg         border   */
/*	[SchemeNorm] = { col_gray3, col_gray1,  col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2,  col_gray3 },
	[ArrowSel]   = { col_gray2, col_gray1,  col_gray1 },
	[ArrowNorm]  = { col_gray1, col_gray2,  col_gray1 },
};*/


static const char nord_polar_darkest_blue[]        = "#2E3440";
static const char nord_polar_darker_blue[]        = "#3B4252";
static const char nord_polar_lighter_dark_blue[]        = "#434C5E";
static const char nord_polar_lightest_dark_blue[]        = "#4C566A";
static const char nord_dark_white[]        = "#D8DEE9";
static const char nord_darker_white[]        = "#E5E9F0";
static const char nord_white[]        = "#ECEFF4";
static const char nord_white_dark[]        = "#d8dee9";
static const char nord_frost_light_blue[]        = "#8FBCBB";
static const char nord_frost_darker_light_blue[]        = "#88C0D0";
static const char nord_frost_lighter_dark_blue[]        = "#81A1C1";
static const char nord_frost_dark_blue[]        = "#5E81AC";
static const char nord_red[]        = "#BF616A";
static const char nord_orange[]        = "#D08770";
static const char nord_yellow[]        = "#EBCB8B";
static const char nord_green[]        = "#A3BE8C";
static const char nord_purple[]        = "#B48EAD";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { nord_white, nord_polar_darkest_blue, nord_polar_darkest_blue },
	[SchemeSel]  = { nord_polar_darkest_blue, nord_frost_darker_light_blue,  nord_red },

    [ArrowSel]  = { nord_polar_darkest_blue, nord_polar_darkest_blue,  nord_red },
    [ArrowNorm]  = { nord_white, nord_polar_darkest_blue,  nord_polar_darkest_blue }
};

static const unsigned int baralpha = 0xd8;
static const unsigned int borderalpha = 0xd8;
static const unsigned int barfgalpha = 0xd8;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { barfgalpha, baralpha, borderalpha },
	[SchemeSel]  = { barfgalpha, baralpha, borderalpha },
	[ArrowSel]  =  { barfgalpha, baralpha, borderalpha },
	[ArrowNorm]  = { barfgalpha, baralpha, borderalpha },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
};

/* tagging */
static const char *tags[] = { "", "", "", "", ""};
static const char *tags_active[] = { "", "", "", "", ""};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance      title   tags mask   isfloating   isterminal noswallo monitor */
    { "st",     NULL,         NULL,   0,          0,           1,         0,      -1 },
    { NULL,		  "spterm",		  NULL,		SPTAG(0),		1,			     1,         0,      -1 },
	  { NULL,		  "spfm",		    NULL,		SPTAG(1),		1,			     0,         0,      -1 },
	  { NULL,		  "keepassxc",	NULL,		SPTAG(2),		0,			     0,         0,      -1 },
};

/* layout(s) */
static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
    
 //  { "",    tile },                       /* Default: Master on left, Slaves on right */
 // { "[M]",      centeredmaster }, // u
  //{ "",u      NULL },    // i /* no layout function means floating behavior */
//{ "",      monocle }, // o 
//	{ "",      spiral },  // mod+shift+z
//  { "",      centeredfloatingmaster }, // mod+shift+u
//  { "",      bstack }, // mod+shift+i
//	{ "",     dwindle }, // mod+shift+o
//	{ "",      deck },
//	{ "===",      bstackhoriz },
//	{ "",      grid },
//	{ "###",      nrowgrid },
//	{ "---",      horizgrid },
//	{ "",      gaplessgrid },
//	{ NULL,       NULL },*/
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon,  NULL };
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_base01, "-nf", col_base04, "-sb", col_base0D, "-sf", col_base00, NULL };
static const char *logoutcmd[] = { "logout-script", NULL };
static const char *lockcmd[] = { "lockscreen", NULL };

static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[] = { "librewolf", NULL };
static const char *calendarcmd[] = { "thunderbird",  NULL };
static const char *mailcmd[] = { "thunderbird", NULL };
static const char *newscmd[] = { "thunderbird", NULL };
static const char *torbrowsercmd[] = { "tor-browser", NULL };
static const char *fileexplorercmd[] = { "st", "-e", "ranger", NULL };
static const char *musicplayercmd[] = { "st", "-e", "ncmpcpp", NULL };
static const char *torrentcmd[] = { "st", "-e", "tremc", NULL };
 
/*
* Xresources preferences to load at startup
*/
ResourcePref resources[] = {
    { "borderpx",          	INTEGER, &borderpx },
    { "snap",          		INTEGER, &snap },
    { "showbar",          	INTEGER, &showbar },
    { "topbar",          	INTEGER, &topbar },
    { "nmaster",          	INTEGER, &nmaster },
    { "resizehints",       	INTEGER, &resizehints },
    { "mfact",      	 	FLOAT,   &mfact },
};


#include <X11/XF86keysym.h>

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static char *statuscmds[] = { "notify-send Mouse$BUTTON" };
static char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

static Key keys[] = {
  // Audio
  { 0, XF86XK_AudioMute,		             spawn,		   SHCMD("$HOME/.local/bin/keybinds/volume toggle")},
  { 0, XF86XK_AudioRaiseVolume,		       spawn,		   SHCMD("$HOME/.local/bin/keybinds/volume up" )},
  { 0, XF86XK_AudioLowerVolume,		       spawn,		   SHCMD("$HOME/.local/bin/keybinds/volume down" )},

	// Brightness
	{ 0, XF86XK_MonBrightnessUp,			   spawn,		   SHCMD("$HOME/.local/bin/keybinds/brightness up" )},
	{ 0, XF86XK_MonBrightnessDown,			 spawn,		   SHCMD("$HOME/.local/bin/keybinds/brightness down" )},

	// Multimedia
	{ 0, XF86XK_AudioPlay,					   spawn,		   SHCMD("mpc toggle" )},
	{ 0, XF86XK_AudioNext,					   spawn,		   SHCMD("mpc next" )},
	{ 0, XF86XK_AudioPrev,					   spawn,		   SHCMD("mpc prev" )},
    
	// Screenshots
	{ 0,                            XK_Print,  spawn,          SHCMD("screenshot") },
	{ ShiftMask,                    XK_Print,  spawn,          SHCMD("screenshot_pick") },

	// Mounting
	{ MODKEY,						XK_F5,	   spawn,		   SHCMD("dmenumount") },

	// Display Select
	{ MODKEY,						XK_F3,	   spawn,		   SHCMD("displayselect") },
	{ 0, XF86XK_Display,					   spawn,		   SHCMD("displayselect") },
    
	{ MODKEY,						XK_F9,	   spawn,		   SHCMD("togglepicom") },
	// Pomodoro
	{ MODKEY|ControlMask,           XK_p,      spawn,          SHCMD("$HOME/.local/bin/keybinds/pomodoro") },	

   // Program Shortcuts
    /* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,    			    XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },
  { MODKEY,                       XK_c,      spawn,          {.v = calendarcmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = mailcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = newscmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = torbrowsercmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = fileexplorercmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = musicplayercmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = torrentcmd } },

  { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = logoutcmd } }, 
  { ControlMask|Mod1Mask,         XK_Delete, spawn,          {.v = lockcmd } },
  { MODKEY|ShiftMask,             XK_x,      spawn,          {.v = lockcmd} },

  { MODKEY|ShiftMask,             XK_r,      quit,          {.v = 23} },

  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_k,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	
  { MODKEY,                       XK_z,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_z,      setlayout,      {.v = &layouts[4]} },
//	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} },
//	{ MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[6]} },
//	{ MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[7]} },
  
  { MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	 
  { MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_ssharp, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_ssharp, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
//	TAGKEYS(                        XK_6,                      5)
//	TAGKEYS(                        XK_7,                      6)
//	TAGKEYS(                        XK_8,                      7)
//	TAGKEYS(                        XK_9,                      8)
//  TAGKEYS(                        XK_0,                      9 )
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
  { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
  { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
 
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

