PROG=proj

SRCS = proj.c video_gr.c timer.c utils.c keyboard.c logic.c mouse.c rtc.c power_up.c animations.c UI_elements.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
