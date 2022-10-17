Automatický překlad na Windows spouštět jako
  mingw32-make.exe --f Makefile.win

případně
  make --f Makefile.win

Očekává se nainstalovaný překladač MinGW v C:\MinGW\bin\gcc.exe, jinak je třeba upravit skript v Makefile.win na prvním řádku.

Pro kontrolu chyb lze využít skript check_output.bat spouštěný v příkazové řádce (cmd), kam je třeba zadat dva parametry, a to dva soubory k porovnání. 
Je třeba mít instalovaný diff program v C:\MinGW\msys\1.0\bin\

příklad použití
  check_output.bat pub01.out pub01.student.out