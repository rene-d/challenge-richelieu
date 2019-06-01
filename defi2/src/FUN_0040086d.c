
char * FUN_0040086d(char *pcParm1)

{
  int iVar1;
  size_t sVar2;
  undefined local_38 [48];

  printf("login $ ");
  fgets(pcParm1,1000,stdin);
  sVar2 = strlen(pcParm1);
  pcParm1[sVar2 - 1] = '\0';
  printf("pass $ ");
  scanf("%s",local_38);
  sVar2 = strlen(pcParm1);
  if (10 < sVar2) {
    puts("ATTENTION : le login est réduit à 10 caractères");
    pcParm1[10] = '\0';
  }
  iVar1 = FUN_004006a6(local_38,pcParm1,pcParm1);
  if (iVar1 == 0) {
    pcParm1 = (char *)0x0;
  }
  return pcParm1;
}
