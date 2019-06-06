FROM debian:stretch-slim

RUN apt-get update \
&&  apt-get install -y --no-install-recommends gdb strace ltrace nano vim emacs figlet sl bsdmainutils gcc make unzip zip python-dev less file \
&&  apt-get install -y --no-install-recommends curl \
&&  apt-get clean

# pip2 et pwntools
RUN curl --insecure https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
&&  python2 /tmp/get-pip.py \
&&  pip2 install --upgrade pwntools \
&&  rm /tmp/get-pip.py

# extensions de gdb
RUN mkdir -p /opt \
&&  curl --insecure https://codeload.github.com/longld/peda/zip/master -o /tmp/peda.zip \
&&  unzip -o -d /opt /tmp/peda.zip \
&&  rm /tmp/peda.zip

RUN apt-get purge -y curl \
&&  apt-get autoremove -y

COPY motd /etc

RUN useradd --create-home --password XXX --shell /bin/bash defi1 \
 && useradd --create-home --password 'DGSE{ce mot de passe doit rester inaccessible}' --shell /bin/bash defi1-drapeau

WORKDIR /home/defi1
COPY defi1 .
RUN chown defi1-drapeau.defi1-drapeau prog.bin drapeau.txt \
&&  chmod 4555 prog.bin \
&&  chmod 400 drapeau.txt

USER defi1

RUN echo "source /opt/peda-master/peda.py" >> .gdbinit \
&&  echo "syntax on" >> .vimrc

CMD ["bash"]
