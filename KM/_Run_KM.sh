g++ -O3 KM.cpp -o temp

echo "cifar_0"
./temp < ../Data/CIFAR/cifar_0.txt
echo "cifar_7"
./temp < ../Data/CIFAR/cifar_1.txt
echo "cifar_14"
./temp < ../Data/CIFAR/cifar_2.txt
echo "cifar_21"
./temp < ../Data/CIFAR/cifar_3.txt
echo "cifar_28"
./temp < ../Data/CIFAR/cifar_4.txt
echo "cifar_35"
./temp < ../Data/CIFAR/cifar_5.txt

echo "CircleSquare_100_100"
./temp < ../Data/CircleSquare/CircleSquare_100_100.txt
echo "CircleSquare_900_900"
./temp < ../Data/CircleSquare/CircleSquare_900_900.txt
echo "CircleSquare_2500_2500"
./temp < ../Data/CircleSquare/CircleSquare_2500_2500.txt
#echo "CircleSquare_4900_4900"
#./temp < ../Data/CircleSquare/CircleSquare_4900_4900.txt