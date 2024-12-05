# include <iostream>

int main() {
    int N, Mean, last_Mean;
    int Count_orig=0, Count_deriv = 0; 
    std::cin >> N;
    int sequen, last_seq; // характер монотонности для <<производной>>, где 0 - убывающаяя, а 1 - возрастающая
    int *differen = new int [N - 1]; // массив разности вещественных чисел
    
    std::cin >> last_Mean;

    for(int i = 0; i < N - 1; i += 1) {
        std::cin >> Mean;
        differen[i] = Mean - last_Mean;
        last_Mean = Mean;
    }
    for (int j = 0; j < N - 2; j += 1){
        if (differen[j + 1] > 0 && differen[j] < 0 || differen[j + 1] < 0 && differen[j] > 0) {
            Count_orig += 1;
        }
        if (j == 0 ){
            if (differen[j + 1] > differen[j]) {
                last_seq = 1;
            }
            else{
                last_seq = 0;
            }
        }
        else {
            if (differen[j + 1] > differen[j]) {
                sequen = 1;
            }
            else{
                sequen = 0;
            }
            if (sequen != last_seq){
                Count_deriv += 1;
                last_seq = sequen;
            }
        }   
    }
    std::cout << "\n";
    std::cout <<"Answer: " << Count_orig << " " << Count_deriv;

    return 0;
}