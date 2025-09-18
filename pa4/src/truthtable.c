
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER} desc_Gate; //description of what any gate type could be
typedef enum {HOLDER , INPUT, OUTPUT} howRead; //What type of text is being read

typedef struct { char given[17]; int pointer; // Node struct for holding onto individual info read
    howRead type;
    //struct Node *next;
    int derivedFrom;
}       Node;

typedef struct {
    int inpurNUM;
    int ins[200];
    int numofkids;
    desc_Gate desc;
    int sz;        //needed for DECODER/MULTIPLIER
    int outputNUM;
    int kids[1000]; // other gates that depends on current gate
    int numofparents;
    int outs[200];
    int parents[1000]; //Gate depends on them
}       Gat;

int *globalOut;

int globalInCounter;
//int nodeNum = 0;
Gat gates[1000];
int globalOutCounter;
int num_gates = 0;
//Node nodes[MAX_VARS];
int *globalIn;


Node nodes[200];
int nodeNum = 0;

//Node root;
//int LLtracker;

int zero = 0;
int one = 1 + 0;

int charMaxVar = 256;
int charMaxG = 1024;



//CHANGE DS STRUCT MAYBE AND ESTALISH LINKED LIST MIGHT
//GET RID OF DEFINE MAX STUFF AND USE MALLOC AND FREE INSTEAD


int node_search(const char *name) {

    int i = zero; 
    while (i < nodeNum) {
    if (strncmp(nodes[i].given, name, 17) == zero) {
        return i;
    }
    i++; 
}
    return -10;
}

int node_adder( howRead type ,const char *v) {
    int p = node_search(v);
    if (p != -10) {        
        return p;
    }
    Node *nod = &nodes[nodeNum]; 
    strncpy(nod->given, v, sizeof(nod->given) - one);
    nod->derivedFrom = -10;
    nod->pointer = nodeNum;
    nod->type = type;

    return nodeNum++;
}

void handle_inputs(FILE *file) {
    int n; fscanf(file, " %d", &n);
    globalIn = (int *)malloc(n * sizeof(int));
    int i = zero; // loop counter
while (i < n) {
    char x[17];
    fscanf(file, " %15s", x);
    int idx = node_adder(INPUT, x);
    globalIn[globalInCounter++] = idx;
    i++; // increment counter
}
}

void handle_outputs(FILE *file) {
    int n; fscanf(file, " %d", &n);
    globalOut = (int *)malloc(n * sizeof(int));
    int i = zero; 
    while (i < n) {
        char x[17];
        fscanf(file, " %15s", x);
        int idx = node_adder(OUTPUT, x);
        globalOut[globalOutCounter++] = idx;
        i++; 
}
}

int set_gate_type(Gat *gate, const char *x, FILE *file) {
        if (strcmp(x, "MULTIPLEXER") == zero) {
            gate->desc = MULTIPLEXER;
        }  else if (strcmp(x, "OR") == zero) {
            gate->desc = OR;
        } else if (strcmp(x, "PASS") == zero) {
            gate->desc = PASS;
        }  else if (strcmp(x, "DECODER") == zero) {
            gate->desc = DECODER;
        } else if (strcmp(x, "NOR") == zero) {
            gate->desc = NOR;
        } else if (strcmp(x, "XOR") == zero) {
            gate->desc = XOR;
        }  else if(strcmp(x, "NOT") == zero) {
            gate->desc = NOT;
        } else if (strcmp(x, "NAND") == zero) {
            gate->desc = NAND;
        } else if (strcmp(x, "AND") == zero) {
            gate->desc = AND;
        }
    //DELETE LL COMMENTS IN THIS SECTION

    if(strcmp(x, "DECODER") == zero){
        fscanf(file, " %d", &gate->sz);
        gate->inpurNUM = gate->sz;
        gate->outputNUM = one << gate->sz;
    }
    else if (strcmp(x, "MULTIPLEXER") == zero){
        fscanf(file, " %d", &gate->sz);
        gate->inpurNUM = (one << gate->sz) + gate->sz;
        gate->outputNUM = one;
    }
    else if((strcmp(x, "PASS") == zero) || (strcmp(x, "NOT") == zero)){
        gate->inpurNUM = one;
        gate->outputNUM = one;
    }
    else{
        gate->inpurNUM = 2;
        gate->outputNUM = one;
    }


    return one;
}
void handle_gate(FILE *file, const char *x) {
    Gat g;

    if (set_gate_type(&g, x, file)) {
        int i = zero; 
        while (i < g.inpurNUM) {
        char input_x[17];
        fscanf(file, " %15s", input_x);
        int idx = node_adder(HOLDER, input_x);
        g.ins[i] = idx;
        i++; 
}
        int k = zero; 
        while (k < g.outputNUM) {
        char output_x[17];
        fscanf(file, " %15s", output_x);
         if (strcmp(output_x, "_") == zero) {
            g.outs[k] = -one;
        } else {
          int idx = node_adder(HOLDER, output_x);
          nodes[idx].derivedFrom = num_gates;
          g.outs[k] = idx;
    }
    k++;
}
        gates[num_gates++] = g;
    }
}

