#include <iostream>
#include <e-antic/renfxx.h>

int main(int argc, char* const argv[])
{
    int prec = 50;
    int n = 100;
    int opt;

    while((opt = getopt(argc, argv, ":p:n:")) != -1)
    {
        switch(opt)
        {
            case 'p':
                prec = atoi(optarg);
                if (prec <= 0)
                {
                    fprintf(stderr, "prec must be positive\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'n':
                n = atoi(optarg);
                if (n <= 0)
                {
                    fprintf(stderr, "n must be positive\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case ':':
                fprintf(stderr, "argument required for %c\n", optopt);
                exit(EXIT_FAILURE);
            case '?':
                fprintf(stderr, "unknown option %c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }

    std::cout << "Running " << n << " multiplication with arb precision " << prec << std::endl;

    auto K = eantic::renf_class::make("a^2 - 2", "a", "1.4142+/-0.0001", prec);
    eantic::renf_elem_class a(K, "13*a - 2");
    eantic::renf_elem_class b(K, "-534*a + 120");
    eantic::renf_elem_class c(K);

    for (int i = 0; i < n; i++)
        c = a * b;
}
