#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 

// определение длины динамической строки
int length(char *string);
// возведение в положительную степень
int powi(int number, int power);
// проверяет является ли число строкой
char verification(char *word);
// получение числа из строки
int get_number(char *char_number);
// получение динамической строки
char *get_string();
// сравнение двух строк
char compare(char *string1, char *string2);
// динамической массив чисел
int *get_array(int *len);
// определяет какой массив выбрал пользователь
int chose_array(char *first_array_name, char *second_array_name);
// линейный поиск по массиву
int search(int *array, int *len, int element);
// вывод элементов массива
void show(int *array, int len);
// добавление элемента в масив
void push(int *array, int *len);
// удаление элемента из масива
void remove_element(int *array, int *len);

int main() { 
    int cont = 1, result;
    int arrays_used = 0, array_chosen;
    int *first_array = NULL, *second_array = NULL;
    char *first_array_name = NULL, *second_array_name = NULL;
    char *input = NULL;
    int len1 = 0, len2 = 0;
    // названия команд
    char create_name[] = "create"; 
    char push_name[] = "push";
    char remove_name[] = "remove";
    char show_name[] = "show";
    char end_name[] = "end";
    printf("Here you can create and use two arrays.\nUse \"create/push/remove/show\" to manipulate with arrays. Use \"end\" to end the program\n");

    // основной цикл действия программы
    while(cont) {
        input = get_string();
        result = -1;
        // сравнение входных данных
        if (compare(create_name, input)) 
            result = 1;
        else if (compare(push_name, input))
            result = 2;
        else if (compare(remove_name, input))
            result = 3;
        else if (compare(show_name, input))
            result = 4;
        else if (compare(end_name, input))
            result = 5;
        
        // выполнение команд на основе входных данных
        switch (result) {
        // задание массивов
        case 1: 
            if ((first_array_name != NULL) && (second_array_name == NULL)) 
                arrays_used = 1;
            else if ((first_array_name != NULL) && (second_array_name != NULL))
                arrays_used = 2;
            switch (arrays_used){
                case 0: 
                    printf("Type a name for the first array\n");
                    first_array_name = get_string();
                    first_array = get_array(&len1);
                    break;
                case 1:
                    printf("Type a name for the second array\n");
                    second_array_name = get_string();
                    second_array = get_array(&len2);
                    break;
                case 2: 
                    printf("There are already two arrays taken\n");
                    break;
            }

            free(input);
            printf("---------------------\n");
            break;
        // добавление элемента в массив
        case 2:
            array_chosen = chose_array(first_array_name, second_array_name);            
            if (array_chosen == 1) 
                push(first_array, &len1);
            else if (array_chosen == 2) 
                push(second_array, &len2);

            free(input);
            printf("---------------------\n");
            break;
        // удаление элемента из масива
        case 3:
            array_chosen = chose_array(first_array_name, second_array_name);            
            if (array_chosen == 1) 
                remove_element(first_array, &len1);
            else if (array_chosen == 2) 
                remove_element(second_array, &len2);

            free(input);
            printf("---------------------\n");
            break;
        // показ элементов масива
        case 4:
            array_chosen = chose_array(first_array_name, second_array_name);
            if (array_chosen == 1) 
                show(first_array, len1);
            else if (array_chosen == 2) 
                show(second_array, len2);  
            
            free(input);
            printf("---------------------\n");
            break;
        // выключение программы
        case 5:
            cont = 0;
            free(input);
            break;
        default:
            printf("This is not a command\n");
            free(input);
            printf("---------------------\n");
        }
    }

    free(first_array);
    free(second_array);
    free(first_array_name);
    free(second_array_name);
    printf("Quitting...\n");
    return 0;
}

int length(char *string) { 
    int i = 0;
    while (string[i]!='\0')
        i++;
    return i;
}

int powi(int number, int power) {
    int result = 1;
    for(int i = 0; i < power; i++)
        result *= number;
    return result;
}

char verification(char *word) {
    char number = 1;

    for (int i = 0; i < length(word); i++)
        if (!(isdigit(word[i])))
            return '\0';
    if (word[0] == '\0')
        return '\0';

    return 1;
}

int get_number(char *char_number) { 
    int number = 0;
    int index = 0;

    for (int i = length(char_number) - 1; i >= 0; i--) {
        number = number + (powi(10, i) * (char_number[index] - '0'));
        index++; 
    }

    return number;
}

char *get_string() { 
    int len = 0;
    char *string = (char*) malloc(sizeof(char));
    char c = getchar();

    while ((c != '\n') && (c != EOF)) { 
        string[len++] = c; 
        string = (char*) realloc(string, (len+1) * sizeof(char)); 
        c = getchar();
    }
    string[len] = '\0'; 

    return string;
}

char compare(char *string1, char *string2) {
    char result = 1;
    int i = 0;

    if ((string1 == NULL) || (string2 == NULL)) {
        result = '\0';
        return result;
    }
    do {
        if (string1[i] != string2[i]) {
            result = '\0';
            return result;
        }
        i++;
    } while (string1[i] != '\0');
    
    return result;
}

int *get_array(int *len) { 
    int *array = (int*) malloc(sizeof(int));
    printf("Enter a number (click enter to close the array)\n");
    char *number = get_string();

    while (verification(number)) { 
        array = (int*) realloc(array, ((*len)+1) * sizeof(int));
        array[(*len)++] = get_number(number); 
        free(number);
        number = get_string();
    }

    free(number);
    printf("Array closed\n");
    return array;
}

int chose_array(char *first_array_name, char *second_array_name) {
    printf("Type a name of the array\n");
    char *name = get_string();
    if (compare(first_array_name, name))
        return 1;
    else if (compare(second_array_name, name))
        return 2;
    else 
        printf("There is no such array\n");
        return 0;
}

int search(int *array, int *len, int element) {
    for (int index = 0; index < (*len); index++) 
        if (array[index] == element)
            return index;

    printf("There is no such element in the array\n");
    return -1;
} 

void show(int *array, int len) { 
    for (int i = 0; i < len; i++)
        printf("%d - %d\n", (i+1), array[i]);
        
    if (len == 0) 
        printf("There is no elements in the array\n");
}

void push(int *array, int *len) {
    printf("Enter an element you want to add\n");
    char *number = get_string();
    if (verification(number)) { 
        array = (int*) realloc(array, ((*len)+1) * sizeof(int));
        array[(*len)++] = get_number(number); 
    } else 
        printf("It's not a number!!\n");

    free(number);
}

void remove_element(int *array, int *len) {
    int index;
    printf("Enter an element you want to remove\n");
    char *number = get_string();
    if (verification(number)) {
        index = search(array, len, get_number(number));
        if (index != -1) {
            for (int i = index; i < (*len) - 1; i++)
                array[i] = array[i+1];
            (*len)--;
            array = (int*) realloc(array, (*len) * sizeof(int));
            printf("Element removed\n");
        }
    } else 
        printf("It's not a number!!\n");

    free(number);
}