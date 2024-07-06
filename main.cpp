#include <iostream>
#include "Item.h"
#include "ShoppingList.h"

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
    Item item1("Bread", "carboidrati", 4);
    Item item2 ("yogurt", "colazione", 2);
    std::cout << item1.getQuantity() << std::endl;
    ShoppingList list1 ("Grocery List");
    list1.addItem(item1);
    list1.addItem(item2);
    list1.printDetails();

}
*/