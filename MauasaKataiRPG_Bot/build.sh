file="build/MauasaKataiRPG"

echo "Building bot..."
g++ -o "$file" *.cpp -ldpp -lcurl -lmysqlcppconn -std=c++17
echo "Build done"