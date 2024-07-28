file="build/MauasaKataiRPG"

echo "Building bot..."
g++ -o "$file" ./headers/src/*.cpp main.cpp -ldpp -lcurl -lmysqlcppconn -std=c++17
echo "Build done"