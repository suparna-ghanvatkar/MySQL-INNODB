# MySQL-INNODB
A program which that connects to a MySQL server and checks if the InnoDB plug-in is installed on it, also prints total number of disk writes by MySQL.<br>
Steps:<br>
$ mysql_config --libs<br>
$ mysql_config --cflags<br>
$ gcc -o output-file $(mysql_config --cflags) mysql-c-api.c $(mysql_config --libs<br>
