FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y python3 python3-pip python3-dev git libssl-dev libffi-dev build-essential rubberband-cli libchromaprint-tools libchromaprint-dev && \
    apt-get clean

RUN python3 -m pip install --upgrade pwntools --break-system-packages

COPY ./requirements.txt /opt/

RUN python3 -m pip install --break-system-packages -r /opt/requirements.txt

COPY ./* /opt/

WORKDIR /opt

CMD python3 /opt/poller.py
