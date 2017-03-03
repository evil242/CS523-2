;redcode-94
;assert CORESIZE == 8000
;author Damion Terrell and Dominic Paul Delvecchio
;name dt_4.red
nop.a  > 0,> 6
jmp.a  # 0,$ 9
cmp.x  $ -8,* 6
djn.f  > -7,> 1
jmn.ba { -2,* 8
slt.ba * 1,{ 5
div.ba > 8,< -8
jmz.i  > -4,{ -8
add.ba @ 1,{ 0
jmn.a  # -3,< -5
end;
