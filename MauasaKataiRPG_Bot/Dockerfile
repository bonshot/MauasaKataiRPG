FROM gcc:latest

WORKDIR /MauasaKataiRPG_Bot
COPY /MauasaKataiRPG_Bot .

RUN apt-get update && apt-get install -y \
    apt-utils\
    wget \
    cmake \
    build-essential \
    gnupg \
    libopus0 \
    libssl-dev \
    libmysqlcppconn-dev \
    lsb-release \
    libsodium23 \
    libcurl4-openssl-dev

RUN wget -O dpp.deb https://dl.dpp.dev/ && \
    dpkg -i dpp.deb && \
    apt-get install -f -y && \
    rm dpp.deb; 

RUN sh build.sh

CMD ["./build/MauasaKataiRPG"]