ARG DISTRO=stretch

FROM buildpack-deps:$DISTRO

RUN apt-get update \
&&  apt-get install -y gdb strace ltrace vim upx python-dev python3-dev poppler-utils ruby binwalk \
&&  apt-get clean

# pwntools (requier Python 2.7 pour l'instant)
RUN curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
&&  python2 /tmp/get-pip.py \
&&  pip2 --no-cache-dir install --upgrade pwntools \
&&  rm /tmp/get-pip.py

# extensions de gdb
RUN mkdir -p /opt \
&&  git clone --depth 1 https://github.com/longld/peda.git /opt/peda-master \
&&  echo "source /opt/peda-master/peda.py" >> /root/.gdbinit \
&&  git clone --depth 1 https://github.com/hugsy/gef.git /opt/gef-master \
&&  echo "# source /opt/gef-master/gef.py" >> /root/.gdbinit \
&&  echo "alias gef='gdb -q -nx -ex \"source /opt/gef-master/gef.py\"'" >> /root/.bashrc

# pip3, ropper et pyasn1
RUN curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
&&  python3 /tmp/get-pip.py \
&&  pip3 install --no-cache-dir ropper pyasn1 Pillow bitarray \
&&  rm /tmp/get-pip.py

# villoc: Visualization of heap operations.
RUN mkdir -p /opt \
&&  git clone --depth 1 https://github.com/wapiflapi/villoc.git /opt/villoc-master \
&&  ln -rsf /opt/villoc-master/villoc.py /usr/local/bin/villoc

# pdftotext: cf. poppler-utils

# zsteg: https://github.com/zed-0xff/zsteg
RUN gem install zsteg

RUN echo "alias ls='ls --color=auto'\nalias ll='ls --color=auto -l'\nalias l='ls --color=auto -lA'" >> /root/.bashrc \
&&  echo export LANG=fr_FR.UTF-8 >> /root/.bashrc \
&&  echo export LC_CTYPE=C.UTF-8 >> /root/.bashrc \
&&  echo '[ $(tty) != "/dev/pts/0" ] && echo -e "I am on tty \033[01;33m$(tty)\033[0m"' >> /root/.bashrc \
&&  echo "syntax on" >> /root/.vimrc

VOLUME /dgse
WORKDIR /dgse

CMD ["bash"]
