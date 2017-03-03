;redcode-94
;assert CORESIZE == 8000
;author Damion Terrell and Dominic Paul Delvecchio
;name dt_3.red
mul.ab > -3,$ -2
spl.ab { 6,@ -1
mov.a  @ -3,> -7
jmz.f  # 2,@ -5
mov.a  # -1,> 7
mov.i  $ 9,> 5
sub.ba > -5,* 10
mul.x  < 1,* -9
jmz.ba < 7,@ -1
dat.ab # 9,> 6
end;
