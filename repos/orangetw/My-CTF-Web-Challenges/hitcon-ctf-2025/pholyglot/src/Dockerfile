FROM debian:bookworm

EXPOSE 80

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        apache2 \
        libapache2-mod-php \
        php \
        php-sqlite3 \
        php-cli \
        && rm -rf /var/lib/apt/lists/*

COPY www/index.php /var/www/html/
COPY ./flag /flag
COPY ./read_flag /read_flag

RUN a2enmod php* && a2enmod rewrite
RUN sed -i 's/Options Indexes FollowSymLinks/Options FollowSymLinks/' /etc/apache2/apache2.conf
RUN rm /var/www/html/index.html

RUN ln -s /var/www/html /www && mkdir /www/sandbox/
RUN chown -R root:root /www/ && chmod 777 /www/sandbox/

RUN chown root:root /flag /read_flag
RUN chmod 400 /flag
RUN chmod 755 /read_flag && chmod +s /read_flag
RUN chmod 755 /www/index.php

WORKDIR /var/www/html

CMD ["apachectl", "-D", "FOREGROUND"]


