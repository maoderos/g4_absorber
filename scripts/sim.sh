
mkdir data
cd data
mkdir phi45 phi60 phi90
cd ..


cmake ../
make

./absorber events45.in

mv plus1 data/phi45
mv plus2 data/phi45
mv minus1 data/phi45
mv minus2 data/phi45

cmake ../
make

./absorber events60.in
mv plus1 data/phi60
mv plus2 data/phi60
mv minus1 data/phi60
mv minus2 data/phi60

cmake ../
make

./absorber events90.in
mv plus1 data/phi90
mv plus2 data/phi90
mv minus1 data/phi90
mv minus2 data/phi90