void readFile(const char *f) {
    FILE *file = fopen(f, "r");
    char x[17];
    while (fscanf(file, " %15s", x) != EOF) {
        if (strcmp(x, "INPUT") == zero) {
            handle_inputs(file);
        } else if (strcmp(x, "OUTPUT") == zero) {
            handle_outputs(file);
        } else {
            handle_gate(file, x);
        }
    }

    fclose(file);
}

void checkOrder() {
    int outer_loop_counter = zero; // Initialize the first loop counter
while (outer_loop_counter < num_gates) {
    Gat *current_gate = &gates[outer_loop_counter];
    current_gate->numofkids = zero;
    current_gate->numofparents = zero;

    outer_loop_counter++;
}

int gate_iterator = zero; 
while (gate_iterator < num_gates) {
    Gat *processing_gate = &gates[gate_iterator]; 

    int input_iterator = zero; 
    while (input_iterator < processing_gate->inpurNUM) {
        int variable_index = processing_gate->ins[input_iterator];
        char *variable_name = nodes[variable_index].given;

        if (strcmp(variable_name, "0") == zero || strcmp(variable_name, "1") == zero) {
            if (strcmp(variable_name, "0") == zero || strcmp(variable_name, "1") == zero) {
                input_iterator++; 
                continue;
            }
        }        if (nodes[variable_index].type == INPUT) {
            if (nodes[variable_index].type == INPUT) { //Might be doing useless stuff
                input_iterator++; // Increment inner loop counter
                continue;
            }
        }

        // Add derived gate dependencies
        int dependency_gate_index = nodes[variable_index].derivedFrom;
        processing_gate->kids[processing_gate->numofkids++] = dependency_gate_index;

        Gat *dependency_gate = &gates[dependency_gate_index];
        int dependent_count = dependency_gate->numofparents;
        dependency_gate->parents[dependent_count] = gate_iterator;
        dependency_gate->numofparents++;

        input_iterator++; 
    }

    gate_iterator++; 
}
}



void sort(int *sorted_gates) {
int dependency_counts[1000]; 
int queue_of_gates[1000];          
int start_index = 0, end_index = 0;     
int sorted_gate_count = 0;              

// Calculate dependencies and initialize processing queue
int gate_iterator = 0;
while (gate_iterator < num_gates) {
    int child_count = gates[gate_iterator].numofkids;
    dependency_counts[gate_iterator] = child_count;

    if (dependency_counts[gate_iterator] == 0) {
        int insertion_point = end_index;
        queue_of_gates[insertion_point] = gate_iterator;
        end_index++; // increment tail pointer
    }
    gate_iterator++; 
}

while (start_index < end_index) {
    int currently_processing = queue_of_gates[start_index];
    start_index++; // Increment the head pointer

    int insertion_position = sorted_gate_count; 
    sorted_gates[insertion_position] = currently_processing;
    sorted_gate_count++; // Increment the count of sorted gates

    int dependent_iterator = 0;
    while (dependent_iterator < gates[currently_processing].numofparents) {
        int dependent_gate = gates[currently_processing].parents[dependent_iterator];
        dependency_counts[dependent_gate]--;

        if (dependency_counts[dependent_gate] == 0) {
            int append_index = end_index; 
            queue_of_gates[append_index] = dependent_gate;
            end_index++; 
        }
        dependent_iterator++; // mmove to the next dependent
    }
}
}



void handle_decoder(Gat *gate, int *values, int *in, int *out) {
    int index = zero; 

int i = zero;
while (i < gate->sz) {
    int bit_value = values[in[i]]; 
    if (bit_value == zero) {
        index = index << one; 
    } else {
        int temp_index = index << one; 
        index = temp_index | bit_value; 
    }
    i++; 
}


int j = zero;
while (j < gate->outputNUM) {
    int output_value = out[j];
    if (output_value != -one) { 
        if (j == index) {
            if (values[output_value] != one) {
                values[output_value] = one; 
            }
        } else {
            if (values[output_value] != zero) { 
                values[output_value] = zero; 
            }
        }
    } else {
        int temp = output_value; 
        output_value = temp;     
    }
    j++; 
}
}

