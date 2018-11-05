#ifndef _BIG_INT_
#define _BIG_INT_
#include "list_node.h"
#include <iostream>
#include <string>
#include <time.h>
extern bool modulo_switch;

list_node *addition(list_node *data1, list_node *data2, list_node *modulus);
pair<bool, list_node *> subtracion(list_node *data1, list_node *data2, list_node *modulus);
list_node *multiplication(list_node *data1, list_node *data2, list_node *modulus);
list_node *division(list_node *data1, list_node *data2, list_node *modulus);
list_node *power(list_node *data, list_node *power, list_node *modulus);

#endif
