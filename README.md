# cordis_atan2
cordic atan2 for stm32



perfomance is good, witrh no optimisation enabled 2.5 time faster than math atan2f. up to 7 faster with optimisation

precision is good too

```
 angle = 355(-913), fxpt_atan2 = -910(942), atan2f = -909(2795), sn= -2855 cs=32642 
 angle = 356(-731), fxpt_atan2 = -727(945), atan2f = -727(2795), sn= -2285 cs=32687 
 angle = 357(-549), fxpt_atan2 = -545(948), atan2f = -545(2795), sn= -1714 cs=32722 
 angle = 358(-367), fxpt_atan2 = -363(942), atan2f = -363(2795), sn= -1143 cs=32747 
 angle = 359(-185), fxpt_atan2 = -181(942), atan2f = -181(2795), sn= -571 cs=32762 
 
 angle = 237(-22393), fxpt_atan2 = -22392(493), atan2f = -22390(3243), sn= -27480 cs=-17846 
 angle = 238(-22211), fxpt_atan2 = -22210(485), atan2f = -22208(3705), sn= -27787 cs=-17363 
 angle = 239(-22029), fxpt_atan2 = -22028(487), atan2f = -22026(3705), sn= -28086 cs=-16876 
 angle = 240(-21847), fxpt_atan2 = -21846(487), atan2f = -21844(3705), sn= -28377 cs=-16383 
 angle = 241(-21665), fxpt_atan2 = -21664(489), atan2f = -21662(3705), sn= -28658 cs=-15885 
```
