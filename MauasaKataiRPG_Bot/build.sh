file="build/MauasaKataiRPG"

echo "Building bot..."
g++ -o "$file" ./src/adt/cpp/*.cpp ./src/classes/cpp/*.cpp ./src/utils/cpp/*.cpp main.cpp -ldpp -lcurl -lmysqlcppconn -std=c++20 -DDPP_CORO
echo "Build done"