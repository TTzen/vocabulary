#include <iostream>
#include <stdio.h>
#include "vocabulary.h"

using namespace std;

int main()
{
    vocabulary::get_instance()->work();
    return 0;
}
