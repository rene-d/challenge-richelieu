FROM docker:edge

RUN apk add --update openssh ca-certificates

# regénère les host keys
RUN rm -rf /etc/ssh/ssh_host_* \
&&  /usr/bin/ssh-keygen -A

# installe le shell qui lance docker
COPY motd /etc
COPY ctfsh /bin
RUN echo /bin/ctfsh >> /etc/shells \
&&  chmod 4755 /bin/ctfsh

# la crontab
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
&&  echo "$USER:$PASSWORD" | chpasswd

EXPOSE 22

COPY entrypoint /entrypoint
ENTRYPOINT ["/entrypoint" ]
