
ulong FUN_004006a6(char *pcParm1,char *pcParm2)

{
  char *pcVar1;
  size_t sVar2;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  uint local_1c;

  local_1c = 1;
  local_20 = 0;
  local_24 = 0;
  local_28 = 0;
  pcVar1 = strcasestr(pcParm1,pcParm2);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = strcasestr(pcParm2,pcParm1);
    if (pcVar1 == (char *)0x0) goto LAB_00400716;
  }
  local_1c = 0;
  puts("[-] le mot de passe est compris dans le login (ou l\'inverse)");
LAB_00400716:
  sVar2 = strlen(pcParm1);
  if (sVar2 < 8) {
    local_1c = 0;
    puts("[-] mot de passe trop petit (moins de 8 caractères)");
  }
  local_2c = 0;
  while (pcParm1[(long)local_2c] != '\0') {
    if (('`' < pcParm1[(long)local_2c]) && (pcParm1[(long)local_2c] < '{')) {
      local_20 = local_20 + 1;
    }
    if (('@' < pcParm1[(long)local_2c]) && (pcParm1[(long)local_2c] < '[')) {
      local_24 = local_24 + 1;
    }
    if (('/' < pcParm1[(long)local_2c]) && (pcParm1[(long)local_2c] < ':')) {
      local_28 = local_28 + 1;
    }
    local_2c = local_2c + 1;
  }
  if (local_28 == 0) {
    local_1c = 0;
    puts("[-] il n\'y a pas de nombre");
  }
  if (local_24 == 0) {
    local_1c = 0;
    puts("[-] il n\'y a pas de majuscule");
  }
  if (local_20 == 0) {
    local_1c = 0;
    puts("[-] il n\'y a pas de minuscule");
  }
  sVar2 = strlen(pcParm1);
  if (local_20 + local_24 + local_28 == (int)sVar2) {
    local_1c = 0;
    puts("[-] il n\'y a pas de caractère spécial");
  }
  return (ulong)local_1c;
}
