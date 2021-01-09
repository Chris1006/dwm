/* See LICENSE file for copyright and license details. */

/* appearance */
static       unsigned int borderpx  = 1;        /* border pixel of windows */
static       unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
 
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static       int showbar            = 1;        /* 0 means no bar */
static       int topbar             = 1;        /* 0 means bottom bar */

static const int vertpad            = 5;       /* vertical padding of bar */
static const int sidepad            = 5;       /* horizontal padding of bar */
static const char font[]            = "monospace 11";
static const char dmenufont[]       = "monospace:size=11";

static const char norm_fg[] = "#88C0D0";
static const char norm_bg[] = "#2E3440";
static const char norm_border[] = "#4C566A";

static const char bar_border[] = "#4C566A";

static const char sel_fg[] = "#D08770";
static const char sel_bg[] = "#4C566A";
static const char sel_border[] = "#8FBCBB";

static const char urg_fg[] = "#8FBCBB";
static const char urg_bg[] = "#88C0D0";
static const char urg_border[] = "#88C0D0";

/* static const char status_fg[] = "#B48EAD"; */

static const char *colors[][3]      = {

    /*               fg           bg         border                         */
    [SchemeNorm]    = { norm_fg,  norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]     = { sel_fg,   sel_bg,    sel_border },  // the focused win
  //  [SchemeUrg]     = { urg_fg,   urg_bg,    urg_border },
 /*   [SchemeStatus]  = { status_fg,   norm_bg,   sel_fg }, // Statusbar right {text,background,not used but cannot be empty} */
}; 

static const unsigned int baralpha = 0xd8;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
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
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask         isfloating   isterminal noswallo monitor */
//	{ "Gimp",	  NULL,			NULL,		0,				1,			 -1 },
//	{ "Firefox",  NULL,			NULL,		1 << 8,			0,			 -1 },
    { "st",       NULL,         NULL,       0,              0,           1,         0,      -1 },
    { NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 1,         0,      -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 0,         0,      -1 },
	{ NULL,		  "keepassxc",	NULL,		SPTAG(2),		0,			 0,         0,      -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    // z /* first entry is default */
    { "|M|",      centeredmaster }, // u
    { "><>",      NULL },    // i /* no layout function means floating behavior */
	{ "[M]",      monocle }, // o 
	{ "[@]",      spiral },  // mod+shift+z
    { ">M>",      centeredfloatingmaster }, // mod+shift+u
    { "TTT",      bstack }, // mod+shift+i
	{ "[\\]",     dwindle }, // mod+shift+o
	{ "H[]",      deck },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ NULL,       NULL },
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
static const char *browsercmd[] = { "firefox", NULL };
static const char *calendarcmd[] = { "st", "-e", "khal", "interactive", NULL };
static const char *mailcmd[] = { "st", "-e", "neomutt", NULL };
static const char *newscmd[] = { "st", "-e", "newsboat", NULL };
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
    { 0, XF86XK_AudioMute,		               spawn,		   SHCMD("$HOME/.local/bin/keybinds/volume toggle")},
    { 0, XF86XK_AudioRaiseVolume,		       spawn,		   SHCMD("$HOME/.local/bin/keybinds/volume up" )},
    { 0, XF86XK_AudioLowerVolume,		       spawn,		   SHCMD("$HOME/.local/bin/keybinds/volume down" )},

	// Brightness
	{ 0, XF86XK_MonBrightnessUp,			   spawn,		   SHCMD("$HOME/.local/bin/keybinds/brightness up" )},
	{ 0, XF86XK_MonBrightnessDown,			   spawn,		   SHCMD("$HOME/.local/bin/keybinds/brightness down" )},

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
	{ MODKEY|ShiftMask,    			XK_Return, togglescratch,  {.ui = 0 } },
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
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[7]} },
    
    { MODKEY,                       XK_f,      togglefullscr,  {0} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
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
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    TAGKEYS(                        XK_0,                      9 )
//	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/*static Key keys[] = {
	/* modifier                     key        function        argument */
/*	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,            			XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_x,	   togglescratch,  {.ui = 2 } },
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
};*/

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

