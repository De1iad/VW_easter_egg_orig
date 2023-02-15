FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

COPY . /

RUN apt-get update && apt-get install -y xorg libxext-dev zlib1g-dev libbsd-dev libxrender-dev openssh-server make && service ssh start && make

ENV DISPLAY :0

ENTRYPOINT [ "/bin/bash", "-l", "-c" ]

CMD ["./car_demo"]