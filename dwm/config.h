/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define TERM "urxvt"
#define BROWSER "firefox"
#define FBROWSER "urxvt -name lf -e lf"
#define READER "zathura"
#define PWDMGR "keepassxc"
#define EDITOR "emacs"

/* appearance */
static const unsigned int borderpx       = 0;   /* border pixel of windows */
static const unsigned int gappih	 = 0;    /* horiz inner gap between windows */
static const unsigned int gappiv    	 = 0;   /* vert inner gap between windows */
static const unsigned int gappoh    	 = 0;   /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    	 = 0;   /* vert outer gap between windows and screen edge */
static int smartgaps           	 	 = 0;   /* 1 means no outer gap when there is only one window */
static const unsigned int snap           = 32;  /* snap pixel */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
#define ICONSIZE 10    /* icon size */
#define ICONSPACING 5  /* space between icon and title */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */
static const int centerwindow = 1;

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]               = { "Cozette:size=10" };
static const char dmenufont[]            = "Cozette:size=10";

static char c000000[]            = "#000000";  // placeholder value

static char normfgcolor[]        = "#ffffff";
static char normbgcolor[]        = "#000000";
static char normbordercolor[]    = "#444444";
static char normfloatcolor[]     = "#db8fd9";

static char selfgcolor[]         = "#ffffff";
static char selbgcolor[]         = "#000000";
static char selbordercolor[]     = "#ffffff";
static char selfloatcolor[]      = "#333333";

static char titlenormfgcolor[]       = "#ffffff";
static char titlenormbgcolor[]       = "#000000";
static char titlenormbordercolor[]   = "#000000";
static char titlenormfloatcolor[]    = "#db8fd9";

static char titleselfgcolor[]        = "#ffffff";
static char titleselbgcolor[]        = "#000000";
static char titleselbordercolor[]    = "#000000";
static char titleselfloatcolor[]     = "#333333";

static char tagsnormfgcolor[]        = "#cccccc";
static char tagsnormbgcolor[]        = "#000000";
static char tagsnormbordercolor[]    = "#000000";
static char tagsnormfloatcolor[]     = "#db8fd9";

static char tagsselfgcolor[]         = "#ffffff";
static char tagsselbgcolor[]         = "#000000";
static char tagsselbordercolor[]     = "#000000";
static char tagsselfloatcolor[]      = "#000000";

static char hidnormfgcolor[]         = "#333333";
static char hidselfgcolor[]          = "#227799";
static char hidnormbgcolor[]         = "#222222";
static char hidselbgcolor[]          = "#222222";

static char urgfgcolor[]             = "#000000";
static char urgbgcolor[]             = "#ffffff";
static char urgbordercolor[]         = "#000000";
static char urgfloatcolor[]          = "#db8fd9";

static const unsigned int baralpha = 0x77;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
	/*                       fg      bg        border     */
	[SchemeNorm]         = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]          = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleNorm]    = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleSel]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidNorm]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidSel]       = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]          = { OPAQUE, baralpha, borderalpha },
};

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static char *tagicons[][NUMTAGS] =
{
	[DEFAULT_TAGS]        = { "一", "二", "三", "四", "五", "六", "七", "八", "九"},
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "lf", .isfloating = 1)
	RULE(.class = "Navigator", .tags = 1 << 0)
	RULE(.class = "emacs", .tags = 1 << 1)
	RULE(.class = "vesktop", .tags = 1 << 2)
	RULE(.class = "easyeffects", .tags = 1 << 8)
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status,             draw_status,            click_status,            NULL,                    "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[@]",      spiral },
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
static const char *j4dmenu[] = {
	"j4-dmenu-desktop",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
static const char *termcmd[]  = { TERM, NULL };
static const char *browser[]  = { BROWSER, NULL };
static const char *filebrowser[]  = { FBROWSER, NULL };
static const char *editor[]  = { EDITOR, NULL };
static const char *pwdmgr[]  = { PWDMGR, NULL };
static const char *reader[]  = { READER, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "urxvt", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *monitor[] = { "autorandr --load lemon && nitrogen --restore", NULL};


static const char *upvol[]      = { "/usr/bin/wpctl",   "set-volume", "@DEFAULT_AUDIO_SINK@",      "5%+",      NULL };
static const char *downvol[]    = { "/usr/bin/wpctl",   "set-volume", "@DEFAULT_AUDIO_SINK@",      "5%-",      NULL };
static const char *mutevol[]    = { "/usr/bin/wpctl",   "set-mute",   "@DEFAULT_AUDIO_SINK@",      "toggle",   NULL };
static const char *light_up[]   = { "/sbin/brightnessctl",   "set", "5%+", NULL };
static const char *light_down[] = { "/sbin/brightnessctl",   "set", "5%-", NULL };

static const Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_d,          spawn,                  {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,          spawn,                  {.v = j4dmenu } },
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_minus,      togglescratch,          {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_Right,      incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_Left,       incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,     zoom,                   {0} },
 	{ MODKEY,                       XK_u,          incrgaps,               {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_u,          incrgaps,               {.i = -1 } },
 	{ MODKEY,                       XK_i,          incrigaps,              {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_i,          incrigaps,              {.i = -1 } },
 	{ MODKEY,                       XK_o,          incrogaps,              {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_o,          incrogaps,              {.i = -1 } },
 	{ MODKEY,                       XK_0,          togglegaps,             {0} },
 	{ MODKEY|ShiftMask,             XK_0,          defaultgaps,            {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY,                       XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_e,          quit,                   {0} },
	{ MODKEY|ShiftMask,             XK_r,          quit,                   {1} },
	{ MODKEY|ShiftMask,             XK_F5,         xrdb,                   {.v = NULL } },
	{ MODKEY,                       XK_s,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,          setlayout,              {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_g,          setlayout,              {.v = &layouts[10]} },
	{ MODKEY|ShiftMask,             XK_f,          togglefullscr,          {0} },
	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     cyclelayout,            {.i = +1 } },
	{ MODKEY,                       XK_x,          spawn,                  SHCMD("xkill")  },
	{ MODKEY,                       XK_F1,         spawn,                  {.v = filebrowser } },
	{ MODKEY,                       XK_F2,         spawn,                  {.v = browser } },
	{ MODKEY,                       XK_F3,         spawn,                  {.v = reader } },
	{ MODKEY,                       XK_F4,         spawn,                  SHCMD("anki") },
	{ MODKEY,                       XK_F10,        spawn,                  {.v = pwdmgr } },
	{ MODKEY,                       XK_F11,        spawn,                  {.v = editor } },
	{ MODKEY,                       XK_F12,        spawn,                  {.v = monitor } },
	{ 0,                  XF86XK_AudioLowerVolume, spawn,                  {.v = downvol } },
	{ 0,                         XF86XK_AudioMute, spawn,                  {.v = mutevol } },
	{ 0,                  XF86XK_AudioRaiseVolume, spawn,                  {.v = upvol   } },
	{ 0,	               XF86XK_MonBrightnessUp, spawn,                  {.v = light_up} },
	{ 0,		     XF86XK_MonBrightnessDown, spawn,                  {.v = light_down} },
	{ 0,                            XK_Print,      spawn,                  SHCMD("$HOME/.scripts/scrshot")  },
	{ ControlMask,                  XK_Print,      spawn,                  SHCMD("$HOME/.scripts/fullscrshot")  },
	{ ShiftMask,                    XK_Print,      spawn,                  SHCMD("$HOME/.scripts/maimrecord")  },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};

