SHELL :=	/bin/sh
# =====================================||===================================== #
#																			   #
#							   Colors and Styles							   #
#																			   #
#																			   #
#																			   #
#		https://chrisyeh96.github.io/2020/03/28/terminal-colors.html		   #
#				 https://www.google.com/search?q=color+chooser				   #
#				  https://en.wikipedia.org/wiki/Tertiary_color				   #
# ================Makefile=============||==============©Othello=============== #

# =====================================||===================================== #
#																			   #
#									 Basics									   #
#																			   #
# ================Makefile=============||==============©Othello=============== #
CC_ESC :=	\033[
CC_COLOR :=	38;2;
CC_BG :=	48;2;
C_RESET :=	$(CC_ESC)0m
# =====================================||===================================== #
#																			   #
#								Cursor Controls								   #
#																			   #
# ================Makefile=============||==============©Othello=============== #
CC_CLEAR =	\033c
CC_ERASE =	\x1b[H\x1b[0J
CC_1UP =	\033[F\x1b[0J
CC_LINE =	\r$(CC_ESC)0J
# =====================================||===================================== #
#																			   #
#									 Styles									   #
#																			   #
# ================Makefile=============||==============©Othello=============== #
C_BOLD =	\x1b[1m
C_WEAK =	\x1b[2m
C_UNDL =	\x1b[4m
C_BLNK =	\x1b[5m
# =====================================||===================================== #
#																			   #
#									 Colors									   #
#																			   #
# =====================================||===================================== #
#								   Graytones								   #
# ================Makefile=============||==============©Othello=============== #
C_WHITE =	$(CC_ESC)$(CC_COLOR)255;255;255m
C_LGRAY =	$(CC_ESC)$(CC_COLOR)192;192;192m
C_GRAY =	$(CC_ESC)$(CC_COLOR)128;128;128m
C_DGRAY =	$(CC_ESC)$(CC_COLOR)64;64;64m
C_BLACK =	$(CC_ESC)$(CC_COLOR)0;0;0m
# =====================================||===================================== #
#									Rainbow									   #
# ================Makefile=============||==============©Othello=============== #
C_LRED =	$(CC_ESC)$(CC_COLOR)255;128;128m
C_RED =		$(CC_ESC)$(CC_COLOR)255;0;0m
C_DRED =	$(CC_ESC)$(CC_COLOR)128;0;0m

C_LORANGE =	$(CC_ESC)$(CC_COLOR)255;192;128m
C_ORANGE =	$(CC_ESC)$(CC_COLOR)255;128;0m
C_DORANGE =	$(CC_ESC)$(CC_COLOR)128;64;0m

C_LYELLOW =	$(CC_ESC)$(CC_COLOR)255;255;128m
C_YELLOW =	$(CC_ESC)$(CC_COLOR)255;255;0m
C_DYELLOW =	$(CC_ESC)$(CC_COLOR)128;128;0m

C_LCHRT =	$(CC_ESC)$(CC_COLOR)192;255;128m
C_CHRT =	$(CC_ESC)$(CC_COLOR)128;255;0m
C_DCHRT =	$(CC_ESC)$(CC_COLOR)64;128;0m

C_LGREEN =	$(CC_ESC)$(CC_COLOR)128;255;128m
C_GREEN =	$(CC_ESC)$(CC_COLOR)0;255;0m
C_DGREEN =	$(CC_ESC)$(CC_COLOR)0;128;0m

C_LSPRGR =	$(CC_ESC)$(CC_COLOR)128;255;192m
C_SPRGR =	$(CC_ESC)$(CC_COLOR)0;255;128m
C_DSPRGR =	$(CC_ESC)$(CC_COLOR)0;128;64m

C_LCYAN =	$(CC_ESC)$(CC_COLOR)128;255;255m
C_CYAN =	$(CC_ESC)$(CC_COLOR)0;255;255m
C_DCYAN =	$(CC_ESC)$(CC_COLOR)0;128;128m

C_LCYBL =	$(CC_ESC)$(CC_COLOR)0;192;255m
C_CYBL =	$(CC_ESC)$(CC_COLOR)0;128;255m
C_DCYBL =	$(CC_ESC)$(CC_COLOR)0;64;128m

C_LBLUE =	$(CC_ESC)$(CC_COLOR)128;128;255m
C_BLUE =	$(CC_ESC)$(CC_COLOR)0;0;255m
C_DBLUE =	$(CC_ESC)$(CC_COLOR)0;0;128m

C_LVIOLET =	$(CC_ESC)$(CC_COLOR)192;0;255m
C_VIOLET =	$(CC_ESC)$(CC_COLOR)128;0;255m
C_DVIOLET =	$(CC_ESC)$(CC_COLOR)64;0;255m

C_LMGNT =	$(CC_ESC)$(CC_COLOR)255;128;255m
C_MGNT =	$(CC_ESC)$(CC_COLOR)255;0;255m
C_DMGNT =	$(CC_ESC)$(CC_COLOR)128;0;128m

C_LROSE =	$(CC_ESC)$(CC_COLOR)255;128;192m
C_ROSE =	$(CC_ESC)$(CC_COLOR)255;0;128m
C_DROSE =	$(CC_ESC)$(CC_COLOR)128;0;64m
# =====================================||===================================== #
#								 Common Colors								   #
# ================Makefile=============||==============©Othello=============== #
C_LPURPLE =	$(CC_ESC)$(CC_COLOR)192;96;192m
C_PURPLE =	$(CC_ESC)$(CC_COLOR)128;0;128m
C_DPURPLE =	$(CC_ESC)$(CC_COLOR)64;0;64m

C_LPINK =	$(CC_ESC)$(CC_COLOR)255;224;229m
C_PINK =	$(CC_ESC)$(CC_COLOR)255;192;203m
C_DPINK =	$(CC_ESC)$(CC_COLOR)128;48;62m

C_LBROWN =	$(CC_ESC)$(CC_COLOR)192;144;96m
C_BROWN =	$(CC_ESC)$(CC_COLOR)128;64;0m
C_DBROWN =	$(CC_ESC)$(CC_COLOR)64;32;0m
# =====================================||===================================== #
#								  Prized Metal								   #
# ================Makefile=============||==============©Othello=============== #
C_BRONZE =	$(CC_ESC)$(CC_COLOR)205;127;50m
C_SILVER =	$(CC_ESC)$(CC_COLOR)192;192;192m
C_GOLD =	$(CC_ESC)$(CC_COLOR)255;215;0m
# =====================================||===================================== #
#																			   #
#							   Background Colors							   #
#																			   #
# =====================================||===================================== #
#								   Graytones								   #
# ================Makefile=============||==============©Othello=============== #
CB_WHITE =	$(CC_ESC)$(CC_BG)255;255;255m
CB_LGRAY =	$(CC_ESC)$(CC_BG)192;192;192m
CB_GRAY =	$(CC_ESC)$(CC_BG)128;128;128m
CB_DGRAY =	$(CC_ESC)$(CC_BG)64;64;64m
CB_BLACK =	$(CC_ESC)$(CC_BG)0;0;0m
# =====================================||===================================== #
#									Rainbow									   #
# ================Makefile=============||==============©Othello=============== #
CB_LRED =	$(CC_ESC)$(CC_BG)255;128;128m
CB_RED =	$(CC_ESC)$(CC_BG)255;0;0m
CB_DRED =	$(CC_ESC)$(CC_BG)128;0;0m

CB_LORANGE =	$(CC_ESC)$(CC_BG)255;192;128m
CB_ORANGE =		$(CC_ESC)$(CC_BG)255;128;0m
CB_DORANGE =	$(CC_ESC)$(CC_BG)128;64;0m

CB_LYELLOW =	$(CC_ESC)$(CC_BG)255;255;128m
CB_YELLOW =		$(CC_ESC)$(CC_BG)255;255;0m
CB_DYELLOW =	$(CC_ESC)$(CC_BG)128;128;0m

CB_LCHRT =	$(CC_ESC)$(CC_BG)192;255;128m
CB_CHRT =	$(CC_ESC)$(CC_BG)128;255;0m
CB_DCHRT =	$(CC_ESC)$(CC_BG)64;128;0m

CB_LGREEN =	$(CC_ESC)$(CC_BG)128;255;128m
CB_GREEN =	$(CC_ESC)$(CC_BG)0;255;0m
CB_DGREEN =	$(CC_ESC)$(CC_BG)0;128;0m

CB_LSPRGR =	$(CC_ESC)$(CC_BG)128;255;192m
CB_SPRGR =	$(CC_ESC)$(CC_BG)0;255;128m
CB_DSPRGR =	$(CC_ESC)$(CC_BG)0;128;64m

CB_LCYAN =	$(CC_ESC)$(CC_BG)128;255;255m
CB_CYAN =	$(CC_ESC)$(CC_BG)0;255;255m
CB_DCYAN =	$(CC_ESC)$(CC_BG)0;128;128m

CB_LCYBL =	$(CC_ESC)$(CC_BG)0;192;255m
CB_CYBL =	$(CC_ESC)$(CC_BG)0;128;255m
CB_DCYBL =	$(CC_ESC)$(CC_BG)0;64;128m

CB_LBLUE =	$(CC_ESC)$(CC_BG)128;128;255m
CB_BLUE =	$(CC_ESC)$(CC_BG)0;0;255m
CB_DBLUE =	$(CC_ESC)$(CC_BG)0;0;128m

CB_LVIOLET =	$(CC_ESC)$(CC_BG)192;0;255m
CB_VIOLET =		$(CC_ESC)$(CC_BG)128;0;255m
CB_DVIOLET =	$(CC_ESC)$(CC_BG)64;0;255m

CB_LMGNT =	$(CC_ESC)$(CC_BG)255;128;255m
CB_MGNT =	$(CC_ESC)$(CC_BG)255;0;255m
CB_DMGNT =	$(CC_ESC)$(CC_BG)128;0;128m

CB_LROSE =	$(CC_ESC)$(CC_BG)255;128;192m
CB_ROSE =	$(CC_ESC)$(CC_BG)255;0;128m
CB_DROSE =	$(CC_ESC)$(CC_BG)128;0;64m
# =====================================||===================================== #
#								 Common Colors								   #
# ================Makefile=============||==============©Othello=============== #
CB_LPURPLE =	$(CC_ESC)$(CC_BG)192;96;192m
CB_PURPLE =		$(CC_ESC)$(CC_BG)128;0;128m
CB_DPURPLE =	$(CC_ESC)$(CC_BG)64;0;64m

CB_LPINK =	$(CC_ESC)$(CC_BG)255;224;229m
CB_PINK =	$(CC_ESC)$(CC_BG)255;192;203m
CB_DPINK =	$(CC_ESC)$(CC_BG)128;48;62m

CB_LBROWN =	$(CC_ESC)$(CC_BG)192;144;96m
CB_BROWN =	$(CC_ESC)$(CC_BG)128;64;0m
CB_DBROWN =	$(CC_ESC)$(CC_BG)64;32;0m
# =====================================||===================================== #
#								  Prized Metal								   #
# ================Makefile=============||==============©Othello=============== #
CB_BRONZE =	$(CC_ESC)$(CC_BG)205;127;50m
CB_SILVER =	$(CC_ESC)$(CC_BG)192;192;192m
CB_GOLD =	$(CC_ESC)$(CC_BG)255;215;0m
# =====================================||===================================== #
#																			   #
#								  Miscellaneous								   #
#																			   #
# ================Makefile=============||==============©Othello=============== #
C_HEADER =	\x1b[48;2;85;85;85m \x1b[48;2;139;139;139m \
\x1b[48;2;192;192;192m \x1b[48;2;255;128;0m \x1b[1m\x1b[38;2;0;0;0m
C_SUBHEAD =	\x1b[48;2;85;85;85m \x1b[48;2;139;139;139m \
\x1b[48;2;192;192;192m \x1b[1m\x1b[38;2;0;0;0m
C_OK =	\x1b[38;2;16;223;16m
