cp analisys.py 0T
cp analisys.py 0.5T

cd 0T
python3 analisys.py
cd ..
cd 0.5T
python3 analisys.py

cd ..

python3 plot_b.py
python3 fit.py
