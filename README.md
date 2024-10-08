# OOP-Project_Italian-Restaurant

The project is based on the following functionalities:
1.customers have the opportunity to consult a menu that contains all the dishes they can order;
2.each preparation has a recipe consisting of the raw materials and the quantities required for the preparation;
3.a customer can add several products from the menu to an order;
4.the program checks the availability of raw materials and launches the orders in the system or not. 
5.the entire flow is managed based on console commands defined in a legend;
The project has been realized in Visual Studio 2022.

# The first part of the project (Restaurant_Italian.cpp)

Five classes are defined in which you can find dynamic, static, constant fields, get/set functions with validations, each class contains processing methods, constructors, destructors, copy operators, index, >>,<<, ++, - -, cast etc.

All data (preparations, stock, etc.) are declared manually. The "Client" can access the following commands:
1. to see the menu;
2. to see the recipe for each recipe;
3. to place an order (with one or more dishes, and at the end the total price will be displayed)
note: if there is not enough stock for a certain order, this will be specified;
4. to see the vegan products;
5. to see the most expensive/cheapest product;
6. to choose extra toppings for the chosen dish (follows a series of steps through which the customer must choose the topping for a specific dish) ;
7. to see the calories for each dish;

# Observations:
1. the customer will have to enter from the keyboard the exact "description" of the order and the dishes he wants;
2. if an order is not written correctly, a message will be displayed and the customer will be asked to rewrite;

![Captură de ecran 2024-10-08 223521](https://github.com/user-attachments/assets/4129ef73-a354-48a3-afde-f8f3409d684d)
![Captură de ecran 2024-10-08 223404](https://github.com/user-attachments/assets/880ecf0e-cee3-406d-858d-073994498549)
![Captură de ecran 2024-10-08 223308](https://github.com/user-attachments/assets/fc5c8188-0cd0-40e4-a922-fb6aac8dff9d)


# The second part of the project (FAZA_2.cpp)

The commands do not change, but the way I can access the data is different:
1. a module is implemented through which the application receives input files (text type) through the arguments of the main function. The files are used to store the initial stock from the kitchen as well as the restaurant's menu along with its dishes;
2. If the application does not receive arguments through the main function, then it will access binary files located at locations known to the programmer;
3. the module is implemented through which the user has the possibility to generate different reports for all the data (examples for the report of the raw material used, report with the orders placed, report with the total amounts);
4. the application allows uploading data from CSV files (the user will choose whether to upload data from CSV or binary files);
5. data-mining reports that show us which was the most used order
6. from the STL library you can find set, map, list, vector;

# Observations:
1. if the user will not enter any text file as arguments, he will have to choose whether to use data from CSV or binary files;
2. if all the necessary text files are not entered in the command line, a message will be displayed;
"meniu.txt" "restaurant_italian.txt" "retetar.txt" "materiiPrime.txt" "preparate.txt"

![Captură de ecran 2024-10-08 224712](https://github.com/user-attachments/assets/46f2349a-b7d8-4b9a-86ca-2e876f01d7cc)
![Captură de ecran 2024-10-08 223723](https://github.com/user-attachments/assets/f05497a7-104c-45f4-b48f-fa2663de9b79)

