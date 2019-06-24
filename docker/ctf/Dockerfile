# Dockerfile pour les containers AttrapeLeDrapeau

#
FROM debian:stretch-slim AS base

RUN apt-get update \
&&  apt-get install -y --no-install-recommends gdb strace ltrace nano vim emacs figlet sl bsdmainutils gcc make unzip zip python-dev less file \
&&  apt-get install -y --no-install-recommends curl \
&&  apt-get clean

# pip2 et pwntools
RUN curl --insecure https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
&&  python2 /tmp/get-pip.py \
&&  pip2 --no-cache-dir install --upgrade pwntools \
&&  rm /tmp/get-pip.py

# extensions de gdb
RUN mkdir -p /opt \
&&  curl --insecure https://codeload.github.com/longld/peda/zip/master -o /tmp/peda.zip \
&&  unzip -o -d /opt /tmp/peda.zip \
&&  rm /tmp/peda.zip

RUN apt-get purge -y curl \
&&  apt-get autoremove -y

COPY motd /etc

#
FROM base

ARG CTF_USER=defi1

# crée les deux users
RUN useradd --create-home --shell /bin/bash ${CTF_USER} \
 && useradd --create-home --shell /bin/bash ${CTF_USER}-drapeau

# installe le défi
WORKDIR /home/${CTF_USER}
COPY ${CTF_USER} .
RUN chown ${CTF_USER}-drapeau.${CTF_USER}-drapeau prog.bin drapeau.txt \
&&  chmod 6555 prog.bin \
&&  chmod 400 drapeau.txt

USER ${CTF_USER}

RUN echo "source /opt/peda-master/peda.py" >> .gdbinit \
&&  echo "syntax on" >> .vimrc

CMD ["bash", "-l"]
