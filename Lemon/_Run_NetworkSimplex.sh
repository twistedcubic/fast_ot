g++ -O3 LemonNetworkSimplex.cpp -o temp -lemon

echo "cifar_0"
./temp < ../Data/CIFAR/cifar_0.txt
echo "cifar_1"
./temp < ../Data/CIFAR/cifar_1.txt
echo "cifar_2"
./temp < ../Data/CIFAR/cifar_2.txt
echo "cifar_3"
./temp < ../Data/CIFAR/cifar_3.txt
echo "cifar_4"
./temp < ../Data/CIFAR/cifar_4.txt
echo "cifar_5"
./temp < ../Data/CIFAR/cifar_5.txt

echo "CircleSquare_100_100"
./temp < ../Data/CircleSquare/CircleSquare_100_100.txt
echo "CircleSquare_900_900"
./temp < ../Data/CircleSquare/CircleSquare_900_900.txt
echo "CircleSquare_2500_2500"
./temp < ../Data/CircleSquare/CircleSquare_2500_2500.txt
echo "CircleSquare_4900_4900"
./temp < ../Data/CircleSquare/CircleSquare_4900_4900.txt

echo "mnist_0"
./temp < ../Data/MNIST/mnist_0.txt
echo "mnist_1"
./temp < ../Data/MNIST/mnist_1.txt
echo "mnist_2"
./temp < ../Data/MNIST/mnist_2.txt
echo "mnist_3"
./temp < ../Data/MNIST/mnist_3.txt
echo "mnist_4"
./temp < ../Data/MNIST/mnist_4.txt
echo "mnist_5"
./temp < ../Data/MNIST/mnist_5.txt
echo "mnist_6"
./temp < ../Data/MNIST/mnist_6.txt
echo "mnist_7"
./temp < ../Data/MNIST/mnist_7.txt
echo "mnist_8"
./temp < ../Data/MNIST/mnist_8.txt
echo "mnist_9"
./temp < ../Data/MNIST/mnist_9.txt

echo "NLP1"
./temp < ../Data/NLP/NLP1.txt
echo "NLP2"
./temp < ../Data/NLP/NLP2.txt
echo "NLP3"
./temp < ../Data/NLP/NLP3.txt
echo "NLP4"
./temp < ../Data/NLP/NLP4.txt
echo "NLP5"
./temp < ../Data/NLP/NLP5.txt

