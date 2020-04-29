FROM ubuntu
COPY ./la6.cpp .
COPY ./123.txt .
RUN apt update
RUN apt install -y vim
RUN apt install -y build-essential