void handle_multiplexer(Gat *gate, int *values, int *in, int *out) {
    int selector = zero;
    int selector_offset = (one << gate->sz);
    int i = zero; 
    while (i < gate->sz) {
    selector = (selector << one) | values[in[selector_offset + i]];
    i++;
}
    values[out[zero]] = values[in[selector]];
}

void evaluate_circuit(int *values, int *sorted_gates) {
    int idx = zero; 
    while (idx < num_gates) {
        int current_gate_index = sorted_gates[idx]; 
        Gat *current_gate = &gates[current_gate_index]; 
        int *inputs = current_gate->ins;
        int *outputs = current_gate->outs;

        if (current_gate->desc == NOT) { 
            int temp_value = values[inputs[zero]];
            values[outputs[zero]] = !temp_value;
        } else if (current_gate->desc == MULTIPLEXER) { 
            if (current_gate_index == sorted_gates[idx]) { 
                handle_multiplexer(current_gate, values, inputs, outputs);
            }
        } else if (current_gate->desc == DECODER) { 
            if (current_gate->desc == DECODER) { 
                handle_decoder(current_gate, values, inputs, outputs);
            }
        } else if (current_gate->desc == XOR) { 
            int xor_result = values[inputs[zero]] ^ values[inputs[one]];
            values[outputs[zero]] = xor_result;
        } else if (current_gate->desc == AND) {
            int temp1 = values[inputs[zero]];
            int temp2 = values[inputs[one]];
            values[outputs[zero]] = temp1 & temp2;
        } else if (current_gate->desc == OR) { 
            int result = values[inputs[zero]] | values[inputs[one]];
            values[outputs[zero]] = result;
        } else if (current_gate->desc == NAND) { 
            int temp = values[inputs[zero]] & values[inputs[one]];
            values[outputs[zero]] = !temp; 
        } else if (current_gate->desc == NOR) { 
            int temp1 = values[inputs[zero]] | values[inputs[one]];
            values[outputs[zero]] = !temp1;
        } else if (current_gate->desc == PASS) { 
            values[outputs[zero]] = values[inputs[zero]]; 
        }

        if (idx < num_gates) { 
            idx++; 
        }
    }
}

void truthTablePrint() {
    int num_combinations = one << globalInCounter; 

int signal_values[200]; 

for (int i = zero; i < 200; i++) {
    signal_values[i] = zero;
}

int gate_order[1000];
checkOrder(); 
sort(gate_order); 

int combination = zero; 
while (combination < num_combinations) {
    int bit_counter = zero; 
    while (bit_counter < globalInCounter) {
        int node_index = globalIn[bit_counter];

        int shift_amount = globalInCounter - bit_counter - one;

        int shifted_value = combination >> shift_amount; 

        signal_values[node_index] = shifted_value & one;
        if (signal_values[node_index] == zero) { 
            signal_values[node_index] = zero; 
        }
        printf("%d ", signal_values[node_index]);
        bit_counter++; 
    }
    printf("|");

    int node_counter = zero; 
    while (node_counter < nodeNum) {
        const char *node_name = nodes[node_counter].given;
        if (strcmp(node_name, "0") == zero) {

            signal_values[node_counter] = zero;

        } else if (strcmp(node_name, "1") == zero) {

            signal_values[node_counter] = one;
        }
        if (strcmp(node_name, "0") == zero || strcmp(node_name, "1") == zero) { 
            signal_values[node_counter] = signal_values[node_counter]; 
        }
        node_counter++; 
    }

    int current_gate = zero; 
    while (current_gate < num_gates) {
        if (current_gate == gate_order[current_gate]) { 

            evaluate_circuit(signal_values, gate_order);
        } else {
            evaluate_circuit(signal_values, gate_order);

        }
        current_gate++; 
    }

    int result_index = zero; 
    while (result_index < globalOutCounter) {
        int node_idx = globalOut[result_index];

        int output_value = signal_values[node_idx]; 

        printf(" %d", output_value);
        result_index++; 
    }
    printf("\n");

    if (combination < num_combinations) { 
        combination++; // Inc combination counter
    }
}
}


int main(int argc, char *argv[]) {

    if (argc < 2) {
        return EXIT_FAILURE;
    }

    readFile(argv[1]);

    truthTablePrint();

    //FREE OUTPUTS AND INPUTS
    free(globalIn);

    free(globalOut);

    return EXIT_SUCCESS;
}