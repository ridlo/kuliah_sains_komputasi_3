#gnuplot input file
set term png size 800,400
set output "verlet.png"
set xlabel "t"
set ylabel "x(t)"
plot "output.txt" u 1:2 w l t "Verlet", "output2.txt" u 1:2 w l t "Euler"
