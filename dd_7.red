;redcode-94
;assert CORESIZE == 8000
;author Damion Terrell and Dominic Paul Delvecchio
;name dd_7.red
mov.x  # 1,> 8
cmp.a  @ 8,@ 5
cmp.f  # -3,$ -5
jmp.f  $ -3,> 10
spl.b  < -8,@ 3
jmz.f  # -8,> -6
div.a  $ 1,* -5
mod.f  @ -1,{ -9
cmp.ab { -4,< 9
mul.b  @ 1,* -7
end;
