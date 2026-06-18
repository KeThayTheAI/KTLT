# KTLT
Lệnh compile:
gcc -std=c11 -Wall -Wextra -pedantic src/main.c src/utils.c src/transaction.c src/budget.c src/report.c src/file_io.c -Iinclude -o expense_manager
Lệnh chạy:
./expense_manager