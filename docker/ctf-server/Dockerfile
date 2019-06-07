FROM docker:edge

RUN apk add --update openssh ca-certificates

RUN rm -rf /etc/ssh/ssh_host_rsa_key /etc/ssh/ssh_host_dsa_key \
&&  /usr/bin/ssh-keygen -f /etc/ssh/ssh_host_rsa_key -N '' -t rsa \
&&  /usr/bin/ssh-keygen -f /etc/ssh/ssh_host_dsa_key -N '' -t dsa \
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
ENV USER="defi1"
ENV PASSWORD="DGSE{2f77c517b06f1cd1ce864f79f41f25ca8874413c8c1204f7ec9c6728c87f270a}"
ENV UID=1000
ENV GID=1000

RUN addgroup --gid "$GID" "$USER" \
    && adduser \
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

COPY startctf.sh /

CMD ["/startctf.sh"]
