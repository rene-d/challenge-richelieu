
undefined8 FUN_00400932(void)

{
  undefined local_418 [1032];
  long local_10;

  puts("************************************************");
  puts("** Vérification du couple login/mot de passe. **");
  puts("************************************************");
  local_10 = FUN_0040086d(local_418);
  if (local_10 == 0) {
    puts("Pas bon. Il vaudrait mieux utiliser un autre couple login/mot de passe");
  }
  else {
    printf("Okay, vous pouvez utiliser ce couple login/mot de passe pour le login %s.\n",local_10);
  }
  return 0;
}
