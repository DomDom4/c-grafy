#include "error.h"

#include <stdio.h>

void instructionMsg( char* progName ) {
    printf( "Usage:\n%s -f from_node -t to_node [-i input_file][[-x width][-y length][-a bottom_range][-b upper_range][-n nb_of_graphs] -o output_file] \n\t from_node - where the path begins\n\t to_node - where the path ends\n\t nb_of_graphs - how many graphs should the graph be divided to", progName );
}
