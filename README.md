# cordis_atan2
cordic atan2 for stm32



perfomance is good, 2.5 time faster than math atan2f. precision is good too

```
 angle = 355(-913), fxpt_atan2 = -910(942), atan2f = -909(2795), sn= -2855 cs=32642 
 angle = 356(-731), fxpt_atan2 = -727(945), atan2f = -727(2795), sn= -2285 cs=32687 
 angle = 357(-549), fxpt_atan2 = -545(948), atan2f = -545(2795), sn= -1714 cs=32722 
 angle = 358(-367), fxpt_atan2 = -363(942), atan2f = -363(2795), sn= -1143 cs=32747 
 angle = 359(-185), fxpt_atan2 = -181(942), atan2f = -181(2795), sn= -571 cs=32762 
```
