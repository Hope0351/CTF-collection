# Feel free to use other base images if you like
FROM ubuntu:24.04 AS whisper-build
RUN apt-get update -qy && apt-get install -y build-essential cmake git wget curl
WORKDIR /src
RUN git clone --depth 1 --branch v1.7.6 https://github.com/ggml-org/whisper.cpp.git
RUN cd whisper.cpp && cmake -B build && cmake --build build -j --config Release && sh ./models/download-ggml-model.sh tiny.en

FROM ubuntu:24.04 AS jukebooox-base

RUN apt-get update && apt-get install xinetd adduser libgomp1 -y

ADD xinetd.cfg /etc/xinetd.d/serv

RUN mkdir -p /opt/whisper/lib
COPY --from=whisper-build /src/whisper.cpp/build/bin/whisper-cli /opt/whisper/
COPY --from=whisper-build /src/whisper.cpp/build/src/libwhisper.so.1.7.6 /opt/whisper/lib/
COPY --from=whisper-build /src/whisper.cpp/build/ggml/src/libggml.so /opt/whisper/lib/
COPY --from=whisper-build /src/whisper.cpp/build/ggml/src/libggml-base.so /opt/whisper/lib/
COPY --from=whisper-build /src/whisper.cpp/build/ggml/src/libggml-cpu.so /opt/whisper/lib/
COPY --from=whisper-build /src/whisper.cpp/models/ggml-tiny.en.bin /opt/whisper/

# set up the lib 
RUN cp /opt/whisper/lib/libwhisper.so.1.7.6 /usr/local/lib/
RUN ln -s /usr/local/lib/libwhisper.so.1.7.6 /usr/local/lib/libwhisper.so.1 && \
    ln -s /usr/local/lib/libwhisper.so.1.7.6 /usr/local/lib/libwhisper.so

RUN cp /opt/whisper/lib/libggml.so /usr/local/lib/
RUN cp /opt/whisper/lib/libggml-base.so /usr/local/lib/
RUN cp /opt/whisper/lib/libggml-cpu.so /usr/local/lib/

# Update the dynamic linker
RUN ldconfig

WORKDIR /app
ADD release/jukebooox /app/

RUN touch /app/filters.txt

# This is optional, you are allowed to run as root :)
# Also at least for 24.04, there is a default ubuntu user in the image
RUN adduser --no-create-home --disabled-password --gecos "" user
USER user

ENV WHISPER_CLI_PATH=/opt/whisper/whisper-cli
ENV WHISPER_MODEL=/opt/whisper/ggml-tiny.en.bin
ENV FILTER_PATH=/app/filters.txt
ENV JUKEBOOOX_DEVICE_DIR=/app

CMD ["/usr/sbin/xinetd", "-dontfork"]

FROM jukebooox-base AS jukebooox-echooo
ADD release/echooo.so /app/

FROM jukebooox-base AS jukebooox-laptooop
ADD release/laptooop.so /app/

FROM jukebooox-base AS jukebooox-prooodigi
ADD release/prooodigi.so /app/

FROM jukebooox-base AS jukebooox-all
# All devices for now
ADD release/echooo.so /app/
ADD release/laptooop.so /app/
ADD release/prooodigi.so /app/
