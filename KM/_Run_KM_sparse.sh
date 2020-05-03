g++ -O3 KMsparse.cpp -o temp

echo "cifar_0"
./temp 61314 < ../Data/CIFAR/cifar_0.txt
echo "cifar_7"
./temp 56688 < ../Data/CIFAR/cifar_1.txt
echo "cifar_14"
./temp 111916 < ../Data/CIFAR/cifar_2.txt
echo "cifar_21"
./temp 71181 < ../Data/CIFAR/cifar_3.txt
echo "cifar_28"
./temp 99205 < ../Data/CIFAR/cifar_4.txt
echo "cifar_35"
./temp 129008 < ../Data/CIFAR/cifar_5.txt

echo "CircleSquare_100_100"
./temp 903047 < ../Data/CircleSquare/CircleSquare_100_100.txt
echo "CircleSquare_900_900"
./temp 1962347 < ../Data/CircleSquare/CircleSquare_900_900.txt
echo "CircleSquare_2500_2500"
./temp 4624285 < ../Data/CircleSquare/CircleSquare_2500_2500.txt
#echo "CircleSquare_4900_4900"
#./temp 9637536 < ../Data/CircleSquare/CircleSquare_4900_4900.txt