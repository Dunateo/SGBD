# SGBD By Valentin Bru and Mael Bouchand
This project is our CIR 2 december C project , the subject was "Made a DBMS in C".
The deadline was very short two weeks (not focused on because we still had lessons)
Database management system
A database is an organized collection of data, generally stored and accessed electronically from a computer system.

## **Specifications**

- [x] Stock and recover the data "persistence"
- [x] fixing some goals reachable in two weeks 

In order to implement a maximum of functions in a good looking program we establish specifications.

## **Adding by us**

- [x] SQL command interpreter
- [x] Creating database
- [x] Menu
- [ ] Stock the database architecture in a C structure to simplify specific queries
- [ ] file command to execute many queries 

## **SQL Commands**

form of the order: COMMAND.PARAMETER dont forget the . 

* INSERT 
  * LIGNE 
* DELETE 
  * ALL 
  * TABLE 
  * LIGNE 
* SELECT
  * "*"
  * TABLE
* UPDATE 
  * ALL 
* HELP
* END

## **Architecture**
![Architecture of database](/images/archit.png)
![Architecture of tables](/images/tables.png)

## **MENU**

* SELECTION 1 
  * In order to SELECT a database and a table
* CREATE 2
  * Create a new database
  * Adding a new table to an old database
* COMMAND 3
  * The SQL interpreter
* EXIT 4
  * Quit the software
  
  ## **Use Scenario**
  
  - Launch the software ./SGBD
  - Create a database by chosing 2
  - Select a database with the 1 menu
  - And type all your commands in the SQL Interpreter 3
  - Type END to go back on the main menu
  - 4 exit the software
  
