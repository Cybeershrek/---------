#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int Sum(int Arr[], int len) {
    int Sum = 0;
    for (int i = 1; i < len; i++){
        if (Arr[i] == 1) {
            Sum += (int)pow(2, i-1);
        }
    }
    return Sum;
}

int SumElem(int i, int Arr[], int k, int len) {

    int Res = 0;
    if (i == 0) {
        while (i < len) {
            Res += Arr[i];
            i ++;
        }
        Res = Res % 2;
        return Res;
    }
    while  (i < len){
        int Pass = 0;
        while (Pass < (int)pow(2, k)) {
            Res += Arr[i];
            i ++;
            Pass ++;
            if (i >= len){
                break;
            }
        }
        i += (int)pow(2, k);
    }
    Res = Res % 2;
    return Res;
}

void Conclusion(int Arr[], int len){
    for (int l = 0; l < len; l++){
        printf("%d ", Arr[l]);
    }
    printf("\n");
}

int main() {
    int i, Len;
    char m[64];
    int Count_El = 0;
    int  Count_bits = 1; // нужное количество контрольных битов
    printf("Please enter sequence of 0 or 1 \n");
    printf("\n");
    scanf("%s", m);
    int Contains = 0;
    Count_El = strlen(m);

    for (int a = 0; a <= 6; a++) { // узнать количество контрольных битов
        if (pow(2, a) < Count_El + Count_bits) {
            Count_bits ++;
        }
    }
    int *Control_Bit; // массив контрольных битов
    Control_Bit = (int*)malloc((unsigned int)Count_bits * sizeof(int));
    for (int b  = 0; b <Count_bits; b ++){
        Control_Bit[b] = 0;
    }

    int *CodMess; // Массив сй результатом кодирования по хеммингу
    CodMess = (int*)malloc((unsigned int)(Count_bits + Count_El) * sizeof(int));
    Len = Count_bits + Count_El;
    CodMess[0] = 0;
    CodMess[1] = 0;
    CodMess[2] = 0;


    int s = 0;

    for (i = 3; i < Len; i ++) { // Заполнение массива
        int Tr_Fa = 0;
        for (int Deg = 0; Deg <= 6; Deg ++){
            if (i == pow(2, Deg)){
                Tr_Fa = 1;
                CodMess[i] = 0;
                break;
            }
        }
        if (Tr_Fa == 1) {
            continue;
        }   
        int A = m[s];
        A -= 48;
        if (A > 1 || A < 0) {
            Contains = 1;
            break;
        }
        CodMess[i] = A;
        s++;
    }

    if (Count_El > 64 || Contains == 1) { // проверка на некорректность ввода
        printf("please enter a sequence of no more than 64 characters consisting of 0 and 1");
        return 0;
    }
    
    for (int Koef1 = 0; Koef1 < 6; Koef1 ++){ // Исполнение Кода Хэмминга
        int j = (int)pow(2, Koef1);
        if (j >= Len){
            break;
        }
        CodMess[j] = SumElem(j, CodMess, Koef1, Len);

    }   

    CodMess[0] = SumElem(0, CodMess, 0, Len);

    Conclusion(CodMess, Len); // Выведение кода Хэмминга

    Conclusion(Control_Bit, Count_bits); // Выведение контроля битов

    int Ran = (rand() % Count_El) + 3; // Строка с инвертированным случайным битом
    for (int e = 1; e < 7; e++){
        if (Ran < pow(2, e) || Ran == Len){
            Ran --;
            break;
        }
        
    }
    if (CodMess[Ran] == 0){
        CodMess[Ran] = 1;
    } else {
        CodMess[Ran] = 0;
    }
    Conclusion(CodMess, Len); // Выведение искажённого сообщения

    for (int Koef2 = 0; Koef2 < Count_bits; Koef2++){   // изменённый контроль битов
        int j = (int)pow(2, Koef2);
        if (j >= Count_bits){
            break;
        }
        Control_Bit[Koef2 + 1] = SumElem(j, CodMess, Koef2, Len);
    }

    Control_Bit[0] = SumElem(0, CodMess, 0, Len);

    Conclusion(Control_Bit, Count_bits); // Выведение изменённого контроля битов

    int err = -1; // Вычисление место ошибки или указание, что ошибки 2
    if (Control_Bit[0] == 0 && Sum(Control_Bit, Count_bits) >= 1) {
        printf("2 errors");
        free(CodMess);
        free(Control_Bit);
        return 0;
    } 
    if (Control_Bit[0] == 1) {
        err = Sum(Control_Bit, Count_bits);
    } 
    if (err >= 0 && err < Len) {
        if (CodMess[err] == 0){ // исправление ошибки и выведение исправленого сообщения
            CodMess[err] = 1;
        } else {
            CodMess[err] = 0;
        }
    }
    Conclusion(CodMess, Len);
    
    free(CodMess);
    free(Control_Bit);
    return 0;
}