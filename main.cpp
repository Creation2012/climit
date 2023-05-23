#include <iostream>
#include <limits.h>

template<typename ...Args>
void print_errors(Args && ...args) {
    (std::cout << ... << args);
    std::cout << std::endl;
}

template<typename ...Args>
void print_num(Args && ...args) {
    (std::cout << ... << args);
}

class CNumSystem {
    private:
        unsigned long long number;
        int base;
        char* chars;

    public:
        CNumSystem(unsigned long long number, int base);
        void ns(); 
        void ns_r();
};

CNumSystem::CNumSystem(unsigned long long number, int base) {
    this->number = number;
    this->base = base;
    if(base >= 10) {
        int fill = base - 10;
        chars = new char[fill];
        for(char i='A'; i<'A'+fill; i++) {
            chars[i-65] = i;
        }
    }

}

void CNumSystem::ns_r() {
    if(this->number == 0) {
        return;
    }

    unsigned long long output = this->number % this->base;
    
    this->number /= this->base;
    ns_r();

    if(output >= 10) {
        char output2 = this->chars[output-10];
        print_num(output2);
    }
    else {
        print_num(output);
    }
}

void CNumSystem::ns() {
    do {
        unsigned long long output = this->number % this->base;
        this->number = this->number / this->base;
        if(output >= 10) {
            char output2 = this->chars[output-10];
            print_num(output2);
        }
        else {
            print_num(output);
        }
    } while(this->number);
}

int main(int argc, char **argv) {
    if(argc > 2) {
        int base = atoi(argv[2]);
        if(base > 36) {
            print_errors("Base out of range");
        }
        CNumSystem* sys = new CNumSystem(std::stoull(argv[1]), atoi(argv[2]));
        //CNumSystem* sys = new CNumSystem(ULLONG_MAX, atoi(argv[2]));
        //sys->ns();
        sys->ns_r();
        std::cout << std::endl;
        return 0; 
    }
    if(argc == 2) {
        print_errors("Only one argument passed");
        return 1;
    }
    else {
        print_errors("No arguments passed");
        return 2;
    }
}
