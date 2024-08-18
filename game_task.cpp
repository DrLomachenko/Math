#include <iostream>
#include <vector>
#include <string>
const int size = 40000000;
int razm = 25;
std::vector<bool> dp;
std::vector<bool> known;
bool win(int x);
int find_lose(int x, bool flag) {
    int start = 1;
    int an = 0;
    flag = false;
    for (int i = 0; i < razm; i++) {
        if ((x & start) == 0) {

            an = x + start; 
            if (flag) {
                std::cout << "an: " << an << std::endl;
            }
            if (!win(x + start)) {
                return x + start;
            }
        }
        
        if (i < razm - 1 and (x & start) == 0 and (x & (start * 2)) != 0) {
            an = x - start;
            if (flag) {
                std::cout << "an: " << an << std::endl;
            }
            if (!win(x - start)) {
                return x - start;
            }
        }
        start *= 2;
    }
    if (flag) {
                std::cout << "an: " << an << std::endl;
    }
    return -1 * an;

}
bool win(int x) {
    if (known[x]) {
        return dp[x];
    }
    int res = find_lose(x, false);
    known[x] = true;
    dp[x] = (res > 0);
    return dp[x];


}
void print(int x) {
    int base = 1;
    for (int i = 0; i < razm - 1; i++) {
        base *= 2;
    }
    for (int i = 0; i < razm; i++) 
    {
        int place = 0;
        if ((x & base) != 0) {
            place = 1;
        }
        base = base/2;
        std::cout << razm - 1 - i << ": " << place << " ";
    }
    std::cout << std::endl;
}
int main(){
    for (int i = 0; i < size; i++) 
    {
        known.push_back(false);
        dp.push_back(false);
    }    
    int base = 0;
    int start = 1;
    for (int i = 0; i < razm; i++) {
        base += start;
        start *= 2;
    }

    known[base] = true;
    dp[base] = false;
    int pole = 0;
    std::cout << "Choose your player 1/2 (write number):";
    int player;
    std::cin >> player;
    std::cout << "\nLet's start, write step bit (from right) [1:24] to shift or put bit (from right) [0:24] to put\n";
    std::cout << "Example: 0000000000000000000000010 step 1 -> 0000000000000000000000001" << std::endl;
    bool hod = (player == 2);
    
    if (!hod) {
        print(pole);
    }
    while (pole != base) {
        if (hod) {
            pole = find_lose(pole, true);
            if (pole < 0) {
                pole *= -1;
            }

            print(pole);
            hod = !hod;
        } else {
            std::cout << "Now you: " << std::endl;
            std::string command;
            int pos;
            std::cin >> command >> pos;
            int w = 1;
            pos = std::abs(pos);
            for (int i = 0; i < std::min(pos, razm - 1); i++) {
                w *= 2;
            }
            if (command == "step") {
                if (w != 1 and (pole & w) != 0 and (pole & (w/2)) == 0) {
                    pole -= w/2;
                    hod = !hod;
                    continue;
                } 
                else {
                    std::cout << "Error, you cannot" << std::endl;
                }
            }
            if (command == "put") {
                if ((pole & w) == 0) {
                    pole += w;
                    hod = !hod;
                    continue;
                } 
                else {
                    std::cout << "Error, you cannot" << std::endl;
                }
            }
            std::cout << "Error, you cannot" << std::endl;
            continue;
        }

    }
    if (hod) {
        std::cout << "Okey, you won" << std::endl;
    } else {
        std::cout << "Ahahhahahahhahahahahah, you have been cocnut by Raigorodskiy" << std::endl;
    }
    int a;
    std::cin >> a;

}
