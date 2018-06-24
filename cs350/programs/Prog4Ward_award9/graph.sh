gnuplot -e "title='80-20 Workload'" -e "input_filename='80-20.csv'" plot_hit_rates.plt > 80-20.png
gnuplot -e "title='No-Locality Workload'" -e "input_filename='no-locality.csv'" plot_hit_rates.plt > no-locality.png
gnuplot -e "title='Looping Workload'" -e "input_filename='looping.csv'" plot_hit_rates.plt > looping.png
