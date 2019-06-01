#! /usr/bin/env python3

import subprocess
import pyasn1.codec.der.encoder
import pyasn1.type.univ
import base64
import logging


logging.basicConfig(format="%(asctime)s:%(levelname)s:%(message)s", level=logging.INFO, datefmt="%H:%M:%S")


class FindPrimes:
    """
    classe de recherche des premiers (prime.txt + changements)
    """
    def __init__(self, bytes, changes):
        logging.info("recherche des nombres premiers")
        self.primes = []
        self.changes = changes
        count = self.is_prime(bytes)
        logging.info("nombre de premiers: %d/%d", len(self.primes), count)

    def is_prime(self, bytes, start=0):
        count = 0
        len_bytes = len(bytes)
        if start == len_bytes:
            result = subprocess.check_output(["openssl", "prime", "-hex", "".join(bytes)]).decode()
            if result.endswith(' is prime\n'):
                logging.debug("openssl prime: %s", result)
                self.primes.append(int("".join(bytes), 16))
            count = 1

        else:
            count += self.is_prime(bytes, start + 1)
            for before, after in self.changes:
                if bytes[start] == after:
                    new_bytes = bytes.copy()
                    new_bytes[start] = before
                    count += self.is_prime(new_bytes, start + 1)
                    break

        return count


def egcd(a, b):
    """
    calcule le GCD étendu
    """
    if a == 0:
        return b, 0, 1
    g, y, x = egcd(b % a, a)
    return g, x - (b // a) * y, y


def modinv(a, m):
    """
    calcule l'Inverse modulaire
    """
    g, x, y = egcd(a, m)
    if g != 1:
        raise ValueError
    return x % m


def pempriv(n, e, d, p, q, dP, dQ, qInv):
    """
    crée un fichier PEM pour stocker une clé RSA
    https://crypto.stackexchange.com/questions/25498/how-to-create-a-pem-file-for-storing-an-rsa-key/25499#25499
    """
    template = '-----BEGIN RSA PRIVATE KEY-----\n{}-----END RSA PRIVATE KEY-----\n'
    seq = pyasn1.type.univ.Sequence()
    for x in [0, n, e, d, p, q, dP, dQ, qInv]:
        seq.setComponentByPosition(len(seq), pyasn1.type.univ.Integer(x))
    der = pyasn1.codec.der.encoder.encode(seq)
    return template.format(base64.encodebytes(der).decode('ascii'))


def main():

    # lecture du fichier prime.txt
    bytes = "".join(s.strip() for s in open("prime.txt") if s.startswith(" ")).split(":")

    # liste des changements effectués par sed
    # e1 a été changé en 66, mais pas tous les 66 sont nécessairement des e1
    # etc.
    changes = [("7f", "fb"),
               ("e1", "66"),
               ("f4", "12"),
               ("16", "54"),
               ("a4", "57"),
               ("b5", "cd")]

    # lecture du modulus de la clé publique
    modulus = subprocess.check_output("openssl rsa -pubin -in public.key -modulus -noout", shell=True)
    modulus = int(modulus.decode().strip()[len("Modulus="):], 16)
    logging.info("modules: %d", modulus)

    fp = FindPrimes(bytes, changes)

    # on doit avoir modulus = p * q
    for p in fp.primes:
        q, r = divmod(modulus, p)
        if r == 0:
            logging.info("solution trouvée")

            # https://0day.work/how-i-recovered-your-private-key-or-why-small-keys-are-bad/

            phi = (p - 1) * (q - 1)
            d = modinv(65537, phi)  # privExp
            dP = d % (p - 1)  # e1
            dQ = d % (q - 1)  # e2
            qInv = pow(q, p - 2, p)  # coeff

            with open("priv.key", "w") as f:
                f.write(pempriv(modulus, 65537, d, p, q, dP, dQ, qInv))

            break
    else:
        logging.error("pas de solution trouvée")


if __name__ == '__main__':
    main()
