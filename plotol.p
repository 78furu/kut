
set term png
set grid
set xlabel "x koordináta (m)"
set ylabel "y koordináta (m)"
set title "A hold pályája"
set out "ered.png"
plot "res.txt" u 2:3 w d t "Számolt adatok"
