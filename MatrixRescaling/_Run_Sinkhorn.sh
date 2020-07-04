g++ -std=c++11 -O3 Sinkhorn.cpp libopenblas.a -o temp -lpthread

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
./temp 903047 0.1 300 < ../Data/CircleSquare/CircleSquare_100_100.txt
echo "CircleSquare_900_900"
./temp 1962347 0.1 2000 < ../Data/CircleSquare/CircleSquare_900_900.txt
echo "CircleSquare_2500_2500"
./temp 4624285 0.1 3000 < ../Data/CircleSquare/CircleSquare_2500_2500.txt
#echo "CircleSquare_4900_4900"
#./temp 9637536 0.1 4000 < ../Data/CircleSquare/CircleSquare_4900_4900.txt

echo "mnist_0"
./temp 30579383 < ../Data/MNIST/mnist_0.txt
echo "mnist_1"
./temp 24935941 < ../Data/MNIST/mnist_1.txt
echo "mnist_2"
./temp 28361475 < ../Data/MNIST/mnist_2.txt
echo "mnist_3"
./temp 13584214 < ../Data/MNIST/mnist_3.txt
echo "mnist_4"
./temp 37182080 < ../Data/MNIST/mnist_4.txt
echo "mnist_5"
./temp 42948629 < ../Data/MNIST/mnist_5.txt
echo "mnist_6"
./temp 17470352 < ../Data/MNIST/mnist_6.txt
echo "mnist_7"
./temp 36895850 < ../Data/MNIST/mnist_7.txt
echo "mnist_8"
./temp 39010950 < ../Data/MNIST/mnist_8.txt
echo "mnist_9"
./temp 21316843 < ../Data/MNIST/mnist_9.txt

echo "NLP1"
./temp 97477212804 < ../Data/NLP/NLP1.txt
echo "NLP2"
./temp 111669857976 < ../Data/NLP/NLP2.txt
echo "NLP3"
./temp 86117234388 < ../Data/NLP/NLP3.txt
echo "NLP4"
./temp 119159619235 < ../Data/NLP/NLP4.txt
echo "NLP5"
./temp 111056421900 < ../Data/NLP/NLP5.txt

