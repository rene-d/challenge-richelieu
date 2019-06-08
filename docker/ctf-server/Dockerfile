FROM docker:edge

RUN apk add --update openssh ca-certificates

# regénère les host keys
RUN rm -rf /etc/ssh/ssh_host_* \
&&  /usr/bin/ssh-keygen -A

# installe le shell qui lance docker
COPY motd /etc
COPY ctfsh /bin
RUN echo /bin/ctfsh >> /etc/shells \
&&  addgroup -g 500 docker

# la crontab (nettoyage des connexions trop longues)
COPY clean-ctf.sh /bin
RUN crontab -l | { cat; echo "*/1 * * * * /bin/clean-ctf.sh"; } | crontab -

# crée l'utilisateur
ARG USER="defi1"
ARG PASSWORD="defi1"
ENV UID=1000 GID=1000
RUN addgroup --gid "$GID" "$USER" \
&&  adduser \
    --disabled-password \
    --gecos "" \
    --home "$(pwd)" \
    --ingroup "$USER" \
    --no-create-home \
    --uid "$UID" \
    --shell "/bin/ctfsh" \
    "$USER" \
&&  addgroup $USER docker \
&&  echo "$USER:$PASSWORD" | chpasswd

# expose le 22 de sshd
EXPOSE 22

COPY entrypoint /entrypoint
ENTRYPOINT ["/entrypoint" ]
