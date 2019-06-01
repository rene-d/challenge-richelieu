FROM buildpack-deps:buster

RUN apt update \
&&  apt install -y gdb strace ltrace vim upx \
&&  apt clean

# pip2 et pwntools
RUN apt-get install -y python2.7 python-pip python-dev git libssl-dev libffi-dev build-essential \
&&  pip install --upgrade pip \
&&  pip install --upgrade pwntools

# extensions de gdb
RUN mkdir -p /opt \
&&  git clone https://github.com/longld/peda.git /opt/peda-master \
&&  echo "source /opt/peda-master/peda.py" >> /root/.gdbinit \
&&  git clone https://github.com/hugsy/gef.git /opt/gef-master \
&&  echo "# source /opt/gef-master/gef.py" >> /root/.gdbinit \
&&  echo "alias gef='gdb -q -nx -ex \"source /opt/gef-master/gef.py\"'" >> /root/.bashrc

# RUN git clone https://github.com/pwndbg/pwndbg /opt/pwndbg-master \
# &&  cd /opt/pwndbg-master \
# &&  ./setup.sh

# RUN git clone https://github.com/snare/voltron /opt/voltron-master \
# &&  cd /opt/voltron-master \
# &&  ./install.sh

# pip3, ropper et pyasn1
RUN curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
&&  python3 /tmp/get-pip.py \
&&  pip3 install virtualenv \
&&  pip3 install ropper pyasn1 \
&&  rm /tmp/get-pip.py

# villoc: Visualization of heap operations.
RUN mkdir -p /opt \
&&  git clone https://github.com/wapiflapi/villoc.git /opt/villoc-master \
&&  ln -rsf /opt/villoc-master/villoc.py /usr/local/bin/villoc

# pdftotext
RUN apt-get install -y poppler-utils

# zsteg: https://github.com/zed-0xff/zsteg
RUN apt-get install -y ruby \
&&  gem install zsteg

RUN echo "alias ll='ls $LS_OPTIONS -l'" >> /root/.bashrc \
&&  echo "syntax on" >> /root/.vimrc

COPY docker-entrypoint.sh /entrypoint
ENTRYPOINT ["/entrypoint"]

CMD ["bash"]
