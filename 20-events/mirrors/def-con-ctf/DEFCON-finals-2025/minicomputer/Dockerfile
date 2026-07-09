# Feel free to use other base images if you like
FROM ubuntu:24.04

RUN apt-get update && apt-get install xinetd adduser -y

ADD xinetd.cfg /etc/xinetd.d/serv

WORKDIR /app
ADD build/shredder /app/shredder
ADD build/donatello /app/donatello
ADD build/leonardo /app/leonardo
ADD build/michelangelo /app/michelangelo
ADD build/raphael /app/raphael
ADD build/splinter /app/splinter
ADD build/april /app/april

# This is optional, you are allowed to run as root :)
# Also at least for 24.04, there is a default ubuntu user in the image
RUN adduser --no-create-home --disabled-password --gecos "" user
USER user

CMD ["/usr/sbin/xinetd", "-dontfork"]
