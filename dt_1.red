;redcode-94
;assert CORESIZE == 8000
;author Damion Terrell and Dominic Paul Delvecchio
;name dt_1.red
spl.x  # 0,< 7
add.ab < -3,{ -1
div.ba < 5,> 6
div.x  # -5,* 5
jmp.i  @ 7,> 3
mul.b  > -6,< 5
slt.x  > -2,> -1
mov.ba < -2,# 0
sne.x  { -8,# 7
djn.b  @ -3,$ 0
end;
