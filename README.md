# cordis_atan2
cordic atan2 for stm32



perfomance is good, witrh no optimisation enabled 2.5 time faster than math atan2f. up to 7 faster with optimisation

precision is good too

```
no opt
 angle = 355(-913), fxpt_atan2 = -910(942), atan2f = -909(2795), sn= -2855 cs=32642 
 angle = 356(-731), fxpt_atan2 = -727(945), atan2f = -727(2795), sn= -2285 cs=32687 
 angle = 357(-549), fxpt_atan2 = -545(948), atan2f = -545(2795), sn= -1714 cs=32722 
 angle = 358(-367), fxpt_atan2 = -363(942), atan2f = -363(2795), sn= -1143 cs=32747 
 angle = 359(-185), fxpt_atan2 = -181(942), atan2f = -181(2795), sn= -571 cs=32762 
 
debug 
 angle = 237(-22393), fxpt_atan2 = -22392(493), atan2f = -22390(3243), sn= -27480 cs=-17846 
 angle = 238(-22211), fxpt_atan2 = -22210(485), atan2f = -22208(3705), sn= -27787 cs=-17363 
 angle = 239(-22029), fxpt_atan2 = -22028(487), atan2f = -22026(3705), sn= -28086 cs=-16876 
 angle = 240(-21847), fxpt_atan2 = -21846(487), atan2f = -21844(3705), sn= -28377 cs=-16383 
 angle = 241(-21665), fxpt_atan2 = -21664(489), atan2f = -21662(3705), sn= -28658 cs=-15885 
 
speed
 angle = 288(-13109), fxpt_atan2 = -13108(241), atan2f = -13106(3035), sn= -31163 cs=10125 
 angle = 289(-12927), fxpt_atan2 = -12926(267), atan2f = -12924(3035), sn= -30981 cs=10667 
 angle = 290(-12745), fxpt_atan2 = -12744(279), atan2f = -12742(3035), sn= -30790 cs=11206 
 angle = 291(-12563), fxpt_atan2 = -12562(274), atan2f = -12560(3035), sn= -30590 cs=11742 
 angle = 292(-12381), fxpt_atan2 = -12380(277), atan2f = -12378(3035), sn= -30381 cs=12274 
 angle = 293(-12199), fxpt_atan2 = -12198(251), atan2f = -12196(3264), sn= -30162 cs=12803 
```
