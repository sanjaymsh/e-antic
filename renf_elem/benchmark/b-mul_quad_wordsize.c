#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <e-antic/renf.h>
#include <e-antic/renf_elem.h>

int main(int argc, char* const argv[])
{
    int prec = 50;
    int n = 100;
    int opt;

    renf_t nf;
    renf_elem_t x, y, z;
    long i;
    fmpq_poly_t p;
    arb_t emb;

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

    printf("Running %d multiplication with arb precision %d\n", n, prec);

    /* x^2 - 2 */
    fmpq_poly_init(p);
    fmpq_poly_set_coeff_si(p, 2, 1);
    fmpq_poly_set_coeff_si(p, 0, -2);

    arb_init(emb);
    arb_set_d(emb, 1.4142135623730951);
    arb_add_error_2exp_si(emb, -20);

    renf_init(nf, p, emb, prec);

    renf_elem_init(x, nf);
    renf_elem_init(y, nf);
    renf_elem_init(z, nf);

    fmpq_poly_zero(p);
    fmpq_poly_set_coeff_si(p, 1, 13);
    fmpq_poly_set_coeff_si(p, 0, -2);
    renf_elem_set_fmpq_poly(x, p, nf);

    fmpq_poly_zero(p);
    fmpq_poly_set_coeff_si(p, 1, -534);
    fmpq_poly_set_coeff_si(p, 0, 120);
    renf_elem_set_fmpq_poly(y, p, nf);

    for (i = 0; i < n; i++) 
        renf_elem_mul(z, x, y, nf);

    fmpq_poly_clear(p);
    renf_elem_clear(x, nf);
    renf_elem_clear(y, nf);
    renf_elem_clear(z, nf);
    renf_clear(nf);

    exit(EXIT_SUCCESS);
}
