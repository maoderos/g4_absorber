cp analysis.py 0T
cp analysis.py 0.5T

cd 0T
python3 analysis.py
cd ..
cd 0.5T
python3 analysis.py

cd ..

python3 plot_b.py
python3 fit.py
