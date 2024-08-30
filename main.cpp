#include <iostream>
#include "Item.h"
#include "ShoppingList.h"
#include "ShoppingListNotifier.h"

/*
 * Classi che rappresentano una lista della spesa (es. Listonic): un utente deve avere
 * diverse liste della spesa dove segnare oggetti da acquistare che appartengono a
 * diverse categorie ed eventualmente con quantità da acquistare.
 * Si usa Observer per aggiornare il numero di oggetti da acquistare in una lista e
 * quali questi siano. Si possono o avere più utenti che condividono la stessa lista
 */

/*

int main() {
    std::cout << "Hello, World!" << std::endl;

    Item item1("Apple", "Fruit", 4);
    Item item2 ("Cereals", "Breakfast", 2);
    Item item3 ("Pasta", "Meal", 0);


    ShoppingList list1 ("Grocery List");
    ShoppingListNotifier listNotifier(&list1);
    list1.addItem(item1);
    list1.addItem(item2);
    list1.addItem(item3);

    list1.removeItem("Cereals");
}

 */
