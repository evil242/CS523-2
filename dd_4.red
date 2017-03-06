;redcode-94
;assert CORESIZE == 8000
;author Damion Terrell and Dominic Paul Delvecchio
;name dd_4.red
jmz.i  @ 3,> 8
sne.ab $ -9,< -1
mul.a  < 5,@ 7
spl.f  # -2,@ 4
cmp.ab * 6,# -3
slt.b  @ 8,$ -6
seq.b  # 6,@ -6
jmz.ba > -9,@ -8
dat.b  $ 2,$ -6
mod.x  # -1,@ -7
end;
