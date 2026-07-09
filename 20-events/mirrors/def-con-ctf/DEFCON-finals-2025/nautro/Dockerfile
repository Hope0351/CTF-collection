FROM ubuntu:24.04@sha256:a08e551cb33850e4740772b38217fc1796a66da2506d312abe51acda354ff061 as builder

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN wget -q https://ziglang.org/builds/zig-x86_64-linux-0.15.0-dev.936+fc2c1883b.tar.xz
RUN tar -xf zig-x86_64-linux-0.15.0-dev.936+fc2c1883b.tar.xz

ADD stdlib.patch /.
RUN cd /zig-x86_64-linux-0.15.0-dev.936+fc2c1883b/lib/std && patch -p1 < /stdlib.patch

ENV PATH="/zig-x86_64-linux-0.15.0-dev.936+fc2c1883b/:$PATH"

WORKDIR /app

RUN echo "CARDS"

ADD src/ /app/src/
ADD Makefile /app/.
ADD *.py /app/.

RUN mkdir -p /app/data/cards && make final

FROM ubuntu:24.04@sha256:a08e551cb33850e4740772b38217fc1796a66da2506d312abe51acda354ff061

WORKDIR /app

ADD entrypoint.sh /app/
COPY --from=builder /app/main /app/.
COPY --from=builder /app/data/cards/ /app/data/cards/
#COPY /main /app/.
#COPY ./data/cards/ /app/data/cards/
COPY frontend/ /app/static/
RUN ln -s /app/static/ /static

ADD libengine_base.so /app/.

CMD ["/app/entrypoint.sh"]
